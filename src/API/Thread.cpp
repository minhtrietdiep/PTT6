#include "../Const.h"
#include "Thread.h"
#include "MessageQueue.h"
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

Thread::Thread()
{
    
}

Thread::~Thread()
{
    
}

void * Thread::MessageThread(void *args)
{
    MessageThreadArgments * messageThreadArgs = (MessageThreadArgments *) args;
    MessageQueue mq;

    char receiveBuffer[MAX_MESSAGE_SIZE];
    int messageSize = 0;
    bool loop = true;

    while(loop)
    {
        messageThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "waiting for tcp message");

        memset(receiveBuffer,'\0', sizeof(receiveBuffer) / sizeof(receiveBuffer[0]));
        messageSize = messageThreadArgs->communication->ReceiveMessage(*messageThreadArgs->clientSocket, receiveBuffer, sizeof(receiveBuffer) / sizeof(receiveBuffer[0]));
        
        std::string str (receiveBuffer);


        if(str == "exit" || messageSize < 1)
        {
            loop = false;
            messageThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "exiting messagethread");
        }
        else
        {
            mq.Write(MQ_NAME_RECEIVED_MESSAGES, str);

            char stringt[256];
            sprintf(stringt, "thread nr %lu, message: %s\n", pthread_self(), receiveBuffer);

            messageThreadArgs->logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, std::string(stringt));
            
            //messageThreadArgs->communication->SendMessage(*messageThreadArgs->clientSocket, receiveBuffer, messageSize);
        }
    }

    shutdown(*messageThreadArgs->clientSocket, SHUT_RDWR);
    close(*messageThreadArgs->clientSocket);
    delete messageThreadArgs->clientSocket;

    messageThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "closed client sockets");

    return NULL;
}

void * Thread::ListenerThread(void *args)
{
    ListenerThreadArgments * listenerThreadArgs = (ListenerThreadArgments *) args;

    while(true)
    {
        //listenerThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "waiting for new client");

        pthread_t subThread;
        Thread thread;
        MessageThreadArgments messageThreadArgments;
        messageThreadArgments.clientSocket = new int (listenerThreadArgs->communication->AcceptTCPConnection(listenerThreadArgs->serverSocket));
        messageThreadArgments.communication = listenerThreadArgs->communication;
        messageThreadArgments.logger = listenerThreadArgs->logger;
        
        pthread_create(&subThread, NULL, thread.MessageThread, &messageThreadArgments); 
        pthread_detach(subThread);

        //listenerThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "new thread created");

        listenerThreadArgs->clientSockets.push_back(messageThreadArgments.clientSocket);
        listenerThreadArgs->receiveThreads.push_back(subThread);
    }

    return NULL;
}