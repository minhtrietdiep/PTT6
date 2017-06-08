#ifndef ARM_H_
#define ARM_H_

#include "Coordinates.h"

#include "Error.h"
#include "Logger.h"

#include <termios.h>

#include <Const.h>

#include <string>

class Arm
{
	public:
        Arm(Coordinates homeposition);
        ~Arm();
        //ErrorCode MoveToCoord(Coordinates coordinates);
        ErrorCode MoveHome();
        void SetFilePath(std::string path);
        ErrorCode MoveToCol(std::string command);
        ErrorCode MoveToColPrep();
        ErrorCode MoveToDrive(std::string command);
        ErrorCode MoveToDrivePrep();
        ErrorCode WriteCommand(std::string command);
    private:
        Coordinates m_HomePosition;
        Logger * m_Logger;
        std::string m_ArmFilePath;
        std::string m_ColPrepCommand;
        std::string m_DrivePrepCommand;
        std::string m_ArmHomeCOmmand;
};

#endif  //  ARM_H_