#
#
#  Makefile for client and server examples
#
#

# Edit the following line to reflect the current project number
PROJNUM = 1

HDR = client.h server.h
SRC = ttt.c 

OBJ = ttt.o
GRD = makefile ${SRC} ${HDR}

CC=gcc
CFLAGS = -g0

# Create all files

all:	ttt

ttt:	ttt.o
	$(CC)	$(CFLAGS)  ttt.o -o ttt
	
ttt.o:	ttt.c client.h server.h
	$(CC)	$(CFLAGS) -c ttt.c


#
# Clean up script
#
clean:
	/bin/rm -f *.o ttt

