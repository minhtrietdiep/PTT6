#pragma once

#include <iostream>

#include "JSONError.h"
#include "ClientMessage.h"
#include <rapidjson/document.h>

//class ClientMessage;

class JSONParser
{
public:
  JSONParser();
  ~JSONParser();
  JSONError JsonToClientMessage(const std::string &src,
                            ClientMessage* dest,
                            std::string &details);
  std::string ClientMessageToJson(ClientMessage &task);

private:
  
};
