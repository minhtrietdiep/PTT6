#include <Const.h>
//#include <Thread.h>
#include <MessageQueue.h>
#include <Logger.h>
#include <JSONParser.h>
#include <ClientMessage.h>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    MessageQueue mq;
    std::vector<std::string> messages;
    std::vector<ClientMessage> clientmessages;
    JSONParser jsparser;

    while (true) {
        messages.push_back(mq.Read(MQ_NAME_RECEIVED_MESSAGES));
        printf("%s\n", messages.back().c_str());
        if (messages.back() == "stahp") {
            break;
        }
    }
    printf("Stuff in MQ: %i\n", mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES));
    printf("Stuff in v<m>: %i\n", messages.size());
    for (auto m : messages) {
        std::cout << "Parsing: \n" <<  m  << std::endl;
        ClientMessage cm;
        jsparser.JsonToClientMessage(m, &cm);
        clientmessages.push_back(cm);
    }
    std::cout << "Press any key to exit" << std::endl;    
    getchar();

    //pthread_exit(NULL);
    return 0;
}

