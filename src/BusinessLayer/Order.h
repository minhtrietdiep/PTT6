#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <vector>
#include "Move.h"

class Order 
{
    private:
        std::vector<Move> m_MoveList;

    public:
        Order();
        ~Order();
        std::vector<Move> GetMoves();
        void NewMove(Move newMove);
        void Start();
        void Stop();
        void Reset();
};

#endif  //  ORDER_H_
