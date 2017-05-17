#ifndef IUICONTROL_H_
#define IUICONTROL_H_

#include <iostream>
#include <vector>
#include <Error.h>
class IUIControl 
{
    private:


    public:
        virtual ~IUIControl(){}
        virtual void PlateToDrive(int plateid)=0; //Move the plate with the corresponding plateid to the storage
        virtual void PlateToCollimator(int plateid)=0; //Move the plate with the corresponding plateid to the collimator
        virtual void CancelCurrentOperation()=0;
        virtual void SetPreset(int presetid)=0;
        virtual void EmergencyStop()=0;
        virtual void ContinueSystem()=0;
        virtual void ResetSystem()=0;
        virtual ErrorCode UploadConfig()=0;
        virtual ErrorCode DownloadConfig()=0;
};

#endif  //  IUICONTROL_H_
