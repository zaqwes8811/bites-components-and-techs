#!/bin/sh

# https://code.google.com/p/v8/wiki/CrossCompilingForARM

V=/home/zaqwes/big_device/condesourcery/arm-2009q1

export TOOL_PREFIX=$V/bin/arm-none-linux-gnueabi
export CXX=$TOOL_PREFIX-g++
export AR=$TOOL_PREFIX-ar
export RANLIB=$TOOL_PREFIX-ranlib
export CC=$TOOL_PREFIX-gcc
export LD=$TOOL_PREFIX-g++

#export CCFLAGS="-march=armv7-a -mtune=cortex-a8 -mfpu=vfp"
export CCFLAGS="-mcpu=arm926ej-s -march=armv5te -mno-thumb-interwork"
# swp half thumb fastmult edsp java - 926j
# 
# -mlittle-endian - not run C++ code anyway
#
# --with-arm-float-abi=soft
#
# http://gcc.gnu.org/onlinedocs/gcc-4.4.5/gcc/ARM-Options.html
# -mfloat-abi=soft
export ARM_TARGET_LIB=$V/arm-none-linux-gnueabi/libc

# http://www.wigwag.com/devblog/cross-compile-v8-target-arm/!!
# https://code.google.com/p/v8/wiki/CrossCompilingForARM
# -j4 - ?
make arm.release \
	armfloatabi=soft \
	armfpu=off \
	wordsize=32 \
	snapshot=off \
	sample=shell \
	vfp3=off \
	werror=no \
	armv7=false \
	hardfp=off \
	armthumb=off \
	armneon=false \
	vfp2=off \
	vfp3=off \
	OUTDIR=./armv5te_dbg_out_armfloat_soft_off_some

# off max count values
# wordsize=32 snapshot=off arch=arm vfp3=off armeabi=soft sample=shell
# armeabi=soft
#fp
#
# Try arm.debug
# GCC switches: -march=XXX, -mtune=XXX, -mno-thumb-interwork
# V8 scons options: vfp3=off/on, armeabi=off/on
# V8 scons snapshot=off  - Later try to move to snapshot=on

#Ibuild/standalone.gypi --depth=. \
#	              -Dv8_target_arch=arm \
#	              -S.arm  -Dv8_enable_backtrace=1 -Dv8_use_snapshot='false' -Dwerror='' -Darmv7=0 -#Darm_fpu=vfp -Darm_float_abi=softfp -Darm_float_abi=soft -Darm_thumb=0

# Error
#root@freescale ~$ ./shell
#Illegal instruction

#-Ibuild/standalone.gypi --depth=. \
#	              -Dv8_target_arch=arm \
#	              -S.arm  -Dv8_enable_backtrace=1 -Dv8_use_snapshot='false' -Dwerror='' -Darmv7=0 -#Darm_fpu=vfp -Darm_float_abi=softfp -Darm_fpu=off -Darm_float_abi=soft -Darm_thumb=0

# Error
#root@freescale ~$ ./shell
#Illegal instruction

# -Ibuild/standalone.gypi --depth=. \
#	              -Dv8_target_arch=arm \
#	              -S.arm  -Dv8_enable_backtrace=1 -Dv8_use_snapshot='false' -Dwerror='' -Darmv7=0 -#Darm_fpu=vfp -Darm_float_abi=softfp -Darm_fpu=off -Darm_float_abi=soft -Darm_thumb=0
# How work order?

# Error
#root@freescale ~$ ./shell
#Illegal instruction

# Need edit Make file GY flags
# http://wiki.qemu.org/Main_Page

#Ibuild/standalone.gypi --depth=. \
#	              -Dv8_target_arch=arm \
#	              -S.arm  -Dv8_enable_backtrace=1 -#Dv8_use_snapshot='false' -Dwerror='' -Darmv7=0 -Darm_float_abi=soft -#Darm_thumb=0







