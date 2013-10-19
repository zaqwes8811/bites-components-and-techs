# -*- coding: utf-8  -*-
from Tkinter import *
from email.Header import make_header as mkh
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email.Encoders import encode_base64
import smtplib

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
