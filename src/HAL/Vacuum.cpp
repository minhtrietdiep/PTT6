#include "Vacuum.h"

enum ErrorCode Vacuum::FileCheck(std::ofstream &f, std::string functionname)
{
   if(f.is_open())
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "In " + functionname + ": failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    } 
}

enum ErrorCode Vacuum::Setup()
{
    std::ofstream f;
    f.open(VACUUMD);
    if(FileCheck(f, "Vacuum Setup") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << "out";
    f.close();
    f.open(VALVED);
    if(FileCheck(f, "Vacuum Setup") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    f << "out";
    f.close();
    return ErrorCode::ERR_OK;
}

Vacuum::Vacuum()
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    Setup();
}

enum ErrorCode Vacuum::EnableVacuum()
{
    m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "Enabling vacuum");
    std::ofstream myfile;
    myfile.open (VACUUM);
    if(FileCheck(myfile, "Vacuum EnableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    myfile << 1;
    myfile.close();
    myfile.open(VALVE);
    if(FileCheck(myfile, "Vacuum EnableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    myfile << 1;
    myfile.close();
    return ErrorCode::ERR_OK;
}

enum ErrorCode Vacuum::DisableVacuum()
{
    m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "Disabling vacuum");
    std::ofstream myfile;
    myfile.open (VACUUM);
    if(FileCheck(myfile, "Vacuum DisableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    myfile << 0;
    myfile.close();
    myfile.open(VALVE);
    if(FileCheck(myfile, "Vacuum DisableVacuum") == ErrorCode::ERR_UNKNOWN)
    {
        return ErrorCode::ERR_UNKNOWN;
    }
    myfile << 0;
    myfile.close();
    return ErrorCode::ERR_OK;
}