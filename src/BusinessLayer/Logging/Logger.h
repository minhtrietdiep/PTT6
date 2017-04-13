/*
 * Logger definition
 * Logging format:
 * TIME;VERSION;FUNCTIONCALL;MESSAGE;\n
 */

#pragma once
#include <string>
#include <array>

class Logger {
public:
    enum class Severity {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        Size // This is just a helper to make arrays.
    };

    Logger(const std::string &systemVersion, Severity printLevel, std::string logFile);
    ~Logger();
    void WriteHeader();
    void Write(Severity severity,
            std::string functionName,
            std::string message);
    std::string GetFileName();

private:
    const std::array<std::string, (int)Severity::Size> SeverityHelper = {
        { "DEBUG",
          "INFO",
          "WARNING",
          "ERROR" }
    };
    
private:
    const std::string separator = ",";
    const std::string logExt = ".csv";
    std::string fileName;
    std::string systemVersion;
    std::string severityText(Severity severity); 
    std::string getTime();
    Severity printLevel;
    std::string logPath;
};

