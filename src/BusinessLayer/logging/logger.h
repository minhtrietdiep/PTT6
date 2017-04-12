/*
 * Logger definition
 * Logging format:
 * TIME;VERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n
 * date/time;systemVersion;module_name;function_name;function_result;\n
 */

#pragma once
#include <string>
#include <array>

enum Result {
    Success
};

class Logger {
public:
    enum class Severity {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        Size //pls don't use as real arg!!11!!
    };

    Logger(const std::string &systemVersion, Severity level);
    ~Logger();
    void Write(Severity severity,
            std::string moduleName,
            std::string functionName,
            Result functionResult);
    std::string GetFileName();

private:
    const std::array<std::string, (int)Severity::Size> SeverityHelper = {
        { "DEBUG",
        "INFO",
        "WARNING",
        "ERROR" }
    };
    
private:
    Result writeHeader();
    std::string fileName;
    std::string systemVersion;
    std::string severityText(Severity severity); 
    std::string getTime();
    const std::string separator = ",";
    Severity printLevel;
};

