//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReadTh.h"
#include "Unit1.h" // ��������� �����
#include "UCom.h"
// !!!!  � ����� ���� ��� �� ����� ��������� �� ������, �� �� �� ���� ���
// ���� ����������� ����� �����
// 

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------
//����������� ������ ReadThread, �� ��������� ������
__fastcall ReadThread::ReadThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//������� ������� ������, ��������� ���� ������ �� COM-�����
void __fastcall ReadThread::Execute()
{
 COMSTAT comstat;		//��������� �������� ��������� �����, � ������ ��������� ������������ ��� ����������� ���������� �������� � ���� ������
 DWORD btr, temp, mask, signal, signal2;	//���������� temp ������������ � �������� ��������
 overlapped.hEvent = CreateEvent(NULL, true, true, NULL);	//������� ���������� ������-������� ��� ����������� ��������
 ov.hEvent=CreateEvent(NULL, true, true, NULL);
 //ov.hEvent = CreateEvent(NULL, true, true, NULL);	//������� ���������� ������-������� ��� ����������� ��������

 SetCommMask(Form1->ports.GetHandCom(), EV_RXCHAR);                   	        //���������� ����� �� ������������ �� ������� ����� ����� � ����
 // !!!!����� ���� ������ ��������� ������ ������ � ��������!!!
 // !! ���� ���� ������� ��� �����, � ����� �������� �������� �� �����
 while(!Terminated){						//���� ����� �� ����� �������, ��������� ����
  // WaitCommEvent(COMport, &mask, &overlapped);               	//������� ������� ����� ����� (��� � ���� ������������� ��������)
  WaitCommEvent(Form1->ports.GetHandCom(), &mask, &overlapped); //== 0){  // ����� ������ ��������� �� ����������
         // ResetEvent(overlapped.hEvent) ;
          //ERROR_IO_PENDING - ������ ������   ? �����������
          //}
          //DWORD er=GetLastError();
   signal = WaitForSingleObject(overlapped.hEvent, INFINITE);	//������������� ����� �� ������� �����
   // Inf ����� �� �������� �� ��� �� ������
   if(signal == WAIT_TIMEOUT){ // ? ��� ����� ������, ����� �������� ������
      ShowMessage("����������� ����� � �����������");
   }
   if(signal == WAIT_OBJECT_0) //���� ������� ������� ����� ���������
   {     // ��� ���� ������ ��-�� ����, ��� ���� �������� ��� ���� ��� ��� �������������
     if(GetOverlappedResult(Form1->ports.GetHandCom(), &overlapped, &temp, true)){ //���������, ������� �� ����������� ������������� �������� WaitCommEvent
      if((mask & EV_RXCHAR)!=0)
      {					//���� ��������� ������ ������� ������� �����
        ClearCommError(Form1->ports.GetHandCom(), &temp, &comstat);		//����� ��������� ��������� COMSTAT
        btr = comstat.cbInQue;                          	//� �������� �� �� ���������� �������� ������
        if(btr)  // ���� ���� ������� ��� �����, �� ��� ����� overlapped.hEvent=������
        {                         			//���� ������������� ���� ����� ��� ������
         ReadFile(Form1->ports.GetHandCom(), bufrd, 39, &temp, &ov);
              //????????? ????? ?? ????? ? ????? ?????????
              signal2=WaitForSingleObject(ov.hEvent, INFINITE);
              if(signal2 ==WAIT_OBJECT_0 ){
         if(GetOverlappedResult(Form1->ports.GetHandCom(), &ov, &temp, true)){
           tmplen=temp;     //??????????? ??????? ??????
           cycle++;
              Synchronize(Printing);
           }
           }
          //1
        }  //2
      } //3
    }
  }
 }
 CloseHandle(overlapped.hEvent);		//����� ������� �� ������ ������� ������-�������
 CloseHandle(ov.hEvent);		//����� ������� �� ������ ������� ������-�������

}

//---------------------------------------------------------------------------
//������� �������� ����� �� ����� � � ���� (���� ��������)
void __fastcall ReadThread::Printing()
{ // ��������� ����������� ���������
  // ��������� ����������� ������� ���� �����
 Form1->ListBox1->Items->Add("����� ������� " + IntToStr(tmplen) + " ����");	//������� ������� � ������ ���������
 // ����������
 if(cycle == 1){ // ���� ���� ������� ��������� ��������
   /* - ��������� ����������� �����
      - ���� ��� ������ ��������� �����������
      - ���� ��� (������ ����� � ������������)
   */
    Form1->UTestCSum.GetConSum(bufrd, tmplen-1);  // ��������� ����������� ����� ���������
    if(Form1->UTestCSum.cSum[0] != bufrd[tmplen-1]){ // ����������
      Form1->Shape2->Brush->Color=clRed; //  ������ ����� � �����������(�����. ���. )
      Form1->Label4->Caption="������ ����� � �����������";
      Form1->ListBox1->Items->Add("������������ ����������� ����");
     } else{
     Form1->Shape2->Brush->Color=clBackground; //  ������ ����� � �����������(�����. ���. )
     Form1->Label4->Caption="����������� ����� �������";
     Form1->AnalyseState(bufrd,tmplen-1); // ����������� ����������
    }
   }
   if(cycle == 2){ // ���������� ������� �� ��������� ����������
     Form1->UTestCSum.GetConSum(bufrd, tmplen-1);  // ��������� ����������� ����� ���������
     //if(Form1->UTestCSum.cSum[0] != bufrd[tmplen-1]){
     // Form1->Shape2->Brush->Color=clRed; //  ������ ����� � �����������(�����. ���. )
     // Form1->Label4->Caption="������ ����� � �����������";
     //// Form1->ListBox1->Items->Add("������������ ����������� ����");
     //}else{
       AnsiString Out_set;
       Form1->Shape2->Brush->Color=clBackground; //  ������ ����� � �����������(�����. ���. )
       Form1->Label4->Caption="����������� ����� �������";
       // ����������� � ���� ��� ����
       Out_set="���������: ";
       for(int i=0;i<11-1;i++){   // ��� ������ 10 ���
         int tmpt=static_cast<int>(bufrd[i]);
         int ibuf[2];
         ibuf[1]=tmpt%16; // L
         tmpt/=16;
         ibuf[0]=tmpt%16;
         if(ibuf[0]>9){
         switch(ibuf[0]){
          case 10: Out_set+="A"; break;
          case 11: Out_set+="B"; break;
          case 12: Out_set+="C"; break;
          case 13: Out_set+="D"; break;
          case 14: Out_set+="E"; break;
          case 15: Out_set+="F"; break;
          }
         }else{
         Out_set+=IntToStr(ibuf[0]);
         }
        if(ibuf[1]>9){
        switch(ibuf[1]){
        case 10: Out_set+="A"; break;
        case 11: Out_set+="B"; break;
        case 12: Out_set+="C"; break;
        case 13: Out_set+="D"; break;
        case 14: Out_set+="E"; break;
        case 15: Out_set+="F"; break;
       }
      }else{
       Out_set+=IntToStr(ibuf[1]);
      }
        Out_set+=" "; // ����� ����
       }
       Form1->ListBox1->Items->Add(Out_set);
       Out_set="A0-A3 : ";
       for(int i=10;i<14;i++){   // ��� ���� �� 4�
         int tmpt=static_cast<int>(bufrd[i]);
         int ibuf[2];
         ibuf[1]=tmpt%16; // L
         tmpt/=16;
         ibuf[0]=tmpt%16;
         if(ibuf[0]>9){
         switch(ibuf[0]){
          case 10: Out_set+="A"; break;
          case 11: Out_set+="B"; break;
          case 12: Out_set+="C"; break;
          case 13: Out_set+="D"; break;
          case 14: Out_set+="E"; break;
          case 15: Out_set+="F"; break;
          }
         }else{
         Out_set+=IntToStr(ibuf[0]);
         }
        if(ibuf[1]>9){
        switch(ibuf[1]){
        case 10: Out_set+="A"; break;
        case 11: Out_set+="B"; break;
        case 12: Out_set+="C"; break;
        case 13: Out_set+="D"; break;
        case 14: Out_set+="E"; break;
        case 15: Out_set+="F"; break;
       }
      }else{
       Out_set+=IntToStr(ibuf[1]);
      }
      if((i)%2 != 0)Out_set+=" "; // ����� ����
      } // end for
    Form1->ListBox1->Items->Add(Out_set);
    // ����������� � ���� ��� ����
       Out_set="B0-B5 :   ";
       for(int i=14;i<20;i++){   // ��� ���� �� 4�
         int tmpt=static_cast<int>(bufrd[i]);
         int ibuf[2];
         ibuf[1]=tmpt%16; // L
         tmpt/=16;
         ibuf[0]=tmpt%16;
         if(ibuf[0]>9){
         switch(ibuf[0]){
          case 10: Out_set+="A"; break;
          case 11: Out_set+="B"; break;
          case 12: Out_set+="C"; break;
          case 13: Out_set+="D"; break;
          case 14: Out_set+="E"; break;
          case 15: Out_set+="F"; break;
          }
         }else{
         Out_set+=IntToStr(ibuf[0]);
         }
        if(ibuf[1]>9){
        switch(ibuf[1]){
        case 10: Out_set+="A"; break;
        case 11: Out_set+="B"; break;
        case 12: Out_set+="C"; break;
        case 13: Out_set+="D"; break;
        case 14: Out_set+="E"; break;
        case 15: Out_set+="F"; break;
       }
      }else{
       Out_set+=IntToStr(ibuf[1]);
      }
      if((i)%2 != 0)Out_set+=" "; //
      } // end for
    Form1->ListBox1->Items->Add(Out_set);
    Out_set="B6-B11 : ";
    for(int i=20;i<26;i++){   // ��� ���� �� 4�
         int tmpt=static_cast<int>(bufrd[i]);
         int ibuf[2];
         ibuf[1]=tmpt%16; // L
         tmpt/=16;
         ibuf[0]=tmpt%16;
         if(ibuf[0]>9){
         switch(ibuf[0]){
          case 10: Out_set+="A"; break;
          case 11: Out_set+="B"; break;
          case 12: Out_set+="C"; break;
          case 13: Out_set+="D"; break;
          case 14: Out_set+="E"; break;
          case 15: Out_set+="F"; break;
          }
         }else{
         Out_set+=IntToStr(ibuf[0]);
         }
        if(ibuf[1]>9){
        switch(ibuf[1]){
        case 10: Out_set+="A"; break;
        case 11: Out_set+="B"; break;
        case 12: Out_set+="C"; break;
        case 13: Out_set+="D"; break;
        case 14: Out_set+="E"; break;
        case 15: Out_set+="F"; break;
       }
      }else{
       Out_set+=IntToStr(ibuf[1]);
      }
      if((i)%2 != 0)Out_set+=" "; // ����� ����
      } // end for
    Form1->ListBox1->Items->Add(Out_set);
   }
   if(cycle == 3){  // ������ �������� ���
      if(bufrd[0]== 3){ // ��� ������
         // ��������� ������
         Form1->AssembleSettings();
      } else{
       Form1->ListBox1->Items->Add("������������ ����������� ����");
     }
   } //
   if(cycle == 4){  // ������ ����������� ���������� �����
      if(bufrd[0]==Form1->UCharArr.cSum[0]){
          Form1->Shape2->Brush->Color=clBackground; //  ������ ����� � �����������(�����. ���. )
          Form1->Label4->Caption="����������� ����� �������";
          Form1->AnalyseState(bufrd,tmplen-1); // ����������� ����������
        } else {
      Form1->Shape2->Brush->Color=clRed; //  ������ ����� � �����������(�����. ���. )
      Form1->Label4->Caption="������ ����� � �����������";
      Form1->ListBox1->Items->Add("������������ ����������� ����");
      }
   }
   if(cycle == 5){   // ������� ������� �� ������������
       if(bufrd[0]== 2){
           Form1->ListBox1->Items->Add("��������� ������������");
       } else{
         Form1->ListBox1->Items->Add("��� �������� �������");
         Form1->Shape2->Brush->Color=clBackground; //  ������ ����� � �����������(�����. ���. )
         Form1->AnalyseState(bufrd,tmplen-1); // ����������� ����������
   
       }
   }

 //
 //if(Form1->CheckBox3->Checked == true)  //���� ������� ����� ������ � ����
  //{
  write(Form1->handle, bufrd, tmplen); //�������� � ���� ������ �� �������� ������
  //}
 memset(bufrd, 0, 255);	        //�������� ����� (����� ������ �� ������������� ���� �� �����)
 tmplen=0;
}
//

