
#include <sstream>

#include "Error.h"
#include "JSONParser.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"


JSONParser::JSONParser() { }


JSONParser::~JSONParser() { }


Error JSONParser::JsonToClientMessage(std::string src, ClientMessage* dest, std::string &details) {
    if(src == "" || dest == NULL) {
        details = "Invalid source";
        return Error::VAR_NULL;
    } 
    Error ret = Error::NONE;
    rapidjson::Document jsonObject;
    jsonObject.Parse(src.c_str());
    if(jsonObject.HasParseError() || !jsonObject["Function"].IsObject()) {
        details = "Can't parse root";
        return Error::PARSE_ERROR;
    }
    const rapidjson::Value& function = jsonObject["Function"].GetObject();
    if(!function["Priority"].IsString()) {
        details = "Priority is not string";
        return Error::PARSE_ERROR;
    }
    else if(!function["Sender"].IsString()) {
        details = "Sender is not string";
        return Error::PARSE_ERROR;
    }
    else if(!function["FunctionName"].IsString()) {
        details = "FunctionName is not string";
        return Error::PARSE_ERROR;
    }
    else if(!function["Parameters"].IsArray()) {
        details = "Parameters is not array";
        return Error::PARSE_ERROR;    
    }

    dest->SetPriority(std::stoi(function["Priority"].GetString()));
    dest->SetSender(function["Sender"].GetString());
    dest->SetFunctionName(function["FunctionName"].GetString());
    int arraySize = function["Parameters"].Size();
    std::string parameters[10];
    for (int i = 0; i < arraySize; i++) 
    {
        parameters[i]=function["Parameters"][i]["Value"].GetString();
    } 
    dest->SetParams(arraySize, parameters);
    return ret;
}


std::string ClientMessageToJson(ClientMessage task)
{
    rapidjson::Document jsonObject;
	rapidjson::Value functionObj;
    rapidjson::Document::AllocatorType& allocator = jsonObject.GetAllocator();
    functionObj.SetObject();
    functionObj.AddMember("Priority",task.GetPriority(),jsonObject.GetAllocator());
    functionObj.AddMember("Sender", rapidjson::Value(task.GetSender().c_str(), allocator).Move(),allocator);
    functionObj.AddMember("FunctionName",rapidjson::Value(task.GetFunctionName().c_str(),allocator),allocator);
    functionObj.AddMember("ReturnType",rapidjson::Value("Response",allocator),allocator);
    
    rapidjson::Value parameters(rapidjson::kArrayType);
    for(int i=0;i<2;i++)
    {
        rapidjson::Value param;
        param.SetObject();
        param.AddMember("Value",rapidjson::Value(task.GetParam(i).c_str(),allocator),jsonObject.GetAllocator());
        //param.AddMember("dataType",task.GetPriority(),jsonObject.GetAllocator());
        //param.AddMember("value",task.GetPriority(),jsonObject.GetAllocator());
        parameters.PushBack(param, allocator);
    }
    functionObj.AddMember("Parameters",parameters,allocator);
    jsonObject.SetObject();
    jsonObject.AddMember("Function", functionObj, jsonObject.GetAllocator());

    rapidjson::StringBuffer buffer;

    buffer.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    return strdup( buffer.GetString() );
}

