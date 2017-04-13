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
    char *string = sprintf("%s -> %s\n", message, strerror(errno));
    logger->Write(Logger::Severity::ERROR, str(string), __func__);
    exit(-1);
}

void MessageQueue::Create(const char *mqName)
{
    logger->Write(Logger::Severity::DEBUG, "creating messagequeue", __func__);
    
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

    logger->Write(Logger::Severity::DEBUG, "messagequeue created", __func__);
}

void MessageQueue::Close(const char *mqName)
{
    logger->Write(Logger::Severity::DEBUG, "closing messagequeue", __func__);
    
    if (mq_unlink(mqName) < 0)
    {
        this->m_Error("mq_unlink() failed");
    }

    logger->Write(Logger::Severity::DEBUG, "messagequeue closed", __func__);
}

void MessageQueue::Write(const char *mqName, std::string data)
{
    logger->Write(Logger::Severity::DEBUG, "opening messagequeue", __func__);

    mqd_t mq = mq_open(mqName, O_WRONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }

    logger->Write(Logger::Severity::DEBUG, "writing to messagequeue", __func__);
    
    if (mq_send(mq, data.c_str(), MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY) < 0)
    {
        this->m_Error("mq_send() failed");
    }

}

std::string MessageQueue::Read(const char *mqName)
{
    ssize_t messageSize;
    char buffer[MAX_MESSAGE_SIZE + 1];

    logger->Write(Logger::Severity::DEBUG, "opening messagequeue", __func__);

    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    logger->Write(Logger::Severity::DEBUG, "reading messagequeue", __func__);

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

    logger->Write(Logger::Severity::DEBUG, "opening messagequeue", __func__);

    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    logger->Write(Logger::Severity::DEBUG, "getting messagequeue attributes", __func__);
    
    if (mq_getattr(mq, &mqAttributes) < 0)
    {
        this->m_Error("mq_getattr() failed");
    }
    
    return mqAttributes.mq_curmsgs;
}