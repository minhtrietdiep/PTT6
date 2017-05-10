#include "Control.h"
#include <fstream>

#include <thread>

Control::Control(std::vector<Preset> presets)
{

}

Control::~Control()
{

}

std::vector<Preset> Control::GetPresets()
{
    std::cout << "Control:Getting presets..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(0));
    return m_Presets;
}

void Control::PlateToDrive(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Control::PlateToCollimator(int plateid)
{
    std::cout << "Control:Moving plate " << plateid << " to collimator..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Control::CancelCurrentOperation()
{
    std::cout << "Control:Canceling current operation..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Control::SetPreset(int presetid)
{
    std::cout << "Control:Setting preset " << presetid << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

void Control::EmergencyStop()
{
    std::cout << "Control:Emergency stop..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(0));
}

void Control::ContinueSystem()
{
    std::cout << "Control:Continueing system..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Control::ResetSystem()
{
    std::cout << "Control:Resetting system..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void Control::UploadConfig()
{
    std::cout << "Control:Uploading config..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Control::DownloadConfig()
{
    std::cout << "Control:Downloading config..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Control::DownloadLog(int logfilenumber)
{
    std::cout << "Control:Downloading log " << logfilenumber << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}



/* OLD CONTOL.H
void Control::SendCommands()
{
    
}

void Control::RecieveCommands()
{
    
}
*/
