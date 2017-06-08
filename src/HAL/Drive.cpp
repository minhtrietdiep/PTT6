#include "Drive.h"

#include <unistd.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

Drive::Drive(int driveid, std::string movecommand) : 
    m_DriveID(driveid),
    m_MoveCommand(movecommand)
{

    SetFilePathDrive0Value(DRIVE0VALUEPATH);
    SetFilePathDrive1Value(DRIVE1VALUEPATH);
    SetFilePathDrive2Value(DRIVE2VALUEPATH);
    SetFilePathDrive3Value(DRIVE3VALUEPATH);
    SetFilePathDrive4Value(DRIVE4VALUEPATH);
    SetFilePathDrive0Dir(DRIVE0DIRPATH);
    SetFilePathDrive1Dir(DRIVE1DIRPATH);
    SetFilePathDrive2Dir(DRIVE2DIRPATH);
    SetFilePathDrive3Dir(DRIVE3DIRPATH);
    SetFilePathDrive4Dir(DRIVE4DIRPATH);

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
            f.open(m_Drive0DirPath);
            break;

        case 1:
            f.open(m_Drive1DirPath);
            break;

        case 2:
            f.open(m_Drive2DirPath);
            break;

        case 3:
            f.open(m_Drive3DirPath);
            break;

        case 4:
            f.open(m_Drive4DirPath);
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
            filepath = m_Drive0ValuePath;
            break;
        case 1:
            filepath = m_Drive1ValuePath;
            break;
        case 2:
            filepath = m_Drive2ValuePath;
            break;
        case 3:
            filepath = m_Drive3ValuePath;
            break;
        case 4:
            filepath = m_Drive4ValuePath;
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

void Drive::SetFilePathDrive0Value(std::string path)
{
    m_Drive0ValuePath = path;
}

void Drive::SetFilePathDrive1Value(std::string path)
{
    m_Drive1ValuePath = path;
}

void Drive::SetFilePathDrive2Value(std::string path)
{
    m_Drive2ValuePath = path;
}

void Drive::SetFilePathDrive3Value(std::string path)
{
    m_Drive3ValuePath = path;
}

void Drive::SetFilePathDrive4Value(std::string path)
{
    m_Drive4ValuePath = path;
}

void Drive::SetFilePathDrive0Dir(std::string path)
{
    m_Drive0DirPath = path;
}

void Drive::SetFilePathDrive1Dir(std::string path)
{
    m_Drive1DirPath = path;
}

void Drive::SetFilePathDrive2Dir(std::string path)
{
    m_Drive2DirPath = path;
}

void Drive::SetFilePathDrive3Dir(std::string path)
{
    m_Drive3DirPath = path;
}

void Drive::SetFilePathDrive4Dir(std::string path)
{
    m_Drive4DirPath = path;
}
