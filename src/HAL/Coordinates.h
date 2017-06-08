#pragma once

#include <vector>

class Coordinates
{
    public:
        Coordinates(int pos1, int pos2, int pos3, int pos4);
        ~Coordinates();
        std::vector<int> GetCoordinates();
	private:
        int m_Pos1;
        int m_Pos2;
        int m_Pos3;
        int m_Pos4;
};
