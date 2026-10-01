using System.Diagnostics;
using System.Text.Json;
using System.Text.Json.Nodes;

namespace TreeLevel.MC;

/// <summary>Runs one job. The physics — the cards of every generator, the machine, the assembly of two draws —
/// lives in the C++ engine (Backends/engine), written once for Windows, the Mac and the Linux image. What stays
/// here is Windows's own business: telling treelevel-engine.exe how to launch the Pythia module (launch.json),
/// or handing the whole job to the Docker image.
///
/// Two ways, and the user picks one in TreeLevel's settings. By default Pythia and the passthrough run natively
/// and the generators that have no Windows build — Herwig, Sherpa, WHIZARD, CalcHEP — run in the image. With
/// « everything in the Docker image » (<c>--docker</c>) every job goes to the image, and nothing falls back to
/// the native module when Docker is missing: the image does not carry the same builds, and a fallback that
/// changes the physics without saying so is a trap.</summary>
public sealed class Runner
{
    readonly MCJobFolder folder;
    readonly MCJob job;
    readonly int number;
    readonly bool dockerOnly;

    public Runner(MCJobFolder folder, MCJob job, int number, bool dockerOnly)
    {
        this.folder = folder; this.job = job; this.number = number;
        this.dockerOnly = dockerOnly;
    }

    void Publish(MCStatus status)
    {
        try { folder.WriteStatus(status); } catch (Exception) { }
    }

    public bool Run()
    {
        var start = DateTimeOffset.Now;
        Publish(new MCStatus(MCStatus.State.Running, job.Id) { Number = number, Started = start, Message = "préparation" });
        try
        {
            if (dockerOnly)
            {
                if (Installation.Container() is not { } container)
                    return Failed("TreeLevel is set to run everything in the Docker image, but Docker or the image "
                                + $"({Installation.Image()}) cannot be found", start);
                return InContainer(container, start);
            }
            if (job.UseGenerator is MCJob.Generator.Passthrough or MCJob.Generator.Pythia8) return Native(start);
            if (Installation.Container() is { } image) return InContainer(image, start);
            return Failed(Installation.Docker == null
                ? $"{MCJob.Label(job.UseGenerator)} has no Windows build: it runs in the TreeLevel Tools Docker image, "
                  + "and Docker is not running"
                : $"{MCJob.Label(job.UseGenerator)} has no Windows build: it runs in the TreeLevel Tools Docker image "
                  + $"({Installation.Image()}), which is not on this machine", start);
        }
        catch (Exception e) { return Failed(e.Message, start); }
    }

    // The native engine

    /// <summary>Writes launch.json — the Pythia module, its data, its version — and runs the C++ engine on the
    /// folder. The engine writes status.json itself as it goes.</summary>
    bool Native(DateTimeOffset start)
    {
        if (Installation.NativeEngine is not string engine)
            return Failed("this installation is incomplete: treelevel-engine.exe is missing — reinstall TreeLevel Tools", start);
        var launch = new JsonObject();
        if (job.UseGenerator == MCJob.Generator.Pythia8)
        {
            if (Installation.PythiaDriver is not string driver)
                return Failed("the Pythia 8 module is not installed", start);
            if (!Installation.DriverWritesCards(driver))
                return Failed("the Pythia 8 module is older than this engine and cannot write its own card — "
                            + "reinstall TreeLevel Tools", start);
            var environment = new JsonObject();
            if (Installation.PythiaData is string data) environment["PYTHIA8DATA"] = data;
            launch["pythia8"] = new JsonObject
            {
                ["program"] = driver,
                ["environment"] = environment,
                ["version"] = Installation.PythiaVersion(driver) ?? "Pythia 8",
            };
        }
        var launchPath = Path.Combine(folder.Path, "launch.json");
        try { File.WriteAllText(launchPath, launch.ToJsonString(new JsonSerializerOptions { WriteIndented = true }), MCEngineProtocol.Utf8); }
        catch (Exception e) { return Failed("cannot write launch.json: " + e.Message, start); }

        var (code, said) = Follow(engine, new[] { "run", folder.Path, "--launch", launchPath, "--number", number.ToString() });
        var status = folder.ReadStatus();
        if (status is null || status.JobState is MCStatus.State.Running or MCStatus.State.Queued)
            return Failed($"the engine stopped with code {code}" + (FirstLine(said) is string reason ? " — " + reason : ""), start);
        return status.JobState == MCStatus.State.Finished;
    }

    /// <summary>Runs a program to its end, its output drained — its real log is the one it writes in the folder,
    /// but a full pipe would block it.</summary>
    (int Code, string Output) Follow(string exe, IEnumerable<string> arguments)
    {
        var info = new ProcessStartInfo(exe)
        {
            WorkingDirectory = folder.Path,
            RedirectStandardOutput = true, RedirectStandardError = true,
            StandardOutputEncoding = MCEngineProtocol.Utf8, StandardErrorEncoding = MCEngineProtocol.Utf8,
            UseShellExecute = false, CreateNoWindow = true,
        };
        foreach (var a in arguments) info.ArgumentList.Add(a);
        using var process = Process.Start(info) ?? throw new InvalidOperationException($"cannot start {Path.GetFileName(exe)}");
        var output = process.StandardOutput.ReadToEndAsync();
        string errors = process.StandardError.ReadToEnd();
        process.WaitForExit();
        return (process.ExitCode, errors + output.Result);
    }

    static string? FirstLine(string text)
        => text.Split('\n').Select(l => l.Trim()).FirstOrDefault(l => l.Length > 0);

    // The image

    /// <summary>The same job, run by the engine inside the image. The folder is mounted as it is: the mount is
    /// the protocol, and the container writes status.json, engine.log and the events itself.</summary>
    bool InContainer((string Docker, string Image) container, DateTimeOffset start)
    {
        Publish(new MCStatus(MCStatus.State.Running, job.Id)
        {
            Number = number, Started = start, Message = "conteneur", GeneratorVersion = MCJob.Label(job.UseGenerator),
        });
        // Docker takes the Windows path of the mount, but only with forward slashes.
        var mount = folder.Path.Replace('\\', '/') + ":/job";
        var (code, said) = Follow(container.Docker, new[] { "run", "--rm", "-v", mount, container.Image, "run", "/job" });

        var status = folder.ReadStatus();
        if (code == 0 && status?.JobState == MCStatus.State.Finished)
        {
            // The engine of the image does not know it ran in one. Said here, so that a job found again months
            // later tells which way it went, and nobody has to guess by comparing cross sections.
            if (!(status.GeneratorVersion ?? "").Contains("Docker", StringComparison.Ordinal))
            {
                status.GeneratorVersion = (status.GeneratorVersion ?? MCJob.Label(job.UseGenerator)) + " (Docker)";
                Publish(status);
            }
            return true;
        }
        if (status?.JobState == MCStatus.State.Failed && !string.IsNullOrEmpty(status.Message))
            return Failed(status.Message, start);
        return Failed($"the container stopped with code {code}" + (FirstLine(said) is string reason ? " — " + reason : ""), start);
    }

    bool Failed(string message, DateTimeOffset start)
    {
        Publish(new MCStatus(MCStatus.State.Failed, job.Id)
        {
            Number = number, Started = start, Finished = DateTimeOffset.Now, Message = message,
            Seconds = (DateTimeOffset.Now - start).TotalSeconds,
        });
        Console.Error.WriteLine("treelevel-tools: " + message);
        return false;
    }
}
