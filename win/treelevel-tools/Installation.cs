using System.Diagnostics;

namespace TreeLevel.MC;

/// <summary>Where the pieces are on Windows, and which generators are usable: the C++ engine and the Pythia
/// module travel with this program; Herwig, Sherpa, WHIZARD and CalcHEP, which have no Windows build, come from
/// the container image through Docker.</summary>
public static class Installation
{
    /// <summary>%LocalAppData%\TreeLevel Tools — job numbers and the published capabilities, and a module built by
    /// hand.</summary>
    public static string SupportDirectory
    {
        get
        {
            foreach (var racine in new[] { Local(), Path.GetTempPath() })
            {
                if (string.IsNullOrEmpty(racine)) continue;
                try
                {
                    var dir = Path.Combine(racine, MCEngineProtocol.SupportFolderName);
                    Directory.CreateDirectory(dir);
                    return dir;
                }
                catch (Exception) { }
            }
            return Path.GetTempPath();
        }
    }

    static string Local()
    {
        try { return Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData, Environment.SpecialFolderOption.Create); }
        catch (Exception) { return ""; }
    }

    public static string ModulesDirectory => Path.Combine(SupportDirectory, "Modules");

    static string EngineDirectory => AppContext.BaseDirectory;

    /// <summary>First match among: beside this program, the given folders, the PATH.</summary>
    static string? Find(string executable, params string[] extraFolders)
    {
        var candidates = new List<string> { Path.Combine(EngineDirectory, executable) };
        candidates.AddRange(extraFolders.Select(f => Path.Combine(f, executable)));
        foreach (var dir in (Environment.GetEnvironmentVariable("PATH") ?? "").Split(Path.PathSeparator))
            if (dir.Length > 0) candidates.Add(Path.Combine(dir, executable));
        foreach (var c in candidates)
        {
            try { if (File.Exists(c)) return Path.GetFullPath(c); }
            catch (Exception) { }
        }
        return null;
    }

    /// <summary>The C++ engine that writes every generator's card and runs it, beside this program — the same
    /// source as the engine of the image and of the Mac.</summary>
    public static string? NativeEngine
    {
        get
        {
            var path = Path.Combine(EngineDirectory, "treelevel-engine.exe");
            return File.Exists(path) ? path : null;
        }
    }

    /// <summary>The Pythia driver: our own small program, built against the Pythia library. The release archive
    /// carries it under <c>Modules\pythia8</c> beside the engine, so that unpacking one folder is the whole
    /// installation; a module built by hand lands in the support folder instead.</summary>
    public static string? PythiaDriver => Find("treelevel-pythia.exe",
        Path.Combine(EngineDirectory, "Modules", "pythia8"),
        Path.Combine(EngineDirectory, "Modules", "pythia8", "bin"),
        Path.Combine(ModulesDirectory, "pythia8"),
        Path.Combine(ModulesDirectory, "pythia8", "bin"));

    /// <summary>Whether this driver writes its card from the job (<c>--features</c> says « job »). A module built
    /// before the 0.4 engine does not, and would fail on an argument it does not know.</summary>
    public static bool DriverWritesCards(string driver)
        => Run(driver, new[] { "--features" }).Output.Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries).Contains("job");

    /// <summary>Whether this driver places partons and hadrons in the interaction zone (<c>--features</c> says « spacetime »).</summary>
    public static bool DriverKnowsSpaceTime(string driver)
        => Run(driver, new[] { "--features" }).Output.Split((char[]?)null, StringSplitOptions.RemoveEmptyEntries).Contains("spacetime");

    /// <summary>« Pythia 8.318 », with where it came from when it is not our module; null when it does not answer.
    /// A file that exists is not a program that runs: a module whose files went missing must not be offered.</summary>
    public static string? PythiaVersion(string driver)
        => VersionOf(driver) is string v ? "Pythia " + v + Origin(driver) : null;

    /// <summary>Pythia's xmldoc folder, which the driver needs; passed through PYTHIA8DATA.</summary>
    public static string? PythiaData
    {
        get
        {
            if (Environment.GetEnvironmentVariable("PYTHIA8DATA") is string set && Directory.Exists(set)) return set;
            var roots = new List<string>();
            if (PythiaDriver is string driver && Path.GetDirectoryName(driver) is string dir)
            {
                roots.Add(dir);
                if (Path.GetDirectoryName(dir) is string parent) roots.Add(parent);
            }
            roots.Add(Path.Combine(ModulesDirectory, "pythia8"));
            foreach (var root in roots)
                foreach (var rel in new[] { "xmldoc", Path.Combine("share", "Pythia8", "xmldoc"), Path.Combine("..", "share", "Pythia8", "xmldoc") })
                {
                    var path = Path.GetFullPath(Path.Combine(root, rel));
                    if (Directory.Exists(path)) return path;
                }
            return null;
        }
    }

    // The image

    /// <summary>Where the image lives, without its tag.</summary>
    public const string Repository = "ghcr.io/gpasa/treelevel-tools";

    /// <summary>The image that carries the generators, as it should be named when telling someone to fetch it.
    /// Its tag comes from the shared protocol, never from this program's own version, so that both systems ask
    /// for the same image. TREELEVEL_MC_IMAGE overrides it, for a local build or a mirror.</summary>
    public static string Image()
        => Environment.GetEnvironmentVariable("TREELEVEL_MC_IMAGE") is string set && set.Trim().Length > 0
            ? set.Trim() : Repository + ":" + MCEngineProtocol.ToolsVersion;

    /// <summary>Docker, but only when its daemon answers: Docker Desktop installs the client long before the
    /// engine can run, and on a machine without virtualisation it never will.</summary>
    public static string? Docker
    {
        get
        {
            var docker = Find("docker.exe",
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles),
                             "Docker", "Docker", "resources", "bin"));
            if (docker == null) return null;
            var (code, output) = Run(docker, new[] { "version", "--format", "{{.Server.Version}}" });
            return code == 0 && output.Trim().Length > 0 ? docker : null;
        }
    }

    /// <summary>Whether the image is already on the machine. Nothing is ever pulled behind the user's back.</summary>
    public static bool ImageIsPresent(string docker, string image)
        => Run(docker, new[] { "image", "inspect", image }).Code == 0;

    /// <summary>Docker and the image together, when both are there. The tag the shared protocol names first, then
    /// <c>latest</c>: refusing an image that is present for a number would be absurd. An explicit setting is not
    /// worked around.</summary>
    public static (string Docker, string Image)? Container()
    {
        if (Docker is not string docker) return null;
        if (Environment.GetEnvironmentVariable("TREELEVEL_MC_IMAGE") is string set && set.Trim().Length > 0)
            return ImageIsPresent(docker, set.Trim()) ? (docker, set.Trim()) : null;
        foreach (var image in new[] { Repository + ":" + MCEngineProtocol.ToolsVersion, Repository + ":latest" })
            if (ImageIsPresent(docker, image)) return (docker, image);
        return null;
    }

    /// <summary>What the engine inside the image reports, asked for by running it.</summary>
    static MCCapabilities? ImageCapabilities(string docker, string image)
    {
        var (code, output) = Run(docker, new[] { "run", "--rm", image, "capabilities" }, timeout: 120_000);
        if (code != 0) return null;
        try { return System.Text.Json.JsonSerializer.Deserialize<MCCapabilities>(output, MCEngineProtocol.JsonOptions); }
        catch (Exception) { return null; }
    }

    static (int Code, string Output) Run(string exe, string[] arguments, int timeout = 20_000)
    {
        try
        {
            var info = new ProcessStartInfo(exe)
            {
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true,
            };
            foreach (var a in arguments) info.ArgumentList.Add(a);
            using var p = Process.Start(info);
            if (p == null) return (127, "");
            var errors = p.StandardError.ReadToEndAsync();
            string output = p.StandardOutput.ReadToEnd();
            if (!p.WaitForExit(timeout)) { try { p.Kill(true); } catch (Exception) { } return (124, output); }
            // The image's capabilities are JSON on standard output alone; what Docker says goes after.
            return (p.ExitCode, output + errors.Result);
        }
        catch (Exception) { return (127, ""); }
    }

    /// <summary>Where a program was found, when it is not where we put our own. A version number that surprises
    /// has no visible explanation otherwise: the PATH is looked at too, and what is found there is somebody
    /// else's build.</summary>
    static string Origin(string exe)
    {
        var dir = Path.GetDirectoryName(Path.GetFullPath(exe)) ?? "";
        foreach (var notre in new[] { ModulesDirectory, Path.Combine(EngineDirectory, "Modules") })
            if (dir.StartsWith(notre, StringComparison.OrdinalIgnoreCase)) return "";
        return $" ({dir})";
    }

    /// <summary>Version string of a program, or null when it is missing or broken.</summary>
    static string? VersionOf(string exe, string argument = "--version")
    {
        var (code, output) = Run(exe, new[] { argument });
        var line = output.Split('\n').FirstOrDefault(l => l.Trim().Length > 0)?.Trim();
        return code == 0 && !string.IsNullOrEmpty(line) ? line : null;
    }

    /// <summary>The next job number, kept in the support folder so that a number is never reused.</summary>
    public static int NextJobNumber()
    {
        var path = Path.Combine(SupportDirectory, "counter.txt");
        int n = 1;
        try { if (File.Exists(path) && int.TryParse(File.ReadAllText(path).Trim(), out int read)) n = read + 1; }
        catch (Exception) { }
        try { File.WriteAllText(path, n.ToString(System.Globalization.CultureInfo.InvariantCulture), MCEngineProtocol.Utf8); }
        catch (Exception) { }
        return n;
    }

    /// <summary>What this machine can run. By default the native engine — the passthrough, and Pythia with every
    /// family of the machine — then what the image adds, said to come from Docker. With <paramref name="dockerOnly"/>
    /// the image alone, and nothing at all when Docker or the image is missing rather than the native module in
    /// silence.</summary>
    public static MCCapabilities Capabilities(string engineVersion, bool dockerOnly)
    {
        var caps = new MCCapabilities { EngineVersion = engineVersion, ColliderChannels = new(), SpaceTimeGenerators = new() };
        if (!dockerOnly)
        {
            caps.Generators.Add(MCJob.Generator.Passthrough);
            if (PythiaDriver is string driver && PythiaVersion(driver) is string pythia)
            {
                string key = MCJob.RawValue(MCJob.Generator.Pythia8);
                caps.Generators.Add(MCJob.Generator.Pythia8);
                caps.Versions[key] = pythia;
                caps.ColliderChannels[key] = Enum.GetValues<MCProcess.Channel>();
                // The positions in the interaction zone: only if the installed driver knows them.
                if (DriverKnowsSpaceTime(driver)) caps.SpaceTimeGenerators.Add(key);
            }
        }
        // Nothing is downloaded here: an image that is not on the machine simply offers nothing.
        if (Container() is (string docker, string found) && ImageCapabilities(docker, found) is MCCapabilities image)
        {
            foreach (var generator in image.Generators)
            {
                // Without the setting, Pythia and the passthrough are the native ones or nothing: a job runs the way
                // its capabilities said, and Runner sends these two to the native engine.
                if (caps.Generators.Contains(generator)
                    || (!dockerOnly && generator is MCJob.Generator.Passthrough or MCJob.Generator.Pythia8)) continue;
                caps.Generators.Add(generator);
                string key = MCJob.RawValue(generator);
                caps.Versions[key] = (image.Versions.TryGetValue(key, out var v) ? v : MCJob.Label(generator)) + " (Docker)";
                // The image says what it can open; one older than 1.3 does not, and MachineChannels then keeps what
                // 1.2 could do.
                var families = image.MachineChannels(generator);
                if (families.Length > 0) caps.ColliderChannels[key] = families;
                if (image.SpaceTimeGenerators?.Contains(key) == true) caps.SpaceTimeGenerators.Add(key);
            }
        }
        return caps;
    }

    /// <summary>Writes the capabilities where a script can read them without launching anything.</summary>
    public static void PublishCapabilities(MCCapabilities caps)
    {
        try
        {
            var path = Path.Combine(SupportDirectory, MCEngineProtocol.CapabilitiesFileName);
            File.WriteAllText(path, System.Text.Json.JsonSerializer.Serialize(caps, MCEngineProtocol.JsonOptions), MCEngineProtocol.Utf8);
        }
        catch (Exception) { }
    }
}
