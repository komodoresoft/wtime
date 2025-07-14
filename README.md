# wtime - Unix time command for Windows
![Build](https://img.shields.io/badge/build-kmak-lightgrey?style=flat-square&logo=c) ![Lang](https://img.shields.io/badge/language-C-blue?style=flat-square&logo=c) ![License](https://img.shields.io/badge/license-MIT-green?style=flat-square) ![Status](https://img.shields.io/badge/status-DONE-green?style=flat-square)<br>
*wtime* is a command-line utility for Windows that replicates the behavior of the Unix `time` command.<br>
It measures the execution time of any command, with support for portable output and Ctrl+C handling.


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

## Examples
```bash
wtime -p test.exe
wtime notepad.exe
wtime -p ping localhost
```
