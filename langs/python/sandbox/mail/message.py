# -*- coding: utf-8 -*-

from email import *
i_f=open('Message1.mim')
msg=message_from_file(i_f)

parts=[]
ct_fields=[]
fnames=[]

for submsg in msg.walk():
    parts.append(submsg.get_content_type())
    ct_fields.append(submsg.get('Content-Type',''))
    fnames.append(submsg.get_filename())
    if submsg.get_filename():
        print "Длина файла :", len(submsg.get_payload())
i_f.close()


print msg
