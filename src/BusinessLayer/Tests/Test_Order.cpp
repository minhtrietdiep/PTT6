#include "gtest/gtest.h"
#include <vector>
#include "../Order.h"
#include "../Move.h"
 
#define MOVESOURCE 0
#define MOVEDESTINATION 2

Order m_Order = Order();

TEST(OrderMove, NewMove) 
{
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(), 1);

}
TEST(OrderMove, GetMoves) 
{
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(), 3);

}
TEST(OrderMove, ResetOrder) 
{
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_Order.Reset();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(),0);
}

