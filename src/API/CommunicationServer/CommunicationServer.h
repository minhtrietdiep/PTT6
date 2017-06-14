#pragma once 

#include <string>
#include <pthread.h>
#include <vector>
#include <Logger.h>
#include "Thread.h"

class CommunicationServer
{
    public:
        CommunicationServer(int port);
        ~CommunicationServer();
        int AcceptTCPConnection(int serverSocket);
        int ReceiveMessage(int socket, char *message, int bufferSize);
        int SendMessage(int socket, const char *message, int bufferSize);   
    private:
        void Error(std::string message);
        int CreateServerSocket(int port);
        pthread_t m_Thread;
        Thread m_MainThread;
        Logger m_Logger;
        std::vector<int*> socketPointers;
};