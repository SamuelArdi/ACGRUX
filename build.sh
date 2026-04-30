#!/bin/bash

if [[ ! -d "build" ]] then
  conan install . --output-folder=build --build=missing
fi

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .

if [[ $1 -eq "run" ]]; then
  ./bin/ACGRUX
fi
