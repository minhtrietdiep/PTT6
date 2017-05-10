#include "HAL.h"

HAL::HAL(std::vector<Drive> drivelist, Vacuum vacuum, Arm arm) : m_Arm(arm)
{
    m_DriveList = drivelist;
    m_Vacuum = vacuum;
}

int HAL::Pickup(bool on)
{
    std::cout << "Activating vacuum" << std::endl;
    return 1;
}

int HAL::MoveArm(int driveid)
{
    std::cout << "Moving arm to drive " << driveid << std::endl;
    return 1;
}

int HAL::MoveArmToHome()
{
    std::cout << "Moving arm to home position" << std::endl;
    return 1;
}

int HAL::OpenDrive(int driveid)
{
    int i = 0;
    for(;i < m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            m_DriveList[i].OpenDrive();
            return 1;
        }
    }
    return -1;
}

int HAL::CloseDrive(int driveid)
{
    int i = 0;
    for(;i < m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            m_DriveList[i].CloseDrive();
            return 1;
        }
    }
    return -1;
}