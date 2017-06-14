#include <gtest/gtest.h>
#include <JSONUtils.h>

TEST(JSONUtils, PresetToJSONStringTest)
{
    EXPECT_EQ(1, 1);
}

TEST(JSONUtils, PlateListToJSONStringTest_InvalidPlateList)
{
    std::string empty = "";
    std::string result;
    std::vector<Plate> plates;
    PlateList type = PlateList::Size;
    result = PlateListToJSONString(plates, type);

    EXPECT_EQ(result, empty);
}

TEST(JSONUtils, PlateListToJSONStringTest_EmptyDriveList)
{
    std::string EmptyDriveString = "{\"Name\":\"m_DriveList\",\"Plates\":[]}";
    std::string result;
    std::vector<Plate> plates;
    PlateList type = PlateList::DRIVELIST;
    result = PlateListToJSONString(plates, type);

    EXPECT_EQ(result, EmptyDriveString);
}

TEST(JSONUtils, PlateListToJSONStringTest_EmptyCollimatorList)
{
    std::string EmptyCollimatorString = "{\"Name\":\"m_CollimatorList\",\"Plates\":[]}";
    std::string result;
    std::vector<Plate> plates;
    PlateList type = PlateList::COLLIMATORLIST;
    result = PlateListToJSONString(plates, type);

    EXPECT_EQ(result, EmptyCollimatorString);
}

TEST(JSONUtils, PlateListToJSONStringTest_SimpleDriveList)
{
    Plate plate0 = Plate(0, 0, -1, "lead", 0.11);
    Plate plate1 = Plate(1, 1, -1, "lead", 0.11);
    Plate plate2 = Plate(2, 2, -1, "copper", 0.11);
    Plate plate3 = Plate(3, 3, -1, "copper", 0.11);
    Plate plate4 = Plate(4, 4, -1, "lead", 0.11);

    std::vector<Plate> plates = {plate0, plate1, plate2, plate3, plate4};

    std::string SimpleDriveString =  "{\"Name\":\"m_DriveList\",\"Plates\":[{\"m_ID\":0,\"m_DrivePosition\":0,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11},{\"m_ID\":1,\"m_DrivePosition\":1,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11},{\"m_ID\":2,\"m_DrivePosition\":2,\"m_CollimatorPosition\":-1,\"m_Property\":\"copper\",\"m_Thickness\":0.11},{\"m_ID\":3,\"m_DrivePosition\":3,\"m_CollimatorPosition\":-1,\"m_Property\":\"copper\",\"m_Thickness\":0.11},{\"m_ID\":4,\"m_DrivePosition\":4,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11}]}";
    std::string result;
    PlateList type = PlateList::DRIVELIST;
    result = PlateListToJSONString(plates, type);

    EXPECT_EQ(result, SimpleDriveString);
}

TEST(JSONUtils, PlateListToJSONStringTest_SimpleCollimatorList)
{
    Plate plate0 = Plate(0, 0, -1, "lead", 0.11);
    Plate plate1 = Plate(1, 1, -1, "lead", 0.11);
    Plate plate2 = Plate(2, 2, -1, "copper", 0.11);
    Plate plate3 = Plate(3, 3, -1, "copper", 0.11);
    Plate plate4 = Plate(4, 4, -1, "lead", 0.11);

    std::vector<Plate> plates = {plate0, plate1, plate2, plate3, plate4};

    std::string SimpleCollimatorString = "{\"Name\":\"m_CollimatorList\",\"Plates\":[{\"m_ID\":0,\"m_DrivePosition\":0,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11},{\"m_ID\":1,\"m_DrivePosition\":1,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11},{\"m_ID\":2,\"m_DrivePosition\":2,\"m_CollimatorPosition\":-1,\"m_Property\":\"copper\",\"m_Thickness\":0.11},{\"m_ID\":3,\"m_DrivePosition\":3,\"m_CollimatorPosition\":-1,\"m_Property\":\"copper\",\"m_Thickness\":0.11},{\"m_ID\":4,\"m_DrivePosition\":4,\"m_CollimatorPosition\":-1,\"m_Property\":\"lead\",\"m_Thickness\":0.11}]}";
    std::string result;
    PlateList type = PlateList::COLLIMATORLIST;
    result = PlateListToJSONString(plates, type);

    EXPECT_EQ(result, SimpleCollimatorString);
}

TEST(JSONUtils, PresetToJSONString_EmptyList) 
{
    std::string expected = "{\"Name\":\"m_Presets\",\"PresetList\":[]}";

    std::vector<Preset> presetList = { };

    std::string result = PresetToJSONString(presetList);
    EXPECT_EQ(result, expected);
}

TEST(JSONUtils, PresetToJSONString_SimpleList) 
{
    std::string expected = "{\"Name\":\"m_Presets\",\"PresetList\":[{\"m_PresetID\":0,\"m_PresetName\":\"preset0\",\"m_PlateIDs\":[{\"ID\":20},{\"ID\":99}]},{\"m_PresetID\":1,\"m_PresetName\":\"preset1\",\"m_PlateIDs\":[{\"ID\":10},{\"ID\":20}]}]}";

    std::string PRESETNAME0 = "preset0";
    std::string PRESETNAME1 = "preset1";
    int PRESETID0         = 0;
    int PRESETID1         = 1;
    int PRESETLISTVALUE0 = 10;
    int PRESETLISTVALUE1 = 20;
    int PRESETLISTVALUE2 = 99;

    std::vector<int> plateList0 = {PRESETLISTVALUE1, PRESETLISTVALUE2};
    std::vector<int> plateList1 = {PRESETLISTVALUE0, PRESETLISTVALUE1};
    Preset m_Preset0 = Preset(PRESETID0, PRESETNAME0, plateList0);
    Preset m_Preset1 = Preset(PRESETID1, PRESETNAME1, plateList1);

    std::vector<Preset> presetList = { m_Preset0, m_Preset1 };

    std::string result = PresetToJSONString(presetList);
    EXPECT_EQ(result, expected);
}
