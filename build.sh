#!/bin/bash

rm -rf out

mkdir -p out/build
pushd out/build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../out ../../
make -j`nproc`
make install
popd
