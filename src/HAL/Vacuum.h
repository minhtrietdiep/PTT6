#ifndef VACUUM_H_
#define VACUUM_H_

#include "Error.h"

#include <Logger.h>
#include <Const.h>

class Vacuum
{
    public:
        Vacuum();
        ~Vacuum();
        ErrorCode EnableVacuum();
        ErrorCode DisableVacuum();
        ErrorCode SetupHardware();
    private:
        ErrorCode FileCheck(std::ofstream &f, std::string functionname);
        int m_VacuumStatus;
        Logger *m_Logger;
};

#endif  //  VACUUM_H_