#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <vector>
#include "Step.h"

class Move {

private:
	int m_Source;
	int m_Destination;
	std::vector<Step> m_Steplist;

public:
	Move(int Source,int Destination,std::vector<Step> Steplist);


};

#endif  //  MOVE_H_
