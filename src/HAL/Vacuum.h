#ifndef VACUUM_H_
#define VACUUM_H_

#include <Logger.h>
#include "Error.h"
#include <Const.h>

class Vacuum
{
    private:
        int m_VacuumStatus;
        Logger *m_Logger;
        ErrorCode FileCheck(std::ofstream &f, std::string functionname);

        const char* VACUUM = "/sys/class/gpio/gpio51/value";
        const char* VACUUMD = "/sys/class/gpio/gpio51/direction";
        const char* VALVE = "/sys/class/gpio/gpio5/value";
        const char* VALVED = "/sys/class/gpio/gpio5/direction";

    public:
        Vacuum();
        ErrorCode EnableVacuum();
        ErrorCode DisableVacuum();
        ErrorCode SetupHardware();
};

#endif  //  VACUUM_H_