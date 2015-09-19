#!/bin/bash

# http://stackoverflow.com/questions/9379363/how-to-build-openssl-with-mingw-in-windows
export PATH="/c/Qt/Tools/mingw491_32/bin:$PATH"
export PATH="/c/Perl/bin:$PATH"

./Configure --prefix=$PWD/dist no-shared mingw
make depend && make && make install

