#include "document.h"
#include "istreamwrapper.h"
#include "writer.h"
#include "stringbuffer.h"
#include "filereadstream.h"
#include "Const.h"
#include "Logger.h"
#include "Config.h"
#include <fstream>
#include <vector>



Config::Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist)
{
    m_DriveList = drivelist;
    m_CollimatorList = collimatorlist;
    DownloadConfig(PlateList::COLLIMATORLIST);
    DownloadConfig(PlateList::DRIVELIST);

}
Config::~Config()
{

}

std::vector<Plate> Config::GetDrivelist()
{
    return m_DriveList;
}

std::vector<Plate> Config::GetCollimatorlist()
{
    return m_CollimatorList;
}

enum ErrorCode Config::DownloadConfig(enum PlateList plate)
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
        return ErrorCode::ERR_FILE_OPEN;    
    }
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;

    document.ParseStream(is);
    if(document.HasParseError()) 
    {
        logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Document has parse error");
        return ErrorCode::ERR_PARSE;    
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
        std::string property = object["m_Property"].GetString();
        double thickness = object["m_Thickness"].GetDouble();
       
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
    return ErrorCode::ERR_OK;
}

enum ErrorCode Config::UploadConfig(enum PlateList plate)
{
    std::cout << "Config:Uploading config..." << std::endl;
	return ErrorCode::ERR_OK;

}

enum ErrorCode Config::SaveConfig(enum PlateList plate)
{
    std::cout << "Config:Saving config..." << std::endl;
	return ErrorCode::ERR_OK;

}


