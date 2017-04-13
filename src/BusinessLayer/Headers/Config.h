#ifndef CONFIG_H
#define CONFIG_H

#include "Plate.h"
#include <vector>

class Config
{
	private:
		std::vector<Plate> DriveList;
	
	public:
		Config();
		
};

#endif
