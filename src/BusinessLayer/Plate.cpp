#include "Plate.h"


Plate::Plate(int id, int drivePos, int colimatorPosition, std::string properties, double thickness)
{
	m_ID = id;
	m_DrivePosition = drivePos;
	m_ColimatorPosition = colimatorPosition;
	m_Properties = properties;
	m_Thickness = thickness;
}
double Plate::GetThickness()
{
	return m_Thickness;
}
std::string Plate::GetProperties()
{
	return m_Properties;
}
int Plate::GetCollimatorPosition()
{
	return m_ColimatorPosition;
}
int Plate::GetDrivePosition()
{
	return m_DrivePosition;
}
int Plate::GetID()
{
	return m_ID;
}
