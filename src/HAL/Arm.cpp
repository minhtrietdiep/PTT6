#include "Arm.h"

Arm::Arm(Coordinates homeposition) : m_HomePosition(homeposition)
{

}

int Arm::MoveToCoord(Coordinates coordinates)
{
    std::cout << "Moving to pos1: " << coordinates.GetCoordinates()[0] << ", pos2: " << coordinates.GetCoordinates()[1] << ", pos3: " << coordinates.GetCoordinates()[2] << ", pos4: " << coordinates.GetCoordinates()[3] << std::endl;
    return 1;
}