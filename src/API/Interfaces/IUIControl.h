#ifndef IUICONTROL_H_
#define IUICONTROL_H_

#include <iostream>
#include <vector>

class IUIControl 
{
    private:


    public:
        virtual void PlateToDrive(int plateid)=0;
        virtual void PlateToCollimator(int plateid)=0;
        virtual void CancelCurrentOperation()=0;
        virtual void EmergencyStop()=0;
        virtual void ContinueSystem()=0;
        virtual void ResetSystem()=0;
        virtual void UploadConfig()=0;
        virtual void DownloadConfig()=0;
};

#endif  //  IUICONTROL_H_
