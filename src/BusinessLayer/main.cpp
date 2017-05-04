#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <future>
#include <thread>
#include <chrono>

#include <Const.h>
#include <MessageQueue.h>
#include <Logger.h>
#include <JSONParser.h>
#include <ClientMessage.h>

#define ESC 0x1B

Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

// CTRL-C, CTRL-V because Linux doesn't have a kbhit
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

// Generate a randomly numbered JSON message
std::string generateJson() {
    JSONParser jsParser;
    std::string funcName = "Generated";
    funcName += std::to_string(rand() % 100);
    ClientMessage cm(
        0,
        funcName,
        "0.0.0.0",
        0,
        {});
    std::string message = jsParser.ClientMessageToJson(cm);
    return message;
}

// Generate/add a message to MessageQueue
void generateReceivedMessage() {
    MessageQueue mq;
    mq.Write(MQ_NAME_RECEIVED_MESSAGES, generateJson());
}

void generateSentMessage() {
    // nope! :D
}

// Consume the clientMessage. This can be blocking. We can return the
// ClientMessage we got, but also a new one if desired?
ClientMessage slowFunc(ClientMessage cm) {
    int priority = cm.GetPriority();
    std::string sender = cm.GetSender();
    std::string funcName = cm.GetFunctionName();
    std::vector<Parameter> params = cm.GetParams();
    int timeout = rand() % 5000;
    std::cout << "Priority:      " << priority << "\n";
    std::cout << "Sender:        " <<  sender << "\n";
    std::cout << "Function Name: " << funcName << "\n";
    for (auto p : params) {
        std::cout   << p.Name << "\n"
                    << p.Type << "\n"
                    << p.Value << "\n";
    }
    std::cout << "Doing stuff for " << timeout << " milliseconds\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    // Don't print anything because we're sneaky,
    // and we want to respond on the thread being done.
    //std::cout << "Function done!\n";
    return cm;
}

int main(int argc, char **argv) {
    srand (time(NULL));
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Program started");
    JSONParser jsparser;
    MessageQueue mq;
    std::vector<std::future<ClientMessage>> futures;
    std::vector<std::thread> threads;
    printf("Press ESC to quit\n");
    printf("Press 9 to hard-exit\n");
    printf("Press 1 to generate MessageQueue->ClientMessage item\n");
    printf("Press 2 to generate ClientMessage->MessageQueue item\n");
    while (true) {
        // User input, because we want to create fake messages to test too
        if (kbhit()) {
            char c = getchar();
            if (c == ESC) {
                std::cout << "\n";
                break;
            }
            if (c == '9') {
                std::cout << "\n";
                std::terminate();
            }
            if (c == '1') {
                std::cout << "\n";
                generateReceivedMessage();
            }
            if (c == '2') {
                std::cout << "\n";
                generateSentMessage();
            }
        }

        // After parsing, launch a function that executes whatever is in the
        // ClientMessage. This is done in a new thread to make this async.
        if (mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES) > 0) {
            std::string rawMq;
            rawMq = mq.Read(MQ_NAME_RECEIVED_MESSAGES);
            ClientMessage clientMessage;
            std::string parseInfo;
            Error result = jsparser.JsonToClientMessage(
                rawMq, 
                &clientMessage, 
                parseInfo);
            if (result == Error::NONE) {
                std::packaged_task<ClientMessage(ClientMessage)> task(&slowFunc);
                auto future = task.get_future();
                std::thread thread(std::move(task), clientMessage);
                futures.push_back(std::move(future));
                threads.push_back(std::move(thread));
                
            } else {
                logger.Write(
                    Logger::Severity::ERROR, 
                    __PRETTY_FUNCTION__, 
                    "Parsing failed: " + parseInfo);
            }
        }

        // We check the threads here, using C++11/STL threading. We also know
        // which thread (ClientMessage) is done.
        // Also don't use a ranged for, because we can remove the current
        // element. Need the iterator!
        for (auto it = futures.begin(); it != futures.end();) {
            auto status = (*it).wait_for(std::chrono::milliseconds(0));
            if (status == std::future_status::ready) {
                ClientMessage doneMessage = (*it).get();
                std::cout << "Function's done! (" << 
                    doneMessage.GetFunctionName() << ")\n";
                // We're done tracking it so we can erase the progress handle.
                futures.erase(it);
                std::cout << "Threads left: " << futures.size() << "\n";
            }
            else {
                ++it;
            }
        }

        // Let's go easy on the cpu here.
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // Use references because otherwise copy ctor and dtor are called.
    for (auto &thread : threads) {
        thread.join();
    }
    printf("Halted program\n");    
    return 0;
}
