// cpp_compiler_options_openmp.cpp
// http://openmp.org/forum/viewtopic.php?f=3&t=1004
// http://msdn.microsoft.com/en-us/library/fw509c3b.aspx
// http://iproc.ru/programming/openmp-visual-studio/
//
// http://www.viva64.com/ru/a/0054/
#include <iostream>
#ifdef _DEBUG
#undef _DEBUG
#include <omp.h>
#define _DEBUG
#else
#include <omp.h>
#endif


using namespace std;

int main(int argc, char **argv)
{
    int test( 999 );

    #pragma omp parallel sections
    {
       #pragma omp section
       {
         cout << "test = 3 " << test << endl;
       }

       #pragma omp section
       {
         cout << "test = 4 " << test << endl;
       }
    }

    #pragma omp barrier

    return EXIT_SUCCESS;
}