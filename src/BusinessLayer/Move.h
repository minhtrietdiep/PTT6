#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <vector>

class Move {

private:
    int m_PlateID;
    int m_Destination;

public:
    Move(int PlateID,int Destination);
    ~Move();
};

#endif  //  MOVE_H_
