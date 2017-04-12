#include "ClientMessage.h"

#include <sstream> 

ClientMessage::ClientMessage()
{
	
}

ClientMessage::ClientMessage(int p_MessageId, 
                             std::string p_FuntionName, 
                             std::string p_Sender, 
                             int p_Priority,
                             int p_Size,
                             std::string* p_Parameters)
{
    this->messageId = p_MessageId;
    this->functionName = p_FuntionName;
    this->sender = p_Sender;
    this->priority = p_Priority;
    this->parameters = new std::string[p_Size];
    for (int i = 0; i < p_Size; i++)
    {
        this->parameters[i] = p_Parameters[i];
    }
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

void ClientMessage::SetParams(int p_Size, std::string p_Parameters[])
{
    this->parameters = new std::string[p_Size];
    for (int i = 0; i < p_Size; i++)
    {
        this->parameters[i] = p_Parameters[i];
    }
}

std::string ClientMessage::GetParam(int p_Index)
{
    return this->parameters[p_Index];
}

std::string ClientMessage::GetString()
{
    std::stringstream ss;
    ss << this->priority;

    std::string d = "Method: ";
    d += this->functionName;
    d += "\n Priority: ";
    d += ss.str();
    d += "\n params: ";
    d += this->GetParam(0);
    d += ", ";
    d += this->GetParam(1);
    return d;
}
