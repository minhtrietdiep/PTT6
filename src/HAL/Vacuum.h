#ifndef VACUUM_H_
#define VACUUM_H_

#include "Error.h"

#include <Logger.h>
#include <Const.h>

#include <string>

class Vacuum
{
    public:
        Vacuum();
        ~Vacuum();
        ErrorCode EnableVacuum();
        ErrorCode DisableVacuum();
        ErrorCode SetupHardware();
        void SetFilePathVacuumValue(std::string path);
        void SetFilePathVacuumDir(std::string path);
        void SetFilePathValveValue(std::string path);
        void SetFilePathValveDir(std::string path);
    private:
        ErrorCode FileCheck(std::ofstream &f, std::string functionname);
        int m_VacuumStatus;
        Logger *m_Logger;
        std::string m_VacuumValuePath;
        std::string m_VacuumDirPath;
        std::string m_ValveValuePath;
        std::string m_ValveDirPath;
};

#endif  //  VACUUM_H_