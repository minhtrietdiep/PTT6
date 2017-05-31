#ifndef ARM_H_
#define ARM_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "Logger.h"
#include "Error.h"
#include <Const.h>

class Arm
{
    private:
        Coordinates m_HomePosition;
        Logger *m_Logger;

    public:
        Arm(Coordinates homeposition);
        enum ErrorCode MoveToCoord(Coordinates coordinates);
        enum ErrorCode MoveHome();
};

#endif  //  ARM_H_