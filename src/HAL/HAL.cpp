#include "HAL.h"

HAL::HAL() : m_Arm(Arm(Coordinates(1,1,1,1)))
{
    Coordinates coords1 = Coordinates(1,2,3,4);
    Drive d1 = Drive(1, coords1);
    Coordinates coords2 = Coordinates(2,1,3,4);
    Drive d2 = Drive(2, coords2);
    Coordinates coords3 = Coordinates(1,2,5,4);
    Drive d3 = Drive(3, coords3);
    Coordinates coords4 = Coordinates(1,7,3,10);
    Drive d4 = Drive(4, coords4);
    Coordinates coords5 = Coordinates(124,2,3,22);
    Drive d5 = Drive(5, coords5);
    std::vector<Drive> drivelist;
    drivelist.push_back(d5);
    drivelist.push_back(d4);
    drivelist.push_back(d3);
    drivelist.push_back(d2);
    drivelist.push_back(d1);
    m_DriveList = drivelist;
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