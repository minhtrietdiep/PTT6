#include "Drive.h"


ErrorCode Drive::Setup()
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

Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions), m_DriveID(driveid)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
}

ErrorCode Drive::ToggleDrive()
{
    std::string filepath = "";
    std::ofstream f1;

    switch(m_DriveID)
    {
        case 0:
            filepath = DRIVE0;
            break;
        case 1:
            filepath = DRIVE1;
            break;
        case 2:
            filepath = DRIVE2;
            break;
        case 3:
            filepath = DRIVE3;
            break;
        case 4:
            filepath = DRIVE4;
            break;
        default:
            return ErrorCode::ERR_UNKNOWN;
            break;
    }
    f1.open(filepath);
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

    f1.open(filepath);
    if(f1.is_open())
    {
        f1 << 0;
        f1.close();
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

ErrorCode Drive::OpenDrive()
{
    std::ostringstream msg;
    msg << "Opening drive: " << m_DriveID;
    m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str()); 
    if(ToggleDrive() == ErrorCode::ERR_OK)  
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        return ErrorCode::ERR_UNKNOWN;
    }
}

ErrorCode Drive::CloseDrive()
{
    std::ostringstream msg;
    msg << "Closing drive: " << m_DriveID;
    m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str());
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
