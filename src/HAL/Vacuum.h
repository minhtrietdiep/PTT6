#ifndef VACUUM_H_
#define VACUUM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "Logger.h"
#include "Error.h"

class Vacuum
{
    private:
        int m_VacuumStatus;
        void Setup();

    public:
        Vacuum();
        enum ErrorCode EnableVacuum();
        enum ErrorCode DisableVacuum();
};

#endif  //  VACUUM_H_