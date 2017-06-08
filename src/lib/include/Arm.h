#ifndef ARM_H_
#define ARM_H_


#include "Coordinates.h"
#include <Logger.h>
#include "Error.h"
#include <Const.h>

class Arm
{
    private:
        Coordinates m_HomePosition;
        Logger *m_Logger;
        const char* ARMPATH = "/dev/ttyUSB0";

    public:
        Arm(Coordinates homeposition);
        ErrorCode MoveToCoord(Coordinates coordinates);
        ErrorCode MoveHome();
};

#endif  //  ARM_H_