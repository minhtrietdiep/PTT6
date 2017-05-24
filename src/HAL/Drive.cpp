#include "Drive.h"


#define DRIVE0 "/sys/class/gpio/gpioGPIO7/value"
#define DRIVE1 "/sys/class/gpio/gpioGPIO20/value"
#define DRIVE2 "/sys/class/gpio/gpioGPIO112/value"
#define DRIVE3 "/sys/class/gpio/gpioGPIO60/value"
#define DRIVE4 "/sys/class/gpio/gpioGPIO50/value"


Drive::Drive(int driveid, Coordinates positions) : m_Positions (positions)
{
    m_DriveID = driveid;
}

enum ErrorCode Drive::OpenDrive()
{
    std::cout << "Opening drive " << m_DriveID << std::endl;
    std::ofstream myfile;
    switch(m_DriveID)
    {
        case 0:
            myfile.open (DRIVE0);
            break;
        case 1:
            myfile.open (DRIVE1);
            break;
        case 2:
            myfile.open (DRIVE2);
            break;
        case 3:
            myfile.open (DRIVE3);
            break;
        case 4:
            myfile.open (DRIVE4);
            break;
        default:

            break;
    }
    myfile << 1;
    myfile.close();

    return ErrorCode::ERR_OK;
}

enum ErrorCode Drive::CloseDrive()
{
    std::cout << "Closing drive " << m_DriveID << std::endl;
    std::ofstream myfile;
    switch(m_DriveID)
    {
        case 0:
            myfile.open (DRIVE0);
            break;
        case 1:
            myfile.open (DRIVE1);
            break;
        case 2:
            myfile.open (DRIVE2);
            break;
        case 3:
            myfile.open (DRIVE3);
            break;
        case 4:
            myfile.open (DRIVE4);
            break;
        default:

            break;
    }
    
    myfile << 0;
    myfile.close();

    return ErrorCode::ERR_OK;
}

int Drive::GetDriveID()
{
    return m_DriveID;
}

Coordinates Drive::GetDriveCoordinates()
{
    return m_Positions;
}