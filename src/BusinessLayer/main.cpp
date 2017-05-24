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
#include "JSONUtils.h"

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
    "UploadCollimatorState" ,
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

ErrorCode executeFunction(IUIControl *control, 
    const std::string &functionName, 
    const std::vector<Parameter> &params,
    std::string &payload) 
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
        payload = control->UploadPresets();
        return ErrorCode::ERR_OK;
    }
    else if (functionName == "UploadDriveState")
    {
        payload = control->UploadDriveState();
        return ErrorCode::ERR_OK;
    }
    else if (functionName == "UploadCollimatorState")
    {
        payload = control->UploadCollimatorState();
        return ErrorCode::ERR_OK;
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
ClientMessage asyncConsumeMessage(ClientMessage cm) 
{
    // We only have one Control for now...
    int priority = cm.GetPriority();
    std::string sender = cm.GetSender();
    std::string funcName = cm.GetFunctionName();
    std::vector<Parameter> params = cm.GetParams();
    int timeout = rand() % 5000;
    //std::cout << "Priority:      " << priority << "\n";
    //std::cout << "Sender:        " <<  sender << "\n";
    //std::cout << "Function Name: " << funcName << "\n";
    for (auto p : params) 
    {
        std::cout   << p.Name << "\n"
                    << p.Type << "\n"
                    << p.Value << "\n";
    }
    std::string payloadData = "";    
    ErrorCode err = executeFunction(&control, funcName, params, payloadData);

    Parameter result = 
    {
        "ReturnValue",
        "String",
        ErrorCodeText[(int)err],
    };




    params.push_back(result);

    if (payloadData != "") {
        Parameter payload = 
        {
            "JSONData",
            "String",
            payloadData,
        };
        params.push_back(payload);
        logger.Write(Logger::Severity::DEBUG,
                     __PRETTY_FUNCTION__,
                     "Payload: " + payloadData);
    }

    cm.SetParams(params);
    return cm;
}

void checkThreads(std::vector<std::future<ClientMessage>> &futures) 
{
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
            if (mq.GetMessageCount(MQ_NAME_SEND_MESSAGES) < MQ_MAX_MESSAGE) 
            {
                JSONParser jsparser;
                mq.Write(MQ_NAME_SEND_MESSAGES, jsparser.ClientMessageToJson(doneMessage));                    
                logger.Write(Logger::Severity::INFO,
                         __PRETTY_FUNCTION__,
                         "Response: " + jsparser.ClientMessageToJson(doneMessage));
            }
            else
            {
                logger.Write(Logger::Severity::ERROR,
                             __PRETTY_FUNCTION__,
                             "MessageQueue is full, emptying...");
                while (mq.GetMessageCount(MQ_NAME_SEND_MESSAGES) > 0) 
                {
                    mq.Read(MQ_NAME_SEND_MESSAGES);
                }
            }

            // We're done tracking it so we can erase the progress handle.
            futures.erase(it);
            logger.Write(Logger::Severity::INFO,
                         __PRETTY_FUNCTION__,
                         "Threads left: " + std::to_string(futures.size()));
        }
        else 
        {
            ++it;
        }
    }
}

// Due to TCP appending multiple messages in one message, we can get an MQ
// message that's not a valid JSON message. Hence needing to split up.
// Due to our networking person being absent today this hack was needed.
std::vector<std::string> splitRawMq(std::string rawMq) 
{
    std::vector<std::string> results;
    
    int leftBracketCount = 0;
    int rightBracketCount = 0;
    int start = 0;
    for(int pos = 0; pos < rawMq.size(); pos++) 
    {
        char c = rawMq[pos];
        if (c == '{') 
        {
            leftBracketCount++;
        }
        if (c == '}') 
        {
            rightBracketCount++;
        }
        if (rightBracketCount == leftBracketCount && leftBracketCount != 0 || pos == rawMq.size() - 1) 
        {
            std::string singleMessage = rawMq.substr(start, pos - start + 1);
            leftBracketCount = 0;
            rightBracketCount = 0;
            start = pos + 1;
            results.push_back(singleMessage);
        }
    }
    return results;
}

void parseSingleJSONString(std::string rawString, 
    MessageQueue &mq, 
    std::vector<std::future<ClientMessage>> &futures,
    std::vector<std::thread> &threads) 
{

    JSONParser jsparser;
    ClientMessage clientMessage;
    std::string parseInfo;
    JSONError result = jsparser.JsonToClientMessage(rawString, 
                                                &clientMessage, 
                                                parseInfo);
    if (result == JSONError::NONE) 
    {
        logger.Write(Logger::Severity::DEBUG, 
                 __PRETTY_FUNCTION__, 
                 "Parse success");
        std::packaged_task<ClientMessage(ClientMessage)> task(&asyncConsumeMessage);
        auto future = task.get_future();
        std::thread thread(std::move(task), clientMessage);
        futures.push_back(std::move(future));
        threads.push_back(std::move(thread));
    } 
    else 
    {
        std::string jsError = GetJSONErrorString(result);

        Parameter result = 
        {
            "ReturnValue",
            "String",
            jsError,
        };
        ClientMessage tempMsg(0, "JsonToClientMessage", "embedded", 999, {result}); // for json formatted stuff response

        std::string returnMessage = jsparser.ClientMessageToJson(tempMsg);

        mq.Write(MQ_NAME_SEND_MESSAGES, returnMessage);
        logger.Write(Logger::Severity::ERROR, 
                     __PRETTY_FUNCTION__, 
                     "Parsing failed: " + parseInfo + " (" + jsError + ")");
        logger.Write(Logger::Severity::ERROR,
                     __PRETTY_FUNCTION__,
                     "Response: " + returnMessage);
    }
}

void checkMessages(MessageQueue &mq, 
    std::vector<std::future<ClientMessage>> &futures,
    std::vector<std::thread> &threads) 
{
    // After parsing, launch a function that executes whatever is in the
    // ClientMessage. This is done in a new thread to make this async.
    if (mq.GetMessageCount(MQ_NAME_RECEIVED_MESSAGES) > 0) 
    {
        std::string rawMq;
        rawMq = mq.Read(MQ_NAME_RECEIVED_MESSAGES);

        logger.Write(Logger::Severity::DEBUG, 
                     __PRETTY_FUNCTION__, 
                     "Received message: " + rawMq);

        std::vector<std::string> splitMessages = splitRawMq(rawMq);
        for (auto message : splitMessages) 
        {
            parseSingleJSONString(message, mq, futures, threads);
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

        control.StartSystem();
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