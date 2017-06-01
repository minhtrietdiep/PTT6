#pragma once

#include <iostream>
#include <vector>
#include <Error.h>
#include <Const.h>
#include "../../API/Interfaces/IUIControl.h"
#include "../../API/Interfaces/IRemoteLog.h"
#include "Preset.h"
#include "Order.h"
#include "Move.h"
#include "Config.h"
#include <Logger.h>
#include <PlateList.h>

class Control : public IUIControl, public IRemoteLog
{
        private:
        std::vector<Preset> m_Presets;
        Order m_Order;
        Config m_Config;
        const char* m_FileName = "Config/Presets.json";
        Logger *m_Logger;

	public:

        Control(std::vector<Preset> presets);
        ErrorCode SetupHardware();
        //IUIControl functions
        std::vector<Preset> GetPresets();
        virtual ~Control();
        virtual enum ErrorCode PlateToDrive(int plateid);
        virtual enum ErrorCode PlateToCollimator(int plateid);
        virtual enum ErrorCode CancelCurrentOperation();
        virtual enum ErrorCode SetPreset(int presetid);
        virtual enum ErrorCode EmergencyStop();
        virtual enum ErrorCode ContinueSystem();
        virtual enum ErrorCode ResetSystem();
        virtual enum ErrorCode StartSystem();
        virtual std::string UploadPresets();
        virtual std::string UploadDriveState();
        virtual std::string UploadCollimatorState();
        virtual enum ErrorCode LoadPresets();
        

        //IRemoteLog functions
        virtual enum ErrorCode DownloadLog(int logfilenumber);
};
