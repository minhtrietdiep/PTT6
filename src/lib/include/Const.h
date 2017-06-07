#pragma once 

#define MAX_MESSAGE_SIZE 4096
#define MQ_NAME_RECEIVED_MESSAGES "/ReceivedMessages"
#define MQ_NAME_SEND_MESSAGES "/SendMessages"
#define MQ_MESSAGE_PRIORITY 0
#define MQ_MAX_MESSAGE 10

#define LOG_PRINTLEVEL Logger::Severity::DEBUG
#define LOG_FOLDER "./logs/"
#define LOG_PATH "./logs/things.csv"

#define VERSION "0.0.1"

#define ARMPATH "/dev/ttyUSB0"

#define DRIVE0VALUEPATH "/sys/class/gpio/gpio30/value"
#define DRIVE1VALUEPATH "/sys/class/gpio/gpio60/value"
#define DRIVE2VALUEPATH "/sys/class/gpio/gpio31/value"
#define DRIVE3VALUEPATH "/sys/class/gpio/gpio50/value"
#define DRIVE4VALUEPATH "/sys/class/gpio/gpio48/value"

#define DRIVE0DIRPATH "/sys/class/gpio/gpio30/direction"
#define DRIVE1DIRPATH "/sys/class/gpio/gpio60/direction"
#define DRIVE2DIRPATH "/sys/class/gpio/gpio31/direction"
#define DRIVE3DIRPATH "/sys/class/gpio/gpio50/direction"
#define DRIVE4DIRPATH "/sys/class/gpio/gpio48/direction"

#define VACUUMVALUEPATH "/sys/class/gpio/gpio51/value"
#define VACUUMDIRPATH "/sys/class/gpio/gpio51/direction"

#define VALVEVALUEPATH "/sys/class/gpio/gpio5/value"
#define VALVEDIRPATH "/sys/class/gpio/gpio5/direction"