#include <gtest/gtest.h>
#include <Move.h>

#define ID 6
#define DES 2 

TEST(Movetest, GetPlateID) 
{
    Move move = Move(ID,DES);
    EXPECT_EQ(move.GetPlateID(), ID);
}

TEST(Movetest, GetDestination) 
{
    Move move = Move(ID,DES);
    EXPECT_EQ(move.GetDestination(), DES);
}

 
