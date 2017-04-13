#pragma once

#include "Logger.h"

class BanaanTest {
private:
    Logger logger;

public:
    BanaanTest(const Logger &logger);
    ~BanaanTest();

    void DoeDingen();
};
