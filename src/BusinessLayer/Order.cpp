#include "Order.h"
#include <Logger.h>
#include <Const.h>

#define COLLIMATORPOS 99


Order::Order()
{
    m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    m_MoveList = std::vector<Move>();
    m_Hal = HAL();
}
Order::~Order()
{
    delete m_Logger;
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
	
    m_States state = m_States::OPEN_DRIVE;
    if ((int)m_MoveList.size() <= 0)
    {
        return ErrorCode::ERR_NO_ITEM;
    }
    int ID = m_MoveList[0].GetPlateID();
    int Destination = m_MoveList[0].GetDestination();

    while (state != m_States::COMPLETED )
    {
        switch(state) 
        { 
          case m_States::OPEN_DRIVE :
                if(m_Hal.OpenDrive(ID) == ErrorCode::ERR_OK)
                state = m_States::MOVE_ARM_SOURCE;

                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Cannot open drive");
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case m_States::MOVE_ARM_SOURCE :
                if(m_Hal.MoveArm(ID) == ErrorCode::ERR_OK)
                state = m_States::ENABLE_VACUUM;
                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to ID");
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case m_States::ENABLE_VACUUM :
                if(m_Hal.Pickup(true) == ErrorCode::ERR_OK)
                state = m_States::MOVE_ARM_DESTINATION;
                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to pickup drive");
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case m_States::MOVE_ARM_DESTINATION :
                if(m_Hal.MoveArm(Destination) == ErrorCode::ERR_OK)
                state = m_States::DISABLE_VACUUM;
                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to Destination");
                    return ErrorCode::ERR_UNKNOWN;
                    
                }
                break;
            case m_States::DISABLE_VACUUM :
                if(m_Hal.Pickup(false) == ErrorCode::ERR_OK)
                state = m_States::MOVE_ARM_HOME;
                else
                    {
                        m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to disable vacuum");
                        return ErrorCode::ERR_UNKNOWN;
                    }
                break;
            case m_States::MOVE_ARM_HOME :
                if(m_Hal.MoveArmToHome() == ErrorCode::ERR_OK)
                state = m_States::CLOSE_DRIVE;
                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to move arm to home");
                    return ErrorCode::ERR_UNKNOWN;

                }
                break;
            case m_States::CLOSE_DRIVE :
                if(m_Hal.CloseDrive(ID) == ErrorCode::ERR_OK)
                state = m_States::COMPLETED;
                else
                {
                    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unable to close drive");
                    return ErrorCode::ERR_UNKNOWN;
                }


                break;
            default:
                m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Unknown switch state");
                return ErrorCode::ERR_UNKNOWN;
                break;
        }
    }

    m_MoveList.erase(m_MoveList.begin());
    return ErrorCode::ERR_OK;
}

ErrorCode Order::Stop() 
{
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Stopping order");
    return ErrorCode::ERR_OK;
}

ErrorCode Order::Reset()
{
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "Resetting order");
    m_MoveList.clear();
    return ErrorCode::ERR_OK;
}

ErrorCode Order::SetupHardware()
{
    return m_Hal.SetupHardware();
}