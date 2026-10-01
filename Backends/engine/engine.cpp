// TreeLevel Tools — the engine of the container image, for Linux.
//
// It runs one job the way the engines of the Mac and of Windows do — same job folder, same status.json, same
// events.hepmc — with the generators the image carries: Pythia 8 (through the shared driver, which writes its
// own card), Herwig 7, Sherpa 3, WHIZARD 3 and CalcHEP 3. It replaces the C# engine the image used to compile:
// the logic of the generators now lives here once, and each host only finds Docker, mounts the folder and
// relays the status.
//
//   treelevel-tools run <job folder> [--launch launch.json] [--number n]
//                                                read job.json, produce events.hepmc, keep status.json current
//   treelevel-tools capabilities [--out file]    what this image can run, as JSON
//   treelevel-tools version
//
// Inside the image the generators are found where the image puts them. A host that runs them natively — the Mac,
// whose modules are built for it — says how to launch each one in launch.json: the program, its extra
// arguments, its environment, its version, and two habits of the platform (CalcHEP in a folder without spaces,
// WHIZARD writing Les Houches). The cards stay here, written once; only the launching belongs to the host.
//
// Build:  g++ -O2 -std=c++17 -I Backends/pythia Backends/engine/engine.cpp -o treelevel-tools   (image)
//         clang++ … -o treelevel-engine, beside the Swift host in TreeLevel Tools.app (Mac)
//         win/engine (CMake, MSVC) → treelevel-engine.exe, beside the C# host (Windows)
//
// Windows runs Pythia and the passthrough only — the other generators live in the image — so what differs there
// is the plumbing alone, behind _WIN32: CreateProcess for fork/exec, and a rename that replaces status.json.
//
// Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later.

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <thread>
#include <windows.h>
#ifndef S_ISREG
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif
#else
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#include "JobCard.h"

namespace {

const char* kEngineVersion = "0.4.0";
const int kProtocolVersion = 2;
/// Where the image keeps its generators: $PREFIX, set by the Dockerfile, or the usual place.
const std::string kPrefix = [] {
  if (const char* p = std::getenv("PREFIX")) if (*p) return std::string(p);
  return std::string("/opt/treelevel-tools");
}();

using jobcard::Value;

// ---------------------------------------------------------------------------------------------------------
// Small tools

bool exists(const std::string& path) { struct stat s; return stat(path.c_str(), &s) == 0; }
bool isFile(const std::string& path) { struct stat s; return stat(path.c_str(), &s) == 0 && S_ISREG(s.st_mode); }
bool isDir(const std::string& path) { struct stat s; return stat(path.c_str(), &s) == 0 && S_ISDIR(s.st_mode); }

std::string readFile(const std::string& path) {
  std::ifstream in(path, std::ios::binary);
  return std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

/// Replaces `to` by `from` in one step, so that a reader never sees half a file.
bool replaceFile(const std::string& from, const std::string& to) {
#ifdef _WIN32
  // rename() refuses an existing target on Windows, and a reader holding status.json open without sharing its
  // deletion makes the replacement fail for a moment: a few tries, then the file is written in place.
  for (int attempt = 0; attempt < 20; ++attempt) {
    if (MoveFileExA(from.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING)) return true;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return false;
#else
  return std::rename(from.c_str(), to.c_str()) == 0;
#endif
}

bool writeFile(const std::string& path, const std::string& text) {
  const std::string tmp = path + ".tmp";
  { std::ofstream out(tmp, std::ios::binary); out << text; if (!out) return false; }
  if (replaceFile(tmp, path)) return true;
  std::remove(tmp.c_str());
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out << text;
  return bool(out);
}

std::string join(const std::string& a, const std::string& b) { return a.empty() || a.back() == '/' ? a + b : a + "/" + b; }

std::string stem(const std::string& name) {
  const size_t dot = name.find_last_of('.');
  return dot == std::string::npos ? name : name.substr(0, dot);
}

/// A number as the other engines write them: shortest round-trip form, no locale.
std::string num(double x) {
  char b[40];
  std::snprintf(b, sizeof b, "%.17g", x);
  double back = std::strtod(b, nullptr);
  for (int p = 1; p <= 17; ++p) {
    char c[40];
    std::snprintf(c, sizeof c, "%.*g", p, x);
    if (std::strtod(c, nullptr) == back) return c;
  }
  return b;
}

std::string sci(double x) { char b[40]; std::snprintf(b, sizeof b, "%.10e", x); return b; }

std::string quote(const std::string& s) {
  std::string out = "'";
  for (char c : s) { if (c == '\'') out += "'\\''"; else out += c; }
  return out + "'";
}

std::string firstLine(const std::string& text) {
  std::istringstream in(text);
  std::string line;
  while (std::getline(in, line)) {
    const size_t a = line.find_first_not_of(" \t\r");
    if (a != std::string::npos) { const size_t b = line.find_last_not_of(" \t\r"); return line.substr(a, b - a + 1); }
  }
  return "";
}

std::string lower(std::string s) { for (auto& c : s) c = char(std::tolower((unsigned char)c)); return s; }

/// The first line that names `word`. Under the caller's own user id a login shell first complains that it cannot
/// read /root/.bash_profile, and that line is not the version.
std::string lineNaming(const std::string& text, const std::string& word) {
  std::istringstream in(text);
  std::string line;
  while (std::getline(in, line)) if (lower(line).find(word) != std::string::npos) return firstLine(line);
  return "";
}

/// The first version number in what a program answers: « Herwig 7.3.0 » gives 7.
int majorVersion(const std::string& text) {
  std::smatch m;
  static const std::regex re("(^|[^\\d.])(\\d+)\\.\\d+");
  return std::regex_search(text, m, re) ? std::stoi(m[2]) : -1;
}

/// Seconds since 1 January 2001, the date Swift's Codable writes.
double appleNow() {
  using namespace std::chrono;
  return duration<double>(system_clock::now().time_since_epoch()).count() - 978307200.0;
}

std::string jsonString(const std::string& s) {
  std::string out = "\"";
  for (unsigned char c : s) {
    switch (c) {
      case '"': out += "\\\""; break;
      case '\\': out += "\\\\"; break;
      case '\n': out += "\\n"; break;
      case '\r': out += "\\r"; break;
      case '\t': out += "\\t"; break;
      default:
        if (c < 0x20) { char b[8]; std::snprintf(b, sizeof b, "\\u%04x", c); out += b; }
        else out += char(c);
    }
  }
  return out + "\"";
}

// ---------------------------------------------------------------------------------------------------------
// Running a program and following it

/// Runs `argv` in `cwd`, standard output and error together, handing each line to `onLine`. Returns the exit
/// code (128 + signal when it was killed, -1 when it could not start).
#ifdef _WIN32
/// One argument as CommandLineToArgvW and the C runtime read it back: quoted when needed, the backslashes before
/// a quote doubled.
std::string windowsArgument(const std::string& a) {
  if (!a.empty() && a.find_first_of(" \t\n\v\"") == std::string::npos) return a;
  std::string out = "\"";
  size_t slashes = 0;
  for (char c : a) {
    if (c == '\\') { ++slashes; continue; }
    if (c == '"') out.append(slashes * 2 + 1, '\\');
    else out.append(slashes, '\\');
    slashes = 0;
    out += c;
  }
  out.append(slashes * 2, '\\');
  return out + "\"";
}

int runProcess(const std::vector<std::string>& argv, const std::string& cwd, const std::map<std::string, std::string>& env,
               const std::function<void(const std::string&)>& onLine) {
  if (argv.empty()) return -1;
  SECURITY_ATTRIBUTES inherit{sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
  HANDLE readEnd = nullptr, writeEnd = nullptr;
  if (!CreatePipe(&readEnd, &writeEnd, &inherit, 0)) return -1;
  SetHandleInformation(readEnd, HANDLE_FLAG_INHERIT, 0);
  // The child inherits this process's environment: the additions are set here for the time of the launch, then
  // put back, rather than rebuilding a whole environment block by hand.
  std::vector<std::pair<std::string, std::optional<std::string>>> saved;
  for (const auto& kv : env) {
    const DWORD n = GetEnvironmentVariableA(kv.first.c_str(), nullptr, 0);
    std::optional<std::string> before;
    if (n > 0) { std::string v(n, '\0'); v.resize(GetEnvironmentVariableA(kv.first.c_str(), v.data(), n)); before = v; }
    saved.emplace_back(kv.first, before);
    SetEnvironmentVariableA(kv.first.c_str(), kv.second.c_str());
  }
  std::string commandLine;
  for (const auto& a : argv) commandLine += (commandLine.empty() ? "" : " ") + windowsArgument(a);
  STARTUPINFOA startup{};
  startup.cb = sizeof startup;
  startup.dwFlags = STARTF_USESTDHANDLES;
  startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
  startup.hStdOutput = writeEnd;
  startup.hStdError = writeEnd;
  PROCESS_INFORMATION child{};
  const BOOL started = CreateProcessA(nullptr, commandLine.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr,
                                      cwd.empty() ? nullptr : cwd.c_str(), &startup, &child);
  const DWORD error = GetLastError();
  for (const auto& s : saved) SetEnvironmentVariableA(s.first.c_str(), s.second ? s.second->c_str() : nullptr);
  CloseHandle(writeEnd);
  if (!started) {
    CloseHandle(readEnd);
    onLine("cannot start " + argv[0] + ": error " + std::to_string(error));
    return 127;
  }
  CloseHandle(child.hThread);
  std::string pending;
  char buffer[8192];
  DWORD n = 0;
  while (ReadFile(readEnd, buffer, sizeof buffer, &n, nullptr) && n > 0) {
    pending.append(buffer, size_t(n));
    size_t cut;
    while ((cut = pending.find('\n')) != std::string::npos) {
      std::string line = pending.substr(0, cut);
      if (!line.empty() && line.back() == '\r') line.pop_back();
      onLine(line);
      pending.erase(0, cut + 1);
    }
  }
  if (!pending.empty()) onLine(pending);
  CloseHandle(readEnd);
  WaitForSingleObject(child.hProcess, INFINITE);
  DWORD code = 0;
  const bool known = GetExitCodeProcess(child.hProcess, &code);
  CloseHandle(child.hProcess);
  return known ? int(code) : -1;
}
#else
int runProcess(const std::vector<std::string>& argv, const std::string& cwd, const std::map<std::string, std::string>& env,
               const std::function<void(const std::string&)>& onLine) {
  int fds[2];
  if (pipe(fds) != 0) return -1;
  const pid_t pid = fork();
  if (pid < 0) { close(fds[0]); close(fds[1]); return -1; }
  if (pid == 0) {
    dup2(fds[1], 1); dup2(fds[1], 2);
    close(fds[0]); close(fds[1]);
    if (!cwd.empty() && chdir(cwd.c_str()) != 0) _exit(126);
    for (const auto& kv : env) setenv(kv.first.c_str(), kv.second.c_str(), 1);
    std::vector<char*> args;
    for (const auto& a : argv) args.push_back(const_cast<char*>(a.c_str()));
    args.push_back(nullptr);
    execvp(args[0], args.data());
    std::fprintf(stderr, "cannot start %s: %s\n", args[0], std::strerror(errno));
    _exit(127);
  }
  close(fds[1]);
  std::string pending;
  char buffer[8192];
  ssize_t n;
  while ((n = read(fds[0], buffer, sizeof buffer)) > 0) {
    pending.append(buffer, size_t(n));
    size_t cut;
    while ((cut = pending.find('\n')) != std::string::npos) {
      std::string line = pending.substr(0, cut);
      if (!line.empty() && line.back() == '\r') line.pop_back();
      onLine(line);
      pending.erase(0, cut + 1);
    }
  }
  if (!pending.empty()) onLine(pending);
  close(fds[0]);
  int status = 0;
  waitpid(pid, &status, 0);
  if (WIFEXITED(status)) return WEXITSTATUS(status);
  if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
  return -1;
}
#endif

/// The whole output of a short command, and its exit code.
std::pair<int, std::string> capture(const std::vector<std::string>& argv) {
  std::string out;
  const int code = runProcess(argv, "", {}, [&](const std::string& l) { out += l + "\n"; });
  return {code, out};
}

std::pair<int, std::string> inShell(const std::string& command) { return capture({"/bin/bash", "-lc", command}); }

/// The number of events a generator says it has made, read from one line of its output.
std::optional<int> eventCount(const std::string& line) {
  size_t k = line.find("Event ");
  if (k != std::string::npos) {
    size_t i = k + 6, j = i;
    while (j < line.size() && std::isdigit((unsigned char)line[j])) ++j;
    if (j > i) return std::stoi(line.substr(i, j - i));
  }
  if (line.find("event") == std::string::npos) return std::nullopt;
  int best = -1;
  std::string token;
  auto flush = [&]() {
    if (!token.empty() && token.size() < 10 && std::all_of(token.begin(), token.end(), ::isdigit)) best = std::max(best, std::stoi(token));
    token.clear();
  };
  for (char c : line) { if (c == ' ' || c == '\t' || c == ':' || c == ',' || c == '(' || c == ')') flush(); else token += c; }
  flush();
  if (best < 0) return std::nullopt;
  return best;
}

struct Summary { int events = 0; std::optional<double> sigma, error; };

/// Events counted in a HepMC file, and the cross section it carries (the last one written).
Summary summary(const std::string& path) {
  Summary s;
  std::ifstream in(path);
  std::string line;
  while (std::getline(in, line)) {
    if (line.rfind("E ", 0) == 0) { s.events += 1; continue; }
    std::istringstream f(line);
    std::vector<std::string> w;
    std::string t;
    while (f >> t) w.push_back(t);
    if (line.rfind("C ", 0) == 0) {
      if (w.size() >= 2) s.sigma = std::strtod(w[1].c_str(), nullptr);
      if (w.size() >= 3) s.error = std::strtod(w[2].c_str(), nullptr);
    } else if (line.rfind("A 0 GenCrossSection", 0) == 0) {
      if (w.size() >= 4) s.sigma = std::strtod(w[3].c_str(), nullptr);
      if (w.size() >= 5) s.error = std::strtod(w[4].c_str(), nullptr);
    }
  }
  return s;
}

// ---------------------------------------------------------------------------------------------------------
// Les Houches, for the passthrough and for CalcHEP

struct LheParticle { int pdg, status, m1, m2, c1, c2; double px, py, pz, e, m; };
struct LheEvent { std::vector<LheParticle> particles; double weight = 1, scale = 0; };
struct LheFile { std::vector<LheEvent> events; std::optional<double> crossSection; std::vector<int> beams; };

LheFile readLesHouches(const std::string& path) {
  LheFile file;
  std::ifstream in(path);
  std::string raw;
  auto next = [&](std::string& out) {
    while (std::getline(in, raw)) {
      const size_t a = raw.find_first_not_of(" \t\r");
      if (a == std::string::npos || raw[a] == '#') continue;
      out = raw.substr(a);
      return true;
    }
    return false;
  };
  auto fields = [](const std::string& l) { std::istringstream f(l); std::vector<std::string> w; std::string t; while (f >> t) w.push_back(t); return w; };
  std::string line;
  while (next(line)) {
    if (line.rfind("<init", 0) == 0) {
      std::string beams, first;
      if (next(beams)) { auto b = fields(beams); if (b.size() >= 2) file.beams = {std::atoi(b[0].c_str()), std::atoi(b[1].c_str())}; }
      if (next(first)) { auto f = fields(first); if (!f.empty()) file.crossSection = std::strtod(f[0].c_str(), nullptr); }
    } else if (line.rfind("<event>", 0) == 0 || line.rfind("<event ", 0) == 0) {
      std::string header;
      if (!next(header)) break;
      auto h = fields(header);
      if (h.size() < 6) continue;
      LheEvent e;
      const int n = std::atoi(h[0].c_str());
      e.weight = std::strtod(h[2].c_str(), nullptr);
      e.scale = std::strtod(h[3].c_str(), nullptr);
      for (int k = 0; k < n; ++k) {
        std::string pl;
        if (!next(pl)) break;
        auto p = fields(pl);
        if (p.size() < 11) continue;
        e.particles.push_back({std::atoi(p[0].c_str()), std::atoi(p[1].c_str()), std::atoi(p[2].c_str()), std::atoi(p[3].c_str()),
                               std::atoi(p[4].c_str()), std::atoi(p[5].c_str()), std::strtod(p[6].c_str(), nullptr),
                               std::strtod(p[7].c_str(), nullptr), std::strtod(p[8].c_str(), nullptr),
                               std::strtod(p[9].c_str(), nullptr), std::strtod(p[10].c_str(), nullptr)});
      }
      file.events.push_back(e);
      std::string tag;
      while (next(tag) && tag.rfind("</event", 0) != 0) {}
    }
  }
  return file;
}

bool writeHepMC(const LheFile& file, const std::string& path) {
  std::ostringstream s;
  s << "HepMC::Version 3.02.00\nHepMC::Asciiv3-START_EVENT_LISTING\n";
  for (size_t n = 0; n < file.events.size(); ++n) {
    const auto& e = file.events[n];
    s << "E " << n << " 1 " << e.particles.size() << "\nU GEV MM\nW " << sci(e.weight) << "\n";
    if (n == 0 && file.crossSection) s << "A 0 GenCrossSection " << sci(*file.crossSection) << " " << sci(0) << " -1 -1\n";
    std::string incoming;
    for (size_t k = 0; k < e.particles.size(); ++k)
      if (e.particles[k].status == -1) incoming += (incoming.empty() ? "" : ",") + std::to_string(k + 1);
    s << "V -1 0 [" << incoming << "]\n";
    for (size_t k = 0; k < e.particles.size(); ++k) {
      const auto& p = e.particles[k];
      const int status = p.status == -1 ? 4 : (p.status == 1 ? 1 : 2);
      const int parent = p.status == -1 ? 0 : -1;
      s << "P " << k + 1 << " " << parent << " " << p.pdg << " " << sci(p.px) << " " << sci(p.py) << " " << sci(p.pz)
        << " " << sci(p.e) << " " << sci(p.m) << " " << status << "\n";
    }
  }
  s << "HepMC::Asciiv3-END_EVENT_LISTING\n";
  return writeFile(path, s.str());
}

// ---------------------------------------------------------------------------------------------------------
// The job, and its status

struct Status {
  std::string state = "running", jobID, message, generatorVersion;
  std::optional<double> progress, crossSection, crossSectionError, seconds, started, finished;
  int eventsWritten = 0;
  std::optional<int> number;

  std::string json() const {
    std::ostringstream o;
    o << "{\n  \"state\" : " << jsonString(state) << ",\n  \"jobID\" : " << jsonString(jobID) << ",\n  \"eventsWritten\" : " << eventsWritten;
    if (progress) o << ",\n  \"progress\" : " << num(*progress);
    if (crossSection) o << ",\n  \"crossSection\" : " << num(*crossSection);
    if (crossSectionError) o << ",\n  \"crossSectionError\" : " << num(*crossSectionError);
    if (!message.empty()) o << ",\n  \"message\" : " << jsonString(message);
    if (!generatorVersion.empty()) o << ",\n  \"generatorVersion\" : " << jsonString(generatorVersion);
    if (seconds) o << ",\n  \"seconds\" : " << num(*seconds);
    if (number) o << ",\n  \"number\" : " << *number;
    if (started) o << ",\n  \"started\" : " << num(*started);
    if (finished) o << ",\n  \"finished\" : " << num(*finished);
    o << "\n}\n";
    return o.str();
  }
};

const char* label(const std::string& g) {
  if (g == "pythia8") return "Pythia 8";
  if (g == "herwig7") return "Herwig 7";
  if (g == "sherpa3") return "Sherpa 3";
  if (g == "whizard3") return "WHIZARD 3";
  if (g == "calchep3") return "CalcHEP 3";
  return "sans gerbe";
}

// ---------------------------------------------------------------------------------------------------------
// What the image can run

std::string pythiaDriver() {
  for (const std::string& c : {kPrefix + "/bin/treelevel-pythia", std::string("/usr/local/bin/treelevel-pythia")})
    if (isFile(c)) return c;
  return "";
}
std::string pythiaData() {
  if (const char* env = std::getenv("PYTHIA8DATA")) if (isDir(env)) return env;
  for (const std::string& c : {kPrefix + "/share/Pythia8/xmldoc", kPrefix + "/share/doc/pythia/xmldoc"}) if (isDir(c)) return c;
  return "";
}
std::string whizardPath() {
  for (const std::string& c : {kPrefix + "/bin/whizard", std::string("/usr/local/bin/whizard")}) if (isFile(c)) return c;
  return "";
}
std::string calchepRoot() {
  const std::string root = kPrefix + "/calchep";
  return isFile(root + "/calchep_batch") ? root : "";
}
std::string calchepVersion(const std::string& root) {
  const std::string header = readFile(root + "/include/version.h");
  const size_t a = header.find('"');
  if (a == std::string::npos) return "";
  const size_t b = header.find('"', a + 1);
  return b == std::string::npos ? "" : "CalcHEP " + header.substr(a + 1, b - a - 1);
}

struct Capabilities { std::vector<std::string> generators{"passthrough"}; std::map<std::string, std::string> versions; };

Capabilities capabilities() {
  Capabilities c;
  const std::string driver = pythiaDriver();
  if (!driver.empty()) {
    auto [code, out] = capture({driver, "--version"});
    if (code == 0 && !firstLine(out).empty()) { c.generators.push_back("pythia8"); c.versions["pythia8"] = "Pythia " + firstLine(out); }
  }
  // A broken installation must not be offered, and the major version matters: a Sherpa 2 reads none of the YAML
  // written for a Sherpa 3.
  {
    auto [code, out] = inShell("Herwig --version 2>/dev/null");
    const std::string v = lineNaming(out, "herwig");
    if (code == 0 && lower(v).find("herwig") != std::string::npos && majorVersion(v) == 7) { c.generators.push_back("herwig7"); c.versions["herwig7"] = v; }
  }
  {
    auto [code, out] = inShell("Sherpa --version 2>/dev/null | head -1");
    const std::string v = lineNaming(out, "sherpa");
    if (code == 0 && lower(v).find("sherpa") != std::string::npos && majorVersion(v) == 3) { c.generators.push_back("sherpa3"); c.versions["sherpa3"] = v; }
  }
  const std::string whizard = whizardPath();
  if (!whizard.empty()) {
    auto [code, out] = capture({whizard, "--version"});
    const std::string v = lineNaming(out, "whizard");
    if (code == 0 && lower(v).find("whizard") != std::string::npos && majorVersion(v) == 3) { c.generators.push_back("whizard3"); c.versions["whizard3"] = v; }
  }
  const std::string calchep = calchepRoot();
  if (!calchep.empty()) {
    const std::string v = calchepVersion(calchep);
    if (!v.empty()) { c.generators.push_back("calchep3"); c.versions["calchep3"] = v; }
  }
  return c;
}

std::string capabilitiesJSON(const Capabilities& c) {
  std::ostringstream o;
  o << "{\n  \"protocolVersion\" : " << kProtocolVersion << ",\n  \"engineVersion\" : " << jsonString(kEngineVersion) << ",\n  \"generators\" : [";
  for (size_t i = 0; i < c.generators.size(); ++i) o << (i ? ", " : "") << jsonString(c.generators[i]);
  o << "],\n  \"versions\" : {";
  size_t i = 0;
  for (const auto& kv : c.versions) o << (i++ ? ", " : "") << jsonString(kv.first) << " : " << jsonString(kv.second);
  o << "}";
  // Seul Pythia mène une machine, et il ouvre toutes les familles.
  if (std::find(c.generators.begin(), c.generators.end(), "pythia8") != c.generators.end()) {
    o << ",\n  \"colliderChannels\" : {\"pythia8\" : [";
    const char* all[] = {"singleBoson", "bosonPair", "bosonExchange", "qcd", "photoproduction", "soft",
                         "annihilation", "neutralCurrent", "chargedCurrent", "inclusive"};
    for (size_t k = 0; k < sizeof all / sizeof *all; ++k) o << (k ? ", " : "") << jsonString(all[k]);
    o << "]}";
  }
  o << "\n}\n";
  return o.str();
}

// ---------------------------------------------------------------------------------------------------------
// One job

class Runner {
public:
  Runner(std::string folder, Value job, Value launch, int number)
      : folder_(std::move(folder)), job_(std::move(job)), launch_(std::move(launch)), number_(number) {
    id_ = job_["id"].str();
    generator_ = job_["generator"].str("passthrough");
    input_ = job_["input"].str("events.lhe");
    output_ = job_["output"].str("events.hepmc");
    events_ = int(job_["events"].num(0));
    seed_ = (long long)job_["seed"].num(0) % 900000000LL;
    process_ = jobcard::readProcess(job_["hardProcess"]);
  }

  bool run() {
    Status s = base();
    s.message = "préparation";
    publish(s);
    const bool readsLHE = generator_ == "pythia8" || generator_ == "herwig7" || generator_ == "passthrough";
    if (readsLHE && !process_.collider && !isFile(join(folder_, input_)))
      return failed("the job has no input file (" + input_ + ")");
    // Une machine confiée à un générateur qui n'en mène pas ne rendrait pas une erreur : il calculerait le
    // processus exclusif que nomme l'état final — ici la signature à chercher — et la mesure rendrait le nombre
    // qu'elle devait mesurer. Seul Pythia mène une machine.
    if (process_.collider && generator_ != "pythia8")
      return failed(std::string(label(generator_)) + " does not drive a machine: only Pythia 8 does. Use Pythia 8, or "
                    "switch to the Process source to compute the drawn process with " + label(generator_));
    if (generator_ == "passthrough") return passthrough();
    if (generator_ == "pythia8") return pythia();
    if (generator_ == "herwig7") return herwig();
    if (generator_ == "sherpa3") return sherpa();
    if (generator_ == "whizard3") return whizard();
    if (generator_ == "calchep3") return calchep();
    return failed("unknown generator '" + generator_ + "'");
  }

private:
  std::string folder_, id_, generator_, input_, output_;
  Value job_, launch_;
  int number_ = 1;
  jobcard::Process process_;
  int events_ = 0;
  long long seed_ = 0;
  double start_ = appleNow();

  Status base() const { Status s; s.jobID = id_; s.number = number_; s.started = start_; return s; }

  // How the host launches a generator (launch.json), or nothing inside the image.
  bool hosted(const std::string& g) const { return !launch_[g].isNull(); }
  std::string program(const std::string& g) const { return launch_[g]["program"].str(); }
  std::vector<std::string> arguments(const std::string& g) const {
    std::vector<std::string> out;
    for (const auto& a : launch_[g]["arguments"].items) out.push_back(a.str());
    return out;
  }
  std::map<std::string, std::string> environment(const std::string& g) const {
    std::map<std::string, std::string> out;
    for (const auto& kv : launch_[g]["environment"].members) out[kv.first] = kv.second.str();
    return out;
  }

  /// What a generator wrote, counted, and the job finished with it.
  bool finishFromOutput(const std::string& name, std::optional<std::pair<double, double>> sigma = std::nullopt) {
    Summary sum = summary(join(folder_, output_));
    if (sum.events <= 0) return failed(name + " wrote no event — see engine.log");
    if (sigma) { sum.sigma = sigma->first; sum.error = sigma->second; }
    return finished(sum.events, sum.sigma, sum.error, name);
  }
  void publish(const Status& s) { writeFile(join(folder_, "status.json"), s.json()); }
  void log(const std::string& line) {
    std::ofstream out(join(folder_, "engine.log"), std::ios::app | std::ios::binary);
    out << line << "\n";
  }

  bool failed(const std::string& message) {
    Status s = base();
    s.state = "failed";
    s.message = message;
    s.finished = appleNow();
    s.seconds = *s.finished - start_;
    publish(s);
    std::cerr << "treelevel-tools: " << message << std::endl;
    return false;
  }

  bool finished(int written, std::optional<double> sigma, std::optional<double> error, const std::string& version) {
    Status s = base();
    s.state = "finished";
    s.eventsWritten = written;
    s.crossSection = sigma;
    s.crossSectionError = error;
    s.generatorVersion = version;
    s.progress = 1;
    s.finished = appleNow();
    s.seconds = *s.finished - start_;
    publish(s);
    return true;
  }

  /// Runs a generator in the job folder, following its output into engine.log and status.json.
  bool runGenerator(const std::vector<std::string>& argv, const std::string& name, const std::string& step, bool finishNow,
                    std::map<std::string, std::string> env = {}, const std::string& cwd = "",
                    std::function<std::optional<std::pair<double, double>>(const std::string&)> crossSection = nullptr) {
    env["TREELEVEL_JOB"] = id_;
    Status s = base();
    s.generatorVersion = name;
    s.message = step.empty() ? "génération" : step;
    publish(s);
    std::ofstream logFile(join(folder_, "engine.log"), std::ios::app | std::ios::binary);
    std::string printed;
    const int code = runProcess(argv, cwd.empty() ? folder_ : cwd, env, [&](const std::string& line) {
      logFile << line << "\n";
      logFile.flush();
      if (crossSection) printed += line + "\n";
      if (auto n = eventCount(line)) {
        Status p = s;
        p.eventsWritten = *n;
        if (events_ > 0) p.progress = std::min(1.0, double(*n) / events_);
        publish(p);
      }
    });
    logFile.close();
    if (code != 0) return failed(name + " stopped with code " + std::to_string(code) + " — see engine.log");
    if (!finishNow) return true;
    Summary sum = summary(join(folder_, output_));
    if (sum.events <= 0) return failed(name + " wrote no event — see engine.log");
    if (crossSection) if (auto read = crossSection(printed)) { sum.sigma = read->first; sum.error = read->second; }
    return finished(sum.events, sum.sigma, sum.error, name);
  }

  std::string version(const std::string& key, const std::string& fallback) {
    const std::string told = launch_[key]["version"].str();
    if (!told.empty()) return told;
    auto c = capabilities();
    auto it = c.versions.find(key);
    return it == c.versions.end() ? fallback : it->second;
  }

  // Backends

  bool passthrough() {
    LheFile f = readLesHouches(join(folder_, input_));
    if (!writeHepMC(f, join(folder_, output_))) return failed("cannot write " + output_);
    return finished(int(f.events.size()), f.crossSection, std::nullopt,
                    std::string("TreeLevel Tools ") + kEngineVersion + " (sans gerbe)");
  }

  /// Habiller les événements de TreeLevel n'a de sens qu'entre deux leptons (voir l'hôte du Mac).
  std::string dressingObjection() {
    if (process_.collider) return "";
    const auto beams = readLesHouchesBeams();
    if (beams.size() != 2) return "";
    auto lepton = [](int id) { int a = std::abs(id); return a >= 11 && a <= 16; };
    if (lepton(beams[0]) && lepton(beams[1])) return "";
    auto coloured = [](int id) { int a = std::abs(id); return (a >= 1 && a <= 6) || a == 21; };
    if (coloured(beams[0]) || coloured(beams[1]))
      return "the beams are free quarks or gluons: without beam remnants their colour closes on nothing, and no generator "
             "can shower or hadronise these events — keep them at parton level, or collide hadrons in machine mode";
    return std::string("only collisions of leptons can be dressed: ") + label(generator_) + " gives any other beam a "
           "structure — partons to a hadron, a hadronic part to a photon — which these events, made of whole "
           "particles, do not have. Keep them at parton level, or use the machine mode";
  }
  std::vector<int> readLesHouchesBeams() {
    std::ifstream in(join(folder_, input_));
    std::string line;
    while (std::getline(in, line)) {
      if (line.find("<init") == std::string::npos) continue;
      if (!std::getline(in, line)) break;
      std::istringstream f(line);
      int a = 0, b = 0;
      if (f >> a >> b) return {a, b};
      break;
    }
    return {};
  }

  bool pythia() {
    const std::string driver = hosted("pythia8") ? program("pythia8") : pythiaDriver();
    if (driver.empty()) return failed("the Pythia 8 driver is missing from this image");
    const std::string no = dressingObjection();
    if (!no.empty()) return failed(no);
    jobcard::Process p = jobcard::expanded(process_);
    const std::string objection = jobcard::objection(p);
    if (!objection.empty()) return failed(objection);
    std::map<std::string, std::string> env = environment("pythia8");
    if (!env.count("PYTHIA8DATA") && !pythiaData().empty()) env["PYTHIA8DATA"] = pythiaData();
    const std::string name = version("pythia8", "Pythia 8");
    if (p.collider && p.mix && p.has("photoproduction") && p.channels.size() > 1) return pythiaMixed(driver, env, name);
    return runGenerator({driver, "--job", "job.json", "--out", output_}, name, "", true, env);
  }

  /// Les faisceaux tels quels, puis leur flux de photons, réunis dans la proportion de leurs sections efficaces.
  bool pythiaMixed(const std::string& driver, const std::map<std::string, std::string>& env, const std::string& name) {
    const std::string a = "events.beams.hepmc", b = "events.photons.hepmc";
    if (!runGenerator({driver, "--job", "job.json", "--part", "beams", "--seed-offset", "0", "--out", a}, name, "faisceaux", false, env)) return false;
    if (!runGenerator({driver, "--job", "job.json", "--part", "photons", "--seed-offset", "1", "--out", b}, name, "flux de photons", false, env)) return false;
    Summary sa = summary(join(folder_, a)), sb = summary(join(folder_, b));
    if (sa.events <= 0 || sb.events <= 0 || !sa.sigma || !sb.sigma || *sa.sigma + *sb.sigma <= 0)
      return failed("one of the two configurations produced nothing — see engine.log");
    const bool equal = job_["hardProcess"]["mixEqualShares"].flag(false);
    const int written = merge(join(folder_, a), join(folder_, b), join(folder_, output_), events_, *sa.sigma, *sb.sigma,
                              sa.error.value_or(0), sb.error.value_or(0), equal);
    if (written <= 0) return failed("the two samples could not be put together");
    std::remove(join(folder_, a).c_str());
    std::remove(join(folder_, b).c_str());
    const double ea = sa.error.value_or(0), eb = sb.error.value_or(0);
    return finished(written, *sa.sigma + *sb.sigma, std::sqrt(ea * ea + eb * eb), name);
  }

  static std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> split(const std::string& path) {
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> events;
    std::ifstream in(path);
    std::string line;
    while (std::getline(in, line)) {
      while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
      if (line.find("END_EVENT_LISTING") != std::string::npos) break;
      if (line.rfind("E ", 0) == 0) events.emplace_back();
      if (!events.empty()) events.back().push_back(line); else header.push_back(line);
    }
    return {header, events};
  }

  /// Deux échantillons HepMC3 réunis : de chacun la part que sa section efficace lui vaut (ou la moitié, à parts
  /// égales, la proportion passant alors dans les poids), pris à tour de rôle pour qu'ils se lisent comme un seul.
  static int merge(const std::string& a, const std::string& b, const std::string& out, int wanted, double sigmaA,
                   double sigmaB, double errorA, double errorB, bool equalShares) {
    auto [header, eventsA] = split(a);
    auto eventsB = split(b).second;
    if (eventsA.empty() || eventsB.empty()) return 0;
    const double total = sigmaA + sigmaB;
    int fromA, fromB;
    if (equalShares) {
      fromA = std::min(wanted / 2, int(eventsA.size()));
      fromB = std::min(wanted - fromA, int(eventsB.size()));
    } else {
      fromA = std::clamp(int(std::floor(wanted * sigmaA / total + 0.5)), 0, int(eventsA.size()));
      fromB = std::clamp(wanted - fromA, 0, int(eventsB.size()));
    }
    if (fromA + fromB == 0) return 0;
    const double weightA = fromA > 0 ? sigmaA / fromA * (fromA + fromB) / total : 1;
    const double weightB = fromB > 0 ? sigmaB / fromB * (fromA + fromB) / total : 1;
    const std::string attribute = "A 0 GenCrossSection " + sci(total) + " " + sci(std::sqrt(errorA * errorA + errorB * errorB)) + " -1 -1";
    std::ostringstream o;
    for (const auto& l : header) o << l << "\n";
    int takenA = 0, takenB = 0, n = 0;
    while (takenA < fromA || takenB < fromB) {
      const bool takeA = takenA < fromA && (takenB >= fromB || fromA == 0 || fromB == 0 || double(takenA) / fromA <= double(takenB) / fromB);
      const double weight = takeA ? weightA : weightB;
      for (const auto& line : takeA ? eventsA[takenA++] : eventsB[takenB++]) {
        if (line.rfind("E ", 0) == 0) {
          std::istringstream f(line);
          std::string e, num0, v, p;
          if (f >> e >> num0 >> v >> p) { o << "E " << n << " " << v << " " << p << "\n"; continue; }
        }
        if (line.rfind("W ", 0) == 0) { o << "W " << sci(weight) << "\n"; continue; }
        if (line.rfind("A 0 GenCrossSection", 0) == 0) { o << attribute << "\n"; continue; }
        o << line << "\n";
      }
      n += 1;
    }
    o << "HepMC::Asciiv3-END_EVENT_LISTING\n";
    return writeFile(out, o.str()) ? n : 0;
  }

  bool herwig() {
    const std::string no = dressingObjection();
    if (!no.empty()) return failed(no);
    const bool shower = job_["shower"].flag(true), hadronisation = job_["hadronisation"].flag(true), decays = job_["decays"].flag(true);
    std::ostringstream in;
    in << "read snippets/EPCollider.in\n"
       << "cd /Herwig/EventHandlers\n"
       << "library LesHouches.so\n"
       << "create ThePEG::LesHouchesFileReader LesHouchesReader\n"
       << "set LesHouchesReader:FileName " << input_ << "\n"
       << "set LesHouchesReader:CacheFileName cache.tmp\n"
       << "set LesHouchesReader:MaxScan 5\n"
       << "create ThePEG::Cuts NoCuts\n"
       << "set LesHouchesReader:Cuts NoCuts\n"
       << "create ThePEG::LesHouchesEventHandler LesHouchesHandler\n"
       << "insert LesHouchesHandler:LesHouchesReaders 0 LesHouchesReader\n"
       << "set LesHouchesHandler:PartonExtractor /Herwig/Partons/EEExtractor\n"
       << "set LesHouchesHandler:CascadeHandler " << (shower ? "/Herwig/Shower/ShowerHandler" : "NULL") << "\n"
       << "set LesHouchesHandler:HadronizationHandler " << (hadronisation ? "/Herwig/Hadronization/ClusterHadHandler" : "NULL") << "\n"
       << "set LesHouchesHandler:DecayHandler " << (decays ? "/Herwig/Decays/DecayHandler" : "NULL") << "\n"
       << "set LesHouchesHandler:WeightOption VarNegWeight\n"
       << "cd /Herwig/Generators\n"
       << "set EventGenerator:EventHandler /Herwig/EventHandlers/LesHouchesHandler\n"
       << "set EventGenerator:NumberOfEvents " << events_ << "\n"
       << "set EventGenerator:RandomNumberGenerator:Seed " << seed_ << "\n"
       << "set EventGenerator:PrintEvent 0\n"
       << "set EventGenerator:MaxErrors 10000\n"
       << "insert EventGenerator:AnalysisHandlers 0 /Herwig/Analysis/HepMCFile\n"
       << "set /Herwig/Analysis/HepMCFile:PrintEvent " << events_ << "\n"
       << "set /Herwig/Analysis/HepMCFile:Format GenEvent\n"
       << "set /Herwig/Analysis/HepMCFile:Units GeV_mm\n"
       << "set /Herwig/Analysis/HepMCFile:Filename " << output_ << "\n";
    const std::string extra = job_["extraSettings"].str();
    if (!extra.empty()) in << extra << "\n";
    in << "saverun job EventGenerator\n";
    writeFile(join(folder_, "job.in"), in.str());
    const std::string name = version("herwig7", "Herwig 7");
    if (hosted("herwig7")) {
      // Le module du Mac : son dépôt reconstruit à sa place et ses chemins de recherche, donnés par l'hôte.
      std::vector<std::string> read = {program("herwig7"), "read", "job.in"}, runArgs = {program("herwig7"), "run", "job.run", "-N", std::to_string(events_)};
      for (const auto& a : arguments("herwig7")) { read.push_back(a); runArgs.push_back(a); }
      if (!runGenerator(read, name, "lecture de la configuration", false, environment("herwig7"))) return false;
      return runGenerator(runArgs, name, "", true, environment("herwig7"));
    }
    const std::string here = quote(folder_);
    if (!runGenerator({"/bin/bash", "-lc", "cd " + here + " && Herwig read job.in"}, name, "lecture de la configuration", false)) return false;
    return runGenerator({"/bin/bash", "-lc", "cd " + here + " && Herwig run job.run -N " + std::to_string(events_)}, name, "", true);
  }

  bool needsProcess(const std::string& who) {
    if (process_.beams.size() == 2 && process_.energies.size() == 2 && !job_["hardProcess"]["finalState"].items.empty()) return true;
    failed(who + " computes the process itself and needs its description (beams, energies, final state)");
    return false;
  }
  std::vector<int> finalState() {
    std::vector<int> out;
    for (const auto& f : job_["hardProcess"]["finalState"].items) out.push_back(int(f.num()));
    return out;
  }
  std::optional<double> minimumPT() {
    const auto& v = job_["hardProcess"]["minimumPT"];
    if (v.isNull()) return std::nullopt;
    return v.num();
  }

  bool sherpa() {
    if (!needsProcess("Sherpa")) return false;
    const auto& p = process_;
    const auto fs = finalState();
    std::string orders;
    const auto& co = job_["hardProcess"]["couplingOrders"];
    if (!co.members.empty()) {
      auto members = co.members;
      std::sort(members.begin(), members.end(), [](auto& x, auto& y) { return x.first < y.first; });
      orders = "\n    Order: {";
      for (size_t i = 0; i < members.size(); ++i) orders += (i ? ", " : "") + members[i].first + ": " + std::to_string(int(members[i].second.num()));
      orders += "}";
    }
    std::string outgoing;
    for (size_t i = 0; i < fs.size(); ++i) outgoing += (i ? " " : "") + std::to_string(fs[i]);
    std::ostringstream c;
    c << "BEAMS: [" << p.beams[0] << ", " << p.beams[1] << "]\n"
      << "BEAM_ENERGIES: [" << num(p.energies[0]) << ", " << num(p.energies[1]) << "]\n"
      << "EVENTS: " << events_ << "\n"
      << "RANDOM_SEED: " << seed_ << "\n"
      << "PROCESSES:\n"
      << "- " << p.beams[0] << " " << p.beams[1] << " -> " << outgoing << ":" << orders << "\n"
      << "SHOWER_GENERATOR: " << (job_["shower"].flag(true) ? "CSS" : "None") << "\n"
      << "FRAGMENTATION: " << (job_["hadronisation"].flag(true) ? "Ahadic" : "None") << "\n"
      << "MI_HANDLER: " << (job_["multipleInteractions"].flag(false) ? "Amisic" : "None") << "\n"
      << "HARD_DECAYS: {Enabled: " << (job_["decays"].flag(true) ? "true" : "false") << "}\n"
      << "EVENT_OUTPUT: HepMC3[" << stem(output_) << "]\n";
    // Sherpa donne d'office aux leptons leur rayonnement initial de QED ; les autres générateurs calculent à
    // énergie fixe, on l'aligne. Les faisceaux hadroniques, eux, ne sont rien sans leurs densités.
    if (!(std::abs(p.beams[0]) > 100 && std::abs(p.beams[1]) > 100)) c << "PDF_LIBRARY: None\n";
    if (auto pt = minimumPT()) c << "SELECTORS:\n- [PT, " << fs[0] << ", " << num(*pt) << ", E_CMS]\n";
    const std::string extra = job_["extraSettings"].str();
    if (!extra.empty()) c << extra << "\n";
    writeFile(join(folder_, "Sherpa.yaml"), c.str());
    const std::string name = version("sherpa3", "Sherpa 3");
    const std::string s = stem(output_);
    if (hosted("sherpa3")) {
      std::vector<std::string> argv = {program("sherpa3"), "-f", "Sherpa.yaml"};
      for (const auto& a : arguments("sherpa3")) argv.push_back(a);
      if (!runGenerator(argv, name, "", false, environment("sherpa3"))) return false;
      // Sherpa 3.0.5 n'ajoute rien au nom de EVENT_OUTPUT ; d'autres ajoutent .hepmc3 ou .hepmc.gz.
      const std::string target = join(folder_, s + ".hepmc");
      if (!isFile(target)) {
        if (isFile(join(folder_, s + ".hepmc3"))) std::rename(join(folder_, s + ".hepmc3").c_str(), target.c_str());
        else if (isFile(join(folder_, s + ".hepmc.gz"))) inShell("gunzip -f " + quote(join(folder_, s + ".hepmc.gz")));
        else if (isFile(join(folder_, s))) std::rename(join(folder_, s).c_str(), target.c_str());
      }
      return finishFromOutput(name);
    }
    // Sherpa 3.0.5 n'ajoute rien au nom de EVENT_OUTPUT ; d'autres ajoutent .hepmc, .hepmc3 ou .hepmc.gz.
    const std::string cmd = "cd " + quote(folder_) + " && Sherpa -f Sherpa.yaml && (test -f " + s + ".hepmc || (test -f " + s +
                            ".hepmc3 && mv " + s + ".hepmc3 " + s + ".hepmc) || (test -f " + s + ".hepmc.gz && gunzip -f " + s +
                            ".hepmc.gz) || (test -f " + s + " && mv " + s + " " + s + ".hepmc))";
    return runGenerator({"/bin/bash", "-lc", cmd}, name, "", true);
  }

  static std::string sindarin(int code) {
    static const std::map<int, std::pair<const char*, const char*>> names = {
        {1, {"d", "D"}}, {2, {"u", "U"}}, {3, {"s", "S"}}, {4, {"c", "C"}}, {5, {"b", "B"}}, {6, {"t", "T"}},
        {11, {"e1", "E1"}}, {12, {"n1", "N1"}}, {13, {"e2", "E2"}}, {14, {"n2", "N2"}}, {15, {"e3", "E3"}}, {16, {"n3", "N3"}},
        {21, {"gl", "gl"}}, {22, {"A", "A"}}, {23, {"Z", "Z"}}, {24, {"Wp", "Wm"}}, {25, {"H", "H"}}};
    auto it = names.find(std::abs(code));
    return it == names.end() ? "" : (code >= 0 ? it->second.first : it->second.second);
  }

  static std::optional<std::pair<double, double>> whizardCrossSection(const std::string& log) {
    std::optional<std::pair<double, double>> result;
    std::istringstream in(log);
    std::string line;
    while (std::getline(in, line)) {
      std::istringstream f(line);
      std::vector<std::string> w;
      std::string t;
      while (f >> t) w.push_back(t);
      if (w.size() < 4) continue;
      auto integer = [](const std::string& s) { return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit); };
      if (!integer(w[0]) || !integer(w[1]) || w[2].find('E') == std::string::npos) continue;
      char* end = nullptr;
      const double value = std::strtod(w[2].c_str(), &end);
      if (*end) continue;
      const double error = std::strtod(w[3].c_str(), &end);
      if (*end || value <= 0) continue;
      result = std::make_pair(value / 1000, error / 1000);              // fb → pb
    }
    return result;
  }

  bool whizard() {
    if (!needsProcess("WHIZARD")) return false;
    const std::string exe = hosted("whizard3") ? program("whizard3") : whizardPath();
    if (exe.empty()) return failed("WHIZARD 3 is not installed in this image");
    // Sur le Mac, WHIZARD s'arrête en fermant son HepMC3 (sa colle C++ et la HepMC3 livrée avec lui ne partagent
    // pas la même bibliothèque standard) : l'hôte lui fait écrire du Les Houches, que l'on convertit.
    const bool lhef = launch_["whizard3"]["sampleFormat"].str() == "lhef";
    const auto& p = process_;
    std::vector<std::string> names;
    std::vector<int> codes = {p.beams[0], p.beams[1]};
    for (int f : finalState()) codes.push_back(f);
    for (int code : codes) {
      const std::string n = sindarin(code);
      if (n.empty()) return failed("WHIZARD does not know the particle " + std::to_string(code));
      names.push_back(n);
    }
    std::string outgoing;
    for (size_t i = 2; i < names.size(); ++i) outgoing += (i > 2 ? ", " : "") + names[i];
    const bool shower = job_["shower"].flag(true);
    const bool hadronBeams = std::abs(p.beams[0]) > 100 && std::abs(p.beams[1]) > 100;
    std::ostringstream s;
    s << "model = SM\n"
      << "process job = " << names[0] << ", " << names[1] << " => " << outgoing << "\n"
      << "sqrts = " << num(p.sqrtS()) << " GeV\n"
      << "seed = " << seed_ << "\n";
    if (auto pt = minimumPT()) s << "cuts = all Pt > " << num(*pt) << " GeV [final]\n";
    s << "?ps_fsr_active = " << (shower ? "true" : "false") << "\n"
      << "?ps_isr_active = " << (shower && hadronBeams ? "true" : "false") << "\n"
      << "?hadronization_active = " << (job_["hadronisation"].flag(true) ? "true" : "false") << "\n"
      << "$hadronization_method = \"PYTHIA6\"\n"
      << "n_events = " << events_ << "\n"
      << "$sample = \"" << stem(output_) << "\"\n"
      << "sample_format = " << (lhef ? "lhef" : "hepmc") << "\n";
    const std::string extra = job_["extraSettings"].str();
    if (!extra.empty()) s << extra << "\n";
    s << "simulate (job)\n";
    writeFile(join(folder_, "job.sin"), s.str());
    const std::string name = version("whizard3", "WHIZARD 3");
    if (!lhef) return runGenerator({exe, "job.sin"}, name, "", true, environment("whizard3"), "", whizardCrossSection);
    if (!runGenerator({exe, "job.sin"}, name, "", false, environment("whizard3"))) return false;
    const std::string lhe = join(folder_, stem(output_) + ".lhe");
    if (!isFile(lhe)) return failed(name + " wrote no event file — see engine.log");
    LheFile f = readLesHouches(lhe);
    // La section efficace du journal porte son erreur d'intégration ; celle du fichier n'en a pas.
    auto fromLog = whizardCrossSection(readFile(join(folder_, "engine.log")));
    if (fromLog) f.crossSection = fromLog->first;
    if (!writeHepMC(f, join(folder_, output_))) return failed("cannot write " + output_);
    return finished(int(f.events.size()), f.crossSection, fromLog ? std::optional<double>(fromLog->second) : std::nullopt, name);
  }

  static std::string calchepName(int code) {
    static const std::map<int, std::pair<const char*, const char*>> names = {
        {1, {"d", "D"}}, {2, {"u", "U"}}, {3, {"s", "S"}}, {4, {"c", "C"}}, {5, {"b", "B"}}, {6, {"t", "T"}},
        {11, {"e", "E"}}, {12, {"ne", "Ne"}}, {13, {"m", "M"}}, {14, {"nm", "Nm"}}, {15, {"l", "L"}}, {16, {"nl", "Nl"}},
        {21, {"G", "G"}}, {22, {"A", "A"}}, {23, {"Z", "Z"}}, {24, {"W+", "W-"}}, {25, {"h", "h"}}};
    auto it = names.find(std::abs(code));
    return it == names.end() ? "" : (code >= 0 ? it->second.first : it->second.second);
  }

  bool calchep() {
    if (!needsProcess("CalcHEP")) return false;
    // Sur le Mac, l'hôte donne une copie du module et un dossier de travail sans espace : les Makefiles que
    // CalcHEP engendre n'en supportent aucune, et le dossier d'un travail en porte deux.
    const std::string root = hosted("calchep3") ? launch_["calchep3"]["root"].str() : calchepRoot();
    if (root.empty()) return failed("CalcHEP 3 is not installed in this image");
    const auto& p = process_;
    std::vector<std::string> names;
    std::vector<int> codes = {p.beams[0], p.beams[1]};
    for (int f : finalState()) codes.push_back(f);
    for (int code : codes) {
      const std::string n = calchepName(code);
      if (n.empty()) return failed("CalcHEP does not know the particle " + std::to_string(code));
      names.push_back(n);
    }
    std::string outgoing;
    for (size_t i = 2; i < names.size(); ++i) outgoing += (i > 2 ? "," : "") + names[i];
    const std::string told = launch_["calchep3"]["workDirectory"].str();
    const std::string work = told.empty() ? join(folder_, "calchep") : told;
    capture({"/bin/rm", "-rf", work});
    capture({"/bin/mkdir", "-p", work.substr(0, work.find_last_of('/'))});
    if (!runGenerator({join(root, "mkWORKdir"), work}, "CalcHEP", "préparation du dossier de travail", false)) return false;
    std::remove(join(work, "lock.batch").c_str());
    std::ostringstream b;
    b << "Model:         SM\nModel changed: False\nGauge:         Feynman\n\n"
      << "Process:   " << names[0] << "," << names[1] << "->" << outgoing << "\n\n"
      << "p1:        " << num(p.energies[0]) << "\n"
      << "p2:        " << num(p.energies[1]) << "\n";
    if (auto pt = minimumPT())
      b << "Cut parameter:    T(" << names[2] << ")\nCut invert:       False\nCut min:          " << num(*pt) << "\nCut max:\n";
    const std::string extra = job_["extraSettings"].str();
    if (!extra.empty()) b << extra << "\n";
    b << "Number of events (per run step):  " << events_ << "\n"
      << "Filename:                         events\nNTuple:                           False\n"
      << "Cleanup:                          False\nParallelization method:           local\n"
      << "Max number of nodes:              4\nMax number of processes per node: 1\n";
    writeFile(join(work, "batch_file"), b.str());
    std::string name = calchepVersion(root);
    if (name.empty()) name = "CalcHEP 3";
    const bool elsewhere = !told.empty();
    // Le dossier de travail est ailleurs : on ramène le compte rendu tant qu'il existe, sinon une panne ne
    // laisserait rien à lire.
    auto bringBack = [&]() {
      if (!elsewhere) return;
      const std::string back = join(folder_, "calchep");
      capture({"/bin/rm", "-rf", back});
      capture({"/bin/mkdir", "-p", back});
      for (const char* n : {"batch_file", "html", "Processes"})
        if (exists(join(work, n))) capture({"/bin/cp", "-R", join(work, n), back + "/"});
    };
    if (!runGenerator({join(work, "calchep_batch"), "batch_file"}, name, "", false, environment("calchep3"), work)) { bringBack(); return false; }
    bringBack();
    // CalcHEP gzippe son fichier Les Houches : on le déballe, puis on le convertit comme le fait le passage sans gerbe.
    const std::string packed = join(work, "batch_results/events-single.lhe.gz");
    if (!isFile(packed)) return failed(name + " wrote no event file — see engine.log");
    const std::string lhe = join(folder_, "events.lhe");
    auto [code, out] = inShell("gzip -dc " + quote(packed) + " > " + quote(lhe));
    if (code != 0) return failed("cannot unpack " + packed + ": " + firstLine(out));
    LheFile f = readLesHouches(lhe);
    if (!writeHepMC(f, join(folder_, output_))) return failed("cannot write " + output_);
    return finished(int(f.events.size()), f.crossSection, std::nullopt, name + " (niveau partonique)");
  }
};

}  // namespace

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "usage: treelevel-tools <command>\n"
                 "  run <job folder>            run the job written by TreeLevel (job.json, events.lhe)\n"
                 "  capabilities [--out file]   list the generators this installation can run, as JSON\n"
                 "  version\n";
    return 2;
  }
  const std::string command = argv[1];
  if (command == "version") { std::cout << "TreeLevel Tools " << kEngineVersion << std::endl; return 0; }
  if (command == "capabilities") {
    const std::string json = capabilitiesJSON(capabilities());
    for (int i = 2; i + 1 < argc; ++i)
      if (std::string(argv[i]) == "--out") { writeFile(argv[i + 1], json); return 0; }
    std::cout << json;
    return 0;
  }
  if (command == "run") {
    if (argc < 3) { std::cerr << "treelevel-tools: run needs the job folder" << std::endl; return 1; }
    std::string folder = argv[2];
    Value launch;
    int number = 1;
    for (int i = 3; i + 1 < argc; ++i) {
      const std::string a = argv[i];
      if (a == "--number") number = std::atoi(argv[i + 1]);
      if (a == "--launch") {
        std::string error;
        const std::string text = readFile(argv[i + 1]);
        if (text.empty() || !jobcard::Parser(text).parse(launch, error)) {
          std::cerr << "treelevel-tools: cannot read " << argv[i + 1] << (error.empty() ? "" : ": " + error) << std::endl;
          return 1;
        }
      }
    }
    if (folder.size() > 1 && (folder.back() == '/' || folder.back() == '\\')) folder.pop_back();
    const std::string text = readFile(join(folder, "job.json"));
    Value job;
    std::string error;
    if (text.empty() || !jobcard::Parser(text).parse(job, error)) {
      std::cerr << "treelevel-tools: cannot read " << join(folder, "job.json") << (error.empty() ? "" : ": " + error) << std::endl;
      return 1;
    }
    if (int(job["protocolVersion"].num(kProtocolVersion)) > kProtocolVersion) {
      Status s;
      s.state = "failed";
      s.jobID = job["id"].str();
      s.message = "This job needs a newer engine (protocol " + std::to_string(int(job["protocolVersion"].num())) + ").";
      writeFile(join(folder, "status.json"), s.json());
      return 1;
    }
    return Runner(folder, job, launch, number).run() ? 0 : 1;
  }
  std::cerr << "treelevel-tools: unknown command '" << command << "'" << std::endl;
  return 1;
}
