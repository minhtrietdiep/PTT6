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

        Logger m_Logger;

    public:
        Order();
        ~Order();
        std::vector<Move> GetMoves();
        ErrorCode NewMove(Move newMove);
        ErrorCode Start();
        ErrorCode Stop();
        ErrorCode Reset();
        ErrorCode SetupHardware();
        ErrorCode PlateToDrive(int driveID);
        ErrorCode PlateToCol(int driveID);
};

#endif  //  ORDER_H_
