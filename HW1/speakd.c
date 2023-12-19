/**
 ** server.c  -  a server program that uses the socket interface to tcp 
 **
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include "server.h"

extern char *inet_ntoa( struct in_addr );
extern int errno;

#define NAMESIZE		255
#define BUFSIZE			81
#define listening_depth		2

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void server( int server_number )
{
int			c, i;
int			n, len;
short			fd, client_fd;
struct sockaddr_in	address, client;
struct hostent		*node_ptr;
char			local_node[NAMESIZE];
char			buffer[BUFSIZE+1];
int errnum;

/*  get the internet name of the local host node on which we are running  */
if( gethostname( local_node, NAMESIZE ) < 0 )
	{
	error( "server gethostname" );
	exit(1);
	}
fprintf(stderr, "server running on node %s\n", local_node);

/*  get structure for local host node on which server resides  */
if( (node_ptr = gethostbyname( local_node )) == NULL )
	{
	error( "server gethostbyname" );
	exit(1);
	}

/*  set up Internet address structure for the server  */
memset(&address, 0, sizeof(address));
address.sin_family = AF_INET;
memcpy(&address.sin_addr, node_ptr->h_addr, node_ptr->h_length);
address.sin_port = htons(server_number);

fprintf(stderr, "server full name of server node %s, internet address %s\n",
		node_ptr->h_name, inet_ntoa(address.sin_addr));

/*  open an Internet tcp socket  */
if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
	error( "server socket" );
	exit(1);
	}

/*  bind this socket to the server's Internet address  */
if( bind( fd, (struct sockaddr *)&address, sizeof(address) ) < 0 )
	{
	error( "server bind" );
	exit(1);
	}

/*  now find out what local port number was assigned to this server  */
len = sizeof(address);
if( getsockname( fd, (struct sockaddr *)&address, &len ) < 0 )
	{
	error( "server getsockname" );
	exit(1);
	}

/*  we are now successfully established as a server  */
fprintf(stderr, "server at internet address %s, port %d\n",
		inet_ntoa(address.sin_addr), ntohs(address.sin_port));

/*  start listening for connect requests from clients  */
if( listen( fd, listening_depth ) < 0 )
	{
	error( "server listen" );
	exit(1);
	}

/*  now accept a client connection (we'll block until one arrives)  */
len = sizeof(client);
if( (client_fd = accept(fd, (struct sockaddr *)&client, &len)) < 0 )
	{
	error( "server accept" );
	exit(1);
	}

/*  we are now successfully connected to a remote client  */
fprintf(stderr, "server connected to client at Internet address %s, port %d\n",
		inet_ntoa(client.sin_addr), ntohs(client.sin_port));



printf("WAITING FOR CLIENT MESSAGE.......\n");
int client_turn = 1;
    while (1) {
        bzero(buffer, BUFSIZE);
        if (client_turn) {
            n = read(client_fd, buffer, BUFSIZE - 1);
            if (n < 0) {
				errnum = errno;
                error("ERROR reading from socket");
				n = write(client_fd, strerror(errno), strlen(buffer));
				exit(1);
			}
            if (!strcmp(buffer, "xx\n")) {
                printf("--Terminating connection: Client called termination-- \n");
				break;
            }
            printf("Mesage from Client:-> %s", buffer);
            if (!strcmp(buffer, "x\n")) {
				printf("--Writing rights restored to Server--\n");
                // fflush(stdin);
				client_turn = 0;
            }
			
        } else {
            printf("Server Message:-> ");
            fgets(buffer, BUFSIZE, stdin);
            n = write(client_fd, buffer, strlen(buffer));
            if (n < 0) {
				errnum = errno;
                error("ERROR writing to socket");
				n = write(client_fd, strerror(errno), strlen(buffer));
            }
            if (!strcmp(buffer, "xx\n")) {
				printf("--Termination called by Server: Sending msg to client to end connection--\n");
                break;
            }
            if (!strcmp(buffer, "x\n")) {
                printf("--Writing rights transferred to client--\n ");
				client_turn = 1;
            }
			
        }
	

    }


// /*  close the connection to the client  */
if( close(client_fd) < 0 )
	{
		errnum = errno;
	error( "server close connection to client" );
	n = write(client_fd, strerror(errno), strlen(buffer));
	exit(1);
	}

// // /*  close the "listening post" socket by which server made connections  */
if( close(fd) < 0 )
	{
	errnum = errno;
	error( "server close" );
	n = write(client_fd, strerror(errno), strlen(buffer));
	exit(1);
	}
}

