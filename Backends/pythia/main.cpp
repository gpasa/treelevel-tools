// TreeLevel Tools — Pythia 8 driver.
//
// Reads a Pythia command file (written by the engine, pointing at the Les Houches events of the job) and
// writes the showered events as HepMC3 (Asciiv3). The HepMC3 output is written here, so that the module needs
// nothing but Pythia itself — MacPorts' `pythia` port ships neither Pythia8Plugins nor HepMC3.
// When Pythia's own HepMC3 interface is available, build with -DTREELEVEL_WITH_HEPMC3 to use it instead.
//
//   treelevel-pythia --job job/job.json --out job/events.hepmc [--part beams|photons] [--seed-offset n]
//   treelevel-pythia --config job/pythia.cmnd --out job/events.hepmc
//   treelevel-pythia --job job/job.json --print-card      (the card only)
//   treelevel-pythia --version | --features
//
// With --job the driver writes the card itself (JobCard.h), next to the job as pythia.cmnd — or
// pythia.<part>.cmnd for one half of an assembled machine —, and runs it.
//
// Build:  make -C Backends/pythia            (MacPorts, Homebrew or a local build of Pythia 8)
//
// Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later (Pythia 8 is GPL).

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <sys/stat.h>
#include <map>
#include <vector>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#include <windows.h>
#ifndef S_IFDIR
#define S_IFDIR _S_IFDIR
#endif
#endif
#include "Pythia8/Pythia.h"
#include "JobCard.h"
#ifdef TREELEVEL_WITH_HEPMC3
#include "Pythia8Plugins/HepMC3.h"
#endif

namespace {

bool isDirectory(const std::string& path) {
  struct stat info;
  return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

/// The folder the running program is in, so that a module can carry its own data next to it.
std::string executableFolder() {
#ifdef _WIN32
  char buffer[MAX_PATH];
  DWORD n = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
  if (n == 0 || n >= MAX_PATH) return "";
  std::string path(buffer, n);
  const size_t cut = path.find_last_of("\\/");
  return cut == std::string::npos ? "" : path.substr(0, cut);
#else
  return "";
#endif
}

/// Where Pythia's xmldoc lives: the environment first, then the usual package layouts. Windows has no such
/// layout — the module that win/backends/pythia/build.ps1 installs carries xmldoc beside the driver.
std::string dataPath() {
  if (const char* env = std::getenv("PYTHIA8DATA")) return env;
#ifdef _WIN32
  std::vector<std::string> candidates;
  const std::string folder = executableFolder();
  if (!folder.empty())
    for (const char* relative : {"/xmldoc", "/share/Pythia8/xmldoc", "/../share/Pythia8/xmldoc"})
      candidates.push_back(folder + relative);
  if (const char* local = std::getenv("LOCALAPPDATA"))
    candidates.push_back(std::string(local) + "/TreeLevel Tools/Modules/pythia8/xmldoc");
  for (const std::string& path : candidates) if (isDirectory(path)) return path;
#else
  const char* candidates[] = {
    "/opt/local/share/doc/pythia/xmldoc",           // MacPorts
    "/opt/homebrew/share/Pythia8/xmldoc",           // Homebrew (Apple silicon)
    "/usr/local/share/Pythia8/xmldoc",              // Homebrew (Intel), local install
    "/usr/share/Pythia8/xmldoc",
  };
  for (const char* path : candidates) if (isDirectory(path)) return path;
#endif
  return "";
}

/// Minimal HepMC3 (Asciiv3) writer: one vertex per particle with two mothers, a parent id otherwise.
/// The syntax is the one TreeLevel reads back and the one Pythia's own writer produces.
class HepMCWriter {
public:
  explicit HepMCWriter(const std::string& path) : out(path) {
    out << "HepMC::Version 3.02.00\n" << "HepMC::Asciiv3-START_EVENT_LISTING\n";
    out << std::scientific << std::setprecision(10);
  }
  ~HepMCWriter() { out << "HepMC::Asciiv3-END_EVENT_LISTING\n"; }
  bool good() const { return out.good(); }

  /// The cross section as it stands once the run is over, which is not the one the last event carried: Pythia
  /// normalises in `stat()`, after the loop. The two agree to a fraction of a percent over tens of thousands
  /// of events and differ by a good ten over a few hundred — and a few hundred is what one asks for while
  /// trying things out. Readers keep the last attribute they meet, so writing it here settles the matter.
  void finalCrossSection(double crossSectionPb, double errorPb) {
    const double error = (errorPb > 0 && errorPb < crossSectionPb) ? errorPb : 0.0;
    out << "A 0 GenCrossSection " << number_(crossSectionPb) << " " << number_(error) << " -1 -1\n";
  }

  void write(const Pythia8::Event& event, double weight, int number, double crossSectionPb, double errorPb,
             int processCode = 0, const std::string& processName = "") {
    // HepMC ids are 1-based and skip Pythia's entry 0 (the whole system).
    // Chaque ensemble de mères a son vertex. On l'écrit quand il en réunit plusieurs, ou quand il n'est pas
    // là où la mère est née : c'est le vol d'un K0S, d'un Λ, d'un hadron b, d'un τ — et la zone lumineuse
    // quand les faisceaux ont une taille. Sinon le raccourci « particule mère » suffit, et le lecteur place
    // la fille où la mère est née.
    const int n = event.size() - 1;
    std::vector<std::string> vertices;
    std::map<std::pair<int, int>, int> vertexOf;
    std::string particles;
    auto position = [](const Pythia8::Vec4& v) {
      if (v.px() == 0 && v.py() == 0 && v.pz() == 0 && v.e() == 0) return std::string();
      // Pythia : vProd() en mm, temps en mm/c ; HepMC : @ x y z t, dans la même unité (U GEV MM).
      // Seize chiffres : un vertex à un demi-millimètre du centre reste juste au femtomètre près.
      auto fine = [](double x) { char b[40]; snprintf(b, sizeof b, "%.15e", x); return std::string(b); };
      return " @ " + fine(v.px()) + " " + fine(v.py()) + " " + fine(v.pz()) + " " + fine(v.e());
    };
    for (int i = 1; i < event.size(); ++i) {
      const Pythia8::Particle& p = event[i];
      int status = p.isFinal() ? 1 : (i <= 2 ? 4 : 2);
      int parent = 0;
      const int m1 = p.mother1(), m2 = std::max(p.mother1(), p.mother2());
      if (m1 > 0) {
        const auto key = std::make_pair(m1, m2);
        const Pythia8::Vec4 here = p.vProd(), born = event[m1].vProd();
        const bool moved = (here - born).pAbs() > 1e-9 || std::abs(here.e() - born.e()) > 1e-9;
        if (auto found = vertexOf.find(key); found != vertexOf.end()) {
          parent = found->second;
        } else if (m2 > m1 || moved) {
          std::string list;
          for (int m = m1; m <= m2; ++m) list += (list.empty() ? "" : ",") + std::to_string(m);
          // Écrit juste avant sa première fille : ses mères, d'indice plus petit, sont déjà écrites — ce que
          // demande la bibliothèque HepMC3.
          vertices.push_back("V " + std::to_string(-(int)vertices.size() - 1) + " 0 [" + list + "]" + position(here) + "\n");
          particles += vertices.back();
          parent = -(int)vertices.size();
          vertexOf[key] = parent;
        } else {
          parent = m1;
        }
      }
      particles += "P " + std::to_string(i) + " " + std::to_string(parent) + " " + std::to_string(p.id()) + " ";
      particles += number_(p.px()) + " " + number_(p.py()) + " " + number_(p.pz()) + " " + number_(p.e()) + " "
                 + number_(p.m()) + " " + std::to_string(status) + "\n";
    }
    out << "E " << number << " " << vertices.size() << " " << n << "\n";
    out << "U GEV MM\n";
    out << "W " << number_(weight) << "\n";
    // Le processus dur qui a fait l'événement — ce qu'un filtre cherchera parmi tout ce qu'une machine produit.
    if (processCode > 0) {
      out << "A 0 signal_process_id " << processCode << "\n";
      if (!processName.empty()) out << "A 0 signal_process_name " << processName << "\n";
    }
    {
      // Every event carries the cross section as it stands after it, which is what HepMC3 asks for and what
      // a reader that keeps the last one needs. Writing it once, on the first event, was enough as long as
      // Pythia only dressed events whose cross section came fixed from the Les Houches file; in collider
      // mode it integrates as it goes, and the estimate after one event is not the answer.
      // With Les Houches input Pythia reports the file's cross section and no useful error: write 0 rather
      // than an error as large as the value itself.
      const double error = (errorPb > 0 && errorPb < crossSectionPb) ? errorPb : 0.0;
      out << "A 0 GenCrossSection " << number_(crossSectionPb) << " " << number_(error) << " -1 -1\n";
    }
    out << particles;
  }

private:
  static std::string number_(double x) {
    char buffer[32];
    snprintf(buffer, sizeof buffer, "%.10e", x);
    return buffer;
  }
  std::ofstream out;
};

}  // namespace

int main(int argc, char* argv[]) {
  std::string config, out, jobPath, part;
  int seedOffset = 0;
  bool printCard = false, plan = false;
  for (int i = 1; i < argc; ++i) {
    std::string a = argv[i];
    if (a == "--version") { std::cout << PYTHIA_VERSION << std::endl; return 0; }
    // Ce que ce pilote sait faire, pour qu'un hôte sache s'il peut lui confier la carte.
    if (a == "--features") { std::cout << "job" << std::endl; return 0; }
    if (a == "--config" && i + 1 < argc) config = argv[++i];
    else if (a == "--out" && i + 1 < argc) out = argv[++i];
    else if (a == "--job" && i + 1 < argc) jobPath = argv[++i];
    else if (a == "--part" && i + 1 < argc) part = argv[++i];
    else if (a == "--seed-offset" && i + 1 < argc) seedOffset = std::atoi(argv[++i]);
    else if (a == "--print-card") printCard = true;             // la carte, sans rien lancer
    else if (a == "--plan") plan = true;                         // ce qu'il faut lancer, sans rien lancer
  }
  if (!jobPath.empty()) {
    std::ifstream in(jobPath, std::ios::binary);
    if (!in) { std::cerr << "cannot read " << jobPath << std::endl; return 1; }
    const std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    jobcard::Value job;
    std::string error, cardText;
    if (!jobcard::Parser(text).parse(job, error) || !jobcard::card(job, part, seedOffset, cardText, error)) {
      std::cerr << error << std::endl;
      return 3;
    }
    if (printCard) { std::cout << cardText; return 0; }
    // Pour un hôte qui ne passe pas par le moteur C++ — le module WebAssembly de l'iPad — : les parties à tirer
    // (une machine entre deux leptons, « tout », se tire en deux : les faisceaux, puis leur flux de photons, réunis
    // ensuite) et l'objection du travail, décidées ici comme le moteur les décide.
    if (plan) {
      const jobcard::Process p = jobcard::expanded(jobcard::readProcess(job["hardProcess"]));
      const bool mixed = p.collider && p.mix && p.has("photoproduction") && p.channels.size() > 1;
      std::string objection = jobcard::objection(p), quoted;
      for (char c : objection) { if (c == '"' || c == '\\') quoted += '\\'; quoted += c; }
      std::cout << "{\"parts\":" << (mixed ? "[\"beams\",\"photons\"]" : "[\"\"]")
                << ",\"objection\":\"" << quoted << "\"}" << std::endl;
      return 0;
    }
    const size_t cut = jobPath.find_last_of("\\/");
    const std::string folder = cut == std::string::npos ? "" : jobPath.substr(0, cut + 1);
    config = folder + (part.empty() ? "pythia.cmnd" : "pythia." + part + ".cmnd");
    std::ofstream card(config, std::ios::binary);
    card << cardText;
    if (!card) { std::cerr << "cannot write " << config << std::endl; return 1; }
  }
  if (config.empty() || out.empty()) {
    std::cerr << "usage: treelevel-pythia --job job.json | --config file.cmnd --out events.hepmc" << std::endl;
    return 2;
  }

  const std::string data = dataPath();
  Pythia8::Pythia pythia(data.empty() ? "../share/Pythia8/xmldoc" : data);
  if (!pythia.readFile(config)) { std::cerr << "cannot read " << config << std::endl; return 1; }
  if (!pythia.init()) {
    // `Print:quiet` cache aussi les raisons de l'échec : Pythia imprime sa bannière puis se tait, et le
    // journal ne dit rien de plus que « failed to initialise ». On recommence une fois en clair, pour que
    // la raison — une grille de densités partoniques absente, un canal fermé — atteigne le journal.
    std::cerr << "Pythia failed to initialise; retrying without Print:quiet to show why" << std::endl;
    Pythia8::Pythia bavard(data.empty() ? "../share/Pythia8/xmldoc" : data);
    bavard.readFile(config);
    bavard.readString("Print:quiet = off");
    bavard.init();
    return 1;
  }

#ifdef TREELEVEL_WITH_HEPMC3
  Pythia8::Pythia8ToHepMC toHepMC(out);
#else
  HepMCWriter writer(out);
  if (!writer.good()) { std::cerr << "cannot write " << out << std::endl; return 1; }
#endif

  const int requested = pythia.mode("Main:numberOfEvents");
  int written = 0, failures = 0;
  for (int i = 0; i < requested; ++i) {
    if (!pythia.next()) {
      if (pythia.info.atEndOfFile()) break;         // the Les Houches file is exhausted
      if (++failures > requested / 10 + 10) { std::cerr << "too many failed events" << std::endl; break; }
      continue;
    }
#ifdef TREELEVEL_WITH_HEPMC3
    toHepMC.writeNextEvent(pythia);
#else
    // HepMC3 cross sections are in pb; Pythia reports mb.
    writer.write(pythia.event, pythia.info.weight(), written,
                 pythia.info.sigmaGen() * 1e9, pythia.info.sigmaErr() * 1e9,
                 pythia.info.code(), pythia.info.name());
#endif
    ++written;
    if (written % 100 == 0 || written == requested)
      std::cout << written << " events have been generated" << std::endl;
  }
  pythia.stat();
#ifndef TREELEVEL_WITH_HEPMC3
  // HepMC3 cross sections are in pb; Pythia reports mb.
  if (written > 0) writer.finalCrossSection(pythia.info.sigmaGen() * 1e9, pythia.info.sigmaErr() * 1e9);
#endif
  std::cout << "written " << written << " events, sigma = " << pythia.info.sigmaGen()
            << " +- " << pythia.info.sigmaErr() << " mb" << std::endl;
  return written > 0 ? 0 : 1;
}
