#ifndef DRIVE_H_
#define DRIVE_H_

#include <iostream>
#include <vector>

class Drive
{
    private:
        int m_DriveID;
        //Coord m_Position;

    public:
        Drive(int driveid);
        void OpenDrive();
        void CloseDrive();
        int GetDriveID();
};

#endif  //  DRIVE_H_