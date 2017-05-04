#include "Move.h"

Move::Move(int Source,int Destination,std::vector<Step> Steplist)
{
    std::cout << "Move:Moving from " << Source << " to " << Destination << std::endl;
	m_Source = Source;
    m_Destination = Destination;
    m_Steplist = Steplist;
}
