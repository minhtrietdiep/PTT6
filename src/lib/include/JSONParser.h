#ifndef JSONComm_H
#define JSONComm_H

#include <iostream>

#include "Error.h"
#include "ClientMessage.h"
#include <rapidjson/document.h>

//class ClientMessage;

class JSONParser
{
public:
  JSONParser();
  ~JSONParser();
  Error JsonToClientMessage(std::string src,
                            ClientMessage* dest,
                            std::string &details);
  std::string ClientMessageToJson(ClientMessage &task);

private:
  

};




#endif