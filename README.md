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