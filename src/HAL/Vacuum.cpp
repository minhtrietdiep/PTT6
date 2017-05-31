#include "Vacuum.h"

#define VACUUM "/sys/class/gpio/gpio51/value"
#define VACUUMD "/sys/class/gpio/gpio51/direction"
#define VALVE "/sys/class/gpio/gpio5/value"
#define VALVED "/sys/class/gpio/gpio5/direction"

enum ErrorCode Vacuum::FileCheck(std::ofstream &f, std::string functionname)
{
   if(f.is_open())
    {
        f << "out";
        f.close(); 
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
    FileCheck(f, "Vacuum Setup");
    f.open(VALVED);
    FileCheck(f, "Vacuum Setup");
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
    FileCheck(myfile, "Vacuum EnableVacuum");
    myfile.open(VALVE);
    return FileCheck(myfile, "Vacuum EnableVacuum");
}

enum ErrorCode Vacuum::DisableVacuum()
{
    m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "Disabling vacuum");
    std::ofstream myfile;
    myfile.open (VACUUM);
    FileCheck(myfile, "Vacuum DisableVacuum");
    myfile.open(VALVE);
    return FileCheck(myfile, "Vacuum DisableVacuum");
}