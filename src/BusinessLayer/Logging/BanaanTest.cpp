#include "BanaanTest.h"
#include "Logger.h"

BanaanTest::BanaanTest(const Logger &logger) : 
    logger(logger) {
        DoeDingen();
}

BanaanTest::~BanaanTest() {}

void BanaanTest::DoeDingen() {
    logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "Hello");
}
