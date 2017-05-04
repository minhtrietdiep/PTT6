#include "Headers/Order.h"

Order::Order(std::vector<Move> moves)
{
	m_Moves = moves;
}

std::vector<Move> Order::GetMoves()
{
    return m_Moves;
}

void Order::Start()
{
	
}

void Order::Stop()
{
	
}

void Order::Reset()
{
	
}
