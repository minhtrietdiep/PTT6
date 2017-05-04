#include "Order.h"

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
	std::cout << "Order:Starting order..." << std::endl;
}

void Order::Stop()
{
	std::cout << "Order:Stopping order..." << std::endl;
}

void Order::Reset()
{
	std::cout << "Order:Resetting order..." << std::endl;
}
