// cpp_compiler_options_openmp.cpp
// http://openmp.org/forum/viewtopic.php?f=3&t=1004
// http://msdn.microsoft.com/en-us/library/fw509c3b.aspx
// http://iproc.ru/programming/openmp-visual-studio/
#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char **argv)
{
    int test( 999 );

    omp_set_num_threads( 2 );
    #pragma omp parallel reduction(+:test)
    {
        #pragma omp critical
        cout << "test = " << test << endl;
    }

    return EXIT_SUCCESS;
}