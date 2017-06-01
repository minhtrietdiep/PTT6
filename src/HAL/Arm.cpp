#include "Arm.h"

enum ErrorCode Arm::Setup()
{
    std::ofstream f;
    f.open(FILEPATH);
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
                "In Arm Setup: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
}

Arm::Arm(Coordinates homeposition) : m_HomePosition(homeposition)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    Setup();
}

enum ErrorCode Arm::MoveToCoord(Coordinates coordinates)
{
    std::ostringstream msg;
    msg << "Moving to pos1: " << coordinates.GetCoordinates()[0] << ", pos2: " << coordinates.GetCoordinates()[1] 
        << ", pos3: " << coordinates.GetCoordinates()[2] << ", pos4: " << coordinates.GetCoordinates()[3];
    m_Logger->Write(Logger::Severity::DEBUG,__PRETTY_FUNCTION__,msg.str());           
    std::ofstream myfile;
    myfile.open (FILEPATH);
    if(myfile.is_open())
    {
        myfile << coordinates.GetCoordinates()[0] << " " << coordinates.GetCoordinates()[1] << " " << coordinates.GetCoordinates()[2] << " " << coordinates.GetCoordinates()[3] << std::endl;
        myfile.close();
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "In Arm MoveToCoord: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
    return ErrorCode::ERR_OK;
}

enum ErrorCode Arm::MoveHome()
{
    m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "Moving home");
    std::ofstream myfile;
    myfile.open (FILEPATH);
    if(myfile.is_open())
    {
        myfile << m_HomePosition.GetCoordinates()[0] << " " << m_HomePosition.GetCoordinates()[1] << " " << m_HomePosition.GetCoordinates()[2] << " " << m_HomePosition.GetCoordinates()[3];
        myfile.close();
    }
    else
    {
        m_Logger->Write(Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "In Arm MoveHome: failed to open a GPIO file");
        return ErrorCode::ERR_UNKNOWN;
    }
    return ErrorCode::ERR_OK;
}