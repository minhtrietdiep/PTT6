#include "Drive.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>

Drive::Drive(int driveid, std::string movecommand) : 
    m_DriveID(driveid)/*,
    m_Positions (positions)*/
{
    //m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    m_MoveCommand = movecommand;
}

Drive::~Drive()
{
    // WHY CRASH? delete m_Logger;
}

ErrorCode Drive::SetupHardware()
{
    std::ofstream f;
    switch(m_DriveID)
    {
        case 0:
            f.open(DRIVE0DIRPATH);
            break;

        case 1:
            f.open(DRIVE1DIRPATH);
            break;

        case 2:
            f.open(DRIVE2DIRPATH);
            break;

        case 3:
            f.open(DRIVE3DIRPATH);
            break;

        case 4:
            f.open(DRIVE4DIRPATH);
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
        //m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Drive Setup: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
        
}

ErrorCode Drive::OpenDrive()
{
    std::ostringstream msg;
    msg << "Opening drive: " << m_DriveID;
    //m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str()); 
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
    //m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str());
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

/*Coordinates Drive::GetDriveCoordinates()
{
    return m_Positions;
}*/


ErrorCode Drive::ToggleDrive()
{
    std::string filepath = "";
    std::ofstream f1;

    switch(m_DriveID)
    {
        case 0:
            filepath = DRIVE0VALUEPATH;
            break;
        case 1:
            filepath = DRIVE1VALUEPATH;
            break;
        case 2:
            filepath = DRIVE2VALUEPATH;
            break;
        case 3:
            filepath = DRIVE3VALUEPATH;
            break;
        case 4:
            filepath = DRIVE4VALUEPATH;
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
        //m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Drive ToggleDrive: failed to open a GPIO file");
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
        //m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Drive ToggleDrive: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    } 

    return ErrorCode::ERR_OK;
}

std::string Drive::GetDriveMoveCommand()
{
    return m_MoveCommand;
}


