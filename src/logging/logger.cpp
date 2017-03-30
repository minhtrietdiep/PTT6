#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

Logger::Logger(const std::string &systemVersion) :
    systemVersion(systemVersion) {
    fileName = getTime() + ".csv";
    writeHeader();
    Write("Logger", "Initialize", Success);
}

Logger::~Logger() {}

void Logger::Write(std::string moduleName, 
           std::string functionName,
           Result functionResult) 
{
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << getTime() << separator
            << systemVersion << separator
            << moduleName << separator
            << functionName << separator
            << functionResult << separator << "\n";
    logFile.close();
}

std::string Logger::GetFileName() {
    return fileName;
}

// Literally write this:
// "TIMESTAMP;SYSTEMVERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n"    
Result Logger::writeHeader() {
    std::ofstream logFile(fileName, std::ios_base::out | std::ios_base::app);
    logFile << "TIMESTAMP" << separator
            << "SYSTEMVERSION"     << separator
            << "MODULENAME"        << separator
            << "FUNCTIONCALL"     << separator
            << "RETURNVALUE"      << separator
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
