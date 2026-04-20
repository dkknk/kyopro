# kyopro

C++ competitive programming environment.

---

## Directory Structure

kyopro/
  lib/                # reusable library
    graph/
    data_structure/
    math/
  verify/             # verification (library checker etc.)
  contest/            # temporary workspace (ignored by git)
  tools/              # scripts (g, b, c)
  pch/                # precompiled header
  .vscode/            # VSCode config
  .verify-helper/     # oj-verify config

---

## Setup

Requirements:
- g++
- clang (optional)
- python3 + pipx
- xsel (clipboard)
- online-judge-verify-helper

Install:
pipx install online-judge-verify-helper

---

## Scripts

### g (compile)

g a.cpp

- uses -O0 (fast compile)
- uses PCH
- output: a.out (or specified)

---

### b (bundle)

b a.cpp submit.cpp

- runs oj-bundle
- auto-detects project root
- copies output to clipboard

---

### c (pipeline)

c a.cpp verify/sample/a.test.cpp

- compile → bundle → verify

---

## PCH (Precompiled Header)

Generate:
g++ -std=c++17 -O2 -x c++-header pch/stdc++.h

Usage:
-include "$ROOT/pch/stdc++.h"

---

## Library Policy

- do NOT use <atcoder/all>
- import only necessary components or reimplement
- namespace: mylib
- internal helpers inside detail

---

## Available Components

graph:
- graph.hpp
- functional_graph.hpp

data_structure:
- dsu.hpp
- segtree.hpp
- lazy_segtree.hpp
- fenwicktree.hpp

math:
- modint.hpp
  - modint998244353
  - modint1000000007

---

## Verification

oj-verify run

config:
.verify-helper/config.toml

---

## Git Policy

ignored:
contest/
*.gch
a.out
submit.cpp

tracked:
- lib/
- verify/
- tools/
- configs

---

## Notes

- main compile bottleneck is -O2
- development uses -O0
- PCH reduces include overhead but not optimization cost
- contest directory is disposable

---

## Rebuild Environment

git clone <repo>
cd kyopro

# setup scripts
ln -s ~/kyopro/tools/g ~/bin/g
ln -s ~/kyopro/tools/b ~/bin/b
ln -s ~/kyopro/tools/c ~/bin/c

# regenerate pch
g++ -std=c++17 -O2 -x c++-header pch/stdc++.h

---