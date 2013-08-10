// first.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "testLua.h"

using namespace std;
///
int main (int argc, char* argv[])
{
        luaOpenInterpr();
        luaTest();
        ::Sleep(1000);
        luaCloseInterpr();
	      return 0;
}

