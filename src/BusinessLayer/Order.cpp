#include "Order.h"

#define COLLIMATORPOS 99


Order::Order() : 
    m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH) 
{


}

Order::~Order() 
{ 

}

std::vector<Move> Order::GetMoves()
{
    return m_MoveList;
}

ErrorCode Order::NewMove(Move newMove)
{

        m_MoveList.push_back(newMove);
       return ErrorCode::ERR_OK;

}

ErrorCode Order::Start() 
{
	
    if ((int)m_MoveList.size() <= 0)
    {
        return ErrorCode::ERR_NO_ITEM;
    }
    int ID = m_MoveList[0].GetPlateID();
    int Destination = m_MoveList[0].GetDestination();

    if(SetupHardware() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Cannot SetupHardware");
        return ErrorCode::ERR_UNKNOWN;
    }

    if(m_Hal.OpenDrive(ID) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Cannot open drive");
        return ErrorCode::ERR_UNKNOWN;
    }

    if (Destination == COLLIMATORPOS)
    {
        if(PlateToCol(ID) != ErrorCode::ERR_OK)
        {
            m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to COLLIMATORPOS");
            return ErrorCode::ERR_UNKNOWN;
        }
    } else
    {
            if(PlateToDrive(ID) != ErrorCode::ERR_OK)
        {
            m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to COLLIMATORPOS");
            return ErrorCode::ERR_UNKNOWN;
        }
    }

    if(m_Hal.MoveArmToHome() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to home");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.CloseDrive(ID) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to close drive");
        return ErrorCode::ERR_UNKNOWN;
    }

    m_MoveList.erase(m_MoveList.begin());
    return ErrorCode::ERR_OK;
}

ErrorCode Order::Stop() 
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Stopping order");
    return ErrorCode::ERR_OK;
}

ErrorCode Order::Reset()
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Resetting order");
    m_MoveList.clear();
    return ErrorCode::ERR_OK;
}

ErrorCode Order::SetupHardware()
{
    return m_Hal.SetupHardware();
}
ErrorCode Order::PlateToDrive(int driveID)
{
    if(m_Hal.MoveToColPrep() != ErrorCode::ERR_OK) 
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to col prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToCol() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to COL");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.Pickup(true) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to pickup drive");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToColPrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to col prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToDrivePrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive Prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToDrive(driveID) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.Pickup(false) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to disable vacuum");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToDrivePrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive Prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    return ErrorCode::ERR_OK;
}
ErrorCode Order::PlateToCol(int driveID)
{
    if(m_Hal.MoveToDrivePrep() != ErrorCode::ERR_OK) 
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to col prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToDrive(driveID) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to COL");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.Pickup(true) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to pickup drive");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToDrivePrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to col prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToColPrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive Prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToCol() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.Pickup(false) != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to disable vacuum");
        return ErrorCode::ERR_UNKNOWN;
    }
    if(m_Hal.MoveToColPrep() != ErrorCode::ERR_OK)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Drive Prep");
        return ErrorCode::ERR_UNKNOWN;
    }
    return ErrorCode::ERR_OK;
}