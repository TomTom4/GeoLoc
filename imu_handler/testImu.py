import socket, traceback
import math

host = ''
port = 5555

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
s.bind((host, port))

timestamp,acceleroid,a_x,a_y,a_z,magnetoid,m_x,m_y,m_z =['0','0','0','0','0','0','0','0','0'] 
while 1:
	try:
		message, address = s.recvfrom(8192)
		my_mess = message.split(',')

		if len(my_mess) == 9:
			timestamp,acceleroid,a_x,a_y,a_z,magnetoid,m_x,m_y,m_z =my_mess	
			print("mon cap : {0}".format((math.atan2(float(m_y),float(m_x))/math.pi)*180))
		#print message
		#print("magneto = x : {0}, y : {1}, z : {2}".format(m_x,m_y, m_z))
	except (KeyboardInterrupt, SystemExit):
		raise
	except:
		traceback.print_exc()

