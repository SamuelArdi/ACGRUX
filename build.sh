#!/bin/bash

if [[ ! -d "build" ]] then
  conan install . --output-folder=build --build=missing
fi

cd build

if [[ $1 == 'rel' ]]; then
  cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
elif [[ $1 == 'dbg' ]]; then
  cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
fi

cmake --build .

cd ../bin

if [[ $2 == "run" ]]; then
  ./ACGRUX
fi
