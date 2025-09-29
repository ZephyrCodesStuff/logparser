# ANTLR4 parser for LogDevice files

This repository uses CMake as the primary build system for the C++ parser.

Requirements
- CMake 3.15 or newer (the build uses FetchContent and modern policies)
- A working C++17 compiler (g++, clang++, or MSVC)
- Java runtime (for running the ANTLR generator jar when generating sources)

How ANTLR is provided
- The project does not vendor the `antlr4` repository. Instead, CMake will
	automatically fetch the ANTLR sources at configure time (using FetchContent)
	and build the C++ runtime as necessary. This keeps the repository smaller
	and lets CMake manage the correct version for you.

Quick start (CMake workflow)

From the repository root:

```fish
# Configure (this will fetch and build the ANTLR C++ runtime if needed)
cmake -S parsers/cpp -B build -G Ninja

# Build
cmake --build build -- -j

# Run the parser
./build/main samples/example_header.log
```

Notes
- Network access is required at configure time the first time CMake fetches
	the ANTLR sources. Subsequent config/builds will reuse the downloaded copy
	in the build directory.
- If you need offline builds or reproducible environments, pin the ANTLR
	tag/commit in `parsers/cpp/CMakeLists.txt` (the default is v4.13.2).
- Manual Make/Ninja instructions and the repository-local `antlr4` layout have
	been removed. Use the CMake workflow above.

Other parsers
- Python parser: see `parsers/python` and its `run.sh` script.

If you want me to add an optional command to pre-populate a local `antlr4`
clone for offline use, I can add a small script or Make target that performs
that step.