#ifndef DRIVE_H_
#define DRIVE_H_

#include <iostream>
#include <vector>
#include "Coordinates.h"

class Drive
{
    private:
        int m_DriveID;
        Coordinates m_Positions;

    public:
        Drive(int driveid, Coordinates positions);
        void OpenDrive();
        void CloseDrive();
        int GetDriveID();
};

#endif  //  DRIVE_H_