//---------------------------------------------------------------------------

#ifndef ReadThH
#define ReadThH
#include <Classes.hpp>
//---------------------------------------------------------------------------
//����� ��� ������ ������������������ ������ �� COM-����� � �����
class ReadThread : public TThread
{
 private:
        int tmplen;
        void __fastcall Printing();	//����� �������� ������ �� ����� � � ����
        OVERLAPPED overlapped;		//����� ������������ ��� �������� ������ (��. ����� ReadThread)
        OVERLAPPED ov;       	//����� ������������ ��� �������� ������ (��. ����� WriteThread)
 protected:
        void __fastcall Execute();	//�������� ������� ������
 public:
        __fastcall ReadThread(bool CreateSuspended);	//����������� ������
        char bufrd[255]; //�������
//
        int cycle; //����� ������(������) ������
};
#endif
