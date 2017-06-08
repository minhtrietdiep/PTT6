#include "gtest/gtest.h"
#include "../Drive.h"
 
#include <fstream>
#include <iostream>

TEST(HAL, DriveSetupFileNotFound) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);
	Drive drive = Drive(0, coords);

	ErrorCode returnVal = drive.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, DriveSetupOutOfRange) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);
	Drive drive = Drive(8, coords);

	drive.SetFilePathDrive0Dir("drive.test");
	ErrorCode returnVal = drive.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, DriveSetupOk) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);
	Drive drive = Drive(0, coords);

	drive.SetFilePathDrive0Dir("drive.test");
	ErrorCode returnVal = drive.SetupHardware();

	std::ifstream ifs("drive.test");
	std::string content((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));

	EXPECT_EQ(content, "out");
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}