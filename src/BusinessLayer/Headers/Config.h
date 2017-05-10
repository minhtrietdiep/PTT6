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
		Config();
		~Config();
		std::vector<Plate> GetDrivelist();
		std::vector<Plate> GetCollimatorlist();
		int DownloadConfig();
		int UploadConfig();
		int SaveConfig();
		
};

#endif
