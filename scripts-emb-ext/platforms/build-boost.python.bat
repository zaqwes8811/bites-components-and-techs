rem bjam.exe -sTOOLS=vc-7_1 -sPYTHON_VERSION=2.2 -sPYTHON_ROOT=C:\Python24
rem bjam.exe -sTOOLS=msvc -sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\Python24

bjam ^
    -j2 ^
    --toolset=msvc-9.0 ^
    release debug ^
    --with-python ^
	-sPYTHON_VERSION=2.7 -sPYTHON_ROOT=C:\opt\Python27 ^
    threading=multi link=static link=shared runtime-link=shared ^
   stage --stagedir="./lib"
   pause