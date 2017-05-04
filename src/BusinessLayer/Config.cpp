#include "Headers/Config.h"

Config::Config()
{

    Plate *plate0 = new Plate(0,0,1,2,5);
    Plate *plate1 = new Plate(0,0,1,2,6);
    Plate *plate2 = new Plate(0,0,1,2,7);
    Plate *plate3 = new Plate(0,0,1,2,8);
    Plate *plate4 = new Plate(0,0,1,2,9);
    Plate *plate5 = new Plate(0,0,1,2,10);

    std::vector<Plate> *drivelist = new std::vector<Plate>();
    std::vector<Plate> *collimatorlist = new std::vector<Plate>();

    drivelist->push_back(*plate0);
    drivelist->push_back(*plate1);
    drivelist->push_back(*plate2);

    collimatorlist->push_back(*plate3);
    collimatorlist->push_back(*plate4);
    collimatorlist->push_back(*plate5);

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


