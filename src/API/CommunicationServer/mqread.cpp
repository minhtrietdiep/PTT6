#include "MessageQueue.h"

#include <iostream>

#include <Const.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv)
{
    MessageQueue mq;
    
    while(true)
    {
        std::cout << mq.Read(MQ_NAME_SEND_MESSAGES) << std::endl;
        printf("MQ count: %ld\n\n", mq.GetMessageCount(MQ_NAME_SEND_MESSAGES));
//        getchar();
    }

    return 0;
}
