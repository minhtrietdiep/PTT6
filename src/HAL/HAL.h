#ifndef HAL_H_
#define HAL_H_

#include "Arm.h"
#include "Drive.h"
#include "Vacuum.h"

#include "Error.h"

#include <Logger.h>

#include <vector>

class HAL
{
    public:
        HAL();
        ~HAL();
        ErrorCode Pickup(bool on);
        ErrorCode MoveArm(int driveid);
        ErrorCode MoveArmToHome();
        ErrorCode OpenDrive(int driveid);
        ErrorCode CloseDrive(int driveid);
        ErrorCode SetupHardware();
    private:
        std::vector<Drive> m_DriveList;
        Vacuum m_Vacuum;
        Arm m_Arm;
};

#endif  //  HAL_H_