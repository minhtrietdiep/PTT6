#include "Headers/Control.h"
#include <../sharedlibs/include/rapidjson/document.h>
#include <../sharedlibs/include/rapidjson/istreamwrapper.h>
#include <../sharedlibs/include/rapidjson/writer.h>
#include <../sharedlibs/include/rapidjson/stringbuffer.h>
#include <../sharedlibs/include/rapidjson/filereadstream.h>
#include <../lib/include/Const.h>
#include <fstream>
#include <vector>
#include <../lib/include/Logger.h>

    
Control::Control(std::vector<Preset> presets)
{
    
    m_Presets = presets;
   
    
}

Control::~Control()
{

}

std::vector<Preset> Control::GetPresets()
{
    std::cout << "Control:Getting presets..." << std::endl;
    return m_Presets;
}

void Control::PlateToDrive(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;
}

void Control::PlateToCollimator(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to collimator..." << std::endl;
}

void Control::CancelCurrentOperation()
{
    std::cout << "Control:Canceling current operation..." << std::endl;
}

void Control::SetPreset(int presetid)
{
    std::cout << "Control:Setting preset " << presetid << "..." << std::endl;
}

void Control::EmergencyStop()
{
    std::cout << "Control:Emergency stop..." << std::endl;
}

void Control::ContinueSystem()
{
    std::cout << "Control:Continueing system..." << std::endl;
}

void Control::ResetSystem()
{
    std::cout << "Control:Resetting system..." << std::endl;
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




/* OLD CONTOL.H
void Control::SendCommands()
{
    
}

void Control::RecieveCommands()
{
    
}
*/
