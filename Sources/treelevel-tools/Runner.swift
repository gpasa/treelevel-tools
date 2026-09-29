import Foundation

/// Runs one job. The physics — the cards of every generator, the machine, the assembly of two draws — lives in
/// the C++ engine (Backends/engine), written once for the Mac and for the Linux image. What stays here is the
/// Mac's own business: preparing the native modules where they were installed, telling the engine how to
/// launch them (launch.json), or handing the whole job to the Docker image when the user chose it — and keeping
/// the engine's window in step with the status the engine writes.
struct Runner {
    var folder: MCJobFolder
    var job: MCJob
    var engineVersion: String
    /// Number of the job in this run of the engine, shown in its window and in TreeLevel.
    var number: Int = 0

    /// Writes the status in the job folder and keeps the engine's list of jobs in step.
    private func publish(_ status: MCStatus) {
        try? folder.write(status: status)
        JobHistory.record(JobHistory.entry(job: job, folder: folder, status: status))
    }

    func run() -> Bool {
        let start = Date()
        var status = MCStatus(state: .running, jobID: job.id)
        status.number = number
        status.started = start
        status.message = "préparation"
        publish(status)
        // Docker, quand l'utilisateur l'a choisi, remplace les modules en entier : une seule voie, qu'il sait.
        if Installation.allowsContainer {
            guard let container = Installation.container() else {
                return finish(failed: "the Docker image is chosen in the engine's window, but Docker or the image "
                                    + "(\(Installation.image())) cannot be found", start: start)
            }
            return inContainer(container, start: start)
        }
        return native(start: start)
    }

    // MARK: Les modules du Mac

    /// Prépare le module du générateur demandé, dit au moteur C++ comment le lancer, et le lance.
    private func native(start: Date) -> Bool {
        guard let engine = Installation.nativeEngine else {
            return finish(failed: "this installation is incomplete: treelevel-engine is missing — reinstall TreeLevel Tools",
                          start: start)
        }
        let versions = Installation.capabilities(engineVersion: engineVersion).versions
        /// Ce qui s'ajoute à l'environnement du moteur, pas tout l'environnement.
        func extra(_ full: [String: String]) -> [String: String] {
            let base = ProcessInfo.processInfo.environment
            return full.filter { base[$0.key] != $0.value }
        }
        var launch: [String: Any] = [:]
        switch job.generator {
        case .passthrough:
            break
        case .pythia8:
            guard let driver = Installation.pythiaDriver else {
                return finish(failed: "the Pythia 8 module is not installed", start: start)
            }
            guard Self.driverWritesCards(driver) else {
                return finish(failed: "the Pythia 8 module is older than this engine and cannot write its own card — "
                                    + "reinstall the Pythia 8 module", start: start)
            }
            launch["pythia8"] = ["program": driver.path, "environment": extra(ModuleSetup.pythiaEnvironment(driver: driver)),
                                 "version": versions["pythia8"] ?? "Pythia 8"]
        case .herwig7:
            guard let herwig = Installation.herwig else {
                return finish(failed: "the Herwig 7 module is not installed", start: start)
            }
            // Un module livré dans l'application porte les chemins de la machine qui l'a construit : son dépôt
            // est reconstruit ici, une fois, et les chemins de recherche sont nommés.
            let module = herwig.deletingLastPathComponent().deletingLastPathComponent()
            var arguments = ModuleSetup.searchPaths(module: module)
            if let repository = ModuleSetup.herwigRepository(module: module, log: { self.append(toLog: $0) }) {
                arguments += ["--repo", repository.path, "-I", module.appendingPathComponent("share/Herwig").path]
            }
            launch["herwig7"] = ["program": herwig.path, "arguments": arguments,
                                 "environment": extra(ModuleSetup.environment(module: module)),
                                 "version": versions["herwig7"] ?? "Herwig 7"]
        case .sherpa3:
            guard let sherpa = Installation.sherpa else {
                return finish(failed: "the Sherpa 3 module is not installed", start: start)
            }
            launch["sherpa3"] = ["program": sherpa.path, "environment": extra(ModuleSetup.sherpaEnvironment(binary: sherpa)),
                                 "version": versions["sherpa3"] ?? "Sherpa 3"]
        case .whizard3:
            // WHIZARD compile chaque processus avec gfortran, que ni macOS ni Xcode ne fournissent : seul celui de
            // l'utilisateur, qui a son compilateur, tourne ici. Il écrit du Les Houches — son HepMC3 plante au
            // Mac en se fermant (deux bibliothèques standard C++ dans le même processus).
            guard let whizard = Installation.systemWhizard else {
                return finish(failed: Self.whizardNeedsContainer, start: start)
            }
            launch["whizard3"] = ["program": whizard.path, "sampleFormat": "lhef", "version": versions["whizard3"] ?? "WHIZARD 3"]
        case .calchep3:
            guard let root = Installation.calchep else {
                return finish(failed: "the CalcHEP 3 module is not installed", start: start)
            }
            // CalcHEP compile chaque processus, et ni make ni ses scripts ne supportent une espace dans un
            // chemin ; le dossier d'un travail en porte deux (« Application Support »). On lui donne un dossier
            // de travail dans le temporaire et une copie du module à côté, où le jeton posé à l'empaquetage est
            // remplacé par ce chemin-là, qui n'en a pas.
            let work = Self.spaceFreeWorkDirectory(for: job.id)
            let racine = work.deletingLastPathComponent().appendingPathComponent("module", isDirectory: true)
            do {
                try FileManager.default.createDirectory(at: work.deletingLastPathComponent(), withIntermediateDirectories: true)
                try? FileManager.default.removeItem(at: racine)
                try FileManager.default.copyItem(at: root, to: racine)
                try ModuleSetup.replacePlaceholder(in: racine, with: racine.path)
            } catch {
                return finish(failed: "cannot prepare CalcHEP: \(error.localizedDescription)", start: start)
            }
            launch["calchep3"] = ["root": racine.path, "workDirectory": work.path,
                                  "version": Installation.calchepVersion(root) ?? "CalcHEP 3"]
        }
        let launchURL = folder.url.appendingPathComponent("launch.json")
        do {
            let data = try JSONSerialization.data(withJSONObject: launch, options: [.prettyPrinted, .sortedKeys])
            try data.write(to: launchURL)
        } catch {
            return finish(failed: "cannot write launch.json: \(error.localizedDescription)", start: start)
        }
        return follow(engine, ["run", folder.url.path, "--launch", launchURL.path, "--number", String(number)], start: start)
    }

    /// Lance le moteur C++ et suit le statut qu'il écrit, pour que la fenêtre du moteur avance avec lui.
    private func follow(_ engine: URL, _ arguments: [String], start: Date) -> Bool {
        let process = Process()
        process.executableURL = engine
        process.arguments = arguments
        process.currentDirectoryURL = folder.url
        let pipe = Pipe()
        process.standardOutput = pipe
        process.standardError = pipe
        do { try process.run() } catch {
            return finish(failed: "cannot start treelevel-engine: \(error.localizedDescription)", start: start)
        }
        // On vide le tuyau à part : le moteur écrit son vrai journal dans le dossier, mais un tuyau plein le
        // bloquerait.
        var said = Data()
        let reader = DispatchQueue(label: "engine-output")
        reader.async { said = pipe.fileHandleForReading.readDataToEndOfFile() }
        var last: MCStatus?
        while process.isRunning {
            Thread.sleep(forTimeInterval: 0.5)
            if let s = folder.readStatus(), s != last {
                JobHistory.record(JobHistory.entry(job: job, folder: folder, status: s))
                last = s
            }
        }
        process.waitUntilExit()
        reader.sync {}
        guard let status = folder.readStatus() else {
            let reason = String(decoding: said, as: UTF8.self).split(separator: "\n").first.map(String.init)
            return finish(failed: "the engine stopped with code \(process.terminationStatus)" + (reason.map { " — " + $0 } ?? ""),
                          start: start)
        }
        JobHistory.record(JobHistory.entry(job: job, folder: folder, status: status))
        return status.state == .finished
    }

    /// Whether this Pythia driver writes its card from the job (`--features` says « job »). A module built
    /// before the 0.4 engine does not, and running it would fail on an argument it does not know.
    static func driverWritesCards(_ driver: URL) -> Bool {
        Process.output(driver, ["--features"], timeout: 10)?.split(whereSeparator: \.isWhitespace).contains("job") ?? false
    }

    static let whizardNeedsContainer =
        "WHIZARD 3 only runs through the container on macOS: it compiles each process with gfortran, "
        + "which neither macOS nor Xcode provides. Turn the container on in the engine's window "
        + "(Docker required), or choose another generator."

    // MARK: Le conteneur

    /// Le même travail, mené par le moteur qui tourne dans l'image. Le dossier est monté tel quel : rien
    /// n'est copié ni converti, le montage *est* le protocole, et le conteneur écrit lui-même sa progression
    /// dans le `status.json` que TreeLevel relit.
    ///
    /// C'est la seconde manière d'avoir les générateurs sur un Mac — celle de qui a déjà Docker et préfère
    /// ne pas installer une seconde fois sept cents mégaoctets de binaires. Les modules natifs restent
    /// prioritaires : ils tournent sans machine virtuelle.
    private func inContainer(_ container: (docker: URL, image: String), start: Date) -> Bool {
        var running = MCStatus(state: .running, jobID: job.id)
        running.number = number
        running.started = start
        running.message = "conteneur"
        running.generatorVersion = job.generator.label
        publish(running)

        let process = Process()
        process.executableURL = container.docker
        process.arguments = ["run", "--rm", "-v", folder.url.path + ":/job", container.image, "run", "/job"]
        process.currentDirectoryURL = folder.url
        let pipe = Pipe()
        process.standardOutput = pipe
        process.standardError = pipe
        do { try process.run() } catch {
            return finish(failed: "cannot start \(container.docker.lastPathComponent): \(error.localizedDescription)",
                          start: start)
        }
        // On vide le tuyau : un conteneur qui écrit beaucoup se bloquerait sur un tuyau plein. Son vrai
        // journal est celui qu'il écrit de l'intérieur, dans le dossier de travail.
        let output = String(decoding: pipe.fileHandleForReading.readDataToEndOfFile(), as: UTF8.self)
        process.waitUntilExit()

        var status = folder.readStatus()
        if process.terminationStatus == 0, status?.state == .finished {
            // Le moteur de l'image a écrit le statut ; il ignore qu'il tournait dans une image. On le dit
            // ici, pour qu'un travail retrouvé six mois plus tard dise par où il est passé — et pour que
            // personne n'ait à deviner en comparant des sections efficaces.
            if var fini = status, !(fini.generatorVersion ?? "").contains("conteneur") {
                fini.generatorVersion = (fini.generatorVersion ?? job.generator.label) + " (conteneur)"
                publish(fini)
                status = fini
            }
            return true
        }
        if status?.state == .failed, let message = status?.message, !message.isEmpty {
            return finish(failed: message, start: start)
        }
        let reason = output.split(separator: "\n").map { $0.trimmingCharacters(in: .whitespaces) }
                           .first(where: { !$0.isEmpty })
        return finish(failed: "the container stopped with code \(process.terminationStatus)"
                              + (reason.map { " — " + $0 } ?? ""), start: start)
    }

    /// Un dossier de travail sans espace, pour les générateurs dont les outils de compilation n'en
    /// supportent pas. Le temporaire du système convient : `/var/folders/…`, jamais d'espace, et le
    /// système le nettoie de lui-même si nous n'y parvenons pas.
    private static func spaceFreeWorkDirectory(for id: String) -> URL {
        let sain = id.map { $0.isLetter || $0.isNumber || $0 == "-" ? $0 : "-" }
        return URL(fileURLWithPath: NSTemporaryDirectory(), isDirectory: true)
            .appendingPathComponent("treelevel-calchep", isDirectory: true)
            .appendingPathComponent(String(sain), isDirectory: true)
    }

    private func append(toLog message: String) {
        guard let handle = try? FileHandle(forWritingTo: folder.logURL) ?? nil else {
            try? (message + "\n").write(to: folder.logURL, atomically: true, encoding: .utf8); return
        }
        handle.seekToEndOfFile()
        handle.write(Data((message + "\n").utf8))
        try? handle.close()
    }

    private func finish(failed message: String, start: Date) -> Bool {
        var status = MCStatus(state: .failed, jobID: job.id)
        status.number = number
        status.started = start
        status.finished = Date()
        status.message = message
        status.seconds = Date().timeIntervalSince(start)
        publish(status)
        FileHandle.standardError.write(("treelevel-tools: " + message + "\n").data(using: .utf8)!)
        return false
    }

    /// "Pythia::next(): 1000 events have been generated" / "Herwig: 1000 events" / Sherpa's
    /// "XS = 16 pb ... Event 200 ( 0s elapsed / 0s left ) -> ETA: ...", whose other numbers — a cross
    /// section, a date — must not be mistaken for a count, hence the explicit "Event <n>" first.
}
