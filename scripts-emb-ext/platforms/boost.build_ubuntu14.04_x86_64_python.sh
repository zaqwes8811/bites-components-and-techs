#!/bin/bash
cd ~/big-3rdparty/boost_1_57_0
./bjam -d2 \
	--toolset=gcc-4.8 \
	target-os=linux \
	'-sBUILD=release static multi/single' \
	link=static \
	--prefix= \
	--layout=system \
	--with-thread \
	--with-python \
	--build-dir=build_gcc_x64 \
	--stagedir=stage_gcc_x64

# just gcc not work seecs
# \
#-arm_4_7 \
#--debug-configuration \
# Without it link correct - DANGER! maybe
#cxxflags="-O2 -mcpu=arm926ej-s -march=armv5te" \
#cflags="-O2 -mcpu=arm926ej-s -march=armv5te" \
# compileflags="" \
#  cxxflags="-m32" cflags="-m32" \

