
import socket   #for sockets
import sys  #for exit
 
# create dgram udp socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.settimeout(1)
except socket.error:
    print 'Failed to create socket'
    sys.exit()
 
host = 'localhost';
port = 8888;

msg = 0

while(1) :
    msg = raw_input('Enter message to send : ')
    #msg = msg + 1 
    #if msg == 10000:
    #    msg = ''
    try :
        #Set the whole string
        packet = str(msg)
        s.sendto(packet, (host, port))
         
        # receive data from client (data, addr)
        #d = s.recvfrom(1024)
        d = s.recvfrom(1024)
        reply = d[0]
        addr = d[1]
        
        print 'S : ' + reply 

        if(reply == 'ACK'):
            continue
        if reply == 'NACK':
            print 'send again'
        
        #s.sendto(packet, (host, port))
        #print 'Server reply : ' + reply + ' from Address:' + str(addr[0]) + ':' + str(addr[1])
     
    except socket.error, msg:
        print 'Error Code : ' + str(packet[0]) + ' Message ' + packet[1]
        sys.exit()