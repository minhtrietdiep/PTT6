/*
 * Logger definition
 * Logging format:
 * TIME;VERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n
 * date/time;systemVersion;module_name;function_name;function_result;\n
 */

#pragma once
#include <string>

enum Result {
    Success
};

class Logger {
public:
    Logger(const std::string &systemVersion);
    ~Logger();
    void Write(std::string moduleName, 
           std::string functionName,
           Result functionResult);
    std::string GetFileName();
    
private:
    Result writeHeader();
    std::string fileName;
    std::string systemVersion;
    
    std::string getTime();
    const std::string separator = ",";
};


