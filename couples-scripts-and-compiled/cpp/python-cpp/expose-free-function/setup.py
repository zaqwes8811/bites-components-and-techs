#-*- coding: utf-8 -*-
""" 
    TODO : узнать как выбирать компиятор и его ключи(директивы)
    
    TODO : подключить чисто Си компилятор
    
    python setup.py install => последний аргумент как-то используется системой сборки
    
    Issues : 
        1. Не принимает *.c файлы
"""

import sys
sys.argv = ['setup.py', 'build']
import shutil
from distutils.core import setup
from distutils.extension import Extension

kLibraryDirs = ['d:/lib']
kLibsNames = ['boost_python-vc90-mt-1_47']
pkg_name = 'PackageName'
path_to_module = 'build/lib.win32-2.7/'
target_pkg_dir = './pkgs'

def _default_init():
    pass

def main(module_name, srcs, include_dirs, fp_init):
    if not fp_init:
        print 'Hello'
    
    one_extention = Extension(
        module_name, 
        srcs,
        include_dirs=include_dirs,
        libraries=kLibsNames,
        library_dirs=kLibraryDirs)
        
    setup(name=pkg_name, ext_modules=[one_extention])

    # Move result modules
    shutil.copy(path_to_module+module_name+'.pyd', target_pkg_dir)
    
    print 'Done'

if __name__=='__main__':
    module_name = 'hello'
    srcs = ['hello_module.cc', 'hello_inc.cc']
    include_dirs = ['D:/work-libs/boost_1_47_0']
    
    main(module_name, srcs, include_dirs, None)
    
""" 
from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext
copt =  {'msvc': ['/openmp', '/Ox', '/fp:fast','/favor:INTEL64','/Og']  ,
     'mingw32' : ['-fopenmp','-O3','-ffast-math','-march=native']       }
lopt =  {'mingw32' : ['-fopenmp'] }

class build_ext_subclass( build_ext ):
    def build_extensions(self):
        c = self.compiler.compiler_type
        if copt.has_key(c):
           for e in self.extensions:
               e.extra_compile_args = copt[ c ]
        if lopt.has_key(c):
            for e in self.extensions:
                e.extra_link_args = lopt[ c ]
        build_ext.build_extensions(self)

mod = Extension('_wripaca',
            sources=['../wripaca_wrap.c', 
                     '../../src/wripaca.c'],
            include_dirs=['../../include']
            )

setup (name = 'wripaca',
   ext_modules = [mod],
   py_modules = ["wripaca"],
   cmdclass = {'build_ext': build_ext_subclass } )
"""