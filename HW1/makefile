#
#
#  Makefile for client and server examples
#
#

# Edit the following line to reflect the current project number
PROJNUM = 1

HDR = client.h server.h
SRC = speak.c speakd.c unixclient.c unixserver.c

OBJ = unixclient.o unixserver.o server.o client.o
GRD = makefile ${SRC} ${HDR}

CC=gcc
CFLAGS = -g0

# Create all files

all:	client server

client:	unixclient.o speak.o
	$(CC)	$(CFLAGS) unixclient.o speak.o -o client

server:	unixserver.o speakd.o
	$(CC)	$(CFLAGS) unixserver.o speakd.o -o server

unixclient.o:	unixclient.c client.h
	$(CC)	$(CFLAGS) -c unixclient.c
	
speak.o:	speak.c client.h
	$(CC)	$(CFLAGS) -c speak.c

unixserver.o:	unixserver.c server.h
	$(CC)	$(CFLAGS) -c unixserver.c

speakd.o:	speakd.c server.h
	$(CC)	$(CFLAGS) -c speakd.c

#
# Clean up script
#
clean:
	/bin/rm -f *.o client server

