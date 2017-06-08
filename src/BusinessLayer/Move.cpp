#include "Move.h"

Move::Move(int PlateID,int Destination)
{
    m_PlateID = PlateID;
    m_Destination = Destination;
}
Move::~Move()
{
    
}
int Move::GetPlateID()
{
    return m_PlateID;
}
int Move::GetDestination()
{
    return m_Destination;
}
