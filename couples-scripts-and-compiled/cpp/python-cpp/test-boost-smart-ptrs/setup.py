#!/usr/bin/env python
from distutils.core import setup
from distutils.extension import Extension

library_dirs=['D:/boost_1_47_0/lib/lib']

setup( name="PackageName",
    ext_modules=[
        Extension("hello", ["*.cpp"],
        libraries = ["boost_python-vc90-mt-1_47","libboost_system-vc90-mt-1_47"],
        include_dirs = ["C:/boost_1_47_0"],
        library_dirs = library_dirs
        )
    ])