#ifndef DRIVE_H_
#define DRIVE_H_

#include "Coordinates.h"
#include "Error.h"
#include "Const.h"
#include <Logger.h>

class Drive
{
    private:
        int m_DriveID;
        Coordinates m_Positions;
        ErrorCode ToggleDrive();
        Logger *m_Logger;

        const char* DRIVE0 = "/sys/class/gpio/gpio30/value";
        const char* DRIVE1 = "/sys/class/gpio/gpio60/value";
        const char* DRIVE2 = "/sys/class/gpio/gpio31/value";
        const char* DRIVE3 = "/sys/class/gpio/gpio50/value";
        const char* DRIVE4 = "/sys/class/gpio/gpio48/value";

        const char* DRIVE0D = "/sys/class/gpio/gpio30/direction";
        const char* DRIVE1D = "/sys/class/gpio/gpio60/direction";
        const char* DRIVE2D = "/sys/class/gpio/gpio31/direction";
        const char* DRIVE3D = "/sys/class/gpio/gpio50/direction";
        const char* DRIVE4D = "/sys/class/gpio/gpio48/direction";


    public:
        Drive(int driveid, Coordinates positions);
        ErrorCode OpenDrive();
        ErrorCode CloseDrive();
        int GetDriveID();
        Coordinates GetDriveCoordinates();
        ErrorCode SetupHardware();
};

#endif  //  DRIVE_H_