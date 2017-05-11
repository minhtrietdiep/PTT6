#pragma once

#include <iostream>
#include <string>
#include <vector>

typedef struct Parameter {
  std::string Name;
  std::string Type;
  std::string Value;
}Parameter;
  
class ClientMessage
{
public:
  ClientMessage();
  ClientMessage(int p_MessageId, 
                std::string p_FuntionName, 
                std::string p_Sender, 
                int p_Priority,
                std::vector<Parameter> p_Parameters);
  ~ClientMessage();
  void SetMessageId(int p_MessageId);
  int GetMessageId();
  void SetFunctionName(const std::string &p_FunctionName);
  std::string GetFunctionName();
  void SetSender(const std::string &p_Sender);
  std::string GetSender();
  void SetPriority(int p_Priority);
  int GetPriority();
  void SetParams(const std::vector<Parameter> &p_Parameters);
  void AddParams(const std::vector<Parameter> &p_Parameters);
  std::vector<Parameter> GetParams();
  std::string GetString();

private:
  int m_messageId;
  std::string m_functionName;
  std::string m_sender;
  int m_priority;
  std::vector<Parameter> m_parameters;
};
