#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

Logger::Logger(const std::string &systemVersion, Severity printLevel, std::string logPath) :
    systemVersion(systemVersion),
    printLevel(printLevel),
    logPath(logPath) {
//    struct stat st = {0};
//    if (stat(logPath.c_str(), &st) == -1) {
//        mkdir(logPath.c_str(), 0700);
//    }
    fileName = logPath;//logPath + getTime() + logExt;
    //writeHeader();
}

Logger::~Logger() {}

void Logger::Write(Severity severity,
            std::string functionName, 
            std::string message) {
    std::stringstream logLine;
    logLine << getTime()              << separator
            << severityText(severity) << separator
            << systemVersion          << separator
            << functionName           << separator
            << message                << separator << "\n";
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << logLine.str();
    if ((int)severity >= (int)printLevel) {
        std::stringstream trace;
        trace << "[" << getTime() << "] " <<
            std::setw(8) << severityText(severity) << message << std::endl; 
        std::cout << trace.str();
    }
    logFile.close();
}

std::string Logger::GetFileName() {
    return fileName;
}

// Literally write this:
// "TIMESTAMP;SYSTEMVERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n"    
void Logger::WriteHeader() {
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << "TIMESTAMP"     << separator
            << "SEVERITY"      << separator
            << "SYSTEMVERSION" << separator
            << "FUNCTIONCALL"    << separator
            << "MESSAGE"  << separator
            << "\n";
    logFile.close();
}

std::string Logger::getTime() {
    std::stringstream timeTemp;
    time_t t = time(0);
    struct tm * now = localtime(&t);
    timeTemp <<                              (now->tm_year + 1900)     << '-'
        << std::setw(2) << std::setfill('0') << (now->tm_mon + 1)     << '-'
        << std::setw(2) << std::setfill('0') <<  now->tm_mday         << '-'
        << std::setw(2) << std::setfill('0') <<  now->tm_hour         << '-'
        << std::setw(2) << std::setfill('0') <<  now->tm_min         << '-'
        << std::setw(2) << std::setfill('0') <<  now->tm_sec;
    return timeTemp.str();
}

std::string Logger::severityText(Severity severity) {
    if (severity == Severity::Size) {
        return "ERROR";
    }

    return SeverityHelper[(int)severity];
}

