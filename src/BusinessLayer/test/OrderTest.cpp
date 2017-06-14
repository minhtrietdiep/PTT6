#include <gtest/gtest.h>
#include <vector>
#include <Order.h>
#include <Move.h>
#include <Logger.h>
#include <Const.h>
 
#define MOVESOURCE 0
#define MOVEDESTINATION 2
#define ID 2


TEST(OrderMove, NewMove) 
{
        Order m_Order;
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(), 1);

}
TEST(OrderMove, GetMoves) 
{
        Order m_Order;
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(), 3);

}
TEST(OrderMove, ResetOrder) 
{
        Order m_Order;
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_Order.Reset();
        m_MoveList = m_Order.GetMoves();
        EXPECT_EQ(m_MoveList.size(),0);
}

TEST(OrderMove, StartEmptyOrder) 
{
        Order m_Order;
        std::vector<Move> m_MoveList = std::vector<Move>();
        m_Order.Reset();
        ErrorCode error = m_Order.Start();
        EXPECT_EQ(error, ErrorCode::ERR_NO_ITEM);
}

TEST(OrderMove, SetupHardware) 
{
        Order m_Order;
        std::vector<Move> m_MoveList = std::vector<Move>();
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        ErrorCode error = m_Order.SetupHardware();
        EXPECT_EQ(error, ErrorCode::ERR_UNKNOWN);
}

TEST(OrderMove, PlateToDrive) 
{
        Order m_Order;
        std::vector<Move> m_MoveList = std::vector<Move>();
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        ErrorCode error = m_Order.PlateToDrive(ID);
        EXPECT_EQ(error, ErrorCode::ERR_UNKNOWN);
}

TEST(OrderMove, PlateToCol) 
{
        Order m_Order;
        std::vector<Move> m_MoveList = std::vector<Move>();
        Move move = Move(MOVESOURCE,MOVEDESTINATION);
        m_Order.NewMove(move);
        m_Order.NewMove(move);
        ErrorCode error = m_Order.PlateToCol(ID);
        EXPECT_EQ(error, ErrorCode::ERR_UNKNOWN);
}