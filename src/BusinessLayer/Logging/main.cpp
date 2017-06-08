#include <iostream>
#include <Const.h>
#include <Logger.h>

class Testing {
public:
    Testing();
    ~Testing();
    void DoeDingen();
private:
    Logger m_Logger;
};

Testing::Testing() : m_Logger(VERSION,Logger::Severity::DEBUG,LOG_PATH) {
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "C'tor called");
}

Testing::~Testing() {
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "D'tor called");
}

void Testing::DoeDingen() {
    m_Logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "DEBUG");
    m_Logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "INFO");
    m_Logger.Write(Logger::Severity::WARNING, __PRETTY_FUNCTION__, "WARNING");
    m_Logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "ERROR");
}


class Testing2 {
public:
    Testing2();
    ~Testing2();
    void DoeDingen();
private:
    Logger *m_Logger;
};

Testing2::Testing2() {
    m_Logger = new Logger(VERSION,Logger::Severity::DEBUG,LOG_PATH);
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "C'tor2 called");
}

Testing2::~Testing2() {
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "D'tor2 called");
    delete m_Logger;
}

void Testing2::DoeDingen() {
    m_Logger->Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "DEBUG");
    m_Logger->Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "INFO");
    m_Logger->Write(Logger::Severity::WARNING, __PRETTY_FUNCTION__, "WARNING");
    m_Logger->Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "ERROR");
}


int main() {
    Logger logger(VERSION,Logger::Severity::DEBUG,LOG_PATH);
    logger.Write(Logger::Severity::DEBUG, __PRETTY_FUNCTION__, "DEBUG");
    logger.Write(Logger::Severity::INFO, __PRETTY_FUNCTION__, "INFO");
    logger.Write(Logger::Severity::WARNING, __PRETTY_FUNCTION__, "WARNING");
    logger.Write(Logger::Severity::ERROR, __PRETTY_FUNCTION__, "ERROR");
    
    Testing testing;
    testing.DoeDingen();
    
    Testing2 testing2;
    testing2.DoeDingen();

    Testing *testingPtr = new Testing();
    testingPtr->DoeDingen();
    delete testingPtr;

    Testing2 *testingPtr2 = new Testing2();
    testingPtr2->DoeDingen();
    delete testingPtr2;

    return 0;
}
