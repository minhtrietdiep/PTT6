Logger::Logger(const std::string &fileName,
			   const std::string &version) :
	fileName(fileName),
	systemVersion(systemVersion)
{
	writeHeader();
	Write("Logger", "Initialize", "OK");
}

Logger::~Logger() {}

void Logger::Write(std::string moduleName, 
	       std::string functionName,
	       Result functionResult) {
#ifdef _DEBUG_
	printf("Bla");
#endif
	// Logging format:
	// TIME;VERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n
	// date/time;systemVersion;module_name;function_name;function_result;\n
	
}

Result Logger::writeHeader() {
	// Literally write this:
	// "TIMESTAMP;SYSTEMVERSION;MODULENAME;FUNCTIONCALL;RETURNVALUE;\n"
	
	return Success;
}

std::string getTime() {
	// do time shizzle
	return std::string();
}
