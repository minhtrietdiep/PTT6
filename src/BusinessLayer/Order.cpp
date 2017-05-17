#include "Order.h"

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
    std::cout << "Order:New Move..." << std::endl;
    return ErrorCode::OK;
}

enum ErrorCode Order::Start() 
{
	std::cout << "Order:Starting order..." << std::endl;
    m_States state = OPEN_DRIVE;
    int ID = m_MoveList[0].GetPlateID();
    int Destination = m_MoveList[0].GetDestination();

    while (state != COMPLETED )
    {
        switch(state) 
        { 
          case OPEN_DRIVE :
                std::cout<<"Open Drive"<<std::endl;
                if(m_Hal.OpenDrive(ID) == 1)
                state = MOVE_ARM_SOURCE;
                break;
            case MOVE_ARM_SOURCE :
                std::cout<<"Move Arm"<<std::endl;
                if(m_Hal.MoveArm(ID) == 1)
                state = ENABLE_VACUUM;
                break;
            case ENABLE_VACUUM :
                std::cout<<"EnableVacuum"<<std::endl;
                if(m_Hal.Pickup(true) == 1)
                state = MOVE_ARM_DESTINATION;
                break;
            case MOVE_ARM_DESTINATION :
                std::cout<<"Move Arm"<<std::endl;
                if(m_Hal.MoveArm(Destination) == 1)
                state = DISABLE_VACUUM;
                break;
            case DISABLE_VACUUM :
                std::cout<<"DisableVacuum"<<std::endl;
                if(m_Hal.Pickup(false) == 1)
                state = MOVE_ARM_HOME;
                break;
            case MOVE_ARM_HOME :
                std::cout<<"MoveToHome"<<std::endl;
                if(m_Hal.MoveArmToHome() == 1)
                state = CLOSE_DRIVE;
                break;
            case CLOSE_DRIVE :
                std::cout<<"CloseDrive"<<std::endl;
                if(m_Hal.CloseDrive(ID) == 1)
                state = COMPLETED;
                break;
            default:
                return ErrorCode::ERR_TIMEOUT;  //////////////////////goede????
                break;
        }
    }

    m_MoveList.erase(m_MoveList.begin());
    return ErrorCode::OK;
}

enum ErrorCode Order::Stop()
{
	std::cout << "Order:Stopping order..." << std::endl;
    return ErrorCode::OK;
}

enum ErrorCode Order::Reset()
{
    m_MoveList.clear();
	std::cout << "Order:Resetting order..." << std::endl;
    return ErrorCode::OK;
}
