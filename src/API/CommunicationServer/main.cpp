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
    
    mq.Create(MQ_NAME_RECEIVED_MESSAGES);

    CommunicationServer *com = new CommunicationServer(4244);

    std::cout << "Press any key to exit" << std::endl;
    
    getchar();

    mq.Close(MQ_NAME_RECEIVED_MESSAGES);
    
    delete com;

    pthread_exit(NULL);
    return 0;
}