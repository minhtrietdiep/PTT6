#include "Coordinates.h"

Coordinates::Coordinates(int pos1, int pos2, int pos3, int pos4)
{
    m_Pos1 = pos1;
    m_Pos2 = pos2;
    m_Pos3 = pos3;
    m_Pos4 = pos4;
}

std::vector<int> Coordinates::GetCoordinates()
{
    std::vector<int> coordinates;
    coordinates.push_back(m_Pos4);
    coordinates.push_back(m_Pos3);
    coordinates.push_back(m_Pos2);
    coordinates.push_back(m_Pos1);
    return coordinates;
}

Coordinates::~Coordinates()
{

}