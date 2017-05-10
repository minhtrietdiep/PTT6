#include "Headers/Control.h"
#include <../sharedlibs/include/rapidjson/document.h>
#include <../sharedlibs/include/rapidjson/istreamwrapper.h>
#include <../sharedlibs/include/rapidjson/writer.h>
#include <../sharedlibs/include/rapidjson/stringbuffer.h>
#include <../sharedlibs/include/rapidjson/filereadstream.h>
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

    //////////////////////////////////////TODO: VERVANGEN ALS HUBERT UITLEZEN GEREED HEEFT
    
    /*FILE* fp = fopen(m_FileName, "r"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);

printf("PlateList = %s\n", d["PlateList"].GetString());

    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    std::cout << "hoi" << std::endl;

    fclose(fp);
    
        
    std::printf("test\n");
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";


    //std::ifstream ifs(m_FileName);
    //rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document d;
    d.ParseStream(json);    
    
    assert(d.IsObject());
    std::printf("test1\n");
    //assert(d.HasMember("Preset"));
    //assert(d["Preset"].IsString());
    //printf("Preset = %s\n", d["Preset"].GetString());

    

        // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    const char* json1 = "{\"hello\": \"world\",\"t\": true ,\"f\": false,\"n\": null,\"i\": 123,\"pi\": 3.1416,\"a\": [1, 2, 3, 4]}";

    Document d;
    d.Parse(json);

    Document document;
    document.Parse(json1);
    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    std::cout << "hoi" << std::endl;


    assert(document.HasMember("hello"));
    assert(document["hello"].IsString());
    printf("hello = %s\n", document["hello"].GetString());
*/
    
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
