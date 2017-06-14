#pragma once

#include <Const.h>
#include <Error.h>
#include <Logger.h>

class Drive
{
    public:
        Drive(int driveid, std::string movecommand);
        ~Drive();
        ErrorCode SetupHardware();
        ErrorCode OpenDrive();
        ErrorCode CloseDrive();
        int GetDriveID();
        std::string GetDriveMoveCommand();

        //Coordinates GetDriveCoordinates();
        void SetFilePathDrive0Value(std::string path);
        void SetFilePathDrive1Value(std::string path);
        void SetFilePathDrive2Value(std::string path);
        void SetFilePathDrive3Value(std::string path);
        void SetFilePathDrive4Value(std::string path);
        void SetFilePathDrive0Dir(std::string path);
        void SetFilePathDrive1Dir(std::string path);
        void SetFilePathDrive2Dir(std::string path);
        void SetFilePathDrive3Dir(std::string path);
        void SetFilePathDrive4Dir(std::string path);
    private:
        ErrorCode ToggleDrive();
        int m_DriveID;
        std::string m_MoveCommand;
        //Coordinates m_Positions;
        std::string m_Drive0ValuePath;
        std::string m_Drive1ValuePath;
        std::string m_Drive2ValuePath;
        std::string m_Drive3ValuePath;
        std::string m_Drive4ValuePath;
        std::string m_Drive0DirPath;
        std::string m_Drive1DirPath;
        std::string m_Drive2DirPath;
        std::string m_Drive3DirPath;
        std::string m_Drive4DirPath;
        Logger m_Logger;
};
