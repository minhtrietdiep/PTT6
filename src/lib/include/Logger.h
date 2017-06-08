#pragma once

/*
 * Logger definition
 * Logging format:
 * TIME;VERSION;FUNCTIONCALL;MESSAGE;\n
 */

#include <string>
#include <array>
//#include <mutex>

class Logger 
{
public:
    enum class Severity 
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        Size // This is just a helper to make arrays.
    };

    Logger(const std::string &systemVersion,
           Severity printLevel,
           const std::string &logPath);
   ~Logger();
    void WriteHeader();
    void Write(Severity severity,
               const std::string &functionName,
               const std::string &message);
    std::string GetFileName();

private:
    std::string severityText(Severity severity); 
    std::string getTime();

    const std::array<std::string, (int)Severity::Size> m_severityHelper = 
    {
        { "DEBUG  ", "INFO   ", "WARNING", "ERROR  " }
    };
    const std::string m_separator = ",";
    const std::string m_logExt = ".csv";
    std::string m_fileName;
    std::string m_systemVersion;
    Severity m_printLevel;
    std::string m_logPath;
//    static std::mutex loggerMutex;  
};
