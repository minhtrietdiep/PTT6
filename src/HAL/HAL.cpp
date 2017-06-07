#include "HAL.h"
#include <iostream>
#include "Coordinates.h"

HAL::HAL() : m_Arm(Arm(Coordinates(1,1,1,1)))
{
    Coordinates coords1 = Coordinates(1,2,3,4);
    Drive d1 = Drive(0, coords1);
    Coordinates coords2 = Coordinates(2,1,3,4);
    Drive d2 = Drive(1, coords2);
    Coordinates coords3 = Coordinates(1,2,5,4);
    Drive d3 = Drive(2, coords3);
    Coordinates coords4 = Coordinates(1,7,3,10);
    Drive d4 = Drive(3, coords4);
    Coordinates coords5 = Coordinates(124,2,3,22);
    Drive d5 = Drive(4, coords5);
    Coordinates coords99 = Coordinates(999,99,999,99);
    Drive d99 = Drive(99, coords99);
    std::vector<Drive> drivelist;
    drivelist.push_back(d5);
    drivelist.push_back(d4);
    drivelist.push_back(d3);
    drivelist.push_back(d2);
    drivelist.push_back(d1);
    drivelist.push_back(d99);
    m_DriveList = drivelist;
    //////TODO: Hubert -> to config file
}

ErrorCode HAL::Pickup(bool on)
{
    if(on)
    {
        return m_Vacuum.EnableVacuum();
    }
    else
    {
        return m_Vacuum.DisableVacuum();
    }
}

ErrorCode HAL::MoveArm(int driveid)
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            return m_Arm.MoveToCoord(m_DriveList[i].GetDriveCoordinates());
        }
    }
    return ErrorCode::ERR_UNKNOWN;
}

ErrorCode HAL::MoveArmToHome()
{
    return m_Arm.MoveHome();
}

ErrorCode HAL::OpenDrive(int driveid)
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            return m_DriveList[i].OpenDrive();
        }
    } 
    return ErrorCode::ERR_UNKNOWN;
}

ErrorCode HAL::CloseDrive(int driveid)
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            return m_DriveList[i].CloseDrive();
        }
    }
    return ErrorCode::ERR_UNKNOWN;
}

ErrorCode HAL::SetupHardware()
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].SetupHardware() != ErrorCode::ERR_OK)
        {
            return ErrorCode::ERR_UNKNOWN;
        }
        
    }
    if(m_Vacuum.SetupHardware() != ErrorCode::ERR_OK)
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        return ErrorCode::ERR_UNKNOWN;
    }
}