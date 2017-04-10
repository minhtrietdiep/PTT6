#include "Const.h"
#include "MessageQueue.h"

#include <stdio.h>
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

void MessageQueue::Create(const char *mqName)
{
    mq_unlink(MQ_NAME_RECEIVED_MESSAGES);

    struct mq_attr mqAttributes;
    mqAttributes.mq_flags = 0;
    mqAttributes.mq_maxmsg = MQ_MAX_MESSAGE;
    mqAttributes.mq_msgsize = MAX_MESSAGE_SIZE;
    mqAttributes.mq_curmsgs = 0;

    printf("creating mq...\n");   
    mqd_t mq = mq_open(mqName, O_RDWR | O_CREAT, 0644, &mqAttributes);
    if (mq == (mqd_t)-1)
    {
        printf("Error: in mq create -> %s\n", strerror(errno));
    }
}

void MessageQueue::Close(const char *mqName)
{
    printf("closing mq...\n");
    mq_unlink(mqName);
}

void MessageQueue::Write(const char *mqName, std::string data)
{
    printf("opening mq...\n");
    mqd_t mq = mq_open(mqName, O_WRONLY);
    
    printf("writing mq...\n");
    mq_send(mq, data.c_str(), MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY);
}

std::string MessageQueue::Read(const char *mqName)
{
    ssize_t messageSize;
    char buffer[MAX_MESSAGE_SIZE + 1];

    printf("opening mq...\n");  
    mqd_t mq = mq_open(mqName, O_RDONLY);
    
    printf("reading mq...\n");
    messageSize = mq_receive(mq, buffer, MAX_MESSAGE_SIZE, MQ_MESSAGE_PRIORITY);
    buffer[messageSize] = '\0';
    
    return std::string(buffer);
}

long MessageQueue::GetMessageCount(const char *mqName)
{
    struct mq_attr mqAttributes;

    printf("opening mq...\n");
    mqd_t mq = mq_open(mqName, O_RDONLY); 
    
    printf("getting mq attributes...\n");
    mq_getattr(mq, &mqAttributes);
    
    return mqAttributes.mq_curmsgs;
}