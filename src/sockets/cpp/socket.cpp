#include <sys/socket.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <errno.h>

#define PORT 4244

void error(const char *msg)
{
    printf("Error: %s -> %s\n", msg, strerror(errno));
}

int createServerSocket() {
	int serverSocket;
	struct sockaddr_in server_address;

	// Create socket
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket < 0) {
    	error("socket() failed");
    }

	int value = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

    // Create server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family		= AF_INET;
    server_address.sin_addr.s_addr	= htonl(INADDR_ANY);
    server_address.sin_port			= htons(PORT);

    // Bind to port
    if(bind(serverSocket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    	error ("bind() failed");
    }

    // Mark the socket so it will listen for incoming connections
    if(listen(serverSocket, 5) < 0) {
    	error ("listen() failed");
    }

    printf("Socket created, listening on %d\n", PORT);

    return serverSocket;
}

int acceptTCPConnection(int serverSocket) {
	int clientSocket;
	struct sockaddr_in client_address;
	unsigned int client_length;

	// Get length of struct
	client_length = sizeof(client_address);

	// Accept client
	clientSocket = accept(serverSocket, (struct sockaddr *) &client_address, &client_length);
	if(clientSocket < 0) {
		error("accept() failed");
	}

	printf("Accepted %s\n", inet_ntoa(client_address.sin_addr));

	return clientSocket;
}

int receiveMessage(int socket, char *message, int buffersize) {
	int  recvMsgSize;
    buffersize--;
        
    // Receive message
    recvMsgSize = recv(socket, message, buffersize, 0);
    message[recvMsgSize] = '\0';

    return recvMsgSize;
}

void *messageThread(void *args) {

	char bf[256];
	bool loop = true;
	int msgSize = 0;
	int *socketclnt = (int *) args;

	std::cout << "started messagethread "<< socketclnt << "  " << pthread_self() << std::endl;

	while(loop) {
		bzero(bf, 256);
		msgSize = receiveMessage(*socketclnt, bf, 256);
		std::string str (bf);
		printf("Thread nr %lu, message: ", pthread_self());

		std::cout << str << std::endl;

		if(str == "exit" || msgSize < 1) {
			loop = false;
		}
	}

	shutdown(*socketclnt, SHUT_RDWR);
	close(*socketclnt);
	delete socketclnt;
	printf("Thread nr %lu, sockets closed\n", pthread_self());
}

void *listenerThread(void *args) {

	int *socketsrv = (int *) args;
	bool loop = true;

	std::cout << "listening for incoming connections " << pthread_self() << std::endl;

	while(loop) {
		pthread_t subThread;
		std::cout << "waiting for new client" << std::endl;
		int * sockclntP = new int (acceptTCPConnection(*socketsrv));
		std::cout << "new client accepted" << std::endl;
		pthread_create(&subThread, NULL, messageThread, sockclntP); 
		pthread_detach(subThread);
	}
}

int main(int argc, char **argv) {
    char buffer[256];
	int socksrv, sockcl;

	socksrv = createServerSocket();

	pthread_t thread;
	int threadCount = 0;

	pthread_create(&thread, NULL, listenerThread, &socksrv);
	pthread_detach(thread);
	std::cout << "created thread" << std::endl; 
	
	while(true){

		// TODO
	}

	std::cout << "Closing server sockets." << std::endl;

	shutdown(socksrv, SHUT_RDWR);
	close(socksrv);

	std::cout << "Main program exiting." << std::endl;

	pthread_exit(NULL);
     
    return 0; 
}