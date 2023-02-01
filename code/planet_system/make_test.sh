#!/bin/bash
cmake -DUSE_GCOV=ON ..
make
./planet_system -e 20
lcov --directory . --capture --output-file summary.info
mkdir report
genhtml -o ./report summary.info