//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WriteTh.h"
#include "Unit1.h" // ��������� �����
#include "UCom.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall WriteThread::WriteThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//������� ������� ������, ��������� �������� ������ �� ������ � COM-����
void __fastcall WriteThread::Execute()
{
 DWORD temp, signal;	//temp - ����������-��������

 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);   	  //������� �������

 while(!Terminated)     //���� ����� �� ����� ��������, ��������� ����
 {
 // ����� ������ ����������, ������� �� �� ��������, �� ��� Form1->UCharArr.store

  char stor=static_cast<char>(0xFF);
  char stora[2];
  stora[0]=stor;
  int buf=static_cast<int>(Form1->UCharArr.store[0]);
  WriteFile(Form1->ports.GetHandCom(),stora ,1, &temp, &overlappedwr);  //�������� ����� � ���� (������������� ��������!)
  Form1->lensend=0;  // ����������� ����� ���� ��� ������
  // ��� ������ �����-������-������� ����� ������� �������� ��� ������ ������
  signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE);	  //������������� �����, ���� �� ���������� ������������� �������� WriteFile
  if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(Form1->ports.GetHandCom(), &overlappedwr, &temp, true))) {
  Form1->fl = true;

  } //���� �������� ����������� �������, ���������� ��������������� ������
  else Form1->fl = false;

  Synchronize(Printing);	//������� ��������� �������� � ������ ���������
  Suspend();		//������������� ����� ������ � ����, ���� �� �� ����������� �����
 }
 CloseHandle(overlappedwr.hEvent);		//����� ������� �� ������ ������� ������-�������
}

//---------------------------------------------------------------------------

//����� ��������� �������� ������ �� �����
void __fastcall WriteThread::Printing()
{
 if(!Form1->fl)	//��������� ��������� ������
  {
   Form1->ListBox1->Items->Add("������ ��������");
   return;
  }
 Form1->ListBox1->Items->Add("�������� ������ �������");

}
