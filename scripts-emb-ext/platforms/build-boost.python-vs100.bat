set VER=msvc-10.0
bjam ^
  -j2 ^
  --toolset=%VER% ^
  release debug ^
  --with-python ^
  -sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\Python27 ^
  threading=multi link=static link=shared runtime-link=shared ^
  stage --stagedir="lib/%VER%"
  pause