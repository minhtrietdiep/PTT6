#include "Control.h"
#include <fstream>



Control::Control(std::vector<Preset> presets)
{
    
}

Control::~Control()
{

}

std::vector<Preset> Control::GetPresets()
{
    std::cout << "Control:Getting presets..." << std::endl;
    return m_Presets;
}

void Control::PlateToDrive(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;
}

void Control::PlateToCollimator(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to collimator..." << std::endl;
}

void Control::CancelCurrentOperation()
{
    std::cout << "Control:Canceling current operation..." << std::endl;
}

void Control::SetPreset(int presetid)
{
    std::cout << "Control:Setting preset " << presetid << "..." << std::endl;
}

void Control::EmergencyStop()
{
    std::cout << "Control:Emergency stop..." << std::endl;
}

void Control::ContinueSystem()
{
    std::cout << "Control:Continueing system..." << std::endl;
}

void Control::ResetSystem()
{
    std::cout << "Control:Resetting system..." << std::endl;
}

void Control::UploadConfig()
{
    std::cout << "Control:Uploading config..." << std::endl;
}

void Control::DownloadConfig()
{
    std::cout << "Control:Downloading config..." << std::endl;
}

void Control::DownloadLog(int logfilenumber)
{
    std::cout << "Control:Downloading log " << logfilenumber << "..." << std::endl;
}



/* OLD CONTOL.H
void Control::SendCommands()
{
    
}

void Control::RecieveCommands()
{
    
}
*/
