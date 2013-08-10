#include "stdafx.h"
#include "WindowsClasses.h"
using namespace mluabind;
using namespace EmbInterpreters;
using namespace std;

void Windows::Run( ) {

	// �������� ��������� �� ���� � ����. ������. ����
	PtrWndWrapper loki_wind_wr( new WindowsWrapper( this ) );

	// �������� � ���������� ������������ ����
	::setMgr( loki_wind_wr );

	// ��� �������������
	std::auto_ptr< AJarvis > jarvis( new mJarvisWindows( ) );
	
	// ����������� ������
	jarvis->exhibit();

	// ��������� ������
	string fname = "config.lua";
	jarvis->runScriptInCurrentThread( fname );

	// �������� - ������ �� �������
	trace( this->getHello( ) );
}

// ������ ����������
Windows::Windows( ) { _hello = "hello";	trace( "constr dflt" ); }

std::string Windows::getHello( ) { return this->_getString( ); };

Windows::~Windows ( ) { trace( "destr dflt" ); }

void Windows::setCore( std::string str ) { _hello = str; }

std::string Windows::_getString( ) { return _hello; }

// ������� ������ ����
WindowsWrapper::WindowsWrapper( Windows* pWindows ) { 
	trace( "wr. constr. extend" ); _pw = pWindows; 
}

WindowsWrapper::WindowsWrapper( ) { trace( "wr. constr. dflt" ); }

WindowsWrapper::~WindowsWrapper( ) { trace( "wr. destr." ); }

std::string WindowsWrapper::getHello( ) { return _pw->getHello( ); }

void WindowsWrapper::setCore( std::string str ) { _pw->setCore( str ); }

void trace( std::string msg ) {
	std::cout <<  msg <<  std::endl;
}

/// ����������� ��������������
// ���������� ������� - �������, �� ���� �������
PtrWndWrapper g_loki_wind_wr( new WindowsWrapper( ) );

PtrWndWrapper getMgr( ) { 
	trace( "get ptr ");
	return g_loki_wind_wr; 
}

void setMgr( PtrWndWrapper sPtr ) { g_loki_wind_wr = sPtr; }

// ���������� ������ ������ ��������������
ErrCode mJarvisWindows::runScriptInCurrentThread( EmbInterpreters::Str fname ) {
	// ��������� ������
	luaL_dofile( __L, fname.c_str() );
}

ErrCode mJarvisWindows::exhibit() {
	// ����������� ������� ����
	// ��� ��� ������ ����� ������ ��������� ��������� � ����� ������� - 
	//   �������� ����� ���� MFC
	__pHost->Insert( 
		Class< WindowsWrapper >( "WindowsWrapper" )
			.Constructor( )
			.Method( "getHello", &WindowsWrapper::getHello )
			.Method( "setCore", &WindowsWrapper::setCore )
		 );

	// ����������� �����-���������
	// ����� ����������� �������� �� �����, �� ��� �������� ���. �������
	//   ������ � ��� ������� ���������� � ����� ���� ������� ��������. 
	//   ����� � �� ����, �� ����� RAII, � ��� ����������, ��� ������ ������
	//   � �� �����, � ������ � ���
	__pHost->Insert( 
		Class< PtrWndWrapper  >( )
			.SmartPtr< WindowsWrapper >( )
	 );

	// ���������� ��������� �� ����������� ������. ����
	__pHost->Insert( Function( "getMgr", &::getMgr, Adopt( -1 ) ) );
}

EmbInterpreters::ErrCode runScriptInNewThread( EmbInterpreters::Str fname ) {

}
