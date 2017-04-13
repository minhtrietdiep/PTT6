#pragma once

/*
 * This module demos stuff
 */

#include "Logger.h"
#include "Const.h"

class BanaanTest {
private:
    Logger logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

public:
    BanaanTest();
    ~BanaanTest();

    void DoeDingen();
};
