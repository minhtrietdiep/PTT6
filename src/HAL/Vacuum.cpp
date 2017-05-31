#include "Vacuum.h"

#define FILEPATH "/sys/class/gpio/gpio51/value"

void Vacuum::Setup()
{
    std::ofstream f;
    f.open(FILEPATH);
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
    myfile.open (FILEPATH);
    myfile << 1;
    myfile.close();
    return ErrorCode::ERR_OK;
}

enum ErrorCode Vacuum::DisableVacuum()
{
    std::cout << "Disabling vacuum" << std::endl;
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << 0;
    myfile.close();
    return ErrorCode::ERR_OK;
}