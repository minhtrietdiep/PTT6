#ifndef DRIVE_H_
#define DRIVE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include "Coordinates.h"
#include "Logger.h"
#include "Error.h"
#include "Const.h"
#include <sstream>
#include <unistd.h>

#define DRIVE0 "/sys/class/gpio/gpio30/value"
#define DRIVE1 "/sys/class/gpio/gpio60/value"
#define DRIVE2 "/sys/class/gpio/gpio31/value"
#define DRIVE3 "/sys/class/gpio/gpio50/value"
#define DRIVE4 "/sys/class/gpio/gpio48/value"

#define DRIVE0D "/sys/class/gpio/gpio30/direction"
#define DRIVE1D "/sys/class/gpio/gpio60/direction"
#define DRIVE2D "/sys/class/gpio/gpio31/direction"
#define DRIVE3D "/sys/class/gpio/gpio50/direction"
#define DRIVE4D "/sys/class/gpio/gpio48/direction"

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