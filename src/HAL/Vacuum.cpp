#include "Vacuum.h"

#define FILEPATH "/dev/Vacuum.txt"

int Vacuum::EnableVacuum()
{
    std::cout << "Enabling vacuum" << std::endl;
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << 1;
    myfile.close();
    return 1;
}

int Vacuum::DisableVacuum()
{
    std::cout << "Disabling vacuum" << std::endl;
    std::ofstream myfile;
    myfile.open (FILEPATH);
    myfile << 0;
    myfile.close();
    return 1;
}