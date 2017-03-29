#pragma once

#ifndef TCP_H_
#define TCP_H_

extern void DieWithError(const char * errorMessage);  /* Error handling function */
extern int createTCPServerSocket(unsigned short port); /* Create TCP server socket */
extern int createTCPClientSocket(const char * addr, unsigned short port); /* Create TCP server socket */
extern int acceptTCPConnection(int servSock);  /* Accept TCP connection request */
extern int sendMessage(int socket, const char * message); /* Send a message */
extern int receiveMessage(int socket, char * message, int buffersize);

#endif