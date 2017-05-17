#include "Move.h"

Move::Move(int PlateID,int Destination)
{
    m_PlateID = PlateID;
    m_Destination = Destination;
    std::cout<<"new move set "<<PlateID<<" " <<Destination<<std::endl;
}
Move::~Move()
{
    
}
