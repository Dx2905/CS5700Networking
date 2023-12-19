#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include "server.h"
#include "client.h"

extern char *inet_ntoa( struct in_addr );
extern int errno;

#define NAMESIZE		255
#define BUFSIZE			1024
#define listening_depth		2
#define default_server_number    0

char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int i,msgbyte, turn;
//int choice;
char choice[BUFSIZE];
//char choice;
char mark, marks;
//char option;
char option[BUFSIZE];
char qs[BUFSIZE];
int turninput;


void resetSquare() {
    char newSquare[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < 10; i++) {
        square[i] = newSquare[i];
    }
}


int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
        
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
        
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
        
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
        
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
        
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
        
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
        
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
        
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  - 1;
}


/****
FUNCTION TO DRAW BOARD OF TIC TAC TOE
 ***/


void board()
{
    
    printf("\n\n\tTic Tac Toe\n\n");

    printf("CLIENT (X)  -  SERVER (O)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

void gamestart( int turninput, short client_fd){
    
    char choice[BUFSIZE];
    resetSquare();
    board();
    
    if( turninput == 1){
mark = 'X';
marks = 'O';
} else{
turninput = 2;
mark = 'O';
marks = 'X';
}
    if(turninput == 1){
        i= checkwin();
        while(i!=1)
        {
            msgbyte=recv(client_fd,&choice,sizeof(choice),0);
            if(msgbyte < 0){
                printf("error recieving msg client msgbyte\n");
            } else {
                choice[msgbyte]= '\0';
                
            }
            
            printf("choice receieved: %s", choice);
//            if(choice==11)
//            if(strcmp(choice,"server win")==0)
//            {
//                printf("You win");
//                close(fd);
//                break;
//            }
//            printf("choice receieved: %s", choice);
//            if(choice==15)
//            if(strcmp(choice,"draw")==0)
//            {
//                printf("Draw");
//                close(fd);
//                break;
//            }
            //        mark='X';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = mark;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = mark;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = mark;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = mark;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = mark;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = mark;
            
            else if (strcmp(choice,"7")==0 && square[7] == '7')
                square[7] = mark;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = mark;
            
            else if(strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = mark;
            
            
            i = checkwin();
//            printf("\n%d\n",i);
            if(i==1)
            {    board();
//                int flag=10;
                char flag[]="client win";
                printf("client win\n");
                msgbyte=send(client_fd,&flag,sizeof(flag),0);
                printf("Play again\n");
//                board();
                gamestart(turninput, client_fd);
//                close(fd);
//                break;
            }
            if(i==0)
            {    board();
//                int flag=16;
                char flag[]="draw";
                printf("Draw\n");
                msgbyte=send(client_fd,&flag,sizeof(flag),0);
                printf("Play again\n");
                board();
                gamestart(turninput, client_fd);
//                close(fd);
//                break;
            }
            
            
            board();
            printf("SERVER Please Enter Your Choice or exit\n");
            scanf("%s",&choice);
//            if(!(choice>=1 && choice<=9))
//            {
//
//                printf("Invalid move \n");
//                printf("please enter a valid choice between 1-9\n");
//                scanf("%d",&choice);
//            }
            //        mark='O';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = marks;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = marks;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = marks;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = marks;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = marks;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = marks;
            
            else if (strcmp(choice,"7")==0 && square[7] == '7')
                square[7] = marks;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = marks;
            
            else if (strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = marks;
            
            
            msgbyte=send(client_fd,&choice,sizeof(choice),0);
            board();
            i = checkwin();
//            printf("\n%d\n",i);
            if(i==1)
            {    board();
//                int flag=10;
//                char flag[]="server win";
                printf("server win\n");
                printf("Play again\n");
                board();
                gamestart(turninput, client_fd);
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
            }
            if(i==0)
            {    board();
//                int flag=16;
//                char flag[]="draw";
                printf("Draw\n");
                printf("Play again\n");
                board();
                gamestart(turninput, client_fd);
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
            }
        }
    }
    
    if(turninput == 2)
    {
        i= checkwin();
        while(i!=1)
        {
            board();
            printf("SERVER Please Enter Your Choice or exit\n");
            scanf("%s",&choice);
//            if(!(choice>=1 && choice<=9))
//            {
//
//                printf("Invalid move \n");
//                printf("please enter a valid choice between 1-9\n");
//                scanf("%s",&choice);
//            }
            //        mark='O';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = marks;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = marks;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = marks;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = marks;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = marks;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = marks;
            
            else if (strcmp(choice,"7")==0&& square[7] == '7')
                square[7] = marks;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = marks;
            
            else if (strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = marks;
            
            
            msgbyte=send(client_fd,&choice,sizeof(choice),0);
            board();
            i = checkwin();
//            printf("\n%d\n",i);
            if(i==1)
            {    board();
//                int flag=10;
                char flag[]="server win";
                printf("server win\n");
                printf("Play again\n");
//                board();
                gamestart(turninput, client_fd);
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
            }
            if(i==0)
            {    board();
//                int flag=16;
                char flag[]="draw";
                printf("Draw\n");
                printf("Play again\n");
                board();
                gamestart(turninput, client_fd);
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
            }

            
            msgbyte=recv(client_fd,&choice,sizeof(choice),0);
            if(msgbyte < 0){
                printf("error recieving msg client msgbyte\n");
            } else {
                choice[msgbyte]= '\0';
                
            }
            printf("choice receieved: %s", choice);
//            if(choice==11)
//            {
//                printf("You win");
//                close(fd);
//                break;
//            }
            printf("choice receieved: %s", choice);
//            if(choice==15)
//            {
//                printf("Draw");
//                close(fd);
//                break;
//            }
            //        mark='X';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = mark;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = mark;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = mark;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = mark;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = mark;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = mark;
            
            else if (strcmp(choice,"7")==0 && square[7] == '7')
                square[7] = mark;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = mark;
            
            else if(strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = mark;
            
            
            i = checkwin();
//            printf("\n%d\n",i);
            if(i==1)
            {    board();
                int flag=10;
                printf("client win\n");
                printf("Play again\n");
                gamestart(turninput, client_fd);
                board();
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
           }
            if(i==0)
            {    board();
                int flag=16;
                printf("Draw\n");
                printf("Play again\n");
                board();
                gamestart(turninput, client_fd);
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
            }
            
            
                   }
    }

    
}

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void server( int server_number)
{
int			c, i;
int			n, len;
    int        msgbyte;
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
//memcpy(&address.sin_addr, node_ptr->h_addr, node_ptr->h_length);
    address.sin_addr.s_addr = inet_addr("10.17.4.93"); // replace with desired IP address
   
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

    printf("the question is \n");
    strcpy(qs, "Choose 'X' or 'O'");
    msgbyte=send(client_fd,&qs,sizeof(qs),0);

printf("WAITING FOR CLIENT MESSAGE.......\n");
    printf("The client's choice 'X' or 'O'\n");
    msgbyte=recv(client_fd,&option,sizeof(option),0);
    if(msgbyte < 0){
        printf("error recieving msg client choice msgbyte\n");
    } else {
        choice[msgbyte]= '\0';
        
    }
    printf("The client's choice received: %s\n", option);
//    if(option == 'X'){
        if(strcmp(option,"X")==0){
            turn = 1;
        mark = 'X';
        marks = 'O';
    } else{
        turn = 2;
        mark = 'O';
        marks = 'X';
    }
    
    gamestart(turn, client_fd);
//    printf("The client's turn '1' or '2'\n");
//    msgbyte=recv(client_fd,&turn,sizeof(turn),0);
//    printf("The client's turn choice received: %d\n", turn);
//    turn = 1;
//    char choice[BUFSIZE];
//    if(turn == 1){
//        i= checkwin();
//        while(i!=1)
//        {
//            msgbyte=recv(client_fd,&choice,sizeof(choice),0);
//            if(msgbyte < 0){
//                printf("error recieving msg client msgbyte\n");
//            } else {
//                choice[msgbyte]= '\0';
//
//            }
//
//            printf("choice receieved: %s", choice);
////            if(choice==11)
////            if(strcmp(choice,"server win")==0)
////            {
////                printf("You win");
////                close(fd);
////                break;
////            }
////            printf("choice receieved: %s", choice);
////            if(choice==15)
////            if(strcmp(choice,"draw")==0)
////            {
////                printf("Draw");
////                close(fd);
////                break;
////            }
//            //        mark='X';
//            if (strcmp(choice,"1")==0 && square[1] == '1')
//                square[1] = mark;
//
//            else if (strcmp(choice,"2")==0 && square[2] == '2')
//                square[2] = mark;
//
//            else if (strcmp(choice,"3")==0 && square[3] == '3')
//                square[3] = mark;
//
//            else if (strcmp(choice,"4")==0 && square[4] == '4')
//                square[4] = mark;
//
//            else if (strcmp(choice,"5")==0 && square[5] == '5')
//                square[5] = mark;
//
//            else if (strcmp(choice,"6")==0 && square[6] == '6')
//                square[6] = mark;
//
//            else if (strcmp(choice,"7")==0 && square[7] == '7')
//                square[7] = mark;
//
//            else if (strcmp(choice,"8")==0 && square[8] == '8')
//                square[8] = mark;
//
//            else if(strcmp(choice,"9")==0 && square[9] == '9')
//                square[9] = mark;
//
//
//            i = checkwin();
//            printf("\n%d\n",i);
//            if(i==1)
//            {    board();
////                int flag=10;
//                char flag[]="client win";
//                printf("client win");
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//            if(i==0)
//            {    board();
////                int flag=16;
//                char flag[]="draw";
//                printf("Draw");
//                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//
//
//            board();
//            printf("SERVER Please Enter Your Choice or exit\n");
//            scanf("%s",&choice);
////            if(!(choice>=1 && choice<=9))
////            {
////
////                printf("Invalid move \n");
////                printf("please enter a valid choice between 1-9\n");
////                scanf("%d",&choice);
////            }
//            //        mark='O';
//            if (strcmp(choice,"1")==0 && square[1] == '1')
//                square[1] = marks;
//
//            else if (strcmp(choice,"2")==0 && square[2] == '2')
//                square[2] = marks;
//
//            else if (strcmp(choice,"3")==0 && square[3] == '3')
//                square[3] = marks;
//
//            else if (strcmp(choice,"4")==0 && square[4] == '4')
//                square[4] = marks;
//
//            else if (strcmp(choice,"5")==0 && square[5] == '5')
//                square[5] = marks;
//
//            else if (strcmp(choice,"6")==0 && square[6] == '6')
//                square[6] = marks;
//
//            else if (strcmp(choice,"7")==0 && square[7] == '7')
//                square[7] = marks;
//
//            else if (strcmp(choice,"8")==0 && square[8] == '8')
//                square[8] = marks;
//
//            else if (strcmp(choice,"9")==0 && square[9] == '9')
//                square[9] = marks;
//
//
//            msgbyte=send(client_fd,&choice,sizeof(choice),0);
//            board();
//            i = checkwin();
//            printf("\n%d\n",i);
//            if(i==1)
//            {    board();
////                int flag=10;
////                char flag[]="server win";
//                printf("server win");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//            if(i==0)
//            {    board();
////                int flag=16;
////                char flag[]="draw";
//                printf("Draw");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//        }
//    }
//
//    if(turn == 2)
//    {
//        i= checkwin();
//        while(i!=1)
//        {
//            board();
//            printf("SERVER Please Enter Your Choice or exit\n");
//            scanf("%s",&choice);
////            if(!(choice>=1 && choice<=9))
////            {
////
////                printf("Invalid move \n");
////                printf("please enter a valid choice between 1-9\n");
////                scanf("%s",&choice);
////            }
//            //        mark='O';
//            if (strcmp(choice,"1")==0 && square[1] == '1')
//                square[1] = marks;
//
//            else if (strcmp(choice,"2")==0 && square[2] == '2')
//                square[2] = marks;
//
//            else if (strcmp(choice,"3")==0 && square[3] == '3')
//                square[3] = marks;
//
//            else if (strcmp(choice,"4")==0 && square[4] == '4')
//                square[4] = marks;
//
//            else if (strcmp(choice,"5")==0 && square[5] == '5')
//                square[5] = marks;
//
//            else if (strcmp(choice,"6")==0 && square[6] == '6')
//                square[6] = marks;
//
//            else if (strcmp(choice,"7")==0&& square[7] == '7')
//                square[7] = marks;
//
//            else if (strcmp(choice,"8")==0 && square[8] == '8')
//                square[8] = marks;
//
//            else if (strcmp(choice,"9")==0 && square[9] == '9')
//                square[9] = marks;
//
//
//            msgbyte=send(client_fd,&choice,sizeof(choice),0);
//            board();
//            i = checkwin();
//            printf("\n%d\n",i);
//            if(i==1)
//            {    board();
////                int flag=10;
//                char flag[]="server win";
//                printf("server win");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//            if(i==0)
//            {    board();
////                int flag=16;
//                char flag[]="draw";
//                printf("Draw");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//
//
//            msgbyte=recv(client_fd,&choice,sizeof(choice),0);
//            if(msgbyte < 0){
//                printf("error recieving msg client msgbyte\n");
//            } else {
//                choice[msgbyte]= '\0';
//
//            }
//            printf("choice receieved: %s", choice);
////            if(choice==11)
////            {
////                printf("You win");
////                close(fd);
////                break;
////            }
//            printf("choice receieved: %s", choice);
////            if(choice==15)
////            {
////                printf("Draw");
////                close(fd);
////                break;
////            }
//            //        mark='X';
//            if (strcmp(choice,"1")==0 && square[1] == '1')
//                square[1] = mark;
//
//            else if (strcmp(choice,"2")==0 && square[2] == '2')
//                square[2] = mark;
//
//            else if (strcmp(choice,"3")==0 && square[3] == '3')
//                square[3] = mark;
//
//            else if (strcmp(choice,"4")==0 && square[4] == '4')
//                square[4] = mark;
//
//            else if (strcmp(choice,"5")==0 && square[5] == '5')
//                square[5] = mark;
//
//            else if (strcmp(choice,"6")==0 && square[6] == '6')
//                square[6] = mark;
//
//            else if (strcmp(choice,"7")==0 && square[7] == '7')
//                square[7] = mark;
//
//            else if (strcmp(choice,"8")==0 && square[8] == '8')
//                square[8] = mark;
//
//            else if(strcmp(choice,"9")==0 && square[9] == '9')
//                square[9] = mark;
//
//
//            i = checkwin();
//            printf("\n%d\n",i);
//            if(i==1)
//            {    board();
//                int flag=10;
//                printf("client win");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//           }
//            if(i==0)
//            {    board();
//                int flag=16;
//                printf("Draw");
////                msgbyte=send(client_fd,&flag,sizeof(flag),0);
//                close(fd);
//                break;
//            }
//
//
//                   }
//    }

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

void client( int server_number, char *server_node )
{
int			length;
int			n, len, buflen;
//int         i, msgbyte, choice;
short			fd;
struct sockaddr_in	address;
struct hostent		*node_ptr;
char			local_node[NAMESIZE];
char			buffer[BUFSIZE];
//    char           mark;

/*  get the internet name of the local host node on which we are running  */
if( gethostname( local_node, NAMESIZE ) < 0 )
	{
	error( "client gethostname" );
	exit(1);
	}
fprintf(stderr, "client running on node %s\n", local_node);

/*  get the name of the remote host node on which we hope to find server  */
    if( server_node == NULL ){
//        	server_node = local_node;
        server_node = "10.17.4.252";
    }

fprintf(stderr, "client about to connect to server at port number %d on node %s\n",
		server_number, server_node);

/*  get structure for remote host node on which server resides  */
if( (node_ptr = gethostbyname( server_node )) == NULL )
	{
	error( "client gethostbyname" );
	exit(1);
	}

/*  set up Internet address structure for the server  */
memset(&address, 0, sizeof(address));
address.sin_family = AF_INET;
memcpy(&address.sin_addr, node_ptr->h_addr, node_ptr->h_length);
    address.sin_port = htons(server_number);

fprintf(stderr, "client full name of server node %s, internet address %s\n",
		node_ptr->h_name, inet_ntoa(address.sin_addr));

/*  open an Internet tcp socket  */
if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
	error( "client socket" );
	exit(1);
	}

/*  connect this socket to the server's Internet address  */
if( connect( fd, (struct sockaddr *)&address, sizeof(address) ) < 0 )
	{
	error( "client connect" );
	exit(1);
	}

/*  now find out what local port number was assigned to this client  */
len = sizeof(address);
if( getsockname( fd, (struct sockaddr *)&address, &length ) < 0 )
	{
	error( "client getsockname" );
	exit(1);
	}

/*  we are now successfully connected to a remote server  */
fprintf(stderr, "client at internet address %s, port %d\n",
		inet_ntoa(address.sin_addr), ntohs(address.sin_port));


printf("Send message to server....\n");
    printf("Enter the your choice : 'X' or 'O'\n");
    scanf("%s",&option);
//    if(!(option == 'X' || option == 'O'))
//    {
//        while(option != 'X' && option != 'O')
//        {
//            printf("Invalid move \n");
//            printf("please enter a valid choice\n");
//            scanf("%c",&option);
//        }
//    }
    if(strcmp(option,"X")==0){
        mark = 'X';
        marks = 'O';
        msgbyte=send(fd,&mark,sizeof(mark),0);
    } else {
        mark = 'O';
        marks = 'X';
        msgbyte=send(fd,&mark,sizeof(mark),0);
    }

//    printf("Enter your turn choice 1 or 2\n");
//    scanf("%d",&turn);
    turn = 1;
    if(!(turn == 1 || turn == 2))
    {
        while(turn != 1 && turn != 0)
        {
            printf("Invalid move \n");
            printf("please enter a valid choice\n");
            scanf("%d",&turn);
        }
    }
//    msgbyte=send(fd,&turn,sizeof(turn),0);
    int k = 1;
    if(turn == 1){
        
        i = checkwin();
        while(i!=1)
        {
            if( k == 1){
                board();
                
                
                
                printf("CLIENT Please Enter Your Choice\n");
                scanf("%s",&choice);
                //            if(!(choice>=1 && choice<=9))
                //            {
                //
                //                printf("Invalid move \n");
                //                printf("please enter a valid choice between 1-9\n");
                //                scanf("%d",&choice);
                //            }
                
                //            mark='X';
                if (strcmp(choice,"1")==0 && square[1] == '1')
                    square[1] = mark;
                
                else if (strcmp(choice,"2")==0 && square[2] == '2')
                    square[2] = mark;
                
                else if (strcmp(choice,"3")==0 && square[3] == '3')
                    square[3] = mark;
                
                else if (strcmp(choice,"4")==0 && square[4] == '4')
                    square[4] = mark;
                
                else if (strcmp(choice,"5")==0 && square[5] == '5')
                    square[5] = mark;
                
                else if (strcmp(choice,"6")==0 && square[6] == '6')
                    square[6] = mark;
                
                else if (strcmp(choice,"7")==0 && square[7] == '7')
                    square[7] = mark;
                
                else if (strcmp(choice,"8")==0 && square[8] == '8')
                    square[8] = mark;
                
                else if (strcmp(choice,"9")==0 && square[9] == '9')
                    square[9] = mark;
                
                
                msgbyte=send(fd,&choice,sizeof(choice),0);
            }
            k = 0;
            memset(choice, 0, sizeof(choice));
            board();
            
                msgbyte=recv(fd,&choice,sizeof(choice),0);
            printf("the message recieved %s\n", choice);
                
                if(msgbyte < 0){
                    printf("error recieving \n");
                } else {
                    choice[msgbyte] = '\0';
                    k = 1;
                }
            printf("the message recieved %s\n", choice);
                
                //            if(choice==10)
                if(strcmp(choice,"client win")==0)
                {
                    printf("You win");
                    close(fd);
                    break;
                }
                //            if(choice==16)
                if(strcmp(choice,"draw")==0)
                {
                    printf("Draw");
                    close(fd);
                    break;
                }
                //            mark='O';
                if (strcmp(choice,"1")==0 && square[1] == '1')
                    square[1] = marks;
                
                else if (strcmp(choice,"2")==0 && square[2] == '2')
                    square[2] = marks;
                
                else if (strcmp(choice,"3")==0 && square[3] == '3')
                    square[3] = marks;
                
                else if (strcmp(choice,"4")==0 && square[4] == '4')
                    square[4] = marks;
                
                else if (strcmp(choice,"5")==0 && square[5] == '5')
                    square[5] = marks;
                
                else if (strcmp(choice,"6")==0 && square[6] == '6')
                    square[6] = marks;
                
                else if (strcmp(choice,"7")==0 && square[7] == '7')
                    square[7] = marks;
                
                else if (strcmp(choice,"8")==0 && square[8] == '8')
                    square[8] = marks;
                
                else if(strcmp(choice,"9")==0 && square[9] == '9')
                    square[9] = marks;
                
                
                
                board();
                i = checkwin();
                printf("\n%d\n",i);
                if(i==1)
                {    board();
                    //                int flag=11;
                    char flag[] = "server win";
                    printf("server win");
                    msgbyte=send(fd,&flag,sizeof(flag),0);
                    close(fd);
                    break;
                }
                if(i==0)
                {    board();
                    //                int flag=15;
                    char flag[] = "draw";
                    printf("Draw");
                    msgbyte=send(fd,&flag,sizeof(flag),0);
                    close(fd);
                    break;
                }
                
        }
    }
    if(turn ==2){
        i = checkwin();
        while(i!=1)
        {
            board();
            msgbyte=recv(fd,&choice,sizeof(choice),0);
            
            if(choice==10)
            {
                printf("You win");
                close(fd);
                break;
            }
            if(choice==16)
            {
                printf("Draw");
                close(fd);
                break;
            }
//            mark='O';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = marks;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = marks;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = marks;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = marks;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = marks;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = marks;
            
            else if (strcmp(choice,"7")==0 && square[7] == '7')
                square[7] = marks;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = marks;
            
            else if(strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = marks;
            
            
            
            board();
            i = checkwin();
//            printf("\n%d\n",i);
            if(i==1)
            {    board();
                int flag=11;
                printf("server win");
                msgbyte=send(fd,&flag,sizeof(flag),0);
                close(fd);
                break;
            }
            if(i==0)
            {    board();
                int flag=15;
                printf("Draw");
                msgbyte=send(fd,&flag,sizeof(flag),0);
                close(fd);
                break;
            }

            
            
            
            printf("CLIENT Please Enter Your Choice\n");
            scanf("%s",&choice);
//            if(!(choice>=1 && choice<=9))
//            {
//
//                printf("Invalid move \n");
//                printf("please enter a valid choice between 1-9\n");
//                scanf("%d",&choice);
//            }
            
//            mark='X';
            if (strcmp(choice,"1")==0 && square[1] == '1')
                square[1] = mark;
            
            else if (strcmp(choice,"2")==0 && square[2] == '2')
                square[2] = mark;
            
            else if (strcmp(choice,"3")==0 && square[3] == '3')
                square[3] = mark;
            
            else if (strcmp(choice,"4")==0 && square[4] == '4')
                square[4] = mark;
            
            else if (strcmp(choice,"5")==0 && square[5] == '5')
                square[5] = mark;
            
            else if (strcmp(choice,"6")==0 && square[6] == '6')
                square[6] = mark;
            
            else if (strcmp(choice,"7")==0 && square[7] == '7')
                square[7] = mark;
            
            else if (strcmp(choice,"8")==0 && square[8] == '8')
                square[8] = mark;
            
            else if (strcmp(choice,"9")==0 && square[9] == '9')
                square[9] = mark;
            
            
            msgbyte=send(fd,&choice,sizeof(choice),0);
            board();
            
            
                        
        }
    }

    close(fd);
/*  close the connection to the server  */
if( close(fd) < 0 )
	{
	error( "client close" );
	// exit(1);
	}
}

int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        printf("Usage: %s [-s|-c]\n", argv[0]);
//        exit(1);
//    }

    char* choice = (argv[1]);
    if (strcmp(choice,"-s")==0) {
        int    server_number;

        /*  there must be zero or one command line argument  */
        if( argc > 3)
            {
            fprintf(stderr, "usage: server [server-number]\n");
            exit(1);
            }

        /*  get the server's port number from the first parameter  */
//        server_number = default_server_number;
        server_number = 0;
        /*  now let the common server do the real work  */
        server( server_number);
    } else if (strcmp(choice,"-c")==0) {
        char    *server_node;
        int    server_number;

        /*  there must be one or two command line arguments  */
        if( argc > 4 || argc < 2 )
            {
            fprintf(stderr, "usage: client server-number [server-node]\n");
            exit(1);
            }

        /*  get the server's port number from the first parameter  */
//        server_number = atoi(argv[1]);
        server_number = atoi(argv[2]);

        /*  get the server's node name from the second parameter  */
        if( argc <= 3 )
            server_node = NULL;
        else
            server_node = argv[3];
//        server_node = argv[4];

        /*  now let the common client do the real work  */
        client( server_number, server_node );

    } else {
        printf("Invalid choice\n");
        exit(1);
    }

    return 0;
}
