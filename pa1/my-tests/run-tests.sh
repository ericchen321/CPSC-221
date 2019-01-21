#!/bin/bash

cp ../chain.h chain.h
cp ../chain_given.cpp chain_given.cpp
cp ../chain.cpp chain.cpp
make
./pa1-test
