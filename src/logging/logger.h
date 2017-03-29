#pragma once

class Logger {
public:
    Logger();
    ~Logger();
    void Write(std::string moduleName, 
	       std::string functionName,
	       Result functionResult);
private:
	std::string fileName;
	std::string version;
	
	std::string getTime();
}

