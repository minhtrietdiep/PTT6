#ifndef COORDINATES_H_
#define COORDINATES_H_

#include <iostream>
#include <vector>

class Coordinates
{
    private:
        int m_Pos1;
        int m_Pos2;
        int m_Pos3;
        int m_Pos4;

    public:
        Coordinates(int pos1, int pos2, int pos3, int pos4);
        ~Coordinates();
        std::vector<int> GetCoordinates();
};

#endif  //  COORDINATES_H_