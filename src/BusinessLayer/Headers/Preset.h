#ifndef PRESET_H_
#define PRESET_H_

#include <iostream>
#include <vector>

class Preset
{
    private:
        int m_ID;
        std::vector<int> m_PlateList;

    public:
        Preset(int id,std::vector<int> PlateList);
        int GetID();
        std::vector<int> GetPlatelist();
};

#endif  //  PRESET_H_
