#!/usr/bin/env python3
"""The public GitHub pages of TreeLevel Tools in eleven languages.

GitHub runs no script: a page cannot choose its language by itself. Each page therefore opens in English, names the
other languages at its head, and holds each of them in a block that unfolds; a link leads to the same text on the
TreeLevel site, which the server serves in the reader's language.

  scripts/gh_pages.py readme                 README.md (and CREDITS.md) from docs/readme/
  scripts/gh_pages.py tools 0.5.0 [out.md]   the notes of the release mac-0.5.0, from docs/release-notes/0.5.0/
  scripts/gh_pages.py ipad <dir> out.md K=V… the notes of the iPad module, from <dir>/<lang>.md, $K replaced by V

The texts live one file per language; English is the reference, French the original.
"""
import os, string, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
LANGS = [("en", "English"), ("fr", "Français"), ("de", "Deutsch"), ("it", "Italiano"), ("es", "Español"),
         ("pt-BR", "Português (Brasil)"), ("ru", "Русский"), ("zh-Hans", "简体中文"), ("ja", "日本語"),
         ("ko", "한국어"), ("hi", "हिन्दी")]
SITE = "https://treelevel.pasahome.org/installation/"


def write(path, text):
    """Par un fichier voisin remplacé d'un coup : un README écrit par Windows à travers le partage de Parallels
    appartient à root, et ne s'ouvre pas en écriture ; le dossier, lui, est à nous."""
    tmp = path + ".tmp"
    with open(tmp, "w", encoding="utf-8") as f:
        f.write(text)
    os.replace(tmp, path)


def read(path):
    with open(path, encoding="utf-8") as f:
        return f.read().strip() + "\n"


def head(title, site):
    bar = " · ".join(f"[{name}](#lang-{code.lower()})" for code, name in LANGS[1:])
    return (f"# {title}\n\n"
            f"🌐 **[This page in your language]({site})** — the TreeLevel site opens it in the language of your "
            f"browser. Or unfold yours below: {bar}.\n\n")


def blocks(folder, subst=None):
    """English first, as the page itself; then one block per other language, folded."""
    def text(code):
        t = read(os.path.join(folder, f"{code}.md"))
        return string.Template(t).safe_substitute(subst) if subst else t
    out = text("en") + "\n"
    for code, name in LANGS[1:]:
        out += (f'<a name="lang-{code.lower()}"></a>\n<details>\n<summary><b>{name}</b></summary>\n\n'
                f"{text(code)}\n</details>\n\n")
    return out


def credits():
    """The links-and-credits part of the README, also CREDITS.md and the foot of the release notes."""
    rest = read(os.path.join(ROOT, "docs/readme/rest.en.md"))
    a = rest.index("## Links and credits"); b = rest.index("## What it does")
    return rest[a:b].strip() + "\n"


def readme():
    d = os.path.join(ROOT, "docs/readme")
    page = head("TreeLevel Tools", SITE + "#outils")
    page += ("[Installation](#installation) · [The container](#the-other-way-the-container) · "
             "[Links and credits](#links-and-credits) · [Contents](#contents)\n\n")
    page += blocks(d) + read(os.path.join(d, "rest.en.md"))
    write(os.path.join(ROOT, "README.md"), page)
    write(os.path.join(ROOT, "CREDITS.md"),
          credits().replace("## Links and credits", "# Links and credits", 1).replace("\n### ", "\n## "))


def tools(version, out):
    d = os.path.join(ROOT, "docs/release-notes", version)
    page = head(f"TreeLevel Tools {version}", SITE + "?os=mac#outils") + blocks(d) + credits()
    write(out, page)


def ipad(folder, out, pairs):
    subst = dict(p.split("=", 1) for p in pairs)
    page = head("Pythia module for TreeLevel on iPad", SITE + "?os=ipad&v=1.4#outils") + blocks(folder, subst)
    write(out, page)


if __name__ == "__main__":
    what = sys.argv[1] if len(sys.argv) > 1 else ""
    if what == "readme":
        readme()
    elif what == "tools":
        tools(sys.argv[2], sys.argv[3] if len(sys.argv) > 3 else os.path.join(ROOT, "build/release/release-notes.md"))
    elif what == "ipad":
        ipad(sys.argv[2], sys.argv[3], sys.argv[4:])
    else:
        sys.exit(__doc__)
