#include "Preset.h"

Preset::Preset(int id,std::vector<int> PlateList)
{
    m_PlateList = PlateList;
    m_ID = id;
}
int Preset::GetID()
{
    return m_ID;
}
std::vector<int> Preset::GetPlatelist()
{
    return m_PlateList;
}
