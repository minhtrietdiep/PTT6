
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
    if(jsonObject.HasParseError()) {
        details = "Can't parse string";
        return Error::PARSE_ERROR;
    }
    if (!jsonObject.HasMember("Function")) {
        details = "JSON doesn't contain \"Function\" as root";
        return Error::PARSE_ERROR;
    }
    if(!jsonObject["Function"].IsObject()) {
        details = "\"Function\" is not an object";
        return Error::PARSE_ERROR;
    }
    const rapidjson::Value& function = jsonObject["Function"].GetObject();

    if (!function.HasMember("Priority") ||
        !function.HasMember("Sender") ||
        !function.HasMember("FunctionName") ||
        !function.HasMember("ReturnType") ||
        !function.HasMember("Parameters")) {
        details = "\"Function\" misses or has corrupted members";
        return Error::PARSE_ERROR;
    }

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
    std::vector<Parameter> parameters;
    for (int i = 0; i < arraySize; i++) 
    {
        std::string name = function["Parameters"][i]["Name"].GetString();;
        std::string type = function["Parameters"][i]["DataType"].GetString();;
        std::string value = function["Parameters"][i]["Value"].GetString();;
        Parameter p;
        p = { name, type, value };
        parameters.push_back(p);
    }
    dest->SetParams(parameters);
    return ret;
}


std::string JSONParser::ClientMessageToJson(ClientMessage &task)
{
    rapidjson::Document jsonObject;
	rapidjson::Value functionObj;
    rapidjson::Document::AllocatorType& allocator = jsonObject.GetAllocator();
    functionObj.SetObject();
    functionObj.AddMember("Priority",rapidjson::Value(std::to_string(task.GetPriority()).c_str(), allocator),allocator);
    functionObj.AddMember("Sender", rapidjson::Value(task.GetSender().c_str(), allocator).Move(),allocator);
    functionObj.AddMember("FunctionName",rapidjson::Value(task.GetFunctionName().c_str(),allocator),allocator);
    functionObj.AddMember("ReturnType",rapidjson::Value("Response",allocator),allocator);
    
    rapidjson::Value parameters(rapidjson::kArrayType);
    std::vector<Parameter> taskParams = task.GetParams();
    for(auto taskParam : taskParams)
    {
        rapidjson::Value param;
        // wtf rapidjson???
        rapidjson::Value jsParamName;
        rapidjson::Value jsParamType;
        rapidjson::Value jsParamValue;

        jsParamName.SetString(taskParam.Name.c_str(), allocator);
        jsParamType.SetString(taskParam.Type.c_str(), allocator);
        jsParamValue.SetString(taskParam.Value.c_str(), allocator);

        param.SetObject();
        param.AddMember("Name", jsParamName, allocator);
        param.AddMember("DataType", jsParamType, allocator);
        param.AddMember("Value", jsParamValue, allocator);
        parameters.PushBack(param, allocator);
    }
    functionObj.AddMember("Parameters",parameters,allocator);
    jsonObject.SetObject();
    jsonObject.AddMember("Function", functionObj, allocator);

    rapidjson::StringBuffer buffer;

    buffer.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    return std::string( buffer.GetString() );
}
