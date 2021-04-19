#!/bin/bash
echo "building compiler"
if [ ! -d "build" ]; then
  mkdir "build"
fi
clang++ -std=c++17 -pedantic -Wall -I include/ -o build/pasc src/*.cpp 