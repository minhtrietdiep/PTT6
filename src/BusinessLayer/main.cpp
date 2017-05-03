#include <Const.h>
#include <MessageQueue.h>
#include <Logger.h>
#include <JSONParser.h>
#include <ClientMessage.h>

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

#define ESC 0x1B

#include <functional>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void someFunctionThatTakesAWhile(int priority,
    std::string sender,
    std::string funcName,
    std::vector<Parameter> params) {
    std::cout << priority << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << sender << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << funcName << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (auto p : params) {
        std::cout   << p.Name << "\n"
                    << p.Type << "\n"
                    << p.Value << "\n";
    }
}

std::thread* consumeClientMessage(ClientMessage cm) {
    printf("New thread:\n");
    std::thread* thread = new std::thread(someFunctionThatTakesAWhile,
            cm.GetPriority(),
            cm.GetSender(),
            cm.GetFunctionName(),
            cm.GetParams());

    //thread.join();
    return thread;
}

int main(int argc, char **argv) {
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Program started");
    JSONParser jsparser;
    MessageQueue mq;
    std::vector<std::thread *> threads;
    printf("Press ESC to quit\n");
    while (true) {
        if (kbhit()) {
            char c = getchar();
            if (c == ESC) {
                break;
            }
        }
        if (mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES) > 0) {
            std::string rawMq;
            rawMq = mq.Read(MQ_NAME_RECEIVED_MESSAGES);
            ClientMessage cm;
            std::string parseInfo;
            Error result = jsparser.JsonToClientMessage(rawMq, &cm, parseInfo);
            if (result == Error::NONE) {
                threads.push_back(consumeClientMessage(cm));
            } else {
                logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Parsing failed: " + parseInfo);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    for (auto t : threads) {
        t->join();
    }
    printf("Halted program\n");    
    return 0;
}
