#include "Headers/Control.h"
#include <fstream>
#include "../sharedlibs/include/rapidjson/document.h"

Control::Control(std::vector<Preset> presets)
{
    m_Presets = presets;
    std::fstream fs;
    fs.open(m_FileName, std::fstream::in);

    for (size_t i = 0; i < 3; ++i) 
    {
        rapidjson::Value item(i);
       // fs.push_back(&item);
        std::cout << item.GetInt() << std::endl;
    }

    fs.close();

}

Control::~Control()
{

}

std::vector<Preset> Control::GetPresets()
{
    return m_Presets;
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
