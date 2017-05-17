#ifndef HAL_H_
#define HAL_H_

#include <iostream>
#include <vector>
#include "Drive.h"
#include "Arm.h"
#include "Vacuum.h"
#include "Coordinates.h"
#include <Error.h>

class HAL
{
    private:
        std::vector<Drive> m_DriveList;
        Vacuum m_Vacuum;
        Arm m_Arm;

    public:
        HAL();
        enum ErrorCode Pickup(bool on);
        enum ErrorCode MoveArm(int driveid);
        enum ErrorCode MoveArmToHome();
        enum ErrorCode OpenDrive(int driveid);
        enum ErrorCode CloseDrive(int driveid);
};

#endif  //  HAL_H_