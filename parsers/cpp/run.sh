#!/bin/bash

# Codegen to C++
antlr -Dlanguage=Cpp ./gen/SensorLog.g4

# Build and run C++ code
mkdir -p build
g++ -std=c++17 -I/usr/local/include/antlr4-runtime \
    -L/usr/local/lib -I../../antlr4/runtime/Cpp/runtime/src -L../../antlr4/runtime/Cpp/build/runtime \
    main.cpp ./gen/SensorLog*.cpp \
    -lantlr4-runtime -o ./build/parse_sensor_log

# Run the parser
./build/parse_sensor_log ../../samples/example_header.log