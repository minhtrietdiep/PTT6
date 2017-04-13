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
    logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
}

Thread::~Thread()
{
    delete logger;
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
        logger->Write(Logger::Severity::DEBUG, "waiting for tcp message", __func__);

        memset(receiveBuffer,'\0', sizeof(receiveBuffer) / sizeof(receiveBuffer[0]));
        messageSize = messageThreadArgs->communication->ReceiveMessage(*messageThreadArgs->clientSocket, receiveBuffer, sizeof(receiveBuffer) / sizeof(receiveBuffer[0]));
        
        std::string str (receiveBuffer);


        if(str == "exit" || messageSize < 1)
        {
            loop = false;
            logger->Write(Logger::Severity::DEBUG, "exiting messagethread", __func__);
        }
        else
        {
            mq.Write(MQ_NAME_RECEIVED_MESSAGES, str);

            char * string = sprintf("thread nr %lu, message: %s\n", pthread_self(), receiveBuffer);

            logger->Write(Logger::Severity::INFO, str(string), __func__);
            
            //messageThreadArgs->communication->SendMessage(*messageThreadArgs->clientSocket, receiveBuffer, messageSize);
        }
    }

    shutdown(*messageThreadArgs->clientSocket, SHUT_RDWR);
    close(*messageThreadArgs->clientSocket);
    delete messageThreadArgs->clientSocket;

    logger->Write(Logger::Severity::DEBUG, "closed client sockets", __func__);

    return NULL;
}

void * Thread::ListenerThread(void *args)
{
    ListenerThreadArgments * listenerThreadArgs = (ListenerThreadArgments *) args;

    while(true)
    {
        logger->Write(Logger::Severity::DEBUG, "waiting for new client", __func__);

        pthread_t subThread;
        Thread thread;
        MessageThreadArgments messageThreadArgments;
        messageThreadArgments.clientSocket = new int (listenerThreadArgs->communication->AcceptTCPConnection(listenerThreadArgs->serverSocket));
        messageThreadArgments.communication = listenerThreadArgs->communication;
        
        pthread_create(&subThread, NULL, thread.MessageThread, &messageThreadArgments); 
        pthread_detach(subThread);

        logger->Write(Logger::Severity::DEBUG, "new thread created", __func__);

        listenerThreadArgs->clientSockets.push_back(messageThreadArgments.clientSocket);
        listenerThreadArgs->receiveThreads.push_back(subThread);
    }

    return NULL;
}