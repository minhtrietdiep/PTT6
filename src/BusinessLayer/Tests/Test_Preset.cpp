#include "gtest/gtest.h"
#include <vector>
#include <iostream>
#include "../Headers/Preset.h"

#define PRESETID 0
#define PRESETLISTVALUE0 10
#define PRESETLISTVALUE1 20
#define PRESETLISTVALUE2 99

Preset *m_Preset;

TEST(Presettest, NewPreset) 
{
    std::vector<int> *presetlist = new std::vector<int> ;
    presetlist->push_back(PRESETLISTVALUE0);
    presetlist->push_back(PRESETLISTVALUE1);
    presetlist->push_back(PRESETLISTVALUE2);
    m_Preset = new Preset(PRESETID,*presetlist);
}    
TEST(Presettest, GetPresetID) 
{
    EXPECT_EQ(m_Preset->GetID(),PRESETID);
}
TEST(Presettest, GetPlateList) 
{
    std::vector<int> presetlisttest ;
    presetlisttest = m_Preset->GetPlatelist();
    EXPECT_EQ(presetlisttest[0], PRESETLISTVALUE0);
    EXPECT_EQ(presetlisttest[1], PRESETLISTVALUE1);
    EXPECT_EQ(presetlisttest[2], PRESETLISTVALUE2);
}
