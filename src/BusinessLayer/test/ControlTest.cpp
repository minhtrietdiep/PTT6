#include "gtest/gtest.h"
#include "../Control.h"

Control control({});

 
TEST(Controltest, ConstructorEmptyGetPresetsTest) 
{
    Control control({});
    std::vector<Preset> emptyPresets;
    EXPECT_EQ(control.GetPresets().size(), emptyPresets.size());
}

TEST(Controltest, ConstructorValidGetPresetsTest) 
{
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

    Control control(presetList);

    std::vector<Preset> getPresetListResult = control.GetPresets();
    EXPECT_EQ(getPresetListResult.size(), presetList.size());

    for (unsigned int i = 0; i < presetList.size(); i++) {
        EXPECT_EQ(getPresetListResult[i].GetID(), presetList[i].GetID());
    }
}

TEST(Controltest, InvalidPlateMoveTest) 
{
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

    Control control(presetList);

    ErrorCode result = control.PlateToDrive(-1);
    ErrorCode expected = ErrorCode::ERR_INVALID_ARG;

    EXPECT_EQ(result, expected);
}

TEST(Controltest, InvalidPlateToCollimatorTest) 
{
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

    Control control(presetList);

    ErrorCode result = control.PlateToCollimator(-1);
    ErrorCode expected = ErrorCode::ERR_INVALID_ARG;

    EXPECT_EQ(result, expected);
}

