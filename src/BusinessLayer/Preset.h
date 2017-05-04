#pragma once

#include "Plate.h"

class Preset {
public:
    Preset(int id,std::vector<Plate> platelist);
    int GetID();
    std::vector<Plate> GetPlatelist();

private:
    int m_ID;
    std::vector<Plate> m_PlateList;
};
