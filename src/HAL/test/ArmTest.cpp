#include "gtest/gtest.h"
#include "../Arm.h"

#include <fstream>
#include <iostream>

TEST(HAL, MoveHome) 
{
    Arm arm = Arm();

    ErrorCode returnVal = arm.MoveHome();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToCol) 
{
    Arm arm = Arm();
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.MoveToCol(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToColPrep) 
{
    Arm arm = Arm();

    ErrorCode returnVal = arm.MoveToColPrep();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToDrive) 
{
    Arm arm = Arm();
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.MoveToDrive(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToDrivePrep) 
{
    Arm arm = Arm();

    ErrorCode returnVal = arm.MoveToDrivePrep();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, WriteCommand) 
{
    Arm arm = Arm();
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.WriteCommand(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

