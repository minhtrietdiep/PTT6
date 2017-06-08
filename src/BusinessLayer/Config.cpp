#include "Config.h"

#include <fstream>
#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>

#include <Const.h>
#include <Logger.h>
#include <JSONUtils.h>

Config::Config(std::vector<Plate> drivelist, std::vector<Plate> collimatorlist) :
    m_DriveList(drivelist),
    m_CollimatorList(collimatorlist),
    m_Logger(VERSION, Logger::Severity::ERROR, LOG_PATH)
{
    LoadConfig(PlateList::COLLIMATORLIST);
    LoadConfig(PlateList::DRIVELIST);
}
Config::~Config() { }

std::vector<Plate> Config::GetDrivelist()
{
    return m_DriveList;
}

std::vector<Plate> Config::GetCollimatorlist()
{
    return m_CollimatorList;
}

 ErrorCode Config::SetCollimatorposition(int drive, int collimatorPosition)
{
    for (unsigned int i = 0; i < m_CollimatorList.size(); i++)
    {
        if (m_CollimatorList[i].GetID() == drive)
        {
            m_CollimatorList[i].SetCollimatorPosition(collimatorPosition);
            return ErrorCode::ERR_OK;
        }
    }
     m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Invalid drive");
    return ErrorCode::ERR_NO_ITEM;
    
}
/*
ErrorCode Config::SetFilename(PlateList plate, std::string filename)
{
    if(file.empty())
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "filename can't be empty");
        return ErrorCode::ERR_INVALID_ARG
    }
    if(plate == PlateList::DRIVELIST)
    {
        m_DriveFileNam
    }
    else if(plate == PlateList::COLLIMATORLIST)
    {

    }
    return ErrorCode::ERR_OK;
}
*/

 ErrorCode Config::LoadConfig(enum PlateList plate)
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

    FILE* fp = fopen(filename, "r"); // non-Windows use "r"
    if(!fp)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't open Config");
        return ErrorCode::ERR_FILE_OPEN;    
    }
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;

    document.ParseStream(is);
    if(document.HasParseError()) 
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Document has parse error");
        return ErrorCode::ERR_PARSE;    
    }
    
    int presetListSize = document["Plates"].Size();
    for (int i = 0; i < presetListSize; i++) 
    { 
        std::string presetName;
        const rapidjson::Value& object = document["Plates"][i].GetObject();

        int id = object["m_ID"].GetInt();
        int drivePosition = object["m_DrivePosition"].GetInt();
        int collimatorPosition = object["m_CollimatorPosition"].GetInt();
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

 ErrorCode Config::SaveConfig(enum PlateList plate)
{
    std::string jsPlateList;
    const char* filename;

    Logger logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    if(plate == PlateList::DRIVELIST)
    {
        filename = m_DriveFileName;
        jsPlateList = PlateListToJSONString(m_DriveList, plate);
    }
    else if(plate == PlateList::COLLIMATORLIST)
    {
        filename = m_CollimatorFileName;
        jsPlateList = PlateListToJSONString(m_CollimatorList, plate);
    }
    std::ofstream ofs (filename, std::ios_base::out|std::ios_base::trunc);
    
    if(!ofs.is_open())   
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't open config");
        return ErrorCode::ERR_FILE_OPEN;       
    }

    ofs << jsPlateList;

    ofs.close();
	return ErrorCode::ERR_OK;

}

