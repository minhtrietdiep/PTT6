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
#include <sstream>

CommunicationServer::CommunicationServer(int port) :
m_Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH)
{
    //m_MainThread = new Thread;
    m_MainThread.my_args.serverSocket = CreateServerSocket(port);
    m_MainThread.my_args.communication = this;
    m_MainThread.my_args.logger = &m_Logger;
    m_MainThread.my_args.clientSockets = &socketPointers;
    
    pthread_create(&m_Thread, NULL, m_MainThread.ListenerThread, &m_MainThread.my_args);
    pthread_detach(m_Thread);
}

CommunicationServer::~CommunicationServer()
{
    for(unsigned int i = 0; i < m_MainThread.my_args.clientSockets->size(); i++)
    {
        close(*(m_MainThread.my_args.clientSockets->at(i)));
    }

    for(unsigned int i=0; i < m_MainThread.my_args.receiveThreads.size(); i++)
    {
        pthread_cancel(m_MainThread.my_args.receiveThreads.at(i));
    }
    
    pthread_cancel(m_Thread);
    shutdown(m_MainThread.my_args.serverSocket, SHUT_RDWR);
    close(m_MainThread.my_args.serverSocket);


    //delete m_MainThread.my_args.clientSockets;
    //delete m_MainThread;

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "killed threads and closed sockets");
 }

void CommunicationServer::Error(std::string message)
{
    std::ostringstream logOutput;
    logOutput << message << " -> " << strerror(errno);
    m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, logOutput.str());
    exit(-1);
}

int CommunicationServer::CreateServerSocket(int port)
{
    int value = 1;
    struct sockaddr_in serverAddress;

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "server socket created");
    
    if(serverSocket < 0)
    {
        Error("socket() failed");
    }

    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)) < 0)
    {
        Error("setsockopt() failed");
    }

    if(bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        Error("bind() failed");
    }

    if(listen(serverSocket, 5) < 0)
    {
        Error("listen() failed");
    }

    std::ostringstream logOutput;
    logOutput << "listening on " << port;
    m_Logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, logOutput.str());

    return serverSocket;
}

int CommunicationServer::AcceptTCPConnection(int serverSocket)
{
    struct sockaddr_in clientAddress;

    socklen_t clientLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientLength);

    if(clientSocket < 0)
    {
        Error("accept() failed");
    }

    std::ostringstream logOutput;
    logOutput << "accepted new connection from " << inet_ntoa(clientAddress.sin_addr);
    m_Logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, logOutput.str());

    return clientSocket;
}

int CommunicationServer::ReceiveMessage(int socket, char *message, int bufferSize)
{
    bufferSize--;
        
    int receiveMessageSize = recv(socket, message, bufferSize, 0);

    if(receiveMessageSize < 0)
    {
        std::ostringstream logOutput;
        logOutput << "recv() failed";
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, logOutput.str());
    }

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "message received");

    message[receiveMessageSize] = '\0';

    return receiveMessageSize;
}

int CommunicationServer::SendMessage(int socket, const char *message, int bufferSize)
{
    int sendMessageSize = send(socket, message, bufferSize, 0);

    if(sendMessageSize < 0)
    {
        Error("send() failed");
    }

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "message sent");

    return sendMessageSize;
}