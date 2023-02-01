#!/bin/bash

# Переходим из каталога myproj в myproj-build
mkdir ../build && cd ../build

# Конфигурируем для сборки из исходников в ../myproj
cmake -DCMAKE_BUILD_TYPE=Debug ../planet_system

# Запускаем сборку в текущем каталоге
cmake --build .

open planet_system.app