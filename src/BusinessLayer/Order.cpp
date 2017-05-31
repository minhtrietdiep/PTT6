#include "Order.h"

#define COLLIMATORPOS 99

Order::Order()
{
    m_MoveList = std::vector<Move>();
    m_Hal = HAL();
}
Order::~Order()
{

}

std::vector<Move> Order::GetMoves()
{
    return m_MoveList;
}

enum ErrorCode Order::NewMove(Move newMove)
{
    m_MoveList.push_back(newMove);
    return ErrorCode::ERR_OK;
}

enum ErrorCode Order::Start() 
{
	
    m_States state = OPEN_DRIVE;
    if ((int)m_MoveList.size() <= 0)
    {
        return ErrorCode::ERR_NO_ITEM;
    }
    int ID = m_MoveList[0].GetPlateID();
    int Destination = m_MoveList[0].GetDestination();

    while (state != COMPLETED )
    {
        switch(state) 
        { 
          case OPEN_DRIVE :
                if(m_Hal.OpenDrive(ID) == ErrorCode::ERR_OK)
                state = MOVE_ARM_SOURCE;

                else
                {
                    std::cout<<"##enable"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case MOVE_ARM_SOURCE :
                if(m_Hal.MoveArm(ID) == ErrorCode::ERR_OK)
                state = ENABLE_VACUUM;
                else
                {
                    std::cout<<"##move arm source"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case ENABLE_VACUUM :
                if(m_Hal.Pickup(true) == ErrorCode::ERR_OK)
                state = MOVE_ARM_DESTINATION;
                else
                {
                    std::cout<<"##pickup"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;
                }
                break;
            case MOVE_ARM_DESTINATION :
                if(m_Hal.MoveArm(Destination) == ErrorCode::ERR_OK)
                state = DISABLE_VACUUM;
                else
                {
                    std::cout<<"##move arm dest"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;
                    
                }
                break;
            case DISABLE_VACUUM :
                if(m_Hal.Pickup(false) == ErrorCode::ERR_OK)
                state = MOVE_ARM_HOME;
                else
                    {
                        
                        std::cout<<"##pickup"<< std::endl;
                        return ErrorCode::ERR_UNKNOWN;
                    }
                break;
            case MOVE_ARM_HOME :
                if(m_Hal.MoveArmToHome() == ErrorCode::ERR_OK)
                state = CLOSE_DRIVE;
                else
                {
                    std::cout<<"##arm to home"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;

                }
                break;
            case CLOSE_DRIVE :
                if(m_Hal.CloseDrive(ID) == ErrorCode::ERR_OK)
                state = COMPLETED;
                else
                {
                    std::cout<<"##close drive"<< std::endl;
                    return ErrorCode::ERR_UNKNOWN;
                }


                break;
            default:
                return ErrorCode::ERR_UNKNOWN;
                break;
        }
    }

    m_MoveList.erase(m_MoveList.begin());
    return ErrorCode::ERR_OK;
}

enum ErrorCode Order::Stop() 
{
	std::cout << "Order:Stopping order..." << std::endl;
    return ErrorCode::ERR_OK;
}

enum ErrorCode Order::Reset()
{
    m_MoveList.clear();
	std::cout << "Order:Resetting order..." << std::endl;
    return ErrorCode::ERR_OK;
}