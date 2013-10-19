# -*- coding: utf-8  -*-

from Tkinter import *
from email.Header import make_header as mkh
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email.Encoders import encode_base64
import smtplib
from mail_functions import *

#Выполняемые команды
#Написать письмо
def newc():
    #отправка письма
    def sendc():
        #кодировки
        rc='utf-8'
        uc='us-ascii'
        #подключение к SMTP серверу
        sender='www.ispanec@mail.ru'
        recievers=[tomail.get()]
        login='www.ispanec@mail.ru'
        password='8233771'
        smtpObj=smtplib.SMTP('smtp.mail.ru',25)
        smtpObj.login(login,password)
        smtpObj.login(login,password)
        #формирование письма
        msg=MIMEMultipart()
        #формирование заголовка
        msg['Subject']=mkh([(sbmail.get(),rc)])
        msg["From"]=mkh([('Черезов Дмитрий',rc),('<www.ispanec@mail.ru>',uc)])
        msg["To"]=mkh([('<'+tomail.get()+'>',uc)])
        ##чего не видно, при поддержке MIME
        msg.preamble='Multipart message'
        msg.epilog=''
        #текстовая часть сообщения
        text=textentry.get('1.0',END).encode(rc)
        to_attach=MIMEText(text,_charset=rc)
        msg.attach(to_attach)
        #файлы
        #отправка письма
        smtpObj.sendmail(sender,recievers,msg.as_string())
        smtpObj.close()
        print "OK"
       
    #Фрэйм поля нового письма
    nmframe=Frame(mframe,bg='#888888')
    nmframe.place(x=1+mbw+cfd,y=1,relwidth=0.9,relheight=1,anchor=NW)
    #поле ввода Кому
    toframe=Frame(nmframe,bg='#888888')
    toframe.place(x=0,y=0,relwidth=1,height=fih,anchor=NW)
    
    tolabel=Label(toframe,text="Кому:")
    tolabel.place(x=0,y=0,width=lbw,relheight=1,anchor=NW)
    
    tomail=StringVar()
    toentry=Entry(toframe,textvariable=tomail)
    toentry.place(x=lbw,y=0,relwidth=0.95,relheight=1,anchor=NW)
    #поле ввода Тема
    sbframe=Frame(nmframe,bg='#888888')
    sbframe.place(x=0,y=fih+1,relwidth=1,height=fih,anchor=NW)
    
    sblabel=Label(sbframe,text="Тема:")
    sblabel.place(x=0,y=0,width=lbw,relheight=1,anchor=NW)
    
    sbmail=StringVar()
    sbentry=Entry(sbframe,textvariable=sbmail)
    sbentry.place(x=lbw,y=0,relwidth=0.95,relheight=1,anchor=NW)
    #поле ввода текста сообщения
    textframe=Frame(nmframe,bg='#888888')
    textframe.place(x=0,y=2*fih+2,relwidth=1,height=fmth,anchor=NW)
    
    textlabel=Label(textframe,text="Текст сообщения:")
    textlabel.place(x=0,y=0,relwidth=1,height=fih-5,anchor=NW)
    
    
    textentry=Text(textframe,font=('times',12))
    textentry.place(relx=0.5,y=fih-4,relwidth=0.99,relheight=1,anchor=N)
    #textentry.get('1.0',END)
    
    #кнопка отправить
    sendb=Button(nmframe,text='Отправить',command=sendc)
    sendb.place(relx=0.995,rely=0.995,width=mbw,height=mbh,anchor=SE)
###Главное окно

main=Tk()
#статические параметры
mbh=40 #размеры главных кнопок
mbw=100#
cfd=20#отступ порождаемых фреймов
fih=25#высота поля ввода типа: Кому, Тема ,от кого...
lbw=90#ширина лэйблов типа: кому, куда ....
fmth=450#высота фрейма текста сообщения
#Меню приложения
main_menu=Menu(main)
main.config(menu=main_menu)
file_menu=Menu(main_menu)
main_menu.add_cascade(label='File',menu=file_menu)
file_menu.add_command(label="Выход",command=main.destroy)

#Главный фрейм
mframe=Frame(main,width=1200,height=750,bg='grey')
mframe.pack(fill=BOTH,expand=1)

#Основные кнопки
#Написать письмо
newb=Button(mframe,text='Написать',command=newc)
newb.place(x=1,y=1,width=mbw,height=mbh,anchor=NW)









main.mainloop()



