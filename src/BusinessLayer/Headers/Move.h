#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <vector>
#include "Step.h"

class Move {

private:
	int Source  ;
	int Destination ;
	std::vector<Step> Steplist;

public:
	Move();


};

#endif  //  MOVE_H_
