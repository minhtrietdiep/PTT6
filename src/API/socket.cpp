//#include "socket.h"


#include <vector>
#include <pthread.h>










struct threadArgments
{
    int serverSocket;
    std::vector<int*> clientSockets;
    std::vector<pthread_t> receiveThreads;
} ;

#define PORT 4244

void error(const char *msg)
{
    printf("Error: %s -> %s\n", msg, strerror(errno));
    exit(-1);
}

int createServerSocket() {
	int serverSocket;
	struct sockaddr_in server_address;

	// Create socket
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket < 0) {
    	error("socket() failed");
    }

    // Set socket options
	int value = 1;
    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0) {
        error("setsockopt() failed");
    }

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
    if(recvMsgSize < 0) {
        error("recv() failed");
    }

    message[recvMsgSize] = '\0';

    return recvMsgSize;
}

int sendMessage(int socket, char *message, int buffersize) {
    int sendMsgSize;
    sendMsgSize = send(socket, message, buffersize, 0);
    if(sendMsgSize < 0) {
        error("send() failed");
    }
    return sendMsgSize;
}

void *messageThread(void *args) {

	char *sendMsg = "JE MOEDER IS EEN HOER!";
	char bf[256];
	bool loop = true;
	int msgSize = 0;
	int *socketclnt = (int *) args;

	while(loop) {
		memset(bf,'\0', 256);
		msgSize = receiveMessage(*socketclnt, bf, 256);
		std::string str (bf);
		printf("Thread nr %lu, message: ", pthread_self());

		std::cout << str << std::endl;

		sendMessage(*socketclnt, sendMsg, 21);

		if(str == "exit" || msgSize < 1) {
			loop = false;
		}
	}

	shutdown(*socketclnt, SHUT_RDWR);
	close(*socketclnt);
	delete socketclnt;
}

void *listenerThread(void *args) {
    threadArgments * threadArgs = (threadArgments *) args;

    while(true) {
        pthread_t subThread;
        
        int * sockclntP = new int (acceptTCPConnection(threadArgs->serverSocket));
        
        std::cout << "new client accepted" << std::endl;

        pthread_create(&subThread, NULL, messageThread, sockclntP); 
        pthread_detach(subThread);

        threadArgs->clientSockets.push_back(sockclntP);
        threadArgs->receiveThreads.push_back(subThread);
    }
}

int main(int argc, char **argv) {
    char buffer[256];
	int socksrv;
    pthread_t thread;
    threadArgments threadArgs;

    threadArgs.serverSocket = createServerSocket();

    pthread_create(&thread, NULL, listenerThread, &threadArgs);
    pthread_detach(thread);

	std::cout << "created thread" << std::endl; 
	
	std::cout << "Press any key to exit" << std::endl;

	getchar();

    for(int i=0; i < threadArgs.clientSockets.size(); i++) {
        close(*threadArgs.clientSockets[i]);
        pthread_cancel(threadArgs.receiveThreads[i]);
    }
    
    std::cout << "Closing client sockets & threads." << std::endl;

    pthread_cancel(thread);

    std::cout << "Closing listener thread." << std::endl;

	shutdown(socksrv, SHUT_RDWR);
	close(socksrv);

    std::cout << "Closing server socket." << std::endl;
	
    std::cout << "Main program exiting." << std::endl;

	pthread_exit(NULL);
     
    return 0; 
}