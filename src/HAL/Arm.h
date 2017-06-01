#ifndef ARM_H_
#define ARM_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "Logger.h"
#include "Error.h"
#include <Const.h>
#include <sstream>

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
        ErrorCode SetupHardware();
};

#endif  //  ARM_H_