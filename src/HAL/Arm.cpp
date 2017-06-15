#include "Arm.h"

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

Arm::Arm() : 
    m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH)
{
    m_ColPrepCommand = COL_PREP_POS;
    m_DrivePrepCommand = DRIVE_PREP_POS;
    m_ArmHomeCommand = HOME_POS;
    cfsetospeed(&m_SerialConfig, BAUDRATE);
    cfsetispeed(&m_SerialConfig, BAUDRATE);
    cfmakeraw(&m_SerialConfig);
    m_SerialConfig.c_cflag = 6322;
    m_SerialConfig.c_iflag = 1030;
    m_SerialConfig.c_oflag = 0;
}

Arm::~Arm() 
{

}


ErrorCode Arm::MoveHome()
{
    return WriteCommand(m_ArmHomeCommand);
}

ErrorCode Arm::MoveToCol(std::string command)
{
    return WriteCommand(command);
}

ErrorCode Arm::MoveToColPrep()
{
    return WriteCommand(m_ColPrepCommand);
}

ErrorCode Arm::MoveToDrive(std::string command)
{
    return WriteCommand(command);
}

ErrorCode Arm::MoveToDrivePrep()
{
    return WriteCommand(m_DrivePrepCommand);
}

ErrorCode Arm::WriteCommand(std::string command)
{
    char const* commandchar = command.c_str();
    int fd = open(ARMPATH, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd < 0)
    {   
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm WriteCommand: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(tcsetattr(fd, TCSANOW, &m_SerialConfig) != 0)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm WriteCommand: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }

    write(fd, commandchar, strlen(commandchar));
    if (close(fd) < 0) 
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Can't close GPIO file");
        return ErrorCode::ERR_FILE_OPEN;
    }

    sleep(2);
    return ErrorCode::ERR_OK;
}

void Arm::SetFilePath(std::string path)
{
    m_ArmFilePath = path;
}
