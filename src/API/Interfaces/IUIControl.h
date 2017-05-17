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
        virtual ErrorCode PlateToDrive(int plateid)=0; //Move the plate with the corresponding plateid to the storage
        virtual ErrorCode PlateToCollimator(int plateid)=0; //Move the plate with the corresponding plateid to the collimator
        virtual ErrorCode CancelCurrentOperation()=0;
        virtual ErrorCode SetPreset(int presetid)=0;
        virtual ErrorCode EmergencyStop()=0;
        virtual ErrorCode ContinueSystem()=0;
        virtual ErrorCode ResetSystem()=0;
        virtual ErrorCode UploadConfig()=0;
        virtual ErrorCode DownloadConfig()=0;
};

#endif  //  IUICONTROL_H_
