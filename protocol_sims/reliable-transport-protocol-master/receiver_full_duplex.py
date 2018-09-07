#!/usr/bin/env python
"""
Receiver.py
"""

import datetime
import signal
import socket
import sys
import util


# Shut down program if interrupted, closing all socks and files
def shutdown(signum, frame):
    if log_file:
        log_file.write("\nTRANSMISSION INCOMPLETE\n")
        log_file.close()

    if packet_file:
        packet_file.write("\nINCOMPLETE PACKETS\n")
        packet_file.close()

    if recv_file:
        recv_file.close()

    if recv_sock:
        recv_sock.close()

    if ack_sock:
        ack_sock.close()

    exit(1)

if __name__ == '__main__':
    signal.signal(signal.SIGINT, shutdown) # Sets the keyboard interrupt handler as shutdown function

    # Set command line args
    try:
        filename = sys.argv[1]
        listen_port = int(sys.argv[2])
        sender_ip = socket.gethostbyname(sys.argv[3])
        sender_port = int(sys.argv[4])
        log_filename = sys.argv[5]
        packet_filename = sys.argv[6]


    except IndexError, TypeError:
        exit("usage: ./receiver.py <filename> <listening_port> <sender_IP> <sender_port> <log_filename> <packet_filename>")

    # Establish initial sockets
    try:
        # UDP socket for receiving file
        recv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)	# AF_INET is the Address Family, INET means IPv4
        recv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Socket level option is set to allow reuse of local addresses
        recv_sock.bind(("", listen_port))

        # TCP socket for sending ACKs
        ack_sock = socket.socket()
        ack_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except socket.error:
        exit("Error creating socket.")

    # Open file for writing
    try:
        recv_file = open(filename, 'w')
    except IOError:
        exit("Unable to open " + filename + ".")
    # Open file for logging
    if log_filename == "stdout":
        log_file = sys.stdout
    else:
        try:
            log_file = open(log_filename, 'w')
            packet_file = open(packet_filename,'w')
        except IOError:
            exit("Unable to open " + log_filename + ".")

    next_acknum = 0

    # Receive first packet
    """
     return value is a pair (string, address) where string is a string representing the data received and address is the address of the socket sending the data
    """
    packet, addr = recv_sock.recvfrom(576)
    source_port, dest_port, seqnum, acknum, header_length, \
        ack, final, window_size, contents = util.unpack(packet)

    checksum = util.get_checksum(packet)
    packet_valid = checksum == 0 and next_acknum == acknum

    if packet_valid:
        recv_file.write(contents)
        next_acknum += 1

    log = str(datetime.datetime.now()) + " " + str(source_port) + " " + str(dest_port) + " " + str(seqnum) + " " + str(
        acknum)
    log_file.write(log + "\n")

    # Establish ack socket connection
    ack_sock.connect((sender_ip, sender_port))
    out_port = ack_sock.getsockname()[1]
    ack_segment = util.make_packet(out_port, sender_port,
                                   seqnum, acknum, packet_valid,
                                   False, 1, "")
    ack_sock.send(ack_segment)

    # At this point, we are connected so we can send ACKs
    while True:

        # Receive every other packet
        packet, addr = recv_sock.recvfrom(576)

        """
        Use the custom written util module to unpack the received packet in the format
        """
        source_port, dest_port, seqnum, acknum, header_length, \
            ack, final, window_size, contents = util.unpack(packet)


        checksum = util.get_checksum(packet)

        # minor fix for checksum issue
        if checksum == 0xFFFF:
            checksum = 0

        log = str(datetime.datetime.now()) + " " + str(source_port) + " " + str(dest_port) + " " + str(
            seqnum) + " " + str(acknum)

        packet_data = str(packet)

        if final:
            log += " FIN"
        log_file.write(log + "\n")
        packet_file.write(packet_data)

        # ACK the packet if it's uncorrupted; otherwise send NAK.
        packet_valid = checksum == 0 and next_acknum == acknum

        if packet_valid:
            recv_file.write(contents)
            next_acknum += 1

        ack_segment = util.make_packet(out_port, sender_port,
                                        seqnum, acknum, packet_valid,
                                        final, 1, "")
        ack_sock.send(ack_segment)
        if final:
            break

    print("File successfully received.")
