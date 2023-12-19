/**
 **  unix server access program
 **
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"


#define default_server_number	0


int main( int argc)
{
int	server_number;

/*  there must be zero or one command line argument  */
if( argc > 2 )
	{
	fprintf(stderr, "usage: ./ttt [server-number]\n");
	exit(1);
	}

/*  get the server's port number from the first parameter  */
server_number = default_server_number;

/*  now let the common server do the real work  */
server( server_number);

return(0);
}

