#ifndef DRIVE_H_
#define DRIVE_H_

#include "Coordinates.h"

#include "Error.h"
#include "Const.h"

#include <Logger.h>

class Drive
{
    public:
        Drive(int driveid, std::string movecommand);
        ~Drive();
        ErrorCode SetupHardware();
        ErrorCode OpenDrive();
        ErrorCode CloseDrive();
        int GetDriveID();
        //Coordinates GetDriveCoordinates();
        std::string GetDriveMoveCommand();

        
    private:
        ErrorCode ToggleDrive();
        int m_DriveID;
        Logger * m_Logger;
        std::string m_MoveCommand;
};

#endif  //  DRIVE_H_