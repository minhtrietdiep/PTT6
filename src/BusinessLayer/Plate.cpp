#include "Plate.h"


Plate::Plate(int id, int drivePos, int collimatorPosition, std::string properties, double thickness)
{
	m_ID = id;
	m_DrivePosition = drivePos;
	m_CollimatorPosition = collimatorPosition;
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
	return m_CollimatorPosition;
}
int Plate::GetDrivePosition()
{
	return m_DrivePosition;
}
int Plate::GetID()
{
	return m_ID;
}
void Plate::SetCollimatorPosition(int value)
{
	m_CollimatorPosition = value;
	std::cout<<"plate set to " << value << std::endl;
}
