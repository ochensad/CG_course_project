#!/bin/bash

cd .. && rm -rf build && cd planet_system

mkdir ../build && cd ../build

cmake -DCMAKE_BUILD_TYPE=Release -DMYLIB_COVERAGE=ON ../planet_system

cmake --build .

./planet_system