#pragma once 

#include <string>
#include <pthread.h>
#include <vector>
#include <Logger.h>

class Thread;

class CommunicationServer
{
    public:
        CommunicationServer(int port);
        ~CommunicationServer();
        int AcceptTCPConnection(int serverSocket);
        int ReceiveMessage(int socket, char *message, int bufferSize);
        int SendMessage(int socket, char *message, int bufferSize);   
    private:
        void m_Error(const char *message);
        int m_CreateServerSocket(int port);
        Thread *m_mainThread;
        pthread_t m_thread;
        Logger *logger;
};