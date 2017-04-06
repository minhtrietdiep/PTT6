#include "Headers/Move.h"

Move::Move(int Source,int Destination,std::vector<Step> Steplist)
{
	m_Source = Source;
    m_Destination = Destination;
    m_Steplist = Steplist;
}
