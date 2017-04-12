#ifndef IUICONTROL_H_
#define IUICONTROL_H_

#include <iostream>
#include <vector>

class IUIControl 
{
    private:


    public:
        virtual void PlateToDrive(int plateid);
        virtual void PlateToCollimator(int plateid);
        virtual void CancelCurrentOperation();
        virtual void EmergencyStop();
        virtual void ContinueSystem();
        virtual void ResetSystem();
        virtual void UploadConfig();
        virtual void DownloadConfig();
};

#endif  //  IUICONTROL_H_
