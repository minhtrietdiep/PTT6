#ifndef CONTROL_H_
#define CONTROL_H_

#include <iostream>
#include <vector>

class Control 
{
    private:


    public:
        Control();
        void SendCommands();
        void RecieveCOmmands();
        void MoveTo();
        void CancelCurrentOperation();
        void EmergencyStop();
        void ResetSystem();
        void ContinueSystem();
        void UploadConfig();
        void DownloadConfig();
};

#endif  //  CONTROL_H_
