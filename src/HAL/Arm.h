#ifndef ARM_H_
#define ARM_H_

#include <iostream>
#include <vector>
#include "Coordinates.h"

class Arm
{
    private:
        Coordinates m_HomePosition;

    public:
        Arm(Coordinates homeposition);
        int MoveToCoord(Coordinates coordinates);

};

#endif  //  ARM_H_