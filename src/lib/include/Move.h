#pragma once

#include <vector>

class Move {

private:
    int m_PlateID;
    int m_Destination;

public:
    Move(int PlateID,int Destination);
    int GetPlateID();
    int GetDestination();
    ~Move();
};
