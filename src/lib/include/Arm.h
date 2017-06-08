#ifndef ARM_H_
#define ARM_H_

#include "Coordinates.h"

#include "Error.h"

#include <Logger.h>
#include <Const.h>

class Arm
{
	public:
        Arm(Coordinates homeposition);
        ~Arm();
        ErrorCode MoveToCoord(Coordinates coordinates);
        ErrorCode MoveHome();
    private:
        Coordinates m_HomePosition;
        Logger m_Logger;
};

#endif  //  ARM_H_