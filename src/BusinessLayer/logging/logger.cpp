#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

Logger::Logger(const std::string &systemVersion, Severity printLevel) :
    systemVersion(systemVersion),
    printLevel(printLevel) {
    fileName = getTime() + ".csv";
    writeHeader();
    //Write("Logger", "Initialize", Success);
}

Logger::~Logger() {}

void Logger::Write(Severity severity,
            std::string moduleName, 
            std::string functionName,
            Result functionResult) {
    std::stringstream logLine;
    logLine << getTime()              << separator
            << severityText(severity) << separator
            << systemVersion          << separator
            << moduleName             << separator
            << functionName           << separator
            << functionResult         << separator << "\n";
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << logLine.str();
    if (severity == Severity::DEBUG && printLevel == Severity::DEBUG) {
        std::cout << logLine.str(); // might wanna reformat this thing? :(
    }
    logFile.close();
}

std::string Logger::GetFileName() {
    return fileName;
}

// Literally write this:
// "TIMESTAMP;SYSTEMVERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n"    
Result Logger::writeHeader() {
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << "TIMESTAMP"     << separator
            << "SEVERITY"      << separator
            << "SYSTEMVERSION" << separator
            << "MODULENAME"    << separator
            << "FUNCTIONCALL"  << separator
            << "RETURNVALUE"   << separator
            << "\n";
    logFile.close();
    return Success;
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
        return "INVALIDLVL";
    }

    return SeverityHelper[(int)severity];
}

