#ifndef DRIVE_H_
#define DRIVE_H_

#include "Coordinates.h"
#include "Error.h"
#include "Const.h"

#include <Logger.h>

class Drive
{
    public:
        Drive(int driveid, Coordinates positions);
        ~Drive();
        ErrorCode SetupHardware();
        ErrorCode OpenDrive();
        ErrorCode CloseDrive();
        int GetDriveID();
        Coordinates GetDriveCoordinates();
        
    private:
        ErrorCode ToggleDrive();
        int m_DriveID;
        Logger *m_Logger;
        Coordinates m_Positions;
};

#endif  //  DRIVE_H_