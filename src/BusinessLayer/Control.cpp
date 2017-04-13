#include "Headers/Control.h"


Control::Control(std::vector<Preset> presets)
{
    m_Presets = presets;
}

Control::~Control()
{

}

void Control::PlateToDrive(int plateid)
{
	
}

void Control::PlateToCollimator(int plateid)
{
    
}

void Control::CancelCurrentOperation()
{
    
}

void Control::SetPreset(int presetid)
{

}

void Control::EmergencyStop()
{
    
}

void Control::ContinueSystem()
{
    
}

void Control::ResetSystem()
{
    
}

void Control::UploadConfig()
{
    
}

void Control::DownloadConfig()
{
    
}

void Control::DownloadLog(int logfilenumber)
{

}



/* OLD CONTOL.H
void Control::SendCommands()
{
	
}

void Control::RecieveCommands()
{
	
}
*/