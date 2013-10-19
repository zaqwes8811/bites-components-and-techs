# -*- coding: cp1251 -*-



import poplib, email, email.Header

#Учетные данные
server='pop.mail.ru'
username='www.ispanec@mail.ru'
password='8233771'

popserv=poplib.POP3(server)
print popserv.getwelcome()
#авторизация
popserv.user(username)
popserv.pass_(password)
#транзакция
resp1, lst1, octets1= popserv.list()
print resp1

(resp2, lst2  ,octets2)=popserv.retr(89)  
#сбор объекта-сообщения
msgtxt='\n'.join(lst2)
msg=email.message_from_string(msgtxt)
#####разбор сообщения
## заголовок
to_mail=''
for text,en in email.Header.decode_header(msg['to']):
	if en==None:
		to_mail+=text+'; '
	else:
		to_mail+=text.decode(en)+'; '
print u'Кому: '+to_mail
from_mail=''
for text,en in email.Header.decode_header(msg['from']):
	if en==None:
		from_mail+=text+'; '
	else:
		from_mail+=text.decode(en)+'; '
print u'От: '+from_mail
subject=''
for text,en in email.Header.decode_header(msg['subject']):
	if en==None:
		subject+=text
	else:
		subject+=text.decode(en)
print u'Тема: '+subject





##части сообщения
count=0
for part in msg.walk():
    if part.is_multipart():
        continue
    count+=1
    contType=part.get_content_maintype()
    subType=part.get_content_subtype()
    print 'Part:',count,", has type: "+contType+', subtype: '+subType
    if contType=='text':
        if subType=='html':
            continue
        else:
            en=part.get_charsets()[0]
            print "charset: "+en
            text=part.get_payload(decode=True).decode(en)
            print text
        
    elif part.get_filename()!=None:
        fname=part.get_filename()
        name,en=email.Header.decode_header(fname)[0]
        if en==None:
            f=open(fname,'wb')
        else:
            fname=name.decode(en)
            f=open(fname,'wb')
        f.write(part.get_payload(decode=True))
        f.close()
        print "saved as "+ fname
    else:
        filename= 'part'+ str(count)+'.dat'
        f=open(fname,'wb')
        f.write(part.get_payload(decode=True))
        f.close()
        print "saved as "+ fname
    

           


popserv.quit()
