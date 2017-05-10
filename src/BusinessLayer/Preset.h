#pragma once

#include "Plate.h"

class Preset {
    private:
        int m_ID;
        std::vector<int> m_PlateList;

    public:
        Preset(int id,std::vector<int> PlateList);
        int GetID();
        std::vector<int> GetPlatelist();
};




