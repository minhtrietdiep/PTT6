#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4245

void error(const char *msg)
{
    printf("Error: %s\n", msg);
}

int createServerSocket() {
	int serverSocket;
	struct sockaddr_in server_address;

	// Create socket
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverSocket < 0) {
    	error("socket() failed");
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

int receiveMessage(int socket, char * message, int buffersize) {
	int  recvMsgSize;
    buffersize--;
        
    // Receive message
    recvMsgSize = recv(socket, message, buffersize, 0);
    message[recvMsgSize] = '\0';
    if (recvMsgSize < 1)
    {		
        error("recv() failed");
    }

    printf("Message received\n");

    return recvMsgSize;
}

int main(int argc, char **argv) {
    char buffer[256];
	int socksrv, sockcl;

	socksrv = createServerSocket();

    while(true){

	    
	    sockcl = acceptTCPConnection(socksrv);

	    printf("\n");

	    int sterf = 1;

	    while(sterf > 0) {
	    	sterf = receiveMessage(sockcl, buffer, 256);
	    	printf("Here is the message: %s\n",buffer);
	    }

	    shutdown(sockcl, SHUT_RDWR);
	    //shutdown(socksrv, SHUT_RDWR);

	    //close(sockcl);
    	//close(socksrv);

	}  
     
    return 0; 
}