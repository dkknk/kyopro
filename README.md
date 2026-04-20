# kyopro

C++競技プログラミング用環境

---

## ディレクトリ構成

kyopro/
  - lib/                # 再利用ライブラリ
    - graph/
    - data_structure/
    - math/
    - などなど(の予定)
  - verify/             # ライブラリ検証用（Library Checkerなど）
  - contest/            # 作業用（Gitでは無視）
  - tools/              # スクリプト（g, a, c）
  - pch/                # プリコンパイルヘッダ
  - .vscode/            # VSCode設定
  - .verify-helper/     # oj-verify設定

---

## セットアップ

必要なもの：
- g++
- python3 + pipx
- xsel（クリップボード用）
- online-judge-verify-helper

インストール：

pipx install online-judge-verify-helper

---

## スクリプト

### g（コンパイル）

g a.cpp

- 開発用
- PCH使用
- 出力：a.out（または指定名）

---

### c（bundle）

c a.cpp submit.cpp

- oj-bundle を実行
- kyoproルートを自動検出
- 結果をクリップボードへコピー

---

## PCH（プリコンパイルヘッダ）

生成：

g++ -std=c++17 -x c++-header pch/stdc++.h

使用：

-include "$ROOT/pch/stdc++.h"

---

## ライブラリ方針

- <atcoder/all> は使わない
- 必要なものだけ使う or 自作する
- 名前空間：mylib
- 内部実装は detail に入れる

---

## 検証

oj-verify run

設定ファイル：
.verify-helper/config.toml

---

## Git管理

無視するもの：
contest/
*.gch
a.out
submit.cpp

管理するもの：
- lib/
- verify/
- tools/
- 設定ファイル

---

## 環境復元

git clone <repo>
cd kyopro

# スクリプト設定
ln -s ~/kyopro/tools/g ~/bin/g
ln -s ~/kyopro/tools/b ~/bin/b
ln -s ~/kyopro/tools/c ~/bin/c

# PCH再生成
g++ -std=c++17 -x c++-header pch/stdc++.h

#memo
何個かはなんとACLそのまま
このREADMEは9割5分くらいChatGPTが書いたよ！
---
