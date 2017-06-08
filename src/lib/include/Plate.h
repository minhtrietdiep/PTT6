#ifndef PLATE_H_
#define PLATE_H_

#include <iostream>
#include <vector>
#include <string>
#include <Logger.h>
#include <Const.h>
#include <Error.h>

class Plate
{
	private:
		int m_ID;
		int m_DrivePosition;
		int m_CollimatorPosition;
		std::string m_Properties;
		double m_Thickness;
		Logger *m_Logger;

	public:
		Plate(int id, int drivePos, int collimatorPosition, std::string properties, double tickness);
		double GetThickness();
		std::string GetProperties();
		int GetCollimatorPosition();
		int GetDrivePosition();
		int GetID();
		 ErrorCode SetCollimatorPosition(int value);

};

#endif  //  PLATE_H_
