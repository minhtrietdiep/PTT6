#ifndef CONTROL_H_
#define CONTROL_H_

#include <iostream>
#include <vector>
#include "Preset.h"
#include "../../API/Interfaces/IUIControl.h"
#include "../../API/Interfaces/IRemoteLog.h"
#include "../../lib/ErrorCode.h"

class Control : public IUIControl, public IRemoteLog
{
	private:
        std::vector<Preset> m_Presets;
        const char* m_FileName = "Config/Presets.json";
        

	public:

        Control(std::vector<Preset> presets);
        std::vector<Preset> GetPresets();

        //IUIControl functions
        virtual ~Control();
        virtual void PlateToDrive(int plateid);
        virtual void PlateToCollimator(int plateid);
        virtual void CancelCurrentOperation();
        virtual void SetPreset(int presetid);
        virtual void EmergencyStop();
        virtual void ContinueSystem();
        virtual void ResetSystem();
        virtual ErrorCode UploadConfig();
        virtual ErrorCode DownloadConfig();
        

        //IRemoteLog functions
        virtual ErrorCode DownloadLog(int logfilenumber);
};

#endif  //  CONTROL_H_
