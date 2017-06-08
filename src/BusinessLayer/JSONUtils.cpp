#include "JSONUtils.h"

#include <Logger.h>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

std::string PresetToJSONString(std::vector<Preset> presets)
{
    rapidjson::Document jsonObject;
    rapidjson::Document::AllocatorType& allocator = jsonObject.GetAllocator();
    
    jsonObject.SetObject();
    
    jsonObject.AddMember("Name",rapidjson::Value("m_Presets", allocator) , allocator);

    rapidjson::Value presetList(rapidjson::kArrayType);

    for (auto preset : presets) 
    {
        rapidjson::Value jsPreset;
        jsPreset.SetObject();

        rapidjson::Value jsPresetID;
        rapidjson::Value jsPresetName;
        rapidjson::Value jsPlateIDs(rapidjson::kArrayType);

        jsPresetID.SetInt(preset.GetID());
        jsPresetName.SetString(preset.GetPresetName().c_str(), allocator);

        for (auto plate : preset.GetPlatelist()) 
        {
            rapidjson::Value jsPlateID;
            jsPlateID.SetObject();
            rapidjson::Value jsPlate;
            jsPlate.SetInt(plate);
            jsPlateID.AddMember("ID", jsPlate, allocator);
            jsPlateIDs.PushBack(jsPlateID, allocator);
        }

        jsPreset.AddMember("m_PresetID", jsPresetID, allocator);
        jsPreset.AddMember("m_PresetName", jsPresetName, allocator);
        jsPreset.AddMember("m_PlateIDs", jsPlateIDs, allocator);

        presetList.PushBack(jsPreset, allocator);
    }

    jsonObject.AddMember("PresetList", presetList, allocator);

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    return std::string(buffer.GetString());
}



std::string PlateListToJSONString(std::vector<Plate> plates, PlateList type)
{
    rapidjson::Document jsonObject;
    rapidjson::Document::AllocatorType& allocator = jsonObject.GetAllocator();
    
    jsonObject.SetObject();

    std::string name;

    switch(type)
    {
        case PlateList::DRIVELIST:
            name = "m_DriveList";
            break;
        case PlateList::COLLIMATORLIST:
            name = "m_CollimatorList";
            break;
        default: {
            Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
            logger.Write(
                Logger::Severity::ERROR,
                __PRETTY_FUNCTION__,
                "Invalid PlateList type");
            return "";
        }
    }

    jsonObject.AddMember("Name",rapidjson::Value(name.c_str(), allocator) , allocator);

    rapidjson::Value plateList(rapidjson::kArrayType);

    for (auto plate : plates) 
    {
        rapidjson::Value jsPlate;
        jsPlate.SetObject();

        rapidjson::Value jsPlateID;
        rapidjson::Value jsDrivePosition;
        rapidjson::Value jsCollimatorPosition;
        rapidjson::Value jsProperty;
        rapidjson::Value jsThickness;

        jsPlateID.SetInt(plate.GetID());
        jsDrivePosition.SetInt(plate.GetDrivePosition());
        jsCollimatorPosition.SetInt(plate.GetCollimatorPosition());
        jsProperty.SetString(plate.GetProperties().c_str(), allocator);
        jsThickness.SetDouble(plate.GetThickness());

        jsPlate.AddMember("m_ID", jsPlateID, allocator);
        jsPlate.AddMember("m_DrivePosition", jsDrivePosition, allocator);
        jsPlate.AddMember("m_CollimatorPosition", jsCollimatorPosition, allocator);
        jsPlate.AddMember("m_Property", jsProperty, allocator);
        jsPlate.AddMember("m_Thickness", jsThickness, allocator);

        plateList.PushBack(jsPlate, allocator);
    }

    jsonObject.AddMember("Plates", plateList, allocator);

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    return std::string(buffer.GetString());
}

