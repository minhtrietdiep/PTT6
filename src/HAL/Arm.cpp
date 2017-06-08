#include "Arm.h"

#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

Arm::Arm(Coordinates homeposition) : 
    m_HomePosition(homeposition)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    m_ArmFilePath = ARMPATH;
}

Arm::~Arm()
{
    delete m_Logger;
}

ErrorCode Arm::MoveToCoord(Coordinates coordinates)
{
    std::ostringstream msg;
    msg << "Moving to pos1: " << coordinates.GetCoordinates()[0] << ", pos2: " << coordinates.GetCoordinates()[1] 
        << ", pos3: " << coordinates.GetCoordinates()[2] << ", pos4: " << coordinates.GetCoordinates()[3];
    m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str());

    std::ofstream f(m_ArmFilePath);
    if(f.is_open())
    {
        f << coordinates.GetCoordinates()[0] << " " << coordinates.GetCoordinates()[1] << " " << coordinates.GetCoordinates()[2] << " " << coordinates.GetCoordinates()[3];
        f.close();
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm MoveToCoord: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }

    return ErrorCode::ERR_OK;
}

ErrorCode Arm::MoveHome()
{
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Moving home");
    
    std::ofstream f(m_ArmFilePath);
    if(f.is_open())
    {
        f << m_HomePosition.GetCoordinates()[0] << " " << m_HomePosition.GetCoordinates()[1] << " " << m_HomePosition.GetCoordinates()[2] << " " << m_HomePosition.GetCoordinates()[3];
        f.close();
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "In Arm MoveHome: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }

    return ErrorCode::ERR_OK;
}

void Arm::SetFilePath(std::string path)
{
    m_ArmFilePath = path;
}