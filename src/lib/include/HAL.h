#pragma once

#include <vector>

#include <Const.h>
#include <Error.h>
#include <Logger.h>

#include "Arm.h"
#include "Drive.h"
#include "Vacuum.h"

class HAL
{
    public:
        HAL();
        ~HAL();
        ErrorCode Pickup(bool on);
        ErrorCode MoveToCol();
        ErrorCode MoveToColPrep();
        ErrorCode MoveToDrive(int driveid);
        ErrorCode MoveToDrivePrep();
        //ErrorCode MoveArm(int driveid);
        ErrorCode MoveArmToHome();
        ErrorCode OpenDrive(int driveid);
        ErrorCode CloseDrive(int driveid);
        ErrorCode SetupHardware();
    private:
        std::vector<Drive> m_DriveList;
        Vacuum m_Vacuum;
        Arm m_Arm;
        Logger m_Logger;
};
