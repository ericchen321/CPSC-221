#!/bin/bash

sudo apt-get update && sudo apt-get install clang-3.5 libc++abi-dev libc++-dev libpng-dev libsvn-dev gdb valgrind graphviz imagemagick subversion gnuplot
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-3.5 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-3.5 100
sudo update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer /usr/bin/llvm-symbolizer-3.5 100
