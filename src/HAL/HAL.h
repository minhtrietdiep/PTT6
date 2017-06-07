#ifndef HAL_H_
#define HAL_H_

#include <vector>
#include "Drive.h"
#include "Arm.h"
#include "Vacuum.h"
#include <Logger.h>
#include "Error.h"

class HAL
{
    private:
        std::vector<Drive> m_DriveList;
        Vacuum m_Vacuum;
        Arm m_Arm;

    public:
        HAL();
        ErrorCode Pickup(bool on);
        ErrorCode MoveArm(int driveid);
        ErrorCode MoveArmToHome();
        ErrorCode OpenDrive(int driveid);
        ErrorCode CloseDrive(int driveid);
        ErrorCode SetupHardware();
};

#endif  //  HAL_H_