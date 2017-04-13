#include "../Const.h"
#include "MessageQueue.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mqueue.h>
#include <cstring>

MessageQueue::MessageQueue()
{
    logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);
}

MessageQueue::~MessageQueue()
{
    delete logger;
}

void MessageQueue::m_Error(const char *message)
{
    char stringt[256];
    sprintf(stringt, "%s -> %s\n", message, strerror(errno));
    logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, std::string(stringt));
    exit(-1);
}

void MessageQueue::Create(const char *mqName)
{
    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "creating messagequeue");
    
    if (mq_unlink(mqName) < 0 && errno != ENOENT)
    {
        this->m_Error("mq_unlink() failed");
    }

    struct mq_attr mqAttributes;
    mqAttributes.mq_flags = 0;
    mqAttributes.mq_maxmsg = MQ_MAX_MESSAGE;
    mqAttributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mqAttributes.mq_curmsgs = 0;
  
    mqd_t mq = mq_open(mqName, O_RDWR | O_CREAT, 0644, &mqAttributes);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed---");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "messagequeue created");
}

void MessageQueue::Close(const char *mqName)
{
    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "closing messagequeue");
    
    if (mq_unlink(mqName) < 0)
    {
        this->m_Error("mq_unlink() failed");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "messagequeue closed");
}

void MessageQueue::Write(const char *mqName, std::string data)
{
    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "opening messagequeue");

    mqd_t mq = mq_open(mqName, O_WRONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "writing to messagequeue");
    
    if (mq_send(mq, data.c_str(), MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY) < 0)
    {
        this->m_Error("mq_send() failed");
    }

}

std::string MessageQueue::Read(const char *mqName)
{
    ssize_t messageSize;
    char buffer[MAX_MESSAGE_SIZE + 1];

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "opening messagequeue");

    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "reading messagequeue");

    messageSize = mq_receive(mq, buffer, MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY);
    if (messageSize < 0)
    {
        this->m_Error("mq_receive() failed");
    }
    buffer[messageSize] = '\0';
    
    return std::string(buffer);
}

long MessageQueue::GetMessageCount(const char *mqName)
{
    struct mq_attr mqAttributes;

    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "opening messagequeue");

    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "getting messagequeue attributes");
    
    if (mq_getattr(mq, &mqAttributes) < 0)
    {
        this->m_Error("mq_getattr() failed");
    }
    
    return mqAttributes.mq_curmsgs;
}