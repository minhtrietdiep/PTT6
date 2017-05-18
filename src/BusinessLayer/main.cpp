#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <future>
#include <thread>
#include <chrono>

#include <Const.h>
#include <MessageQueue.h>
#include <Logger.h>
#include <JSONParser.h>
#include <ClientMessage.h>
#include <Error.h>

#include "../API/Interfaces/IUIControl.h"
#include "Control.h"
#include "Config.h"
#include "CommandUtils.h"

Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
Control control({});

std::vector<std::string> knownOperations = 
{
    "PlateToDrive"          ,
    "PlateToCollimator"     ,
    "CancelCurrentOperation",
    "SetPreset"             ,
    "EmergencyStop"         ,
    "ContinueSystem"        ,
    "ResetSystem"           ,
    // Embedded -> Client
    "UploadPresets"         ,
    "UploadDriveState"      ,
    "UploadColliState"      ,
    "InvalidOperationTest"  ,
};

// Generate a randomly numbered JSON message
std::string generateJson() 
{
    JSONParser jsParser;
    std::string funcName = 
        knownOperations.at(rand() % knownOperations.size());
    ClientMessage cm(
        0,
        funcName,
        "0.0.0.0",
        rand() % 10,
        {}
    );
    std::string message = jsParser.ClientMessageToJson(cm);
    return message;
}

// Generate/add a message to MessageQueue
void generateReceivedMessage() 
{
    MessageQueue mq;
    mq.Write(MQ_NAME_RECEIVED_MESSAGES, generateJson());
}

void generateSentMessage() 
{
    MessageQueue mq;
    mq.Write(MQ_NAME_SEND_MESSAGES, generateJson());
}

ErrorCode executeFunction(IUIControl *control, const std::string &functionName, const std::vector<Parameter> &params) 
{
    if (std::find(knownOperations.begin(), knownOperations.end(), functionName) == knownOperations.end())
    {
        return ErrorCode::ERR_UNKNOWN_FUNC;
    }

    if (functionName == "PlateToDrive") 
    {
        if (params.size() != 1)
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        Parameter param = params[0];
        if (param.Name != "plateID") 
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        return control->PlateToDrive(std::stoi(param.Value));
    }
    else if (functionName == "PlateToCollimator") 
    {
        if (params.size() != 1)
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        Parameter param = params[0];
        if (param.Name != "plateID") 
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        return control->PlateToCollimator(std::stoi(param.Value));
    }
    else if (functionName == "SetPreset") 
    {
        if (params.size() != 1)
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        Parameter param = params[0];
        if (param.Name != "presetID") 
        {
            return ErrorCode::ERR_INVALID_ARG;
        }
        return control->SetPreset(std::stoi(param.Value));
    }
    else if (functionName == "CancelCurrentOperation") 
    {
        return control->CancelCurrentOperation();
    }
    else if (functionName == "EmergencyStop") 
    {
        return control->EmergencyStop();
    }
    else if (functionName == "ContinueSystem") 
    {
        return control->ContinueSystem();
    }
    else if (functionName == "ResetSystem")
    {
        return control->ResetSystem();
    } 
    else if (functionName == "UploadPresets")
    {
        auto result = control->UploadPresets();
        std::cout << result;

        // do send stuff

        return ErrorCode::ERR_UNKNOWN;
    }
    else if (functionName == "UploadDriveState")
    {

        return ErrorCode::ERR_UNKNOWN;//control->UploadDriveState();
    }
    else if (functionName == "UploadColliState")
    {
        return ErrorCode::ERR_UNKNOWN;//control->UploadColliState();
    }
    else    // This shouldn't happen tho
    {
        logger.Write(Logger::Severity::ERROR,
            __PRETTY_FUNCTION__,
            "Function not implemented somehow????");
        return ErrorCode::ERR_UNKNOWN;
    }
}

// Consume the clientMessage. This can be blocking. 
// We can return a ClientMessage we got, but also a new one if desired?
ClientMessage slowFunc(ClientMessage cm) 
{
    // We only have one Control for now...
    int priority = cm.GetPriority();
    std::string sender = cm.GetSender();
    std::string funcName = cm.GetFunctionName();
    std::vector<Parameter> params = cm.GetParams();
    int timeout = rand() % 5000;
    std::cout << "Priority:      " << priority << "\n";
    std::cout << "Sender:        " <<  sender << "\n";
    std::cout << "Function Name: " << funcName << "\n";
    for (auto p : params) 
    {
        std::cout   << p.Name << "\n"
                    << p.Type << "\n"
                    << p.Value << "\n";
    }    
    ErrorCode err = executeFunction(&control, funcName, params);

    Parameter result = 
    {
        "ReturnValue",
        "String",
        ErrorCodeText[(int)err],
    };

    params.push_back(result);
    cm.SetParams(params);
    return cm;
}

void checkThreads(std::vector<std::future<ClientMessage>> &futures) {
    // We check the threads here, using C++11/STL threading. We also know
    // which thread (ClientMessage) is done.
    // Also don't use a ranged for, because we can remove the current
    // element. Need the iterator!
    for (auto it = futures.begin(); it != futures.end();) 
    {
        auto status = (*it).wait_for(std::chrono::milliseconds(0));
        if (status == std::future_status::ready) 
        {
            ClientMessage doneMessage = (*it).get();

            MessageQueue mq;
            if (mq.GetMessageCount(MQ_NAME_SEND_MESSAGES) < MQ_MAX_MESSAGE) {
                JSONParser jsparser;
                mq.Write(MQ_NAME_SEND_MESSAGES, jsparser.ClientMessageToJson(doneMessage));                    
                logger.Write(Logger::Severity::INFO,
                         __PRETTY_FUNCTION__,
                         jsparser.ClientMessageToJson(doneMessage));
            }
            else
            {
                logger.Write(Logger::Severity::ERROR,
                             __PRETTY_FUNCTION__,
                             "MessageQueue is full, emptying...");
                while (mq.GetMessageCount(MQ_NAME_SEND_MESSAGES) > 0) {
                    mq.Read(MQ_NAME_SEND_MESSAGES);
                }
            }

            // We're done tracking it so we can erase the progress handle.
            futures.erase(it);
            std::cout << "Threads left: " << futures.size() << "\n";
        }
        else 
        {
            ++it;
        }
    }
}

void checkMessages(MessageQueue &mq, 
    std::vector<std::future<ClientMessage>> &futures,
    std::vector<std::thread> &threads) {
    // After parsing, launch a function that executes whatever is in the
    // ClientMessage. This is done in a new thread to make this async.
    if (mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES) > 0) 
    {
        JSONParser jsparser;
        std::string rawMq;
        rawMq = mq.Read(MQ_NAME_RECEIVED_MESSAGES);

        std::cout << rawMq << "\n";

        ClientMessage clientMessage;
        std::string parseInfo;
        JSONError result = jsparser.JsonToClientMessage(rawMq, 
                                                    &clientMessage, 
                                                    parseInfo);
        if (result == JSONError::NONE) 
        {
            std::packaged_task<ClientMessage(ClientMessage)> task(&slowFunc);
            auto future = task.get_future();
            std::thread thread(std::move(task), clientMessage);
            futures.push_back(std::move(future));
            threads.push_back(std::move(thread));
        } 
        else 
        {
            logger.Write(Logger::Severity::ERROR, 
                         __PRETTY_FUNCTION__, 
                         "Parsing failed: " + parseInfo);
        }
    }
}

int main(int argc, char **argv) 
{
    srand (time(NULL));
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Program started");
    MessageQueue mq;
    std::vector<std::future<ClientMessage>> futures;
    std::vector<std::thread> threads;
    std::cout << "Press ESC or q to quit\n";
    std::cout << "Press 9 to hard-exit\n";
    std::cout << "Press 1 to generate MessageQueue->ClientMessage item\n";
    std::cout << "Press 2 to generate ClientMessage->MessageQueue item\n";
    while (true) 
    {
        // User input, because we want to create fake messages to test too
        if (kbhit()) 
        {
            char c = getchar();
            if (c == ESCAPE_KEY || c == 'q') 
            {
                std::cout << "\n";
                break;
            }
            if (c == '9') 
            {
                std::cout << "\n";
                std::terminate();
            }
            if (c == '1') 
            {
                std::cout << "\n";
                generateReceivedMessage();
            }
            if (c == '2') 
            {
                std::cout << "\n";
                generateSentMessage();
            }
            if (c == '3') 
            {
                std::cout << "\n";
                executeFunction(&control, "UploadPresets", {});
                
            }
        }

        checkMessages(mq, futures, threads);

        checkThreads(futures);

        // Let's go easy on the cpu here.
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // Use references because otherwise copy ctor and dtor are called.
    for (auto &thread : threads) 
    {
        thread.join();
    }
    std::cout << "Halted program\n";    
    return 0;

}