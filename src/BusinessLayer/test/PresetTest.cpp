#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include "../Preset.h"

#define PRESETID 0
#define PRESETLISTVALUE0 10
#define PRESETLISTVALUE1 20
#define PRESETLISTVALUE2 99
#define PRESETNAME "preset1"


TEST(Presettest, NewPreset) 
{
    //std::string name = PRESETNAME; 
    std::vector<int> presetlist;
    presetlist.push_back(PRESETLISTVALUE0);
    presetlist.push_back(PRESETLISTVALUE1);
    presetlist.push_back(PRESETLISTVALUE2);
    Preset m_Preset = Preset(PRESETID, PRESETNAME, presetlist);

    EXPECT_EQ(m_Preset.GetID(),PRESETID);

    std::vector<int> presetlisttest ;
    presetlisttest = m_Preset.GetPlatelist();
    EXPECT_EQ(presetlisttest[0], PRESETLISTVALUE0);
    EXPECT_EQ(presetlisttest[1], PRESETLISTVALUE1);
    EXPECT_EQ(presetlisttest[2], PRESETLISTVALUE2);

    EXPECT_EQ(m_Preset.GetPresetName(),PRESETNAME);
}
