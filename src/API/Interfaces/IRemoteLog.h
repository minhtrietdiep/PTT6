#ifndef IREMOTELOG_H_
#define IREMOTELOG_H_

#include <iostream>
#include <vector>
#include "ErrorCode.h"
class IRemoteLog
{
    private:


    public:
        virtual ~IRemoteLog(){}
        virtual ErrorCode DownloadLog(int logfilenumber)=0;
};

#endif  //  IREMOTELOG_H_
