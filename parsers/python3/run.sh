#!/usr/bin/env bash

# Codegen to Python3
antlr -Dlanguage=Python3 ./gen/SensorLog.g4
./virtualenv/bin/python3 ./main.py