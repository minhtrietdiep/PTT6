#pragma once

class Logger {
public:
    Logger();
    ~Logger();
    void write(std::string moduleName, 
	       std::string functionName,
	       Result functionResult);

}

