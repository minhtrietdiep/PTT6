#include "HAL.h"

HAL::HAL() :
    m_Arm(Arm()),
    m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH)
{
    m_DriveList.push_back(Drive(0, DRIVE0_POS));
    m_DriveList.push_back(Drive(1, DRIVE1_POS));
    m_DriveList.push_back(Drive(2, DRIVE2_POS));
    m_DriveList.push_back(Drive(3, DRIVE3_POS));
    m_DriveList.push_back(Drive(4, DRIVE4_POS));
    //m_DriveList.push_back(Drive(99, COL_POS)  );

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
            m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Drive setup failed");
            return ErrorCode::ERR_UNKNOWN;
        }
        
    }
    if(m_Vacuum.SetupHardware() == ErrorCode::ERR_OK)
    {
        return ErrorCode::ERR_OK;
    }
    else
    {
        return ErrorCode::ERR_UNKNOWN;
    }
}