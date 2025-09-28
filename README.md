# ANTLR4 parser for LogDevice files

### Getting started with C++

Go to the root of the repository, then:

```bash
# Clone ANTLR4 C++ runtime
git clone https://github.com/antlr/antlr4.git
cd antlr4/runtime/Cpp
mkdir build && cd build
```

Now use `Make` or `Ninja` to build:

```bash
cmake ..
make
sudo make install
```

With `Ninja`:

```bash
cmake .. -G Ninja
ninja
sudo make install
```

## Running the parsers

### Python

Go to `parsers/python` and `./run.sh`

### C++

Go to `parsers/cpp` and `./run.sh`

> This script expects the folder `antlr4` in the repository's root.
>
> If you've moved it or cloned it in this folder, please adapt the script.

### C++ (CMake) — build with automatic ANTLR generation

If you prefer a CMake-based workflow (recommended for development), you can
configure and build the C++ parser with CMake/Ninja. This project already
contains a small CMake wrapper that will run the ANTLR tool to generate the
C++ sources before compilation when needed.

From the repository root, an example configure+build using the Homebrew
ANTLR jar and the repo prebuilt C++ runtime is:

```bash
# Configure
cmake -G Ninja -S parsers/cpp -B build

# Build
cmake --build build

# Run
./build/main samples/example_header.log
```

Notes:

- If you use the fish shell, substitute `$(which java)` with `(which java)`.
- The CMakeLists.txt attempts to prefer the repo-local prebuilt runtime and
	a Homebrew-installed ANTLR jar automatically; you can still pass them to
	override detection.
- If you prefer the original `run.sh` script (which uses a local g++ compile
	invocation), it is still available at `parsers/cpp/run.sh`.