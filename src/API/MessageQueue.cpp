#include "Const.h"
#include "MessageQueue.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mqueue.h>
#include <cstring>

MessageQueue::MessageQueue()
{
    // Nothing to do here
}

MessageQueue::~MessageQueue()
{
    // Nothing to do here
}

void MessageQueue::m_Error(const char *message)
{
    printf("Error: %s -> %s\n", message, strerror(errno));
    exit(-1);
}

void MessageQueue::Create(const char *mqName)
{
    if (mq_unlink(mqName) < 0 && errno != ENOENT)
    {
        this->m_Error("mq_unlink() failed");
    }

    struct mq_attr mqAttributes;
    mqAttributes.mq_flags = 0;
    mqAttributes.mq_maxmsg = MQ_MAX_MESSAGE;
    mqAttributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mqAttributes.mq_curmsgs = 0;

    printf("creating mq...\n");   
    mqd_t mq = mq_open(mqName, O_RDWR | O_CREAT, 0644, &mqAttributes);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed---");
    }
}

void MessageQueue::Close(const char *mqName)
{
    printf("closing mq...\n");
    if (mq_unlink(mqName) < 0)
    {
        this->m_Error("mq_unlink() failed");
    }
}

void MessageQueue::Write(const char *mqName, std::string data)
{
    printf("opening mq...\n");
    mqd_t mq = mq_open(mqName, O_WRONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    printf("writing mq...\n");
    if (mq_send(mq, data.c_str(), MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY) < 0)
    {
        this->m_Error("mq_send() failed");
    }

}

std::string MessageQueue::Read(const char *mqName)
{
    ssize_t messageSize;
    char buffer[MAX_MESSAGE_SIZE + 1];

    printf("opening mq...\n");  
    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    printf("reading mq...\n");
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

    printf("opening mq...\n");
    mqd_t mq = mq_open(mqName, O_RDONLY);
    if (mq == (mqd_t)-1)
    {
        this->m_Error("mq_open() failed");
    }
    
    printf("getting mq attributes...\n");
    
    if (mq_getattr(mq, &mqAttributes) < 0)
    {
        this->m_Error("mq_getattr() failed");
    }
    
    return mqAttributes.mq_curmsgs;
}