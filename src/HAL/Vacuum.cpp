#include "Vacuum.h"

#define VACUUM "/sys/class/gpio/gpio51/value"
#define VACUUMD "/sys/class/gpio/gpio51/direction"
#define VALVE "/sys/class/gpio/gpio5/value"
#define VALVED "/sys/class/gpio/gpio5/direction"

void Vacuum::Setup()
{
    std::ofstream f;
    f.open(VACUUMD);
    f << "out";
    f.close();
    f.open(VALVED);
    f << "out";
    f.close();
}

Vacuum::Vacuum()
{
    Setup();
}

enum ErrorCode Vacuum::EnableVacuum()
{
    std::cout << "Enabling vacuum" << std::endl;
    std::ofstream myfile;
    myfile.open (VACUUM);
    myfile << 1;
    myfile.close();
    myfile.open(VALVE);
    myfile << 0;
    myfile.close();
    return ErrorCode::ERR_OK;
}

enum ErrorCode Vacuum::DisableVacuum()
{
    std::cout << "Disabling vacuum" << std::endl;
    std::ofstream myfile;
    myfile.open (VACUUM);
    myfile << 0;
    myfile.close();
    myfile.open(VALVE);
    myfile << 1;
    myfile.close();
    return ErrorCode::ERR_OK;
}