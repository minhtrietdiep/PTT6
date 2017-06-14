#include "Vacuum.h"

#include <iostream>
#include <fstream>
#include <vector>

Vacuum::Vacuum() :
    m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH)
{
    SetFilePathVacuumValue(VACUUMVALUEPATH);
    SetFilePathVacuumDir(VACUUMDIRPATH);
    SetFilePathValveValue(VALVEVALUEPATH);
    SetFilePathValveDir(VALVEDIRPATH);
}

Vacuum::~Vacuum()
{

}

ErrorCode Vacuum::EnableVacuum()
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Enabling vacuum");
    std::ofstream f(m_VacuumValuePath);
    if(FileCheck(f, "Vacuum EnableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 1;
    f.close();
    f.open(m_ValveValuePath);
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
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Disabling vacuum");
    std::ofstream f(m_VacuumValuePath);
    if(FileCheck(f, "Vacuum DisableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << 0;
    f.close();
    f.open(m_ValveValuePath);
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
    std::ofstream f(m_VacuumDirPath);
    if(FileCheck(f, "Vacuum Setup") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << "out";
    f.close();
    f.open(m_ValveDirPath);
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
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In " + functionname + ": failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    } 
}

void Vacuum::SetFilePathVacuumValue(std::string path)
{
    m_VacuumValuePath = path;
}

void Vacuum::SetFilePathVacuumDir(std::string path)
{
    m_VacuumDirPath = path;
}

void Vacuum::SetFilePathValveValue(std::string path)
{
    m_ValveValuePath = path;
}

void Vacuum::SetFilePathValveDir(std::string path)
{
    m_ValveDirPath = path;
}