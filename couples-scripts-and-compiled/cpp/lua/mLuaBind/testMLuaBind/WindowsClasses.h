/*
	���� :
		������ ���������� ������ �����, �������� �������. ������ ������.
		��� ���� ������ �� ������� ������������. ��� ����� ������ �������� 
			� �����-���������. ��� �� ������ ������� ������� �������.

	����� :
		������� ���������� ����� ���������� ������. ����. ����� �������� 
			����� �� �����.

*/
#pragma once

#include <mluabind/mluabind.h>
#include <Loki/SmartPtr.h>
#include "mJarvis.h"

#include <iostream>
#include <memory>

void trace ( std::string msg );

class Windows {
	public :
		Windows( );
		~Windows( );
		// 
		void Run();
		std::string getHello();
		void setCore( std::string str );
	private :
		std::string _getString();
		std::string _hello;

		// for mt runner : std::auto_ptr< AJarvis > jarvis(
};

class WindowsWrapper {
	public :
		explicit WindowsWrapper( Windows* pWindows );
		explicit WindowsWrapper( );
		~WindowsWrapper();

		std::string getHello();
		void setCore( std::string str );

	private : 
		Windows* _pw;
};

// ����� ��� ��������������
typedef Loki::SmartPtr< WindowsWrapper > PtrWndWrapper;
PtrWndWrapper getMgr( );
void setMgr( PtrWndWrapper sPtr );
extern PtrWndWrapper g_loki_wind_wr;

// �������������
class mJarvisWindows : public EmbInterpreters::AJarvis {
	public :
		explicit mJarvisWindows() : AJarvis() {}
		EmbInterpreters::ErrCode exhibit();
		EmbInterpreters::ErrCode runScriptInCurrentThread( EmbInterpreters::Str fname );
		EmbInterpreters::ErrCode runScriptInNewThread( EmbInterpreters::Str fname );
};
