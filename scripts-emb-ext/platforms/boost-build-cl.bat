rem bjam  --toolset=msvc --with-python install
bjam --with-python python-debugging=off threading=multi variant=release link=shared stage
pause