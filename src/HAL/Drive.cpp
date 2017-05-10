#include "Drive.h"

Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions)
{
    m_DriveID = driveid;
}

void Drive::OpenDrive()
{
    std::cout << "Opening drive " << m_DriveID << std::endl;
}

void Drive::CloseDrive()
{
    std::cout << "Closing drive " << m_DriveID << std::endl;
}

int Drive::GetDriveID()
{
    return m_DriveID;
}