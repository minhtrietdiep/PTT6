
#include <sstream>

#include "Error.h"
#include "JSONParser.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"


JSONParser::JSONParser() { }


JSONParser::~JSONParser() { }


Error JSONParser::JsonToClientMessage(std::string src, ClientMessage* dest)
{
    if(src == "" || dest == NULL){  return Error::VAR_NULL;  } 
    Error ret = Error::NONE;
    rapidjson::Document jsonObject;
    jsonObject.Parse(src.c_str());
    if(jsonObject.HasParseError() || !jsonObject["function"].IsObject()){  ret = Error::PARSE_ERROR;  }
    else
    {
        const rapidjson::Value& function = jsonObject["function"].GetObject();
        if(!function["priority"].IsInt()){  ret = Error::PARSE_ERROR;    }
        else if(!function["sender"].IsString()){  ret = Error::PARSE_ERROR;    }
        else if(!function["functionName"].IsString()){  ret = Error::PARSE_ERROR;    }
        else if(!function["parameters"].IsArray()){  ret = Error::PARSE_ERROR;    }
        if(ret == Error::NONE)
        {
            dest->SetPriority(function["priority"].GetInt());
            dest->SetSender(function["sender"].GetString());
            dest->SetFunctionName(function["functionName"].GetString());
            int arraySize = function["parameters"].Size();
            std::string parameters[10];
            for (int i = 0; i < arraySize; i++) 
            {
                parameters[i]=function["parameters"][i]["value"].GetString();
            } 
            dest->SetParams(arraySize, parameters);
        }
    }
    return ret;
}


std::string ClientMessageToJson(ClientMessage task)
{
    rapidjson::Document jsonObject;
	rapidjson::Value functionObj;
    rapidjson::Document::AllocatorType& allocator = jsonObject.GetAllocator();
    functionObj.SetObject();
    functionObj.AddMember("priority",task.GetPriority(),jsonObject.GetAllocator());
    functionObj.AddMember("sender", rapidjson::Value(task.GetSender().c_str(), allocator).Move(),allocator);
    functionObj.AddMember("functionName",rapidjson::Value(task.GetFunctionName().c_str(),allocator),allocator);
    functionObj.AddMember("returnType",rapidjson::Value("response",allocator),allocator);
    
    rapidjson::Value parameters(rapidjson::kArrayType);
    for(int i=0;i<2;i++)
    {
        rapidjson::Value param;
        param.SetObject();
        param.AddMember("value",rapidjson::Value(task.GetParam(i).c_str(),allocator),jsonObject.GetAllocator());
        //param.AddMember("dataType",task.GetPriority(),jsonObject.GetAllocator());
        //param.AddMember("value",task.GetPriority(),jsonObject.GetAllocator());
        parameters.PushBack(param, allocator);
    }
    functionObj.AddMember("parameters",parameters,allocator);
    jsonObject.SetObject();
    jsonObject.AddMember("function", functionObj, jsonObject.GetAllocator());

    rapidjson::StringBuffer buffer;

    buffer.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    return strdup( buffer.GetString() );
}



