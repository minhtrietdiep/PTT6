#ifndef ClientMessage_H
#define ClientMessage_H

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
  void SetFunctionName(std::string p_FunctionName);
  std::string GetFunctionName();
  void SetSender(std::string p_Sender);
  std::string GetSender();
  void SetPriority(int p_Priority);
  int GetPriority();
  void SetParams(std::vector<Parameter> p_Parameters);
  std::vector<Parameter> GetParams();
  std::string GetString();

private:
  int messageId;
  std::string functionName;
  std::string sender;
  int priority;
  std::vector<Parameter> parameters;
};


#endif