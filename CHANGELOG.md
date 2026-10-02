# Changelog

## 4.1.0 — 2026-10-02

- Replace recursive execution with a bounded instruction loop.
- Validate NJBF headers, segment sizes, opcodes, jumps and stack operations.
- Fix the four-byte magic buffer overflow and leaked file handles.
- Handle division and modulo by zero with non-zero exit codes.
- Add a working interactive step debugger.
- Build and test on Windows, Linux, macOS Intel and macOS Apple Silicon.
- Preserve the original THM/KSP Ninja and assembly examples in one archive.
- Remove committed CLion settings and generated CMake output.
