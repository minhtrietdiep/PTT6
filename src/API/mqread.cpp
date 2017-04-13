#include "../Const.h"
#include "MessageQueue.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(int argc, char **argv) {
    MessageQueue mq;
    
    while(true)
    {
        std::cout << mq.Read(MQ_NAME_RECEIVED_MESSAGES) << std::endl;
        printf("MQ count: %ld\n\n", mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES));
        getchar();
    }

    return 0;
}