#include <stdio.h>
#include "Logger.h"
const std::string myVer = "0.0.0";
Logger logger(myVer, Logger::Severity::DEBUG, "./logjes/");

void successFunction() {
    logger.Write(Logger::Severity::INFO, "This should succeed!", __func__, Success);
}

void failingFunction() {
    logger.Write(Logger::Severity::ERROR, "This should error", __func__, Success);
}

void asPointer(Logger *mylogger) {
    mylogger->Write(Logger::Severity::INFO, "Yes pointers!", __func__, Success);
}

int main() {
    printf("Hello!\n");
    logger.Write(Logger::Severity::DEBUG, "test", __func__, Success); 

    successFunction();
    failingFunction();
    asPointer(&logger);

    std::string logFile = logger.GetFileName();
    printf("We're done, check %s\n", logFile.c_str());
    return 0;
}
