#include "Headers/Config.h"
#include <../sharedlibs/include/rapidjson/document.h>
#include <../sharedlibs/include/rapidjson/istreamwrapper.h>
#include <../sharedlibs/include/rapidjson/writer.h>
#include <../sharedlibs/include/rapidjson/stringbuffer.h>
#include <../sharedlibs/include/rapidjson/filereadstream.h>
#include <../lib/include/Const.h>
#include <fstream>
#include <vector>
#include <../lib/include/Logger.h>

Config::Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist)
{
	m_DriveList = drivelist;
    m_CollimatorList = collimatorlist;
}

int Config::DownloadConfig(enum PlateList plate)
{
    const char* filename;
    if(plate == PlateList::DRIVELIST)
    {
        filename = m_DriveFileName;
    }
    else if(plate == PlateList::COLLIMATORLIST)
    {
        filename = m_CollimatorFileName;
    }

    Logger logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    FILE* fp = fopen(filename, "r"); // non-Windows use "r"
    if(!fp)
    {
        logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't open logfile");
        //return ErrorCode::ERR_FILE_OPEN;    
        return -1;
    }
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;

    document.ParseStream(is);
    if(document.HasParseError()) 
    {
        logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Document has parse error");
        //return ErrorCode::PARSE_ERROR;    
        return -1;    
    }
    
    int presetListSize = document["Plates"].Size();

    for (int i = 0; i < presetListSize; i++) 
    {
        std::string presetName;
        const rapidjson::Value& object = document["Plates"][i].GetObject();
        //std::cout << "dd" << "\n";
       /* if (!object["Plates"].IsObject()) 
        {
            logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't get m_PlateIDs object");
            //return ErrorCode::PARSE_ERROR;
            return -1;
        }*/
        int id = object["m_ID"].GetInt();
        int drivePosition = object["m_DrivePosition"].GetInt();
        int collimatorPosition = object["m_ColimatorPostion"].GetInt();
        int property = object["m_Property"].GetInt();
        double thickness = object["m_Thickness"].GetDouble();

        std::cout << "ID: "<<id << "drivepos: " << drivePosition << "collpos: "<< collimatorPosition << "prop: " << property << "thickness: " << thickness << "\n";
        

        Plate newPlate(id, drivePosition, collimatorPosition, property, thickness);
        if(plate == PlateList::DRIVELIST)
        {
            m_DriveList.push_back(newPlate);
        }
        else if(plate == PlateList::COLLIMATORLIST)
        {
            m_CollimatorList.push_back(newPlate);
        }

    }

    fclose(fp);
    
    std::cout << "Control:Downloading config..." << std::endl;
    //return ErrorCode::OK;
	return 0;
}

int Config::UploadConfig(enum PlateList plate)
{
    std::cout << "Config:Uploading config..." << std::endl;
	return 0;
}

int Config::SaveConfig(enum PlateList plate)
{
    std::cout << "Config:Saving config..." << std::endl;
	return 0;
}


