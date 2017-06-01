#ifndef VACUUM_H_
#define VACUUM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "Logger.h"
#include "Error.h"
#include <Const.h>

#define VACUUM "/sys/class/gpio/gpio51/value"
#define VACUUMD "/sys/class/gpio/gpio51/direction"
#define VALVE "/sys/class/gpio/gpio5/value"
#define VALVED "/sys/class/gpio/gpio5/direction"

class Vacuum
{
    private:
        int m_VacuumStatus;
        enum ErrorCode Setup();
        Logger *m_Logger;
        enum ErrorCode FileCheck(std::ofstream &f, std::string functionname);

    public:
        Vacuum();
        enum ErrorCode EnableVacuum();
        enum ErrorCode DisableVacuum();
};

#endif  //  VACUUM_H_