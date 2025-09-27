#!/usr/bin/env bash

# Codegen to Python3
antlr -Dlanguage=Python3 SensorLog.g4
./virtualenv/bin/python3 ./main.py