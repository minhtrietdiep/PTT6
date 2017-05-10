#include "HAL.h"

HAL::HAL(std::vector<Drive> drivelist, Vacuum vacuum, Arm arm)
{
    m_DriveList = drivelist;
    m_Vacuum = vacuum;
    m_Arm = arm;
}

void HAL::Pickup(bool on)
{
    std::cout << "Activating vacuum" << std::endl;
}

void HAL::MoveArm(int driveid)
{
    std::cout << "Moving arm to drive " << driveid << std::endl;
}

void HAL::MoveArmToHome()
{
    std::cout << "Moving arm to home position" << std::endl;
}

void HAL::OpenDrive(int driveid)
{
    int i = 0;
    for(;i < m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            m_DriveList[i].OpenDrive();
        }
    }
}

void HAL::CloseDrive(int driveid)
{
    int i = 0;
    for(;i < m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            m_DriveList[i].CloseDrive();
        }
    }
}