#pragma once 

#include <vector>
#include <pthread.h>
#include <Logger.h>

class CommunicationServer;

class Thread
{
    public:
        Thread();
        ~Thread();
        static void *MessageThread(void *args);
        static void *ListenerThread(void *args);
        static void *SenderThread(void *args);
        struct MessageThreadArguments 
        {
            std::vector<int*> *clientSockets;
            int *clientSocket;
            CommunicationServer *communication;
            Logger *logger;
        };
        struct ListenerThreadArguments
        {
            int serverSocket;
            std::vector<int*> *clientSockets;
            std::vector<pthread_t> receiveThreads;
            CommunicationServer *communication;
            Logger *logger;
        };
        struct SenderThreadArguments
        {
            std::vector<int*> *clientSockets;
            CommunicationServer *communication;
            Logger *logger;
        };
        ListenerThreadArguments my_args ;
};