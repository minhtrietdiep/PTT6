#include "gtest/gtest.h"
#include "../Vacuum.h"
 
#include <fstream>
#include <iostream>

TEST(HAL, VacuumEnableFileNotFound1) 
{
	Vacuum vacuum = Vacuum();

	ErrorCode returnVal = vacuum.EnableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumEnableFileNotFound2) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumValue("vacuum.test");
	ErrorCode returnVal = vacuum.EnableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumEnableFileNotFound3) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathValveValue("valve.test");
	ErrorCode returnVal = vacuum.EnableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumEnableTestFile) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumValue("vacuum.test");
	vacuum.SetFilePathValveValue("valve.test");
	ErrorCode returnVal = vacuum.EnableVacuum();

	std::ifstream ifsVacuum("vacuum.test");
	std::string contentVacuum((std::istreambuf_iterator<char>(ifsVacuum)),
                       (std::istreambuf_iterator<char>()));

	std::ifstream ifsValve("vacuum.test");
	std::string contentValve((std::istreambuf_iterator<char>(ifsValve)),
                       			(std::istreambuf_iterator<char>()));

	EXPECT_EQ(contentVacuum, "1");
	EXPECT_EQ(contentValve, "1");
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}

TEST(HAL, VacuumDisableFileNotFound1) 
{
	Vacuum vacuum = Vacuum();

	ErrorCode returnVal = vacuum.DisableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumDisableFileNotFound2) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumValue("vacuum.test");
	ErrorCode returnVal = vacuum.DisableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumDisableFileNotFound3) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathValveValue("valve.test");
	ErrorCode returnVal = vacuum.DisableVacuum();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumDisableTestFile) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumValue("vacuum.test");
	vacuum.SetFilePathValveValue("valve.test");
	ErrorCode returnVal = vacuum.DisableVacuum();

	std::ifstream ifsVacuum("vacuum.test");
	std::string contentVacuum((std::istreambuf_iterator<char>(ifsVacuum)),
                       (std::istreambuf_iterator<char>()));

	std::ifstream ifsValve("vacuum.test");
	std::string contentValve((std::istreambuf_iterator<char>(ifsValve)),
                       			(std::istreambuf_iterator<char>()));

	EXPECT_EQ(contentVacuum, "0");
	EXPECT_EQ(contentValve, "0");
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}

TEST(HAL, VacuumSetupFileNotFound1) 
{
	Vacuum vacuum = Vacuum();

	ErrorCode returnVal = vacuum.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumSetupFileNotFound2) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumDir("vacuum.test");
	ErrorCode returnVal = vacuum.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumSetupFileNotFound3) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathValveDir("valve.test");
	ErrorCode returnVal = vacuum.SetupHardware();

    EXPECT_EQ(ErrorCode::ERR_UNKNOWN, returnVal);
}

TEST(HAL, VacuumSetupTestFile) 
{
	Vacuum vacuum = Vacuum();

	vacuum.SetFilePathVacuumDir("vacuum.test");
	vacuum.SetFilePathValveDir("valve.test");
	ErrorCode returnVal = vacuum.SetupHardware();

	std::ifstream ifsVacuum("vacuum.test");
	std::string contentVacuum((std::istreambuf_iterator<char>(ifsVacuum)),
                       (std::istreambuf_iterator<char>()));

	std::ifstream ifsValve("vacuum.test");
	std::string contentValve((std::istreambuf_iterator<char>(ifsValve)),
                       			(std::istreambuf_iterator<char>()));

	EXPECT_EQ(contentVacuum, "out");
	EXPECT_EQ(contentValve, "out");
    EXPECT_EQ(ErrorCode::ERR_OK, returnVal);
}