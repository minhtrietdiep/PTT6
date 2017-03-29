#include <memory.h>     /* for memset() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <sys/socket.h> /* for send() and recv() */
#include <stdio.h>		/* for perror() */
#include <stdlib.h>		/* for exit() */
#include <unistd.h> 	/* for close() */
#include <iostream>
#include <string.h>
#include <signal.h>

using namespace std;

#include "socket.h"

#define MAXPENDING 5    /* Maximum outstanding connection requests */

void DieWithError(const char * errorMessage)
{
	perror(errorMessage);
	exit(1);
}

int createTCPServerSocket(unsigned short port)
{
	int                 sock;         /* socket to create */
	struct sockaddr_in  echoServAddr; /* Local address */

									  /* Create socket for incoming connections */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		DieWithError("socket() failed");
	}

	/* Construct local address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr));  /* Zero out structure */
	echoServAddr.sin_family = AF_INET;                /* Internet address family */
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	echoServAddr.sin_port = htons(port);              /* Local port */

													  /* Bind to the local address */
	if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	{
		DieWithError("bind() failed");
	}

	/* Mark the socket so it will listen for incoming connections */
	if (listen(sock, MAXPENDING) < 0)
	{
		DieWithError("listen() failed");
	}

	return (sock);
}

int createTCPClientSocket(const char * servIP, unsigned short port)
{
	int                 sock;         /* Socket descriptor */
	struct sockaddr_in  echoServAddr; /* Echo server address */

									  /* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		DieWithError("socket() failed");
	}

	/* Construct the server address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
	echoServAddr.sin_family = AF_INET;             /* Internet address family */
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
	echoServAddr.sin_port = htons(port);         /* Server port */

												 /* Establish the connection to the echo server */
	if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	{
		DieWithError("connect() failed");
	}

	return (sock);
}

int acceptTCPConnection(int servSock)
{
	// 'servSock' is obtained from CreateTCPServerSocket()

	int                 clntSock;     /* Socket descriptor for client */
	struct sockaddr_in  echoClntAddr; /* Client address */
	unsigned int        clntLen;      /* Length of client address data structure */

									  /* Set the size of the in-out parameter */
	clntLen = sizeof(echoClntAddr);

	/* Wait for a client to connect */
	clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen);
	if (clntSock < 0)
	{
		DieWithError("accept() failed");
	}
	/* clntSock is connected to a client! */

	return (clntSock);
}

int receiveMessage(int socket, char * message, int buffersize)
{
	// 'clntSocket' is obtained from AcceptTCPConnection()

	int  recvMsgSize;                   /* Size of received message */
	buffersize--;

	// Preventing TCP sockets from sending a SIGPIPE signal when disconnected
	signal(SIGPIPE, SIG_IGN);

	/* Receive message */
	recvMsgSize = recv(socket, message, buffersize, 0);
	message[recvMsgSize] = '\0';
	if (recvMsgSize < 1)
	{
		perror("recv() failed");
	}
	return recvMsgSize;
}

int sendMessage(int socket, const char * message)
{
	int sendMsgSize = strlen(message);	/* Size of message to send */

										// Preventing TCP sockets from sending a SIGPIPE signal when disconnected
	signal(SIGPIPE, SIG_IGN);

	/* Send message */
	if (send(socket, message, sendMsgSize, 0) != sendMsgSize)
	{
		perror("send() failed");
		return -1;
	}
	else {
		return 1;
	}
}


