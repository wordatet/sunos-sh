# SunOS 4.1.4 Bourne Shell for Linux

> SunOS sh, ported to other OSes. PLS DONT TAKE DOWN ORACLE!!1

This repository contains a functional port of the classic **SunOS 4.1.4 Bourne Shell** (`sh`) to modern 64-bit Linux and BSD environments.

## Overview
The goal of this project was to preserve a piece of computing history by making the original BSD-lineage Bourne shell functional on contemporary hardware and kernels. The SunOS 4.1.4 shell represents a "cleaner" branch of the Bourne family tree, predating the heavy internationalization and POSIX layers that made later System V releases significantly more complex.

## Porting Process
This port was developed by **Mario (@wordatet)** using the [**Antigravity IDE**](https://antigravity.google). Me with the help of Gemini 3 Flash, we analyzed the 30-year-old C source code and implemented several critical modernizations:

### Technical Highlights
- **64-bit Pointer Safety**: Overhauled the original shell's pointer tagging logic (which abused the least significant bits for internal flags) to use `uintptr_t`, ensuring stability on 64-bit Linux.
- **Memory Management**: Adapted the custom `sbrk`-based circular allocator (`blok.c`) to maintain 64-bit address alignment.
- **Compatibility Layer**: Developed `compat.h` to bridge BSD/SunOS-specific signals and system calls to their modern equivalents (Linux/FreeBSD/etc).
- **Hash Table Fixes**: Corrected initialization order bugs that triggered segmentation faults during early environment processing.

## Building
To compile the shell on a modern Linux or BSD system:

```bash
make
```

This will produce the `sh` binary. Use `make clean` to remove build artifacts.

### Cross-Compilation
The shell can be cross-compiled for other architectures (e.g., AArch64) using the `CROSS_COMPILE` variable:

```bash
make CROSS_COMPILE=aarch64-linux-gnu-
```

### FreeBSD & BSD Compatibility
This port is designed for high portability. Since SunOS 4.1.4 was a BSD-based operating system, this shell is natively close to modern FreeBSD. The 64-bit safety fixes provided here are essential for all modern 64-bit Unix environments.

## License
The modifications, porting logic, and 64-bit safety fixes provided in this repository are licensed under **The Mario Legacy License** (an MIT-based permissive license). Originally developed code from AT&T and Sun Microsystems remains under their respective historical copyrights. See the [LICENSE](LICENSE) file for the full text.

## Disclaimer
This project is for digital archaeology, research, and educational purposes.
