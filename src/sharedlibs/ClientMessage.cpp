#include "ClientMessage.h"

#include <sstream> 

ClientMessage::ClientMessage()
{
	
}

ClientMessage::ClientMessage(int p_MessageId, 
                             std::string p_FuntionName, 
                             std::string p_Sender, 
                             int p_Priority,
                             std::vector<Parameter> p_Parameters)
{
    this->messageId = p_MessageId;
    this->functionName = p_FuntionName;
    this->sender = p_Sender;
    this->priority = p_Priority;
    parameters = p_Parameters;
}

ClientMessage::~ClientMessage()
{
	
}

void ClientMessage::SetMessageId(int p_MessageId)
{
    this->messageId = p_MessageId;
}

int ClientMessage::GetMessageId()
{
    return this->messageId;
}

void ClientMessage::SetFunctionName(std::string p_FunctionName)
{
    this->functionName = p_FunctionName;
}

std::string ClientMessage::GetFunctionName()
{
    return this->functionName;
}

void ClientMessage::SetSender(std::string p_Sender)
{
    this->sender = p_Sender;
}

std::string ClientMessage::GetSender()
{
    return this->sender;
}

void ClientMessage::SetPriority(int p_Priority)
{
    this->priority = p_Priority;
}

int ClientMessage::GetPriority()
{
    return this->priority;
}

void ClientMessage::SetParams(std::vector<Parameter> p_Parameters)
{
    for (auto p : p_Parameters) {
        parameters.push_back(p);
    }
}

std::vector<Parameter> ClientMessage::GetParams()
{
    return parameters;
}

std::string ClientMessage::GetString()
{
    std::stringstream ss;
    ss << this->priority;

    auto params = this->GetParams();

    std::string d = "Method: ";
    d += this->functionName;
    d += "\n Priority: ";
    d += ss.str();
    d += "\n ParamCount: ";
    d += params.size();
    d += "\n ";
    for (auto param : params) {
        d += "\nName: " + param.Name;
        d += "\nType: " + param.Type;
        d += "\nVal : " + param.Value;
    }
    return d;
}
