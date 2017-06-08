#include <Const.h>
#include <fstream>
#include <vector>

#include "Control.h"
#include <Config.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <Const.h>
#include <JSONUtils.h>


#define COLLIMATORPOS 99

#define MAX_PLATE_ID 4
#define MIN_PLATE_ID 0

Control::Control(std::vector<Preset> presets) : m_Presets(presets),
m_Config(std::vector<Plate>(), std::vector<Plate>()),
m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH)
{
    //m_Logger = new Logger(VERSION,Logger::Severity::ERROR,LOG_PATH);
    LoadPresets();
}

Control::~Control()
{
    //delete m_Logger;
}

std::vector<Preset> Control::GetPresets()
{
    return m_Presets;
}

 ErrorCode Control::PlateToDrive(int plateid)
{
    if (plateid < MIN_PLATE_ID && plateid > MAX_PLATE_ID)
    {
         m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Plate to drive : Invalid PlateID ");
         return ErrorCode::ERR_INVALID_ARG;
    }
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
        Move move(plateid,driveID);
        if (m_Order.NewMove(move) != ErrorCode::ERR_OK)
            return ErrorCode::ERR_UNKNOWN;
  
    } 
    else
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Invalid driveID");
        return ErrorCode::ERR_INVALID_ARG;
    }

    return ErrorCode::ERR_OK;

}

 ErrorCode Control::PlateToCollimator(int plateid)
{
    if (plateid < MIN_PLATE_ID && plateid > MAX_PLATE_ID)
    {
         m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Plate to drive : Invalid PlateID ");
         return ErrorCode::ERR_INVALID_ARG;
    }
    Move move(plateid,COLLIMATORPOS);
    if (m_Order.NewMove(move) != ErrorCode::ERR_OK)
        return ErrorCode::ERR_UNKNOWN;  
    return ErrorCode::ERR_OK;
}

 ErrorCode Control::CancelCurrentOperation()
{
    if (m_Order.Stop() != ErrorCode::ERR_OK)
        return ErrorCode::ERR_UNKNOWN;
    return ErrorCode::ERR_OK;
}

 ErrorCode Control::SetPreset(int presetid)
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
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "no preset found");
        return ErrorCode::ERR_UNKNOWN;

    }
    return ErrorCode::ERR_OK;
}

 ErrorCode Control::EmergencyStop()
{
    m_Order.Stop();
    std::cout << "Control:Emergency stop..." << std::endl;
    return ErrorCode::ERR_OK;
}

 ErrorCode Control::ContinueSystem()
{
    m_Order.Start();
    std::cout << "Control:Continueing system..." << std::endl;
    return ErrorCode::ERR_OK;
}

 ErrorCode Control::ResetSystem() 
{
    if (m_Order.Stop() != ErrorCode::ERR_OK)
        return ErrorCode::ERR_UNKNOWN;
    if (m_Order.Reset() != ErrorCode::ERR_OK)
        return ErrorCode::ERR_UNKNOWN;


    std::vector<Plate> collimatorList = m_Config.GetCollimatorlist();
    for(int i = 0; i < collimatorList.size(); i++)
    {
            for (int j = collimatorList.size(); j <= 0; j--)
            {
                if(collimatorList[i].GetCollimatorPosition() == j)
                {
                   PlateToDrive(collimatorList[i].GetID()); 
                }
            }
     
    }
    return ErrorCode::ERR_OK;

}
 ErrorCode Control::StartSystem()
{

    std::vector<Move> moves = m_Order.GetMoves(); 
    if (moves.size() < 1)
    {
        return ErrorCode::ERR_NO_ITEM;
    }
    int ID = moves[0].GetPlateID();
    int Destination = moves[0].GetDestination();

    if (m_Order.Start() == ErrorCode::ERR_OK)
    {
        if (Destination == COLLIMATORPOS)
        {
            int position = 0;
            std::vector<Plate> platelist = m_Config.GetCollimatorlist();
            for (int i = 0; i < platelist.size(); i ++)
            {
                if (platelist[i].GetCollimatorPosition() > position)
                    position = platelist[i].GetCollimatorPosition();
            }
            position ++;
            if (m_Config.SetCollimatorposition(ID,position) != ErrorCode::ERR_OK)
                return ErrorCode::ERR_UNKNOWN;

        } else
        {
            if (m_Config.SetCollimatorposition(ID,Destination) != ErrorCode::ERR_OK)
                return ErrorCode::ERR_UNKNOWN;
        }
        
        if (m_Config.SaveConfig(PlateList::COLLIMATORLIST) != ErrorCode::ERR_OK)
            return ErrorCode::ERR_UNKNOWN;
        if (m_Config.SaveConfig(PlateList::DRIVELIST) != ErrorCode::ERR_OK)
            return ErrorCode::ERR_UNKNOWN;
        return ErrorCode::ERR_OK;
    } 
    m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "cannot start order");
    m_Order.Stop();
    m_Order.Reset();
    return ErrorCode::ERR_UNKNOWN;
   
}


std::string Control::UploadPresets()
{
    return PresetToJSONString(m_Presets);
}

std::string Control::UploadDriveState()
{
    return PlateListToJSONString(m_Config.GetDrivelist(),PlateList::DRIVELIST);
}
std::string Control::UploadCollimatorState()
{
    return PlateListToJSONString(m_Config.GetCollimatorlist(), PlateList::COLLIMATORLIST);
}

ErrorCode Control::LoadPresets()
{

    FILE* fp = fopen(m_FileName, "r"); // non-Windows use "r"
    if(!fp)
    {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't open logfile");
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
    
    int presetListSize = document["PresetList"].Size();

    for (int i = 0; i < presetListSize; i++) 
    {
        std::string presetName;
        const rapidjson::Value& object = document["PresetList"][i].GetObject();
        if(!object.IsObject()) 
        {
            m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't get PresetList object");
            return ErrorCode::ERR_PARSE;    
        }
        int id = object["m_PresetID"].GetInt();

        if (!object["m_PlateIDs"].IsArray()) 
        {
            m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Coudn't get m_PlateIDs object");
            return ErrorCode::ERR_PARSE;
        }
        presetName = object["m_PresetName"].GetString();

        std::vector<int> plateList;
        for (int j = 0; j < object["m_PlateIDs"].Size(); j++) 
        {
            plateList.push_back(object["m_PlateIDs"][j]["ID"].GetInt());

        }
        m_Presets.push_back(Preset(id, presetName, plateList));
    }

    fclose(fp);
    
    return ErrorCode::ERR_OK;
}

ErrorCode Control::DownloadLog(int logfilenumber)
{
    std::cout << "Control:Downloading log " << logfilenumber << "..." << std::endl;
}

ErrorCode Control::SetupHardware()
{
    return m_Order.SetupHardware();
}