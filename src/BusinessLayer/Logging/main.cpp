#include <stdio.h>
#include "Logger.h"
#include "BanaanTest.h"

#define SYSTEM_VERSION "1.2.3.4"

const std::string LOG_PATH = "./loggies/";

Logger logger(SYSTEM_VERSION, Logger::Severity::DEBUG, LOG_PATH);

void successFunction() {
    logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "Success! :)");
}

void failingFunction() {
    logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Fail! :)");
}

void asPointer(Logger *mylogger) {
    mylogger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "Pointers zijn koel");
}

int main() {
    printf("Hello!\n");
    
    BanaanTest banaanTest(logger);
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Hi main! :)");

    successFunction();
    failingFunction();
    asPointer(&logger);

    std::string logFile = logger.GetFileName();
    printf("We're done, check %s\n", logFile.c_str());
    return 0;
}
