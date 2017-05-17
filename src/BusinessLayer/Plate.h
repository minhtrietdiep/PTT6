#ifndef PLATE_H_
#define PLATE_H_

#include <iostream>
#include <vector>
#include <string>

class Plate
{
	private:
		int m_ID;
		int m_DrivePosition;
		int m_ColimatorPosition;
		std::string m_Properties;
		double m_Thickness;

	public:
		Plate(int id, int drivePos, int colimatorPosition, std::string properties, double tickness);
		double GetThickness();
		std::string GetProperties();
		int GetColimatorPosition();
		int GetDrivePosition();
		int GetID();

};

#endif  //  PLATE_H_
