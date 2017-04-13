#include "BanaanTest.h"
#include "Logger.h"

BanaanTest::BanaanTest() {
    DoeDingen();
}

BanaanTest::~BanaanTest() {}

void BanaanTest::DoeDingen() {
    logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "Dingen doet!");
}
