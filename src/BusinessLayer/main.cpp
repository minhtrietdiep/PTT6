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

#include "../API/Interfaces/IUIControl.h"
#include "Control.h"

#define ESC 0x1B

Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
Control control({});
#include "Headers/Control.h"

void init()
{

    control = Control();

    //std::cout << control->GetPresets()[0].GetPlatelist()[0].GetThickness() << std::endl; //just to test
    //std::cout << control->GetPresets()[0].GetPlatelist()[1].GetThickness() << std::endl; //just to test
    //control->ResetSystem();
    control.SetPreset(1);


}
// CTRL-C, CTRL-V because Linux doesn't have a kbhit
int kbhit(void) 
{
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

    if(ch != EOF) 
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

std::vector<std::string> knownOperations = 
{
    "PlateToDrive"          ,
    "PlateToCollimator"     ,
    "CancelCurrentOperation",
    "SetPreset"             ,
    "EmergencyStop"         ,
    "ContinueSystem"        ,
    "ResetSystem"           ,
    "UploadConfig"          ,
    "DownloadConfig"        ,
};


int main(int argc, char **argv)
// Generate a randomly numbered JSON message
std::string generateJson() 
{
    init();
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
    std::cout << "Halted program\n";    
    return 0;
}
