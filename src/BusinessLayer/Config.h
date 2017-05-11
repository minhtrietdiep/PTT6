#ifndef CONFIG_H
#define CONFIG_H

#include <Error.h>
#include "Plate.h"
#include <vector>


enum class PlateList
{    
    DRIVELIST,
    COLLIMATORLIST,
    Size // This is just a helper to make arrays.
};

class Config
{

	private:
		std::vector<Plate> m_DriveList;
		std::vector<Plate> m_CollimatorList;
		const char* m_DriveFileName = "Config/DriveList.json";
		const char* m_CollimatorFileName = "Config/CollimatorList.json";
	
	public:
		Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist);
		~Config();
		std::vector<Plate> GetDrivelist();
		std::vector<Plate> GetCollimatorlist();
		int DownloadConfig(enum PlateList plate);
		int UploadConfig(enum PlateList plate);
		int SaveConfig(enum PlateList plate);
		
};

#endif
