#pragma once

#include <termios.h>

#include <Const.h>
#include <Error.h>
#include <Logger.h>

class Arm
{
	public:
        Arm();
        ~Arm();
        ErrorCode MoveHome();
        ErrorCode MoveToCol(std::string command);
        ErrorCode MoveToColPrep();
        ErrorCode MoveToDrive(std::string command);
        ErrorCode MoveToDrivePrep();
        ErrorCode WriteCommand(std::string command);
        void SetFilePath(std::string path);
    private:
        std::string m_ArmFilePath;
        std::string m_ColPrepCommand;
        std::string m_DrivePrepCommand;
        std::string m_ArmHomeCommand;
        struct termios m_SerialConfig;
        Logger m_Logger;
};
