#pragma once 

#include <vector>
#include <pthread.h>

class CommunicationServer;

class Thread {
    public:
        static void * MessageThread(void *args);
        static void * ListenerThread(void *args);
        struct MessageThreadArgments { int *clientSocket; CommunicationServer *communication; } ;
        struct ListenerThreadArgments { int serverSocket; std::vector<int*> clientSockets; std::vector<pthread_t> receiveThreads; CommunicationServer *communication; } ;
        ListenerThreadArgments my_args;
};