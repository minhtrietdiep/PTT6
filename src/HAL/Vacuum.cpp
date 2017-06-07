#include "Vacuum.h"

#include <iostream>
#include <fstream>
#include <vector>

Vacuum::Vacuum()
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
}

Vacuum::~Vacuum()
{
    delete m_Logger;
}

ErrorCode Vacuum::EnableVacuum()
{
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Enabling vacuum");
    std::ofstream f(VACUUMDIRPATH);
    if(FileCheck(f, "Vacuum EnableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 1;
    f.close();
    f.open(VALVEVALUEPATH);
    if(FileCheck(f, "Vacuum EnableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 1;
    f.close();
    return ErrorCode::ERR_OK;
}

ErrorCode Vacuum::DisableVacuum()
{
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Disabling vacuum");
    std::ofstream f(VACUUMDIRPATH);
    if(FileCheck(f, "Vacuum DisableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 0;
    f.close();
    f.open(VALVEVALUEPATH);
    if(FileCheck(f, "Vacuum DisableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 0;
    f.close();
    return ErrorCode::ERR_OK;
}

ErrorCode Vacuum::SetupHardware()
{
    std::ofstream f(VACUUMDIRPATH);
    if(FileCheck(f, "Vacuum Setup") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << "out";
    f.close();
    f.open(VALVEDIRPATH);
    if(FileCheck(f, "Vacuum Setup") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << "out";
    f.close();
    return ErrorCode::ERR_OK;
}


ErrorCode Vacuum::FileCheck(std::ofstream &f, std::string functionname)
{
   if(f.is_open())
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In " + functionname + ": failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    } 
}