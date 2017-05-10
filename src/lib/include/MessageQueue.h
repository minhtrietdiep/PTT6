#pragma once

#include <string>
#include <Logger.h>

class MessageQueue
{
    public:
        MessageQueue();
        ~MessageQueue();
        void Create(std::string mqName);
        void Close(std::string mqName);
        void Write(std::string mqName, std::string data);
        std::string Read(std::string mqName);
        long GetMessageCount(std::string mqName);
    private:
        void Error(std::string message);
        Logger m_Logger;
};