#include "Plate.h"

#define MAX_COLLIMATORPOS_VALUE 4
#define MIN_COLLIMATORPOS_VALUE -1


Plate::Plate(int id, int drivePos, int collimatorPosition, std::string properties, double thickness) :
	m_ID(id),
	m_DrivePosition(drivePos),
	m_CollimatorPosition(collimatorPosition),
	m_Properties(properties),
	m_Thickness(thickness),
	m_Logger(VERSION,Logger::Severity::ERROR,LOG_PATH)
{

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
 ErrorCode Plate::SetCollimatorPosition(int value)
{
	if (value <= MAX_COLLIMATORPOS_VALUE && value >= MIN_COLLIMATORPOS_VALUE)
	{
		m_CollimatorPosition = value;
		return ErrorCode::ERR_OK;
	}
	m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "SetCollimatorPosition no int");
	return ErrorCode::ERR_INVALID_ARG;

	
}
 ErrorCode Plate::SetDrivePos(int value)
{
	if (value <= MAX_COLLIMATORPOS_VALUE && value >= MIN_COLLIMATORPOS_VALUE)
	{
		m_DrivePosition = value;
		return ErrorCode::ERR_OK;
	}
	m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "SetDrivePosition no int");
	return ErrorCode::ERR_INVALID_ARG;

	
}
