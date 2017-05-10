#include "MessageQueue.h"

#include <Const.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mqueue.h>
#include <cstring>
#include <sstream>

MessageQueue::MessageQueue() :
    m_Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH)
{
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::Error(std::string message)
{
    std::ostringstream logOutput;
    logOutput << message << " -> " << strerror(errno);
    m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, logOutput.str());
    exit(-1);
}

void MessageQueue::Create(std::string mqName)
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "creating messagequeue");
    
    if (mq_unlink(mqName.c_str()) < 0 && errno != ENOENT)
    {
        Error("mq_unlink() failed");
    }

    struct mq_attr mqAttributes;
    mqAttributes.mq_flags = 0;
    mqAttributes.mq_maxmsg = MQ_MAX_MESSAGE;
    mqAttributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mqAttributes.mq_curmsgs = 0;
  
    mqd_t mq = mq_open(mqName.c_str(), O_RDWR | O_CREAT, 0644, &mqAttributes);
    if (mq == (mqd_t)-1)
    {
        Error("mq_open() failed");
    }

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "messagequeue created");
}

void MessageQueue::Close(std::string mqName)
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "closing messagequeue");
    
    if (mq_unlink(mqName.c_str()) < 0)
    {
        Error("mq_unlink() failed");
    }

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "messagequeue closed");
}

void MessageQueue::Write(std::string mqName, std::string data)
{
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "opening messagequeue");

    mqd_t mq = mq_open(mqName.c_str(), O_WRONLY);
    if (mq == (mqd_t)-1)
    {
        Error("mq_open() failed");
    }

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "writing to messagequeue");
    
    if (mq_send(mq, data.c_str(), MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY) < 0)
    {
        Error("mq_send() failed");
    }

}

std::string MessageQueue::Read(std::string mqName)
{
    ssize_t messageSize;
    char buffer[MAX_MESSAGE_SIZE + 1];

    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "opening messagequeue");

    mqd_t mq = mq_open(mqName.c_str(), O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        Error("mq_open() failed");
    }
    
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "reading messagequeue");

    messageSize = mq_receive(mq, buffer, MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY);
    if (messageSize < 0)
    {
        Error("mq_receive() failed");
    }
    buffer[messageSize] = '\0';
    
    return std::string(buffer);
}

long MessageQueue::GetMessageCount(std::string mqName)
{
    struct mq_attr mqAttributes;

    mqd_t mq = mq_open(mqName.c_str(), O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        Error("mq_open() failed");
    }
        
    if (mq_getattr(mq, &mqAttributes) < 0)
    {
        Error("mq_getattr() failed");
    }

    int ret = mq_close(mq);
    if (ret != 0) {
        m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "Failed to close mq handle: " + errno);
    }
    return mqAttributes.mq_curmsgs;
}