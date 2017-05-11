#ifndef HAL_H_
#define HAL_H_

#include <iostream>
#include <vector>
#include "Drive.h"
#include "Arm.h"
#include "Vacuum.h"
#include "Coordinates.h"

class HAL
{
    private:
        std::vector<Drive> m_DriveList;
        Vacuum m_Vacuum;
        Arm m_Arm;

    public:
        HAL();
        int Pickup(bool on);
        int MoveArm(int driveid);
        int MoveArmToHome();
        int OpenDrive(int driveid);
        int CloseDrive(int driveid);
};

#endif  //  HAL_H_