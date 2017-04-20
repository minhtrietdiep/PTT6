#include <stdio.h>
#include <Logger.h>
#include <Const.h>
#include "BanaanTest.h"

Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

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
    logger.WriteHeader();
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "main start");

    BanaanTest banaanTest;

    successFunction();
    failingFunction();
    asPointer(&logger);

    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "we're done!");
    std::string logFile = logger.GetFileName();
    printf("We're done, check %s\n", logFile.c_str());
    return 0;
}
