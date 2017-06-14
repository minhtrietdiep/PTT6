#pragma once

#include <iostream>
#include <vector>

#include <Const.h>
#include <Error.h>
#include <Logger.h>

#include <Move.h>
#include <HAL.h>

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
        ErrorCode Reset();
        ErrorCode SetupHardware();
        ErrorCode PlateToDrive(int driveID);
        ErrorCode PlateToCol(int driveID);
};
