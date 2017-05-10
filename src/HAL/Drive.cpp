#include "Drive.h"

Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions)
{
    m_DriveID = driveid;
}

int Drive::OpenDrive()
{
    std::cout << "Opening drive " << m_DriveID << std::endl;
    return 1;
}

int Drive::CloseDrive()
{
    std::cout << "Closing drive " << m_DriveID << std::endl;
    return 1;
}

int Drive::GetDriveID()
{
    return m_DriveID;
}

Coordinates Drive::GetDriveCoordinates()
{
    return m_Positions;
}