#ifndef CONFIG_H
#define CONFIG_H

#include "Plate.h"
#include <vector>

class Config
{
	private:
		std::vector<Plate> m_DriveList;
		std::vector<Plate> m_CollimatorList;
	
	public:
		Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist);
		int DownloadConfig();
		int UploadConfig();
		int SaveConfig();
		
};

#endif
