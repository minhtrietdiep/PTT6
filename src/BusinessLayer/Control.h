#pragma once

#include <iostream>
#include <vector>
#include <Error.h>
#include "../../API/Interfaces/IUIControl.h"
#include "../../API/Interfaces/IRemoteLog.h"
#include "Preset.h"
#include "Order.h"
#include "Move.h"
#include "Config.h"


class Control : public IUIControl, public IRemoteLog
{
        private:
        std::vector<Preset> m_Presets;
        Order m_Order;
        Config m_Config;
        const char* m_FileName = "Config/Presets.json";

	public:

        Control(std::vector<Preset> presets);
        //IUIControl functions
        std::vector<Preset> GetPresets();
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
