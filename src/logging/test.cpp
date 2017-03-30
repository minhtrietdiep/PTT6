#include <stdio.h>
#include "logger.h"

int main() {
    printf("Hello!\n");

    Logger logger(/*testFile, */"0.0.0");
    std::string logFile = logger.GetFileName();

    logger.Write("test", "main", Success);
    printf("We're done, check %s\n", logFile.c_str());
    return 0;
}
