using System.Text.Json;
using TreeLevel.MC;

// TreeLevel Tools (Windows) — runs a parton shower and hadronisation on the parton-level events of a TreeLevel
// job, or a generator on the process it describes. The same protocol and the same commands as the macOS engine.
//
//   treelevel-tools run <job folder> [--docker]            read job.json, produce events.hepmc, keep status.json current
//   treelevel-tools capabilities [--out file] [--docker]   what this installation can do, as JSON
//   treelevel-tools serve <folder> [--every s] [--docker]  stay up, run every job folder that turns up inside it
//   treelevel-tools version
//
// This program is the host: it finds Docker and the image, writes launch.json, and runs either the C++ engine
// beside it (treelevel-engine.exe, for Pythia and the passthrough) or the image. --docker is TreeLevel's setting
// « everything in the Docker image ». Nothing here links against a generator.
//
// Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later.

// La version vient du projet, et de nulle part ailleurs : un numéro écrit deux fois finit par différer.
var assemblee = typeof(Installation).Assembly.GetName().Version;
string EngineVersion = assemblee is null ? "0" : $"{assemblee.Major}.{assemblee.Minor}.{assemblee.Build}";

Console.OutputEncoding = System.Text.Encoding.UTF8;
if (args.Length == 0)
{
    Console.WriteLine("""
    usage: treelevel-tools <command>
      run <job folder> [--docker]            run the job written by TreeLevel (job.json, events.lhe)
      capabilities [--out file] [--docker]   list the generators this installation can run, as JSON
      serve <folder> [--every s] [--docker]  stay up, run every job folder that turns up inside it
      version

      --docker   everything in the Docker image, and nothing when it is missing
    """);
    return 2;
}

bool dockerOnly = args.Contains("--docker");

switch (args[0])
{
    case "version":
        Console.WriteLine($"TreeLevel Tools {EngineVersion}");
        return 0;

    case "capabilities":
    {
        var caps = Installation.Capabilities(EngineVersion, dockerOnly);
        string json = JsonSerializer.Serialize(caps, MCEngineProtocol.JsonOptions);
        int k = Array.IndexOf(args, "--out");
        if (k >= 0 && k + 1 < args.Length) File.WriteAllText(args[k + 1], json, MCEngineProtocol.Utf8);
        else Console.WriteLine(json);
        Installation.PublishCapabilities(caps);
        return 0;
    }

    case "run":
    {
        if (args.Length < 2) return Fail("run needs the job folder");
        var folder = new MCJobFolder(args[1]);
        MCJob job;
        try { job = folder.ReadJob(); }
        catch (Exception e) { return Fail($"cannot read {folder.JobPath}: {e.Message}"); }
        if (job.ProtocolVersion > MCEngineProtocol.Version)
        {
            folder.WriteStatus(new MCStatus(MCStatus.State.Failed, job.Id)
            {
                Message = $"This job needs a newer engine (protocol {job.ProtocolVersion}).",
            });
            return Fail($"job protocol {job.ProtocolVersion} is newer than this engine ({MCEngineProtocol.Version})");
        }
        var runner = new Runner(folder, job, Installation.NextJobNumber(), dockerOnly);
        return runner.Run() ? 0 : 1;
    }

    case "serve":
    {
        if (args.Length < 2) return Fail("serve needs the folder to watch");
        double every = 2;
        int k = Array.IndexOf(args, "--every");
        if (k >= 0 && k + 1 < args.Length) double.TryParse(args[k + 1], System.Globalization.NumberStyles.Float,
                                                           System.Globalization.CultureInfo.InvariantCulture, out every);
        return Serve.Run(args[1], EngineVersion, every, dockerOnly);
    }

    default:
        return Fail($"unknown command '{args[0]}'");
}

static int Fail(string message)
{
    Console.Error.WriteLine("treelevel-tools: " + message);
    return 1;
}
