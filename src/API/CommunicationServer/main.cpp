#include "Thread.h"
#include "CommunicationServer.h"
#include "MessageQueue.h"

#include <Const.h>
#include <Logger.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv)
{
    MessageQueue mq;
    Logger *logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
    
    mq.Create(MQ_NAME_RECEIVED_MESSAGES);
    mq.Create(MQ_NAME_SEND_MESSAGES);

    CommunicationServer *com = new CommunicationServer(4244);

    logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "press any key to exit");
    
    getchar();

    mq.Close(MQ_NAME_RECEIVED_MESSAGES);
    mq.Close(MQ_NAME_SEND_MESSAGES);
    
    delete com;
    delete logger;

    pthread_exit(NULL);
    return 0;
}