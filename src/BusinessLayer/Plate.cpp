#include "Headers/Plate.h"

Plate::Plate(int id, int drivePos, int colimatorPosition, int properties, double tickness)
{
	m_ID = id;
	m_DrivePosition = drivePos;
	m_ColimatorPosition = colimatorPosition;
	m_Properties = properties;
	m_Thickness = tickness;
}
double GetThickness()
{
	return m_Thickness;
}
int GetProperties()
{
	return m_Properties;
}
int GetColimatorPosition()
{
	return m_ColimatorPosition;
}
int GetDrivePosition()
{
	return m_DrivePosition
}
int GetID()
{
	return m_ID;
}
