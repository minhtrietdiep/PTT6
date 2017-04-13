#ifndef IREMOTELOG_H_
#define IREMOTELOG_H_

#include <iostream>
#include <vector>

class IRemoteLog
{
    private:


    public:
        virtual ~IRemoteLog(){}
        virtual void DownloadLog(int logfilenumber)=0;
};

#endif  //  IREMOTELOG_H_
