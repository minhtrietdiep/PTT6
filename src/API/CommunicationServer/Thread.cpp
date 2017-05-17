#include "Thread.h"
#include "MessageQueue.h"
#include "CommunicationServer.h"

#include <Const.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

Thread::Thread()
{
    
}

Thread::~Thread()
{
    
}

void * Thread::MessageThread(void *args)
{
    MessageThreadArguments * messageThreadArgs = (MessageThreadArguments *) args;
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

            std::ostringstream logOutput;
            logOutput << "thread nr " << pthread_self() << ", message: " << receiveBuffer;
            messageThreadArgs->logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, logOutput.str());
        }
    }

    shutdown(*messageThreadArgs->clientSocket, SHUT_RDWR);
    close(*messageThreadArgs->clientSocket);
    delete messageThreadArgs->clientSocket;

    for(unsigned int i = 0; i < messageThreadArgs->clientSockets->size(); i++)
    {
        if (messageThreadArgs->clientSockets->at(i) == messageThreadArgs->clientSocket)
        {
            messageThreadArgs->clientSockets->erase(messageThreadArgs->clientSockets->begin() + i);
        }
    }

    messageThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "closed client sockets");

    return NULL;
}

void * Thread::ListenerThread(void *args)
{
    ListenerThreadArguments * listenerThreadArgs = (ListenerThreadArguments *) args;

    Thread thread;

    pthread_t senderThread;
    
    SenderThreadArguments senderThreadArgs;
    senderThreadArgs.clientSockets = listenerThreadArgs->clientSockets;
    senderThreadArgs.logger = listenerThreadArgs->logger;
    senderThreadArgs.communication = listenerThreadArgs->communication;
    
    pthread_create(&senderThread, NULL, thread.SenderThread, &senderThreadArgs); 
    pthread_detach(senderThread);

    listenerThreadArgs->receiveThreads.push_back(senderThread);

    while(true)
    {
        pthread_t subThread;
        MessageThreadArguments messageThreadArguments;
        messageThreadArguments.clientSocket = new int (listenerThreadArgs->communication->AcceptTCPConnection(listenerThreadArgs->serverSocket));
        messageThreadArguments.communication = listenerThreadArgs->communication;
        messageThreadArguments.logger = listenerThreadArgs->logger;
        messageThreadArguments.clientSockets = listenerThreadArgs->clientSockets;
        
        pthread_create(&subThread, NULL, thread.MessageThread, &messageThreadArguments); 
        pthread_detach(subThread);

        listenerThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "new thread created");

        listenerThreadArgs->clientSockets->push_back(messageThreadArguments.clientSocket);
        listenerThreadArgs->receiveThreads.push_back(subThread);
    }

    return NULL;
}

void * Thread::SenderThread(void *args)
{
    SenderThreadArguments * senderThreadArgs = (SenderThreadArguments *) args;

    std::ostringstream logOutput;
    logOutput << "sender thread created " << pthread_self();
    senderThreadArgs->logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, logOutput.str());

    MessageQueue mq;

    while(true)
    {
        if(senderThreadArgs->clientSockets->size() > 0)
        {
            std::string sendMessage = mq.Read(MQ_NAME_SEND_MESSAGES);

            char *cstring = new char[sendMessage.length() + 1];
            strcpy(cstring, sendMessage.c_str()); 

            for(unsigned int i = 0; i < senderThreadArgs->clientSockets->size(); i++)
            {
                senderThreadArgs->communication->SendMessage(*senderThreadArgs->clientSockets->at(i), cstring, strlen(cstring));
            }

            delete [] cstring;
        }
        else if (mq.GetMessageCount(MQ_NAME_SEND_MESSAGES) >= MQ_MAX_MESSAGE)
        {
            // We need to consume the mq objects, 
            // otherwise mq-using programs block.
            mq.Read(MQ_NAME_SEND_MESSAGES);
        }
    }

    return NULL;
}