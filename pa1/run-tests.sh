#!/bin/bash

cp chain.h my_tests/chain.h
cp chain_given.cpp my_tests/chain_given.cpp
cp chain.cpp my_tests/chain.cpp
cd my_tests
make
./pa1-test
rm chain.h
rm chain_given.cpp
rm chain.cpp
cd ..
