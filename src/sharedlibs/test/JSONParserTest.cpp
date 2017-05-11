#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "../ClientMessage.h"
#include "../JSONParser.h"

#define MESSAGE_EMPTY ""
#define MESSAGE_VALID  "{\"Function\":{\"Priority\":\"1\",\"Sender\":\"id\",\"FunctionName\":\"GETSYSTEMLOG\",\"ReturnType\":\"Response\",\"Parameters\":[{\"Name\":\"param_1\",\"DataType\":\"int\",\"Value\":\"123\"},{\"Name\":\"param_2\",\"DataType\":\"string\",\"Value\":\"Hello World\"}]}}"                   
#define MESSAGE_MISSGING_MEMBER  "{\"Function\":   {    \"Sender\": \"id\", \"FunctionName\": \"GETSYSTEMLOG\", \"ReturnType\": \"int\",  \"Parameters\":  [  {  \"Name\": \"param_1\",  \"DataType\": \"int\",  \"Value\": \"123\" },  { \"Name\": \"param_2\",   \"DataType\": \"string\",  \"Value\":\"Hello World\"  } ] }}"                   


TEST(JSONParser_test, JsonMessage_empty) 
{
    JSONParser parser;
    ClientMessage cm;
    std::string details;
    Error res = parser.JsonToClientMessage(MESSAGE_EMPTY, &cm, details);
    
    EXPECT_EQ(res, Error::VAR_NULL);
    EXPECT_EQ(details, "Invalid source");
}


TEST(JSONParser_test, JsonMessage_MissingMember) 
{
    JSONParser parser;
    ClientMessage cm;
    std::string details;
    Error res = parser.JsonToClientMessage(MESSAGE_MISSGING_MEMBER, &cm, details);
    
    EXPECT_EQ(res, Error::PARSE_ERROR);
    EXPECT_EQ(details, "\"Function\" misses or has corrupted members");
}


TEST(JSONParser_test, JsonToClientMessage_valid) 
{
    JSONParser parser;
    ClientMessage cm;
    std::string details;
    Error res = parser.JsonToClientMessage(MESSAGE_VALID, &cm, details);
    
    EXPECT_EQ(res, Error::NONE);
    EXPECT_EQ(details, "");
}


TEST(JSONParser_test, JsonToClientMessage) 
{
    JSONParser parser;
    ClientMessage cm;
    std::string details;
    parser.JsonToClientMessage(MESSAGE_VALID, &cm, details);
    
    EXPECT_EQ(cm.GetFunctionName(), "GETSYSTEMLOG");
    EXPECT_EQ(cm.GetSender(), "id");
    EXPECT_EQ(cm.GetPriority(), 1);
}


TEST(JSONParser_test, JsonToClientMessageRewind) 
{
    JSONParser parser;
    ClientMessage cm;
    std::string details;
    parser.JsonToClientMessage(MESSAGE_VALID, &cm, details);
    std::string res = parser.ClientMessageToJson(cm);
    
    EXPECT_EQ(res, MESSAGE_VALID);
}


TEST(JSONParser_test, ClientMessageToJson) 
{
    JSONParser parser;
    
    std::string functionName = "GETSYSTEMLOG";
    std::string ipAddress = "id";
    int priority = 1;
    std::vector<Parameter> params = {};
    Parameter param1;
    param1.Name = "param_1";
    param1.Type = "int";
    param1.Value = "123";
    params.push_back(param1);
    Parameter param2;
    param2.Name = "param_2";
    param2.Type = "string";
    param2.Value = "Hello World";
    params.push_back(param2);
    ClientMessage cm (  0, 
                        functionName, 
                        ipAddress, 
                        priority,
                        params);
    
    std::string res = parser.ClientMessageToJson(cm);
                        
    EXPECT_EQ(res, MESSAGE_VALID);
}


TEST(JSONParser_test, ClientMessageToJsonRewind) 
{
    JSONParser parser;
    
    std::string functionName = "GETSYSTEMLOG";
    std::string ipAddress = "id";
    int priority = 1;
    std::vector<Parameter> params = {};
    Parameter param1;
    param1.Name = "param_1";
    param1.Type = "int";
    param1.Value = "123";
    params.push_back(param1);
    Parameter param2;
    param2.Name = "param_2";
    param2.Type = "string";
    param2.Value = "Hello World";
    params.push_back(param2);
    ClientMessage cm (  0, 
                        functionName, 
                        ipAddress, 
                        priority,
                        params);
    
    std::string JSONMessage = parser.ClientMessageToJson(cm);
                        
    ClientMessage cm2;
    std::string details;
    parser.JsonToClientMessage(JSONMessage, &cm2, details);
    
    EXPECT_EQ(cm.GetString(), cm2.GetString());
    EXPECT_EQ(cm.GetFunctionName(), cm2.GetFunctionName());
    EXPECT_EQ(cm.GetSender(), cm2.GetSender());
    EXPECT_EQ(cm.GetPriority(), cm2.GetPriority());
}
