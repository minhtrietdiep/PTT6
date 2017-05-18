#include "Arm.h"

#define FILEPATH "/dev/Arm.txt"

Arm::Arm(Coordinates homeposition) : m_HomePosition(homeposition)
{
    
}

enum ErrorCode Arm::MoveToCoord(Coordinates coordinates)
{
    std::cout << "Moving to pos1: " << coordinates.GetCoordinates()[0] << ", pos2: " << coordinates.GetCoordinates()[1] << ", pos3: " << coordinates.GetCoordinates()[2] << ", pos4: " << coordinates.GetCoordinates()[3] << std::endl;
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << coordinates.GetCoordinates()[0] << " " << coordinates.GetCoordinates()[1] << " " << coordinates.GetCoordinates()[2] << " " << coordinates.GetCoordinates()[3] << std::endl;
    myfile.close();
    return ErrorCode::ERR_OK;
}

enum ErrorCode Arm::MoveHome()
{
    std::cout << "Moving home" << std::endl;
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << m_HomePosition.GetCoordinates()[0] << " " << m_HomePosition.GetCoordinates()[1] << " " << m_HomePosition.GetCoordinates()[2] << " " << m_HomePosition.GetCoordinates()[3] << std::endl;
    myfile.close();
    return ErrorCode::ERR_OK;
}