#include "Thread.h"
#include "CommunicationServer.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <cstring>
#include <iostream>

void * Thread::MessageThread(void *args)
{
    MessageThreadArgments * messageThreadArgs = (MessageThreadArgments *) args;

    char receiveBuffer[256];
    int messageSize = 0;
    bool loop = true;

    while(loop) {
        memset(receiveBuffer,'\0', 256);
        messageSize = messageThreadArgs->communication->ReceiveMessage(*messageThreadArgs->clientSocket, receiveBuffer, 256);
        std::string str (receiveBuffer);
        printf("Thread nr %lu, message: %s\n", pthread_self(), receiveBuffer);

        messageThreadArgs->communication->SendMessage(*messageThreadArgs->clientSocket, receiveBuffer, messageSize);

        if(str == "exit" || messageSize < 1) {
            loop = false;
        }
    }

    shutdown(*messageThreadArgs->clientSocket, SHUT_RDWR);
    close(*messageThreadArgs->clientSocket);
    delete messageThreadArgs->clientSocket;

    return NULL;
}

void * Thread::ListenerThread(void *args)
{
    ListenerThreadArgments * listenerThreadArgs = (ListenerThreadArgments *) args;

    while(true) {
        pthread_t subThread;
        Thread thread;
        MessageThreadArgments messageThreadArgments;
        messageThreadArgments.clientSocket = new int (listenerThreadArgs->communication->AcceptTCPConnection(listenerThreadArgs->serverSocket));
        messageThreadArgments.communication = listenerThreadArgs->communication;
        
        pthread_create(&subThread, NULL, thread.MessageThread, &messageThreadArgments); 
        pthread_detach(subThread);

        listenerThreadArgs->clientSockets.push_back(messageThreadArgments.clientSocket);
        listenerThreadArgs->receiveThreads.push_back(subThread);
    }

    return NULL;
}