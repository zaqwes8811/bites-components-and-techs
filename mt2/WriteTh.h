//---------------------------------------------------------------------------

#ifndef WriteThH
#define WriteThH
#include <Classes.hpp>
//---------------------------------------------------------------------------
//����� ��� ������ ������������������ ������ �� ������ � COM-����
class WriteThread : public TThread
{
private:
        OVERLAPPED overlappedwr;       	//����� ������������ ��� �������� ������ (��. ����� WriteThread)
 	void __fastcall Printing();	//����� ��������� �� �����
protected:
        void __fastcall Execute();      //�������� ������� ������
public:
        __fastcall WriteThread(bool CreateSuspended);	//����������� ������

};
#endif
