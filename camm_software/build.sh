#!/bin/sh
set -eu
mkdir -p build/obj
CXX=${CXX:-g++}
FLAGS="-std=c++17 -O2 -Wall -Wextra -Wpedantic -pthread -Iinclude"
for f in src/store/*.cpp src/cache/*.cpp src/policy/*.cpp src/observer/*.cpp src/adapter/*.cpp src/metrics/*.cpp; do
 o="build/obj/$(echo "$f" | tr '/.' '__').o"; $CXX $FLAGS -c "$f" -o "$o"
done
ar rcs build/libcamm.a build/obj/*.o
$CXX $FLAGS src/main.cpp build/libcamm.a -o build/camm_demo
for f in tests/*.cpp; do n=$(basename "$f" .cpp); $CXX $FLAGS "$f" build/libcamm.a -o "build/$n"; "./build/$n"; done
./build/camm_demo
