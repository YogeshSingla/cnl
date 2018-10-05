import socket
import sys
 
HOST = ''   # Symbolic name meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port
 
# Datagram (udp) socket
try :
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    print 'Socket created'
except socket.error, msg :
    print 'Failed to create socket. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
 
 
# Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error , msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
print 'Socket bind complete'
 
data = 0
errors = 0
#now keep talking with the client
while 1:
    # receive data from client (data, addr)
    #d = s.recvfrom(1024)
    d = s.recvfrom(1024)
    previous_data = data
    data = d[0]
    addr = d[1]
     
    if not data: 
        break
     
    #reply = 'OK...' + data 
    #s.sendto(reply , addr)

    #ack = data
    #s.sendto(ack, addr)

    if data == '0':
        reply = 'NACK'
        errors = errors + 1
    else:
        reply = 'ACK'
    s.sendto(reply, addr)
    #print 'Message[' + addr[0] + ':' + str(addr[1]) + '] - ' + data.strip()
    print ' ' + data

    #if(int(previous_data) +1 != int(data)):
     #   errors = errors + 1
      #  print("errors: ",errors)
     

print("total errors: ", errors)
s.close()