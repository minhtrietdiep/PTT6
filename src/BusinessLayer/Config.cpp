#include "Headers/Config.h"

Config::Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist)
{
	m_DriveList = drivelist;
    m_CollimatorList = collimatorlist;
}

int Config::DownloadConfig()
{
	return 0;
}

int Config::UploadConfig()
{
	return 0;
}

int Config::SaveConfig()
{
	return 0;
}


