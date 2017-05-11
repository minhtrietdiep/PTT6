
#include "Control.h"
#include "document.h"
#include "istreamwrapper.h"
#include "writer.h"
#include "stringbuffer.h"
#include "filereadstream.h"
#include "ErrorCode.h"
#include "Config.h"
#include "Logger.h"
#include <Const.h>
#include <fstream>
#include <vector>

#define COLLIMATORPOS 99

Control::Control(std::vector<Preset> presets) : m_Presets(presets),
m_Config(std::vector<Plate>(), std::vector<Plate>())
{
    //TODO: VERVANGEN ALS HUBERT UITLEZEN GEREED HEEFT
    /*std::vector<Preset> presets = std::vector<Preset>();
    std::vector<int> presetlist;
    presetlist.push_back(10);
    presetlist.push_back(25);
    presetlist.push_back(51);
    Preset p0 = Preset(0,presetlist);
    presets.push_back(p0);
    presetlist.clear();
    presetlist.push_back(15);
    presetlist.push_back(20);
    presetlist.push_back(16);
    Preset p1 = Preset(1,presetlist);
    presets.push_back(p1);*/
    // driveList;
    //std::vector<Plate> collimatorList;
    // m_Order = Order();
    //m_Config = Config(driveList, collimatorList);
    //m_Presets = ;
    
    
}

Control::~Control()
{

}

std::vector<Preset> Control::GetPresets()
{
    std::cout << "Control:Getting presets..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(0));
    return m_Presets;
}

void Control::PlateToDrive(int plateid)
{
    int driveID = -1;
    std::vector<Plate> drivelist = m_Config.GetDrivelist();
    std::vector<Plate> collimatorList = m_Config.GetCollimatorlist();

    for(int i = 0; i < collimatorList.size(); i++)
    {
        if (collimatorList[i].GetID() == plateid)
        {
            driveID = collimatorList[i].GetDrivePosition();
            break;
        }
    }
    if (driveID < 0)
    {
        for(int i = 0; i < drivelist.size(); i++)
        {
            if (drivelist[i].GetID() == plateid)
            {
                driveID = drivelist[i].GetDrivePosition();
                break;
            }
        }
    }

    if(driveID >= 0)
    {
        Move move(driveID,plateid);
        m_Order.NewMove(move);
        std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;    
    } 
    else
    {
        std::cout << "Drive niet gevonden!" << std::endl;  
    }

}

void Control::PlateToCollimator(int plateid)
{
    Move move(plateid,COLLIMATORPOS);
    m_Order.NewMove(move);
    std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;
}

void Control::CancelCurrentOperation()
{
    m_Order.Stop();
    std::cout << "Control:Canceling current operation..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Control::SetPreset(int presetid)
{
    int status = -1;
    std::vector<int> presetlist;

    ResetSystem();

    for (auto preset : m_Presets) {
        if (preset.GetID() == presetid) {
            status = 1;

            presetlist = preset.GetPlatelist();
            for(int j = 0; j < presetlist.size(); j++)
            {
                PlateToCollimator(presetlist[j]);
            }
            break;
        }
    }

    if (status < 0)
    {
        std::cout << "ERROR -> Preset not found." << std::endl;

    }
    std::cout << "Control:Setting preset " << presetid << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void Control::EmergencyStop()
{
    m_Order.Stop();
    std::cout << "Control:Emergency stop..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(0));
}

void Control::ContinueSystem()
{
    m_Order.Start();
    std::cout << "Control:Continueing system..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Control::ResetSystem()
{
    std::cout << "Control:Resetting system..." << std::endl;
    m_Order.Stop();
    m_Order.Reset();


    std::vector<Plate> collimatorList = m_Config.GetCollimatorlist();
    for(int i = 0; i < collimatorList.size(); i++)
    {
      PlateToDrive(collimatorList[i].GetID());
    }


}

ErrorCode Control::UploadConfig()
{
    std::cout << "Control:Uploading config..." << std::endl;
}

ErrorCode Control::DownloadConfig()
{
    
    Logger logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    FILE* fp = fopen(m_FileName, "r"); // non-Windows use "r"
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
        return ErrorCode::PARSE_ERROR;    
    }
    
    int presetListSize = document["PresetList"].Size();

    for (int i = 0; i < presetListSize; i++) 
    {
        std::string presetName;
        const rapidjson::Value& object = document["PresetList"][i].GetObject();
        if(!object.IsObject()) 
        {
            logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't get PresetList object");
            return ErrorCode::PARSE_ERROR;    
        }
        int id = object["m_PresetID"].GetInt();
       // std::cout << object["m_PresetID"].GetInt() << "\n";
        if (!object["m_PlateIDs"].IsArray()) 
        {
            logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't get m_PlateIDs object");
            return ErrorCode::PARSE_ERROR;
        }
        presetName = object["m_PresetName"].GetString();
        //std::cout << object["m_PresetName"].GetString() << "\n";
        std::vector<int> plateList;
        for (int j = 0; j < object["m_PlateIDs"].Size(); j++) 
        {
            //std::cout << object["m_PlateIDs"][j]["ID"].GetInt() << "\n";
            plateList.push_back(object["m_PlateIDs"][j]["ID"].GetInt());

        }
        m_Presets.push_back(Preset(id, presetName, plateList));
    }

    fclose(fp);
    
    std::cout << "Control:Downloading config..." << std::endl;

    return ErrorCode::OK;
}

ErrorCode Control::DownloadLog(int logfilenumber)
{
    std::cout << "Control:Downloading log " << logfilenumber << "..." << std::endl;
}