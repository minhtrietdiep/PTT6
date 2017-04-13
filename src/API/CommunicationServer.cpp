#include "CommunicationServer.h"
#include "Thread.h"

#include <Const.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstring>
#include <iostream>

CommunicationServer::CommunicationServer(int port)
{
    logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

    this->m_mainThread = new Thread;
    this->m_mainThread->my_args.serverSocket = this->m_CreateServerSocket(port);
    this->m_mainThread->my_args.communication = this;
    this->m_mainThread->my_args.logger = logger;

    pthread_create(&this->m_thread, NULL, this->m_mainThread->ListenerThread, &this->m_mainThread->my_args);
    pthread_detach(this->m_thread);
}

CommunicationServer::~CommunicationServer()
{
   for(unsigned int i=0; i < this->m_mainThread->my_args.clientSockets.size(); i++)
   {
        close(*this->m_mainThread->my_args.clientSockets[i]);
        pthread_cancel(this->m_mainThread->my_args.receiveThreads[i]);
    }

    pthread_cancel(this->m_thread);
    shutdown(this->m_mainThread->my_args.serverSocket, SHUT_RDWR);
    close(this->m_mainThread->my_args.serverSocket);

    delete this->m_mainThread;

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "killed threads and closed sockets");

    delete logger;
}

void CommunicationServer::m_Error(const char *message)
{
    char stringt[256];
    sprintf(stringt, "%s -> %s\n", message, strerror(errno));
    logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, std::string(stringt));
    exit(-1);
}

int CommunicationServer::m_CreateServerSocket(int port)
{
    int value = 1;
    struct sockaddr_in serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "server socket created");
    
    if(serverSocket < 0)
    {
        this->m_Error("socket() failed");
    }

    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0)
    {
        this->m_Error("setsockopt() failed");
    }

    if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        this->m_Error("bind() failed");
    }

    if(listen(serverSocket, 5) < 0)
    {
        this->m_Error("listen() failed");
    }

    char stringt[256];
    sprintf(stringt, "listening on %d\n", port);
    logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, std::string(stringt));

    return serverSocket;
}

int CommunicationServer::AcceptTCPConnection(int serverSocket)
{
    struct sockaddr_in clientAddress;

    socklen_t clientLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientLength);

    if(clientSocket < 0)
    {
        this->m_Error("accept() failed");
    }

    char stringt[256];
    sprintf(stringt, "accepted new connection from %s\n", inet_ntoa(clientAddress.sin_addr));
    logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, std::string(stringt));

    return clientSocket;
}

int CommunicationServer::ReceiveMessage(int socket, char *message, int bufferSize)
{
    bufferSize--;
        
    int receiveMessageSize = recv(socket, message, bufferSize, 0);

    if(receiveMessageSize < 0)
    {
        this->m_Error("recv() failed");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "message received");

    message[receiveMessageSize] = '\0';

    return receiveMessageSize;
}

int CommunicationServer::SendMessage(int socket, char *message, int bufferSize)
{
    int sendMessageSize = send(socket, message, bufferSize, 0);

    if(sendMessageSize < 0)
    {
        this->m_Error("send() failed");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "message sent");

    return sendMessageSize;
}