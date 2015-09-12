#!/bin/bash

#http://llvm.org/docs/GettingStarted.html

cmake \
-DCMAKE_INSTALL_PREFIX=/opt/llvm \
-DCMAKE_BUILD_TYPE=Release \
-DLLVM_ENABLE_ASSERTIONS=On ..

cd tools/llvm-symbolizer/; make -j3; sudo make install

# ../build/bin/

# http://stackoverflow.com/questions/21163828/meaningful-stack-traces-for-address-sanitizer-in-gcc
#
# Troubles: libc calls
# https://groups.google.com/forum/#!msg/thread-sanitizer/pOaO2SNBen0/dZQ3f5kHL6AJ
export ASAN_SYMBOLIZER_PATH=/opt/llvm/bin/llvm-symbolizer
ASAN_OPTIONS=symbolize=1 