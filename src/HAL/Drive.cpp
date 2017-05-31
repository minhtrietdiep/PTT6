#include "Drive.h"
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

void Drive::Setup()
{
    std::ofstream f;
    switch(m_DriveID)
    {
        case 0:
            f.open(DRIVE0D);
            break;

        case 1:
            f.open(DRIVE1D);
            break;

        case 2:
            f.open(DRIVE2D);
            break;

        case 3:
            f.open(DRIVE3D);
            break;

        case 4:
            f.open(DRIVE4D);
            break; 

        default:
            break;
    }
        f << "out";
        f.close();
}

Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions)
{
    m_DriveID = driveid;
    Setup();
}

enum ErrorCode Drive::ToggleDrive()
{
    std::ofstream myfile;
    std::ofstream mijnfile;

    switch(m_DriveID)
    {
        case 0:
            myfile.open (DRIVE0);
            mijnfile.open (DRIVE0);
            break;
        case 1:
            myfile.open (DRIVE1);
            mijnfile.open (DRIVE1);
            break;
        case 2:
            myfile.open (DRIVE2);
            mijnfile.open (DRIVE2);
            break;
        case 3:
            myfile.open (DRIVE3);
            mijnfile.open (DRIVE3);
            break;
        case 4:
            myfile.open (DRIVE4);
            mijnfile.open (DRIVE4);
            break;
        default:

            break;
    }
    myfile << 1;
    myfile.close();

    usleep(20000);


    mijnfile << 0;
    mijnfile.close();

    usleep(2000000);

    return ErrorCode::ERR_OK;
}

enum ErrorCode Drive::OpenDrive()
{
    std::cout << "Opening drive " << m_DriveID << std::endl;
    return ToggleDrive();
}

enum ErrorCode Drive::CloseDrive()
{
    std::cout << "Closing drive " << m_DriveID << std::endl;
    return ToggleDrive();;
}

int Drive::GetDriveID()
{
    return m_DriveID;
}

Coordinates Drive::GetDriveCoordinates()
{
    return m_Positions;
}
