#ifndef DRIVE_H_
#define DRIVE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "Logger.h"
#include "Error.h"
#include "Const.h"

class Drive
{
    private:
        int m_DriveID;
        Coordinates m_Positions;
        enum ErrorCode ToggleDrive();
        enum ErrorCode Setup();
        Logger *m_Logger;

    public:
        Drive(int driveid, Coordinates positions);
        enum ErrorCode OpenDrive();
        enum ErrorCode CloseDrive();
        int GetDriveID();
        Coordinates GetDriveCoordinates();
};

#endif  //  DRIVE_H_