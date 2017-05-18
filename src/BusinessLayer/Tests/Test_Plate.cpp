#include "gtest/gtest.h"
#include "./../Plate.h"
#include <string>
 
 #define PLATEID 1
 #define PLATEDRIVEPOSITION 2
 #define PLATECOLLIMATORPOSITION 3
 #define PLATEPROPERTIES "properties"
 #define PLATETHICKNESS 5

Plate m_Plate = Plate(PLATEID,PLATEDRIVEPOSITION,PLATECOLLIMATORPOSITION,PLATEPROPERTIES,PLATETHICKNESS);

TEST(NewPlate, GetPlateID) 
{
    EXPECT_EQ(PLATEID, m_Plate.GetID());
}
TEST(NewPlate, GetDrivePosition) 
{
    EXPECT_EQ(PLATEDRIVEPOSITION, m_Plate.GetDrivePosition());
}
TEST(NewPlate, GetColimatorPosition) 
{
    EXPECT_EQ(PLATECOLIMATORPOSITION, m_Plate.GetCollimatorPosition());
}
TEST(NewPlate, GetProperties) 
{
    EXPECT_EQ(PLATEPROPERTIES, m_Plate.GetProperties());
}
TEST(NewPlate, GetThickness) 
{
    EXPECT_EQ(PLATETHICKNESS, m_Plate.GetThickness());
}

