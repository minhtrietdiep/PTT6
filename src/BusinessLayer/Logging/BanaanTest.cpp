#include "BanaanTest.h"
#include "Logger.h"

BanaanTest::BanaanTest() {
	logger = new Logger(VERSION, LOG_PRINTLEVEL, LOG_PATH);

    DoeDingen();
}

BanaanTest::~BanaanTest() {
	delete logger;
}

void BanaanTest::DoeDingen() {
    logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "Dingen doet!");
}
