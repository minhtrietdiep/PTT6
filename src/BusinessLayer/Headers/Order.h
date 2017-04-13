#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <vector>
#include "Move.h"

class Order 
{
	private:
		std::vector<Move> m_Moves;

	public:
		Order(std::vector<Move> moves);
        std::vector<Move> GetMoves();
		void Start();
		void Stop();
		void Reset();
};

#endif  //  ORDER_H_
