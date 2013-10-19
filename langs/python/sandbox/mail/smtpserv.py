import smtplib
sender='cherezov89@gmail.com'
recievers=['www.ispanec@mail.ru']
login='cherezov89'


password='cherezov27071989'




smtpObj=smtplib.SMTP('smtp.gmail.com',25)
smtpObj.set_debuglevel(1)
smtpObj.login(login,password)
smtpObj.sendmail(sender,recievers,str(msg))
smtpObj.close()
print "OK"
