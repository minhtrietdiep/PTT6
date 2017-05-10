#pragma once

#include <string>
#include <Logger.h>

class MessageQueue
{
    public:
        MessageQueue();
        ~MessageQueue();
        void Create(const char *mqName);
        void Close(const char *mqName);
        void Write(const char *mqName, std::string data);
        std::string Read(const char *mqName);
        long GetMessageCount(const char *mqName);
    private:
        void Error(std::string message);
        Logger m_Logger;
};