#! /bin/bash

cmake -B ./build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg-master/scripts/buildsystems/vcpkg.cmake

cmake --build ./build --config Debug

cd build/examples

./TestAll
