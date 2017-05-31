#include "Arm.h"

#define FILEPATH "/dev/Arm.txt"

Arm::Arm(Coordinates homeposition) : m_HomePosition(homeposition)
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
}

enum ErrorCode Arm::MoveToCoord(Coordinates coordinates)
{
    int buffsize = 100;
    char buffer [buffsize];
    if(snprintf(buffer, buffsize, "Moving to pos1: %d, pos2: %d, pos3: %d, pos4: %d",coordinates.GetCoordinates()[0],coordinates.GetCoordinates()[1],coordinates.GetCoordinates()[2],coordinates.GetCoordinates()[3]) >= buffsize)
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "In arm movetocoord: string exceeded buffer size");
    }
    else
    {
        m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                buffer);
    }            
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << coordinates.GetCoordinates()[0] << " " << coordinates.GetCoordinates()[1] << " " << coordinates.GetCoordinates()[2] << " " << coordinates.GetCoordinates()[3] << std::endl;
    myfile.close();
    return ErrorCode::ERR_OK;
}

enum ErrorCode Arm::MoveHome()
{
    m_Logger->Write(Logger::Severity::DEBUG,
                __PRETTY_FUNCTION__,
                "Moving home");
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << m_HomePosition.GetCoordinates()[0] << " " << m_HomePosition.GetCoordinates()[1] << " " << m_HomePosition.GetCoordinates()[2] << " " << m_HomePosition.GetCoordinates()[3];
    myfile.close();
    return ErrorCode::ERR_OK;
}