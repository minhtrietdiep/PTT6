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

#define FILEPATH "/dev/ttyUSB0"

class Arm
{
    private:
        Coordinates m_HomePosition;
        Logger *m_Logger;
        enum ErrorCode Setup();

    public:
        Arm(Coordinates homeposition);
        enum ErrorCode MoveToCoord(Coordinates coordinates);
        enum ErrorCode MoveHome();
};

#endif  //  ARM_H_