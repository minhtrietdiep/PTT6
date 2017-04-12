#include <stdio.h>
#include "logger.h"

int main() {
    printf("Hello!\n");

    Logger logger("JUSTTESTING", Logger::Severity::DEBUG);
    std::string logFile = logger.GetFileName();

    logger.Write(Logger::Severity::DEBUG, "test", "main", Success);
    
    logger.Write(Logger::Severity::ERROR, "WOAH THAT WAS BAD", "main", Success);
    printf("We're done, check %s\n", logFile.c_str());
    return 0;
}
