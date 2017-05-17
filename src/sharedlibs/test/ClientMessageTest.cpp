#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "../ClientMessage.h"

TEST(ClientMessage_test, Constructor) 
{
    int messageId = 0;
    std::string functionName = "TestFunction";
    std::string ipAddress = "127.0.0.1";
    int priority = 0;
    ClientMessage cm (  messageId, 
                        functionName, 
                        ipAddress, 
                        priority,
                        {});
    EXPECT_EQ(cm.GetMessageId(), messageId);
    EXPECT_EQ(cm.GetFunctionName(), functionName);
    EXPECT_EQ(cm.GetSender(), ipAddress);
    EXPECT_EQ(cm.GetPriority(), priority);
}


TEST(ClientMessage_test, GetParams) 
{
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
	std::vector<Parameter> paramsRewind = cm.GetParams();
	
	EXPECT_EQ(paramsRewind.size(), params.size());
	for (unsigned int i = 0; i < params.size(); i++)
	{
		EXPECT_EQ(paramsRewind[i].Value, params[i].Value);
		EXPECT_EQ(paramsRewind[i].Name, params[i].Name);
		EXPECT_EQ(paramsRewind[i].Type, params[i].Type);
	}

}

