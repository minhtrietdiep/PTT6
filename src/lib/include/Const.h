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

#define COL_PREP_POS        "#0P650S1400#2P1969S1400#3P535S1400#4P1801S1400\r"
#define COL_POS             "#0P650S1400#2P1850S2000#3P1245S1400#4P670S1400\r"
#define DRIVE_PREP_POS      "#0P2440S1400#2P1969S1400#3P535S700#4P1801S1400\r"
#define DRIVE0_POS          "#0P2440S1400#2P2070S2000#3P1325S14000#4P861S1400\r"
#define DRIVE1_POS          "#0P2440S1400#2P2120S2000#3P1209S2000#4P1040S1400\r"
#define DRIVE2_POS          "#0P2440S1400#2P2113S2000#3P1030S2000#4P1185S1400\r"
#define DRIVE3_POS          "#0P2440S1400#2P2005S2000#3P870S2000#4P1240S1400\r"
#define DRIVE4_POS          "#0P2440S1400#2P1849S2000#3P590S2000#4P1290S1400\r"
#define HOME_POS            "#0P1545S1400#2P1969S1400#3P535S1400#4P1801S1400\r"
#define BAUDRATE            115200