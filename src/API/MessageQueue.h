#pragma once

#include <string>

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
        void m_Error(const char *message);
};