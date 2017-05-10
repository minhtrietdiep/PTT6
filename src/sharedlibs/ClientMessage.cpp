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
    m_messageId = p_MessageId;
    m_functionName = p_FuntionName;
    m_sender = p_Sender;
    m_priority = p_Priority;
    m_parameters = p_Parameters;
}

ClientMessage::~ClientMessage()
{
	
}

void ClientMessage::SetMessageId(int p_MessageId)
{
    m_messageId = p_MessageId;
}

int ClientMessage::GetMessageId()
{
    return m_messageId;
}

void ClientMessage::SetFunctionName(const std::string &p_FunctionName)
{
    m_functionName = p_FunctionName;
}

std::string ClientMessage::GetFunctionName()
{
    return m_functionName;
}

void ClientMessage::SetSender(const std::string &p_Sender)
{
    m_sender = p_Sender;
}

std::string ClientMessage::GetSender()
{
    return m_sender;
}

void ClientMessage::SetPriority(int p_Priority)
{
    m_priority = p_Priority;
}

int ClientMessage::GetPriority()
{
    return m_priority;
}

void ClientMessage::SetParams(const std::vector<Parameter> &p_Parameters)
{
    for (auto p : p_Parameters) 
    {
        m_parameters.push_back(p);
    }
}

std::vector<Parameter> ClientMessage::GetParams()
{
    return m_parameters;
}

std::string ClientMessage::GetString()
{
    std::stringstream ss;
    ss << m_priority;

    auto params = m_parameters;

    std::string d = "Method: ";
    d += m_functionName;
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
