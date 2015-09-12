#!/bin/bash

# http://www.outsky.org/article.php?id=62

wget https://ftp.gnu.org/gnu/gcc/gcc-4.8.2/gcc-4.8.2.tar.bz2
wget https://ftp.gnu.org/gnu/gcc/gcc-4.8.2/gcc-4.8.2.tar.bz2.sig
wget https://ftp.gnu.org/gnu/gnu-keyring.gpg
signature_invalid=`gpg --verify --no-default-keyring --keyring ./gnu-keyring.gpg gcc-4.8.2.tar.bz2.sig`
if [ $signature_invalid ]; then echo "Invalid signature" ; exit 1 ; fi
tar -xvjf gcc-4.8.2.tar.bz2
cd gcc-4.8.2
./contrib/download_prerequisites
#cd ..
mkdir gcc-4.8.2-build
cd gcc-4.8.2-build
../configure --prefix=/opt/gcc4.8_x86_64 --enable-languages=c,c++ --enable-multilib --with-multilib-list=m32,m64
#make -j$(nproc)
#make install