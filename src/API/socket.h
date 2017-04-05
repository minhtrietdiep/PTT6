#pragma once

void DieWithError(const char * errorMessage);  /* Error handling function */
int createTCPServerSocket(unsigned short port); /* Create TCP server socket */
int createTCPClientSocket(const char * addr, unsigned short port); /* Create TCP server socket */
int acceptTCPConnection(int servSock);  /* Accept TCP connection request */
int sendMessage(int socket, const char * message); /* Send a message */
int receiveMessage(int socket, char * message, int buffersize);
int sendMessage(int socket, char *message, int buffersize)