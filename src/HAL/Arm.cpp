#include "Arm.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

Arm::Arm(Coordinates homeposition) : 
    m_HomePosition(homeposition)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
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

Arm::~Arm() {
    delete m_Logger;
}

/*ErrorCode Arm::MoveToCoord(Coordinates coordinates)
{
    std::ostringstream msg;
    msg << "Moving to pos1: " << coordinates.GetCoordinates()[0] << ", pos2: " << coordinates.GetCoordinates()[1] 
        << ", pos3: " << coordinates.GetCoordinates()[2] << ", pos4: " << coordinates.GetCoordinates()[3];
    m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str());           
    std::ofstream f(ARMPATH);
    if(f.is_open())
    {
        f << coordinates.GetCoordinates()[0] << " " << coordinates.GetCoordinates()[1] << " " << coordinates.GetCoordinates()[2] << " " << coordinates.GetCoordinates()[3] << std::endl;
        f.close();
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm MoveToCoord: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
    return ErrorCode::ERR_OK;
}*/

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
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm WriteCommand: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(tcsetattr(fd, TCSANOW, &m_SerialConfig) != 0)
    {
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm WriteCommand: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }

    write(fd, commandchar, strlen(commandchar));
    return ErrorCode::ERR_OK;
}