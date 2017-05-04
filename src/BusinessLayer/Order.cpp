#include "Headers/Order.h"

Order::Order()
{
    std::vector<Move> *movelist = new std::vector<Move>();
    m_MoveList = movelist;
}

std::vector<Move> Order::GetMoves()
{
    return *m_MoveList;
}

void Order::NewMove(Move newMove)
{
    m_MoveList->push_back(newMove);
    std::cout << "Order:New Move..." << std::endl;
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
    m_MoveList->clear();
	std::cout << "Order:Resetting order..." << std::endl;
}
