#include "Coordinates.h"

#include <Logger.h>
#include <iostream>

Coordinates::Coordinates(int pos1, int pos2, int pos3, int pos4) : 
	m_Pos1(pos1),
	m_Pos2(pos2),
	m_Pos3(pos3),
	m_Pos4(pos4)
{

}

Coordinates::~Coordinates()
{

}

std::vector<int> Coordinates::GetCoordinates()
{
    std::vector<int> coordinates { m_Pos1, m_Pos2, m_Pos3, m_Pos4 };
    return coordinates;
}