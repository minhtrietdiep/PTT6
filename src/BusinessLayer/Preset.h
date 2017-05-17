#pragma once

#include "Plate.h"

class Preset {
    private:
        int m_ID;
        std::string m_PresetName;
        std::vector<int> m_PlateList;

    public:
        Preset(int id, std::string presetName, std::vector<int> plateList);
        int GetID();
        std::string GetPresetName();
        std::vector<int> GetPlatelist();
};




