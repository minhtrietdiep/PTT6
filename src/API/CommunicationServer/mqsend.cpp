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
        mq.Write(MQ_NAME_SEND_MESSAGES, "test");
        getchar();
    }

    return 0;
}
