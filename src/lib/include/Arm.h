#ifndef ARM_H_
#define ARM_H_

#include "Coordinates.h"

#include "Error.h"
#include "Logger.h"

#include <Const.h>

#include <string>

class Arm
{
	public:
        Arm(Coordinates homeposition);
        ~Arm();
        ErrorCode MoveToCoord(Coordinates coordinates);
        ErrorCode MoveHome();
        void SetFilePath(std::string path);
    private:
        Coordinates m_HomePosition;
        Logger * m_Logger;
        std::string m_ArmFilePath;
};

#endif  //  ARM_H_