#include "HAL.h"
#include "Coordinates.h"

HAL::HAL() : m_Arm(Arm(Coordinates(1,1,1,1)))
{
    /*Coordinates coords1 = Coordinates(1,2,3,4);
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
    Drive d99 = Drive(99, coords99);*/

    m_DriveList.push_back(Drive(0, DRIVE0_POS));
    m_DriveList.push_back(Drive(1, DRIVE1_POS));
    m_DriveList.push_back(Drive(2, DRIVE2_POS));
    m_DriveList.push_back(Drive(3, DRIVE3_POS));
    m_DriveList.push_back(Drive(4, DRIVE4_POS));
    m_DriveList.push_back(Drive(99, COL_POS)  );

}

HAL::~HAL()
{
    
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

ErrorCode HAL::MoveToCol()
{
    return m_Arm.MoveToCol(COL_POS);
}

ErrorCode HAL::MoveToColPrep()
{
    return m_Arm.MoveToCol(COL_PREP_POS);
}

ErrorCode HAL::MoveToDrive(int driveid)
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            return m_Arm.MoveToDrive(m_DriveList[i].GetDriveMoveCommand());
        }
    }
    return ErrorCode::ERR_UNKNOWN;
}

ErrorCode HAL::MoveToDrivePrep()
{
    return m_Arm.MoveToCol(DRIVE_PREP_POS);
}


/*ErrorCode HAL::MoveArm(int driveid)
{
    for(int i = 0;i < (int)m_DriveList.size(); i++)
    {
        if(m_DriveList[i].GetDriveID() == driveid)
        {
            return m_Arm.MoveToCoord(m_DriveList[i].GetDriveCoordinates());
        }
    }
    return ErrorCode::ERR_UNKNOWN;
}*/

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