#include "Config.h"

Config::Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist)
{
	m_DriveList = drivelist;
    m_CollimatorList = collimatorlist;
}

int Config::DownloadConfig()
{
    std::cout << "Config:Downloading config..." << std::endl;
	return 0;
}

int Config::UploadConfig()
{
    std::cout << "Config:Uploading config..." << std::endl;
	return 0;
}

int Config::SaveConfig()
{
    std::cout << "Config:Saving config..." << std::endl;
	return 0;
}


