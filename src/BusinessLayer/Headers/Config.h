#ifndef CONFIG_H
#define CONFIG_H

#include "Plate.h"
#include <vector>

class Config
{
	private:
		std::vector<Plate> DriveList;
		std::vector<Plate> CollimatorList;
	
	public:
		Config();
		int DownloadConfig();
		int UploadConfig();
		int SaveConfig();
		
};

#endif
