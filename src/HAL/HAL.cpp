#include "HAL.h"

HAL::HAL(std::vector<Drive> drivelist, Vacuum vacuum, Arm arm) : m_Arm(arm)
{
    m_DriveList = drivelist;
    m_Vacuum = vacuum;
}

int HAL::Pickup(bool on)
{
    if(on)
    {
        m_Vacuum.EnableVacuum();
    }
    else
    {
        m_Vacuum.DisableVacuum();
    }
    return 1;
}

int HAL::MoveArm(int driveid)
{
    int i = 0;
    for(;i < m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            m_Arm.MoveToCoord(m_DriveList[i].GetDriveCoordinates());
            return 1;
        }
    }
    return -1;
}

int HAL::MoveArmToHome()
{
    m_Arm.MoveHome();
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