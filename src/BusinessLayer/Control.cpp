#include "Control.h"
#include <fstream>

#define COLLIMATORPOS 99


Control::Control()
{
    /////////////////////////////////////TODO: VERVANGEN ALS HUBERT UITLEZEN GEREED HEEFT
    m_Order = Order();
    m_Config = Config();
    std::vector<Preset> presets = std::vector<Preset>();
    std::vector<int> presetlist;
    presetlist.push_back(10);
    presetlist.push_back(25);
    presetlist.push_back(51);
    Preset p0 = Preset(0,presetlist);
    presets.push_back(p0);
    presetlist.clear();
    presetlist.push_back(15);
    presetlist.push_back(20);
    presetlist.push_back(16);
    Preset p1 = Preset(1,presetlist);
    presets.push_back(p1);
    m_Presets = presets;
    
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
    int driveID = -1;
    std::vector<Plate> drivelist = m_Config.GetDrivelist();
    std::vector<Plate> collimatorList = m_Config.GetCollimatorlist();

    for(int i = 0; i < collimatorList.size(); i++)
    {
        if (collimatorList[i].GetID() == plateid)
        {
            driveID = collimatorList[i].GetDrivePosition();
            break;
        }
    }
    if (driveID < 0)
    {
        for(int i = 0; i < drivelist.size(); i++)
        {
            if (drivelist[i].GetID() == plateid)
            {
                driveID = drivelist[i].GetDrivePosition();
                break;
            }
        }
    }

    if(driveID >= 0)
    {
        Move move(driveID,plateid);
        m_Order.NewMove(move);
        std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;    
    } 
    else
    {
        std::cout << "Drive niet gevonden!" << std::endl;  
    }

}

void Control::PlateToCollimator(int plateid)
{
    Move move(plateid,COLLIMATORPOS);
    m_Order.NewMove(move);
    std::cout << "Control:Moving plate " << plateid << " to drive..." << std::endl;
}

void Control::CancelCurrentOperation()
{
    m_Order.Stop();
    std::cout << "Control:Canceling current operation..." << std::endl;
}

void Control::SetPreset(int presetid)
{
    int status = -1;
    std::vector<int> presetlist;

    ResetSystem();

    for (auto preset : m_Presets) {
        if (preset.GetID() == presetid) {
            status = 1;

            presetlist = preset.GetPlatelist();
            for(int j = 0; j < presetlist.size(); j++)
            {
                PlateToCollimator(presetlist[j]);
            }
            break;
        }
    }

    if (status < 0)
    {
        std::cout << "ERROR -> Preset not found." << std::endl;

    }
    std::cout << "Control:Setting preset " << presetid << "..." << std::endl;
}

void Control::EmergencyStop()
{
    m_Order.Stop();
    std::cout << "Control:Emergency stop..." << std::endl;
}

void Control::ContinueSystem()
{
    m_Order.Start();
    std::cout << "Control:Continueing system..." << std::endl;
}

void Control::ResetSystem()
{
    std::cout << "Control:Resetting system..." << std::endl;
    m_Order.Stop();
    m_Order.Reset();


    std::vector<Plate> collimatorList = m_Config.GetCollimatorlist();
    for(int i = 0; i < collimatorList.size(); i++)
    {
      PlateToDrive(collimatorList[i].GetID());
    }


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
