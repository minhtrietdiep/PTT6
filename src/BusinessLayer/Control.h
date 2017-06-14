#pragma once

#include <vector>

#include <Const.h>
#include <Logger.h>
#include <Error.h>

#include <Preset.h>
#include <Order.h>
#include <Move.h>
#include <Config.h>
#include <PlateList.h>

#include "../../API/Interfaces/IUIControl.h"
#include "../../API/Interfaces/IRemoteLog.h"

class Control : public IUIControl, public IRemoteLog
{
    private:
        std::vector<Preset> m_Presets;
        Order m_Order;
        Config m_Config;
        const char* m_FileName = "Config/Presets.json";
        Logger m_Logger;

	public:

        Control(std::vector<Preset> presets);
        ErrorCode SetupHardware();
        //IUIControl functions
        std::vector<Preset> GetPresets();
        virtual ~Control();
        virtual  ErrorCode PlateToDrive(int plateid);
        virtual  ErrorCode PlateToCollimator(int plateid);
        virtual  ErrorCode CancelCurrentOperation();
        virtual  ErrorCode SetPreset(int presetid);
        virtual  ErrorCode EmergencyStop();
        virtual  ErrorCode ContinueSystem();
        virtual  ErrorCode ResetSystem();
        virtual  ErrorCode StartSystem();
        virtual std::string UploadPresets();
        virtual std::string UploadDriveState();
        virtual std::string UploadCollimatorState();
        virtual  ErrorCode LoadPresets();
        

        //IRemoteLog functions
        virtual  ErrorCode DownloadLog(int logfilenumber);
};
