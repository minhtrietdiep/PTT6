#include "Headers/Control.h"
#include <../sharedlibs/include/rapidjson/document.h>
#include <../sharedlibs/include/rapidjson/istreamwrapper.h>
#include <../sharedlibs/include/rapidjson/writer.h>
#include <../sharedlibs/include/rapidjson/stringbuffer.h>
#include <../sharedlibs/include/rapidjson/filereadstream.h>
#include <fstream>



Control::Control()
{
    m_Order = new Order();
    m_Config = new Config();

    
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
