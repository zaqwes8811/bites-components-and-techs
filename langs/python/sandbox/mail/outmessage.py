# -*- coding: utf-8 -*-


from email.Header import make_header as mkh
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email.Encoders import encode_base64
import smtplib
#кодировки
rc='utf-8'
uc='us-ascii'
##
frommail='www.ispanec@mail.ru'
msg=MIMEMultipart()
msg['Subject']=mkh([('ТЕМА TEMA',rc)])
msg["From"]=mkh([('отправитель sender',rc),('<'+frommail+'>',uc)])
msg["To"]=mkh([('<www.ispanec@mail.ru>',uc)])
##чего не видно, при поддержке MIME
msg.preamble='Multipart message'
msg.epilog=''
#текстовая часть сообщения
text=u"""текстовая часть""".encode(rc)
to_attach=MIMEText(text,_charset=rc)
msg.attach(to_attach)
##файл
fp=open('1.jpg',"rb")
to_attach=MIMEBase('application','octet-stream')
to_attach.set_payload(fp.read())
encode_base64(to_attach)
to_attach.add_header("Content-Disposition","attachment",
                     filename='1.jpg')
fp.close()
msg.attach(to_attach)
#########

sender='www.ispanec@mail.ru'
recievers=['www.ispanec@mail.ru']

login='www.ispanec@mail.ru'
password='8233771'

smtpObj=smtplib.SMTP('smtp.mail.ru',25)

smtpObj.login(login,password)
smtpObj.sendmail(sender,recievers,msg.as_string())
smtpObj.close()
print "OK"
