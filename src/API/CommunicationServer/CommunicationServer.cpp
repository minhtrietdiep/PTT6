#include "CommunicationServer.h"
#include "Thread.h"

#include <Const.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstring>
#include <iostream>

CommunicationServer::CommunicationServer(int port)
{
    logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

    
    m_mainThread = new Thread;
    m_mainThread->my_args.serverSocket = m_CreateServerSocket(port);
    m_mainThread->my_args.communication = this;
    m_mainThread->my_args.logger = logger;
    m_mainThread->my_args.clientSockets = new std::vector<int*>;

    pthread_create(&m_thread, NULL, m_mainThread->ListenerThread, &m_mainThread->my_args);
    pthread_detach(m_thread);
}

CommunicationServer::~CommunicationServer()
{
    for(unsigned int i = 0; i < m_mainThread->my_args.clientSockets->size(); i++)
    {
        close(*m_mainThread->my_args.clientSockets->at(i));
    }

    for(unsigned int i=0; i < m_mainThread->my_args.receiveThreads.size(); i++)
    {
        pthread_cancel(m_mainThread->my_args.receiveThreads.at(i));
    }
    
    pthread_cancel(m_thread);
    shutdown(m_mainThread->my_args.serverSocket, SHUT_RDWR);
    close(m_mainThread->my_args.serverSocket);

    delete m_mainThread->my_args.clientSockets;
    delete m_mainThread;

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "killed threads and closed sockets");

    delete logger;
}

void CommunicationServer::m_Error(const char *message)
{
    char stringt[256];
    sprintf(stringt, "%s -> %s", message, strerror(errno));
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
        m_Error("socket() failed");
    }

    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0)
    {
        m_Error("setsockopt() failed");
    }

    if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        m_Error("bind() failed");
    }

    if(listen(serverSocket, 5) < 0)
    {
        m_Error("listen() failed");
    }

    char stringt[256];
    sprintf(stringt, "listening on %d", port);
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
        m_Error("accept() failed");
    }

    char stringt[256];
    sprintf(stringt, "accepted new connection from %s", inet_ntoa(clientAddress.sin_addr));
    logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, std::string(stringt));

    return clientSocket;
}

int CommunicationServer::ReceiveMessage(int socket, char *message, int bufferSize)
{
    bufferSize--;
        
    int receiveMessageSize = recv(socket, message, bufferSize, 0);

    if(receiveMessageSize < 0)
    {
        m_Error("recv() failed");
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
        m_Error("send() failed");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "message sent");

    return sendMessageSize;
}