#ifndef VACUUM_H_
#define VACUUM_H_

#include <iostream>
#include <vector>

class Vacuum
{
    private:
        int m_VacuumStatus;

    public:
        void EnableVacuum();
        void DisableVacuum();
};

#endif  //  VACUUM_H_