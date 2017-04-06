#ifndef PLATE_H_
#define PLATE_H_

#include <iostream>
#include <vector>

class Plate
{
	private:
		int m_ID;
		int m_DrivePosition;
		int m_ColimatorPosition ;
		int m_Properties ;
		double m_Thickness ;

	public:
		Plate(int id, int drivePos, int colimatorPosition, int properties, double tickness);
		double GetThickness();
		int GetProperties();
		int GetColimatorPosition();
		int GetDrivePosition();
		int GetID();

};

#endif  //  PLATE_H_
