#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <vector>
#include <Error.h>
#include "Move.h"
#include "../HAL/HAL.h"

class Order 
{
    private:
        std::vector<Move> m_MoveList;
        HAL m_Hal;

    public:
        Order();
        ~Order();
        std::vector<Move> GetMoves();
        ErrorCode NewMove(Move newMove);
        ErrorCode Start();
        ErrorCode Stop();
        ErrorCode Reset();
};

#endif  //  ORDER_H_
