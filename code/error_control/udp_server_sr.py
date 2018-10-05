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

WINDOW = 4

#now keep talking with the client
flag = 1
reply = ''
reply_flag = ''
while flag:
    # receive data from client (data, addr)
    #d = s.recvfrom(1024)
    window_data = []
    for i in range(WINDOW):

        d = s.recvfrom(1024)
        #previous_data = data
        data = d[0]
        addr = d[1]
         
        if not data: 
            break
        
        window_data.append(data) 
        #reply = 'OK...' + data 
        #s.sendto(reply , addr)

        #ack = data
        #s.sendto(ack, addr)
    count = 0
    reply_flag = ''
    for data in window_data:
        count = count + 1
        if data == '0':
            reply = str(count)
            reply_flag = 'NACK'
            errors = errors + 1
            print 'error, asking for' + str(count) + 'frame'
    if reply_flag != 'NACK':
        reply = 'ACK'
    s.sendto(reply, addr)
    
        #print 'Message[' + addr[0] + ':' + str(addr[1]) + '] - ' + data.strip()
    print window_data
    #flag = 0

        #if(int(previous_data) +1 != int(data)):
         #   errors = errors + 1
          #  print("errors: ",errors)
     

print("total errors: ", errors)
s.close()