#-*- coding: utf-8 -*-
import os, sys
import socket
from api_dbg.doColoredConsole import co

# Report on all data packets received and
# where they came from in each case (as this is
# UDP, each may be from a different source and it's
# up to the server to sort this out!)

''' '''
def run( printTx, printRx ):
	# A UDP server

	# Set up a UDP server
	UDPSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

	# Listen on port 5001
	# (to all IP addresses on this system)
	port = 15001
	print 'Listed port :'+str(port)
	listen_addr = ( "", port )
	UDPSock.bind( listen_addr )
	try:
		step = 20
		i = 0
		while True:
			# принимаем
			data, addr = UDPSock.recvfrom(1024)
			
			# Разделение потоков
			if ord(data[-1]) == 0:
				printTx( data[:-1] )
			else :
				printRx( data[:-1] )
	finally:
		co.printN ( '' )