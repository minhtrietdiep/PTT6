#ifndef ORDER_H_
#define ORDER_H_

#include <iostream>
#include <vector>
#include <Error.h>
#include <Move.h>
#include <HAL.h>
#include <Logger.h>
#include <Const.h>

class Order 
{
    private:
        std::vector<Move> m_MoveList;
        HAL m_Hal;
        enum class m_States {
            OPEN_DRIVE,
            MOVE_ARM_SOURCE,
            ENABLE_VACUUM,
            MOVE_ARM_DESTINATION,
            DISABLE_VACUUM,
            MOVE_ARM_HOME,
            CLOSE_DRIVE,
            COMPLETED
            };
        Logger /***/m_Logger;

    public:
        Order();
        ~Order();
        std::vector<Move> GetMoves();
        ErrorCode NewMove(Move newMove);
        ErrorCode Start();
        ErrorCode Stop();
        ErrorCode Reset();
        ErrorCode SetupHardware();
};

#endif  //  ORDER_H_
