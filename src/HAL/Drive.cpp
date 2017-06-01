#include "Drive.h"
#include <unistd.h>

#define DRIVE0 "/sys/class/gpio/gpio30/value"
#define DRIVE1 "/sys/class/gpio/gpio60/value"
#define DRIVE2 "/sys/class/gpio/gpio31/value"
#define DRIVE3 "/sys/class/gpio/gpio50/value"
#define DRIVE4 "/sys/class/gpio/gpio48/value"

#define DRIVE0D "/sys/class/gpio/gpio30/direction"
#define DRIVE1D "/sys/class/gpio/gpio60/direction"
#define DRIVE2D "/sys/class/gpio/gpio31/direction"
#define DRIVE3D "/sys/class/gpio/gpio50/direction"
#define DRIVE4D "/sys/class/gpio/gpio48/direction"

#define BUFFSIZE 50

enum ErrorCode Drive::Setup()
{
    std::ofstream f;
    switch(m_DriveID)
    {
        case 0:
            f.open(DRIVE0D);
            break;

        case 1:
            f.open(DRIVE1D);
            break;

        case 2:
            f.open(DRIVE2D);
            break;

        case 3:
            f.open(DRIVE3D);
            break;

        case 4:
            f.open(DRIVE4D);
            break; 

        default:
            return ErrorCode::ERR_UNKNOWN;
            break;
    }
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
                "In Drive Setup: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
        
}

Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    m_DriveID = driveid;
    Setup();
}

enum ErrorCode Drive::ToggleDrive()
{
    std::ofstream f1;
    std::ofstream f2;

    switch(m_DriveID)
    {
        case 0:
            f1.open (DRIVE0);
            f2.open (DRIVE0);
            break;
        case 1:
            f1.open (DRIVE1);
            f2.open (DRIVE1);
            break;
        case 2:
            f1.open (DRIVE2);
            f2.open (DRIVE2);
            break;
        case 3:
            f1.open (DRIVE3);
            f2.open (DRIVE3);
            break;
        case 4:
            f1.open (DRIVE4);
            f2.open (DRIVE4);
            break;
        default:
            return ErrorCode::ERR_UNKNOWN;
            break;
    }
    if(f1.is_open())
    {
        f1 << 1;
        f1.close();
        usleep(20000);
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "In Drive ToggleDrive: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }

    if(f2.is_open())
    {
        f2 << 0;
        f2.close();
        usleep(2000000);
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "In Drive ToggleDrive: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    } 

    return ErrorCode::ERR_OK;
}

enum ErrorCode Drive::OpenDrive()
{
    char buffer [BUFFSIZE];
    if(snprintf(buffer, BUFFSIZE, "Opening drive: %d", m_DriveID) >= BUFFSIZE)
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "In drive OpenDrive: string exceeded buffer size");
    }
    else
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                buffer);
    }  
    if(ToggleDrive() == ErrorCode::ERR_OK)  
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        return ErrorCode::ERR_UNKNOWN;
    }
}

enum ErrorCode Drive::CloseDrive()
{
    char buffer [BUFFSIZE];
    if(snprintf(buffer, BUFFSIZE, "Closing drive: %d", m_DriveID) >= BUFFSIZE)
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "In drive CloseDrive: string exceeded buffer size");
    }
    else
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                buffer);
    }
    if(ToggleDrive() == ErrorCode::ERR_OK)  
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        return ErrorCode::ERR_UNKNOWN;
    }
}

int Drive::GetDriveID()
{
    return m_DriveID;
}

Coordinates Drive::GetDriveCoordinates()
{
    return m_Positions;
}
