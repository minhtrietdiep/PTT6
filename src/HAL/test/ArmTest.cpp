#include "gtest/gtest.h"
#include "../Arm.h"

#include <fstream>
#include <iostream>
 /*
TEST(HAL, ArmMoveToCoordFileNotFound) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	Arm arm = Arm(coords);

	ErrorCode returnVal = arm.MoveToCoord(coords);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, ArmMoveHomeFileNotFound) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	Arm arm = Arm(coords);

	ErrorCode returnVal = arm.MoveHome();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, ArmMoveToCoordTestFile) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);
	Coordinates coordsMoveTo = Coordinates(4, 3, 2, 1);

	Arm arm = Arm(coords);
	arm.SetFilePath("arm.test");
	ErrorCode returnVal = arm.MoveToCoord(coordsMoveTo);

	std::string expected = "4 3 2 1";

	std::ifstream ifs("arm.test");
	std::string content(	(std::istreambuf_iterator<char>(ifs)),
                       		(std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, expected);
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}

TEST(HAL, ArmMoveHomeTestFile) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	Arm arm = Arm(coords);
	arm.SetFilePath("arm.test");
	ErrorCode returnVal = arm.MoveHome();

	std::string expected = "1 2 3 4";

	std::ifstream ifs("arm.test");
	std::string content(	(std::istreambuf_iterator<char>(ifs)),
							(std::istreambuf_iterator<char>()));

    EXPECT_EQ(content, expected);
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}*/

TEST(HAL, MoveHome) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);

    ErrorCode returnVal = arm.MoveHome();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToCol) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.MoveToCol(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToColPrep) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);

    ErrorCode returnVal = arm.MoveToColPrep();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToDrive) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.MoveToDrive(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, MoveToDrivePrep) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);

    ErrorCode returnVal = arm.MoveToDrivePrep();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, WriteCommand) 
{
    Coordinates coords = Coordinates(1, 2, 3, 4);

    Arm arm = Arm(coords);
    std::string content = "#0P2440S700#2P2070S1000#3P1325S1000#4P861S700\r";
    ErrorCode returnVal = arm.WriteCommand(content);

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

