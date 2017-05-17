#include "Order.h"

Order::Order()
{
    m_MoveList = std::vector<Move>();
}
Order::~Order()
{

}

std::vector<Move> Order::GetMoves()
{
    return m_MoveList;
}

void Order::NewMove(Move newMove)
{
    m_MoveList.push_back(newMove);
    std::cout << "Order:New Move..." << std::endl;
}

void Order::Start()
{
	std::cout << "Order:Starting order..." << std::endl;
    int state = 0;
   // int ID = m_MoveList[0].GetPlateID();
   // int Destination = m_MoveList[0].GetDestination();
                        ///////////////////////////todo: PlateID == de drive locatie van de plaat.
    while (state < 7 )
    {
       /* switch(state) 
        {
          case 0 :
                std::cout<<"Open Drive"<<std::endl;
                if(hal.OpenDrive(ID) == 1)
                state ++;
                break;
            case 1 :
                std::cout<<"Move Arm"<<std::endl;
                if(hal.MoveArm(ID) == 1)
                state ++;
                break;
            case 2 :
                std::cout<<"EnableVacuum"<<std::endl;
                if(hal.EnableVacuum() == 1)
                state ++;
                break;
            case 3 :
                std::cout<<"Move Arm"<<std::endl;
                if(hal.MoveArm(Destination) == 1)
                state ++;
                break;
            case 4 :
                std::cout<<"DisableVacuum"<<std::endl;
                if(hal.DisableVacuum() == 1)
                state ++;
                break;
            case 5 :
                std::cout<<"MoveToHome"<<std::endl;
                if(hal.MoveArmToHome() == 1)
                state ++;
                break;
            case 6 :
                std::cout<<"CloseDrive"<<std::endl;
                if(hal.CloseDrive(ID) == 1)
                state ++;
                break;
        }*/
    }

    m_MoveList.erase(m_MoveList.begin());
}

void Order::Stop()
{
	std::cout << "Order:Stopping order..." << std::endl;
}

void Order::Reset()
{
    m_MoveList.clear();
	std::cout << "Order:Resetting order..." << std::endl;
}
