#include "gtest/gtest.h"
#include "../Drive.h"
 
#include <fstream>
#include <iostream>

TEST(HAL, SetupHardwareFail) 
{
    Drive drive = Drive(0, "movecommand");

    ErrorCode returnVal = drive.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, OpenDriveFail) 
{
    Drive drive = Drive(0, "movecommand");

    ErrorCode returnVal = drive.OpenDrive();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, CloseDriveFail) 
{
    Drive drive = Drive(0, "movecommand");

    ErrorCode returnVal = drive.CloseDrive();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, GetDriveID) 
{
    Drive drive = Drive(2, "movecommand");

    int returnVal = drive.GetDriveID();

    EXPECT_EQ(returnVal, 2);
}

TEST(HAL, GetDriveMoveCommand) 
{
    Drive drive = Drive(2, "movecommand");

    std::string returnVal = drive.GetDriveMoveCommand();

    EXPECT_EQ(returnVal, "movecommand");
}