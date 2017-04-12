#ifndef CONTROL_H_
#define CONTROL_H_

#include <iostream>
#include <vector>
#include "../../API/Interfaces/IUIControl.h"
#include "../../API/Interfaces/IRemoteLog.h"

class Control : public IUIControl, public IRemoteLog
{
	private:

	public:
        void PlateToDrive(int plateid);
        void PlateToCollimator(int plateid);
        void CancelCurrentOperation();
        void EmergencyStop();
        void ContinueSystem();
        void ResetSystem();
        void UploadConfig();
        void DownloadConfig();
        void DownloadLog(int logfilenumber);
};

#endif  //  CONTROL_H_
