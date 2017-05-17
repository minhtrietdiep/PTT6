#include "Preset.h"

Preset::Preset(int id, std::string presetName, std::vector<int> plateList)
{
    m_ID = id;
    m_PresetName = presetName;
    m_PlateList = plateList;
}

int Preset::GetID()
{
    return m_ID;
}

std::string Preset::GetPresetName()
{
    return m_PresetName;
}

std::vector<int> Preset::GetPlatelist()
{
    return m_PlateList;
}
