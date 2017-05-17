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
        enum m_States { OPEN_DRIVE,MOVE_ARM_SOURCE,ENABLE_VACUUM,MOVE_ARM_DESTINATION,DISABLE_VACUUM,MOVE_ARM_HOME,CLOSE_DRIVE,COMPLETED };

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
