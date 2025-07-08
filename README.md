# wtime - Unix time command for Windows
![Build](https://img.shields.io/badge/build-kmak-lightgrey?style=flat-square&logo=c) ![Lang](https://img.shields.io/badge/language-C-blue?style=flat-square&logo=c) ![License](https://img.shields.io/badge/license-GPL-green?style=flat-square) ![Status](https://img.shields.io/badge/status-WIP-orange?style=flat-square)<br>
*wtime*  is command line utility that measures the execution time of an

## Features

- Measure real, user, and system CPU time
- Portable output mode (`-p`)
- Handles Ctrl+C to pass interrupt signals to the child process

## How to compile and get running
1. **Clone the repository:**
```bash
git clone https://github.com/komodoresoft/wtime.git
cd wtime
```

2. **Compile the source code using [KMAK](https://github.com/blueberry077/KMAK):**
```bash
kmak make.kmk compile
```

## Usage
```bash
wtime [-p] command [args...]
```