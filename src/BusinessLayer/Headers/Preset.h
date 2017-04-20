#ifndef PRESET_H_
#define PRESET_H_

#include <iostream>
#include <vector>
#include "Plate.h"

class Preset
{
	private:
        int m_ID;
        std::vector<Plate> m_PlateList;

	public:
		Preset(int id,std::vector<Plate> platelist);
        int GetID();
        std::vector<Plate> GetPlatelist();
};

#endif  //  PRESET_H_
