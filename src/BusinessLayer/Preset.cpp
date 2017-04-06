#include "Headers/Preset.h"

Preset:Preset(int id,std::vector<Plate> platelist)
{
m_PlateList = platelist;
m_ID = id;
}
int GetID()
{
    return m_ID;
}
std::vector<Plate> GetPlatelist()
{
    return m_PlateList;
}
