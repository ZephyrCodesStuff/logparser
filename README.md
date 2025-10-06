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
cmake --build build --parallel

# Run the parser
./build/main samples/example.log
```

Notes
- Network access is required at configure time the first time CMake fetches
	the ANTLR sources. Subsequent config/builds will reuse the downloaded copy
	in the build directory.

Other parsers
- Python parser: see `parsers/python` and its `run.sh` script.

## Usage 
In order to use the parser, you can either compile it yourself using the compilation guide, or you can download the release version for your OS. 

**Windows version requires libantlr4-runtime.dll in the same folder as logparser.exe to work!**

You can specify the operation mode using the available command-line flags:

```bash
.\logparser.exe [-j] [-p] [-jp] <inputPath> <outputPath>
```
The program supports the following options:

-   **`-j`** Join split files into merged `.bin` batches and write them to the specified `<outputPath>`.
	- `<inputPath>` must be a directory to join files 
    
-   **`-p`** Parse files into CSV format.
    
    -   If `<inputPath>` is a directory, all files inside will be parsed individually.
        
    -   If `<inputPath>` is a single file, only that file will be parsed.
        
-   **`-jp`**  Join and then parse the merged batches in one step (similar to using **`-j -p`**).
### Example Usage : 
```bash
.\logparser.exe -jp logs output
```
Where logs is a folder containing all the binary files and output is an empty folder.
Keep in mind that you need to use the path of the logparser, so either your terminal should be in the same folder or you should paste the path like :
```bash
C:\Users\User\Downloads\logparser.exe -jp logs output
```

