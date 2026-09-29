// TreeLevel Tools — the Pythia card, built from the job itself.
//
// The Mac and Windows hosts used to write the Pythia command file each in its own language, and the two had
// to be kept in step by hand; that is where most of the back-and-forth between them went. The driver now
// reads job.json and writes the card once, for the Mac, for Windows and for the Linux image alike.
//
// Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later (Pythia 8 is GPL).

#pragma once
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

namespace jobcard {

// ---------------------------------------------------------------------------------------------------------
// A small JSON reader: what job.json holds (objects, arrays, strings, numbers, booleans, null), no more.

struct Value {
  enum Kind { Null, Bool, Number, String, Array, Object } kind = Null;
  bool boolean = false;
  double number = 0;
  std::string text;
  std::vector<Value> items;
  std::vector<std::pair<std::string, Value>> members;

  const Value& operator[](const std::string& key) const {
    static const Value none;
    for (const auto& m : members) if (m.first == key) return m.second;
    return none;
  }
  bool isNull() const { return kind == Null; }
  double num(double fallback = 0) const { return kind == Number ? number : fallback; }
  bool flag(bool fallback = false) const { return kind == Bool ? boolean : fallback; }
  std::string str(const std::string& fallback = "") const { return kind == String ? text : fallback; }
};

class Parser {
public:
  explicit Parser(const std::string& s) : s_(s) {}
  bool parse(Value& out, std::string& error) {
    try {
      out = value();
      space();
      if (i_ != s_.size()) throw std::string("trailing characters");
      return true;
    } catch (const std::string& e) {
      error = "job.json: " + e + " at offset " + std::to_string(i_);
      return false;
    }
  }

private:
  const std::string& s_;
  size_t i_ = 0;

  void space() { while (i_ < s_.size() && (s_[i_] == ' ' || s_[i_] == '\n' || s_[i_] == '\r' || s_[i_] == '\t')) ++i_; }
  char peek() { space(); if (i_ >= s_.size()) throw std::string("unexpected end"); return s_[i_]; }
  void expect(char c) { if (peek() != c) throw std::string("expected '") + c + "'"; ++i_; }
  bool word(const char* w) {
    size_t n = std::char_traits<char>::length(w);
    if (s_.compare(i_, n, w) == 0) { i_ += n; return true; }
    return false;
  }

  Value value() {
    Value v;
    char c = peek();
    if (c == '{') {
      v.kind = Value::Object; ++i_;
      if (peek() == '}') { ++i_; return v; }
      for (;;) {
        std::string key = string();
        expect(':');
        v.members.emplace_back(key, value());
        if (peek() == ',') { ++i_; continue; }
        expect('}');
        return v;
      }
    }
    if (c == '[') {
      v.kind = Value::Array; ++i_;
      if (peek() == ']') { ++i_; return v; }
      for (;;) {
        v.items.push_back(value());
        if (peek() == ',') { ++i_; continue; }
        expect(']');
        return v;
      }
    }
    if (c == '"') { v.kind = Value::String; v.text = string(); return v; }
    if (word("true")) { v.kind = Value::Bool; v.boolean = true; return v; }
    if (word("false")) { v.kind = Value::Bool; v.boolean = false; return v; }
    if (word("null")) return v;
    const char* start = s_.c_str() + i_;
    char* end = nullptr;
    v.number = std::strtod(start, &end);
    if (end == start) throw std::string("unexpected character");
    i_ += end - start;
    v.kind = Value::Number;
    return v;
  }

  static void utf8(std::string& out, unsigned code) {
    if (code < 0x80) out += char(code);
    else if (code < 0x800) { out += char(0xC0 | (code >> 6)); out += char(0x80 | (code & 0x3F)); }
    else if (code < 0x10000) { out += char(0xE0 | (code >> 12)); out += char(0x80 | ((code >> 6) & 0x3F)); out += char(0x80 | (code & 0x3F)); }
    else { out += char(0xF0 | (code >> 18)); out += char(0x80 | ((code >> 12) & 0x3F)); out += char(0x80 | ((code >> 6) & 0x3F)); out += char(0x80 | (code & 0x3F)); }
  }
  unsigned hex4() {
    if (i_ + 4 > s_.size()) throw std::string("short \\u escape");
    unsigned v = std::stoul(s_.substr(i_, 4), nullptr, 16);
    i_ += 4;
    return v;
  }
  std::string string() {
    expect('"');
    std::string out;
    while (i_ < s_.size() && s_[i_] != '"') {
      char c = s_[i_++];
      if (c != '\\') { out += c; continue; }
      if (i_ >= s_.size()) break;
      char e = s_[i_++];
      switch (e) {
        case 'n': out += '\n'; break;
        case 't': out += '\t'; break;
        case 'r': out += '\r'; break;
        case 'b': out += '\b'; break;
        case 'f': out += '\f'; break;
        case 'u': {
          unsigned code = hex4();
          if (code >= 0xD800 && code < 0xDC00 && i_ + 6 <= s_.size() && s_[i_] == '\\' && s_[i_ + 1] == 'u') {
            i_ += 2;
            unsigned low = hex4();
            code = 0x10000 + ((code - 0xD800) << 10) + (low - 0xDC00);
          }
          utf8(out, code);
          break;
        }
        default: out += e;                              // \" \\ \/
      }
    }
    if (i_ >= s_.size()) throw std::string("unterminated string");
    ++i_;
    return out;
  }
};

// ---------------------------------------------------------------------------------------------------------
// The card.

inline std::string number(double x) {
  char b[40];
  std::snprintf(b, sizeof b, "%.15g", x);
  return b;
}

inline bool isLepton(int id) { int a = std::abs(id); return a >= 11 && a <= 16; }
inline bool isHadron(int id) { return std::abs(id) >= 100; }

/// A process, with the fields the card needs.
struct Process {
  bool collider = false, fixedTarget = false, mix = false;
  std::vector<int> beams;
  std::vector<double> energies;
  std::vector<std::string> channels;
  double minimumPT = 0, minimumQ2 = 0;
  bool hasQ2 = false;

  bool has(const std::string& c) const { for (const auto& x : channels) if (x == c) return true; return false; }
  double sqrtS() const { double s = 0; for (double e : energies) s += e; return s; }
};

inline Process readProcess(const Value& h) {
  Process p;
  if (h.isNull()) return p;
  p.collider = h["colliderMode"].str() == "collider";
  p.fixedTarget = h["fixedTarget"].flag();
  p.mix = h["mixConfigurations"].flag();
  for (const auto& b : h["beams"].items) p.beams.push_back(int(b.num()));
  for (const auto& e : h["beamEnergies"].items) p.energies.push_back(e.num());
  for (const auto& c : h["channels"].items) p.channels.push_back(c.str());
  if (h["channels"].isNull()) p.channels = {"singleBoson"};
  p.minimumPT = h["minimumPT"].num(0);
  if (!h["minimumQ2"].isNull()) { p.minimumQ2 = h["minimumQ2"].num(0); p.hasQ2 = true; }
  return p;
}

/// What a detector sees: ten degrees of deflection on a lepton ring (Q² = s (1 − cos θ) / 2), 4 GeV² on an
/// electron–proton ring, (20 GeV)² between two hadrons.
inline double defaultQ2(const Process& p) {
  bool allLeptons = p.beams.size() == 2 && isLepton(p.beams[0]) && isLepton(p.beams[1]);
  bool anyLepton = p.beams.size() == 2 && (isLepton(p.beams[0]) || isLepton(p.beams[1]));
  if (allLeptons) { double s = p.sqrtS() * p.sqrtS(); return s * (1 - std::cos(10 * 3.14159265358979323846 / 180)) / 2; }
  return anyLepton ? 4 : 400;
}

/// « Everything the detector sees » on a machine with a lepton: every family these beams allow, and the
/// photon flux apart, since it replaces the beam — two draws, assembled by the host.
inline Process expanded(Process p) {
  if (!p.collider || p.channels.size() != 1 || p.channels[0] != "inclusive" || p.beams.size() != 2) return p;
  if (!isLepton(p.beams[0]) && !isLepton(p.beams[1])) return p;
  if (isLepton(p.beams[0]) && isLepton(p.beams[1])) {
    p.channels.clear();
    if (p.beams[0] == -p.beams[1]) { p.channels.push_back("annihilation"); p.channels.push_back("bosonPair"); }
    for (const char* c : {"neutralCurrent", "chargedCurrent", "photoproduction"}) p.channels.push_back(c);
  } else {
    p.channels = {"neutralCurrent", "chargedCurrent", "photoproduction"};
  }
  p.mix = true;
  if (!p.hasQ2) { p.minimumQ2 = defaultQ2(p); p.hasQ2 = true; }
  return p;
}

/// The lines that put Pythia in front of a machine: beams, frame, the families left open, their thresholds,
/// the luminous region.
inline std::vector<std::string> colliderLines(const Process& p) {
  std::vector<std::string> L;
  L.push_back("Beams:idA = " + std::to_string(p.beams[0]));
  L.push_back("Beams:idB = " + std::to_string(p.beams[1]));
  if (p.fixedTarget) {
    // Le repos de la cible se dit par ses trois composantes nulles : une énergie voisine de sa masse lui
    // laisserait une petite impulsion.
    L.push_back("Beams:frameType = 3");
    L.push_back("Beams:pxA = 0"); L.push_back("Beams:pyA = 0"); L.push_back("Beams:pzA = " + number(p.energies[0]));
    L.push_back("Beams:pxB = 0"); L.push_back("Beams:pyB = 0"); L.push_back("Beams:pzB = 0");
  } else if (std::abs(p.energies[0] - p.energies[1]) < 1e-9) {
    L.push_back("Beams:frameType = 1");
    L.push_back("Beams:eCM = " + number(p.sqrtS()));
  } else {
    L.push_back("Beams:frameType = 2");
    L.push_back("Beams:eA = " + number(p.energies[0]));
    L.push_back("Beams:eB = " + number(p.energies[1]));
  }
  const bool leptonic = isLepton(p.beams[0]) && isLepton(p.beams[1]);
  const bool hadronic0 = isHadron(p.beams[0]), hadronic1 = isHadron(p.beams[1]);
  for (const auto& c : p.channels) {
    if (c == "singleBoson") {
      L.push_back("WeakSingleBoson:ffbar2gmZ = on");
      if (!leptonic) L.push_back("WeakSingleBoson:ffbar2W = on");
    } else if (c == "bosonPair") {
      L.push_back("WeakDoubleBoson:ffbar2gmZgmZ = on"); L.push_back("WeakDoubleBoson:ffbar2ZW = on");
      L.push_back("WeakDoubleBoson:ffbar2WW = on");
    } else if (c == "bosonExchange") {
      L.push_back("WeakBosonExchange:ff2ff(t:gmZ) = on"); L.push_back("WeakBosonExchange:ff2ff(t:W) = on");
    } else if (c == "qcd") {
      L.push_back("HardQCD:all = on");
    } else if (c == "photoproduction") {
      L.push_back("PDF:lepton2gamma = on"); L.push_back("Photon:ProcessType = 0"); L.push_back("HardQCD:all = on");
    } else if (c == "soft") {
      L.push_back("SoftQCD:all = on");
    } else if (c == "annihilation") {
      L.push_back("WeakSingleBoson:ffbar2gmZ = on");
    } else if (c == "neutralCurrent") {
      L.push_back("WeakBosonExchange:ff2ff(t:gmZ) = on");
    } else if (c == "chargedCurrent") {
      L.push_back("WeakBosonExchange:ff2ff(t:W) = on");
      if (hadronic0 && hadronic1) L.push_back("WeakSingleBoson:ffbar2W = on");
    } else if (c == "inclusive") {
      // Entre deux hadrons, ce que le détecteur voit : la section efficace inélastique.
      L.push_back("SoftQCD:inelastic = on");
    }
  }
  const bool scattering = p.has("neutralCurrent") || p.has("chargedCurrent");
  if (hadronic0 != hadronic1 && scattering) L.push_back("SpaceShower:dipoleRecoil = on");
  if (scattering) {
    double q2 = p.hasQ2 ? p.minimumQ2 : (p.has("neutralCurrent") ? defaultQ2(p) : 0);
    if (q2 > 1) L.push_back("PhaseSpace:Q2Min = " + number(q2));
  }
  // Le seuil en pT ne vaut que pour la QCD.
  const bool jets = p.has("qcd") || p.has("photoproduction");
  double floor = jets ? p.minimumPT : 0;
  if (floor <= 0 && jets) floor = 20;
  if (p.has("soft")) floor = 0;
  if (floor > 0) L.push_back("PhaseSpace:pTHatMin = " + number(floor));
  // La zone lumineuse, de taille typique ; sur cible fixe, la cible fixe le point.
  if (!p.fixedTarget) {
    double sx = 0.016, sy = 0.016, sz = 40;
    if (leptonic) { sx = 0.15; sy = 0.005; sz = 10; }
    else if (isLepton(p.beams[0]) || isLepton(p.beams[1])) { sx = 0.08; sy = 0.02; sz = 100; }
    L.push_back("Beams:allowVertexSpread = on");
    L.push_back("Beams:sigmaVertexX = " + number(sx));
    L.push_back("Beams:sigmaVertexY = " + number(sy));
    L.push_back("Beams:sigmaVertexZ = " + number(sz));
    L.push_back("Beams:maxDevVertex = 4");
  }
  return L;
}

/// The tune, by name or by number. Pythia wants numbers, and the one that governs a lepton machine is
/// Tune:ee, not Tune:pp. « pp:N » and « ee:N » set one of them explicitly.
inline bool tuneLines(const std::string& raw, std::vector<std::string>& L, std::string& error) {
  std::string t;
  for (char c : raw) if (c != ' ' && c != '-' && c != '_') t += char(std::tolower((unsigned char)c));
  if (t.empty()) return true;
  struct Named { const char* name; int pp; int ee; };
  static const Named named[] = {
    {"monash", 14, 7}, {"monash2013", 14, 7}, {"a14", 21, 0}, {"atlasa14", 21, 0}, {"az", 17, 0}, {"atlasaz", 17, 0},
    {"monashstar", 18, 0}, {"cuetp8m1", 18, 0}, {"4c", 5, 0}, {"tune4c", 5, 0},
  };
  for (const auto& n : named) if (t == n.name) {
    L.push_back("Tune:pp = " + std::to_string(n.pp));
    if (n.ee) L.push_back("Tune:ee = " + std::to_string(n.ee));
    return true;
  }
  auto numberAfter = [&](const std::string& prefix, int& out) {
    if (t.compare(0, prefix.size(), prefix) != 0) return false;
    std::string rest = t.substr(prefix.size());
    if (rest.empty() || rest.find_first_not_of("0123456789") != std::string::npos) return false;
    out = std::stoi(rest);
    return true;
  };
  int n = 0;
  if (numberAfter("pp:", n) || numberAfter("pp=", n)) { L.push_back("Tune:pp = " + std::to_string(n)); return true; }
  if (numberAfter("ee:", n) || numberAfter("ee=", n)) { L.push_back("Tune:ee = " + std::to_string(n)); return true; }
  if (numberAfter("", n)) { L.push_back("Tune:pp = " + std::to_string(n)); return true; }
  error = "unknown tune '" + raw + "': use Monash, A14, AZ, CUETP8M1, 4C, a Tune:pp number, or pp:N / ee:N";
  return false;
}

/// Why this machine cannot work, in one sentence, or "" when nothing is obviously wrong. Pythia refuses these
/// cases by printing an empty process table without a word of explanation; naming them first spares the reader.
inline std::string objection(const Process& p) {
  if (!p.collider || p.beams.size() != 2) return "";
  const bool h0 = isHadron(p.beams[0]), h1 = isHadron(p.beams[1]);
  if (p.has("soft") && p.has("qcd"))
    return "soft QCD already contains hard parton scattering — its multiple interactions make it — so asking for "
           "both counts the same events twice. Choose one: soft for everything the machine makes, hard QCD for the "
           "scattering above a transverse-momentum floor";
  if (p.has("photoproduction") && p.channels.size() > 1 && !p.mix)
    return "photoproduction replaces the beam rather than adding to it: switching the photon flux on leaves no "
           "lepton to annihilate or to exchange a boson, and Pythia draws one machine at a time. Ask for the two "
           "configurations to be drawn and assembled, or keep photoproduction on its own";
  const bool annihilate = (h0 && h1) || p.beams[0] == -p.beams[1];
  bool open = false, onlyQCD = true, onlyPhoto = true;
  for (const auto& c : p.channels) {
    bool ok;
    if (c == "singleBoson" || c == "bosonPair" || c == "annihilation") ok = annihilate;
    else if (c == "qcd" || c == "soft") ok = h0 && h1;
    else if (c == "photoproduction") ok = !h0 || !h1;
    else if (c == "chargedCurrent") ok = h0 || h1 || p.beams[0] == -p.beams[1];
    else ok = true;                                  // bosonExchange, neutralCurrent, inclusive
    open = open || ok;
    onlyQCD = onlyQCD && (c == "qcd" || c == "soft");
    onlyPhoto = onlyPhoto && c == "photoproduction";
  }
  if (open || p.channels.empty()) return "";
  const std::string b = std::to_string(p.beams[0]) + " and " + std::to_string(p.beams[1]);
  if (onlyQCD) return "beams " + b + " carry no partons, so QCD has nothing to scatter — those families want two hadrons";
  if (onlyPhoto) return "neither beam " + b + " radiates the photon flux photoproduction needs — that family wants at least one lepton";
  return "beams " + b + " cannot annihilate, so the channels asked for (ff̄ → γ*/Z, ff̄ → VV) have nothing to work "
         "with — these two scatter rather than annihilate, which is the boson-exchange family";
}

/// The whole card of a job. `part` is "" for everything, "beams" or "photons" for one half of an assembled
/// machine; `seedOffset` gives the second half its own randomness.
inline bool card(const Value& job, const std::string& part, int seedOffset, std::string& out, std::string& error) {
  Process p = expanded(readProcess(job["hardProcess"]));
  if (part.empty()) { error = objection(p); if (!error.empty()) return false; }
  if (part == "beams" || part == "photons") {
    std::vector<std::string> kept;
    for (const auto& c : p.channels) if ((c == "photoproduction") == (part == "photons")) kept.push_back(c);
    p.channels = kept;
  }
  std::vector<std::string> L;
  if (p.collider) {
    if (p.beams.size() != 2 || p.energies.size() != 2) { error = "collider mode needs two beams and their energies"; return false; }
    L = colliderLines(p);
  } else {
    L.push_back("Beams:frameType = 4");
    L.push_back("Beams:LHEF = " + job["input"].str("events.lhe"));
  }
  const bool soft = p.collider && (p.has("soft") || p.has("inclusive"));
  const long long seed = ((long long)job["seed"].num(0) + seedOffset) % 900000000LL;
  L.push_back("Main:numberOfEvents = " + std::to_string((long long)job["events"].num(0)));
  L.push_back("Random:setSeed = on");
  L.push_back("Random:seed = " + std::to_string(seed < 0 ? -seed : seed));
  const bool shower = job["shower"].flag(true);
  L.push_back(std::string("PartonLevel:ISR = ") + (shower ? "on" : "off"));
  L.push_back(std::string("PartonLevel:FSR = ") + (shower ? "on" : "off"));
  L.push_back(std::string("PartonLevel:MPI = ") + (job["multipleInteractions"].flag(false) || soft ? "on" : "off"));
  L.push_back(std::string("HadronLevel:all = ") + (job["hadronisation"].flag(true) ? "on" : "off"));
  L.push_back(std::string("HadronLevel:Decay = ") + (job["decays"].flag(true) ? "on" : "off"));
  L.push_back("Print:quiet = on");
  L.push_back("Next:numberShowEvent = 0");
  if (!tuneLines(job["tune"].str(), L, error)) return false;
  out.clear();
  for (const auto& l : L) out += l + "\n";
  // Les lignes libres viennent en dernier : elles priment sur tout le reste.
  const std::string extra = job["extraSettings"].str();
  if (!extra.empty()) out += extra + (extra.back() == '\n' ? "" : "\n");
  return true;
}

}  // namespace jobcard
