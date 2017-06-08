#pragma once 

#include <string>

#include <Const.h>
#include <Error.h>
#include <Logger.h>

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
