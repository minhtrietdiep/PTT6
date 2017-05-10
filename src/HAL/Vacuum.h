#ifndef VACUUM_H_
#define VACUUM_H_

#include <iostream>
#include <vector>

class Vacuum
{
    private:
        int m_VacuumStatus;

    public:
        int EnableVacuum();
        int DisableVacuum();
};

#endif  //  VACUUM_H_