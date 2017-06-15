#pragma once

#include <vector>
#include <Const.h>
#include <Logger.h>

#include <Error.h>
#include <Plate.h>
#include <PlateList.h>

class Config
{

    private:
        std::vector<Plate> m_DriveList;
        std::vector<Plate> m_CollimatorList;
        const char* m_DriveFileName = "Config/DriveList.json";
        const char* m_CollimatorFileName = "Config/CollimatorList.json";
        Logger m_Logger;
    
    public:
        Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist);
        ~Config();
        ErrorCode SetCollimatorposition(int drive, int collimatorPosition);
        ErrorCode SetDriveposition(int drive, int DrivePosition);

        //ErrorCode SetFilename(PlateList plate, std::string filename);
        std::vector<Plate> GetDrivelist();
        std::vector<Plate> GetCollimatorlist();
        ErrorCode LoadConfig(PlateList plate);
        ErrorCode SaveConfig(PlateList plate);


        
};
