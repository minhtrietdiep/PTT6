using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient
{
    enum ReturnStatus
    {
        OK,
        ERR_UNKNOWN_FUNC,
        ERR_UNKNOWN,
        ERR_PARSE,
        ERR_HW,
        ERR_TIMEOUT
    }

    class PlateChanger
    {
        private const string m_ServerIp = "192.168.0.137";
        private const int m_ServerPort = 4244;

        private MainForm m_UserInterface;
        private JsonSerializer m_JsonSerializer;
        private CommunicationClient m_TcpClient;
        private List<Preset> m_PresetList;
        private List<Plate> m_CollimatorPlateList;
        private List<Plate> m_DrivePlateList;

        public PlateChanger()
        {
            m_PresetList = new List<Preset>();
            m_CollimatorPlateList = new List<Plate>();
            m_DrivePlateList = new List<Plate>();
            m_UserInterface = new MainForm(SendFunctionRequest);
            m_UserInterface.Shown += UserInterface_Shown;
            m_UserInterface.FormClosed += M_UserInterface_FormClosed;
            m_JsonSerializer = new JsonSerializer();
            m_TcpClient = new CommunicationClient(m_ServerIp, m_ServerPort);
            ConnectToServer();
            Application.Run(m_UserInterface);
        }



        private void M_UserInterface_FormClosed(object sender, FormClosedEventArgs e)
        {
            m_TcpClient.Disconnect();
            Application.Exit();
        }

        private void UserInterface_Shown(object sender, EventArgs e)
        {
            TESTgenerateTestData();
            UpdateUserInterface();
        }

        private void UpdateUserInterface()
        {
            m_UserInterface.BeginInvoke((MethodInvoker)delegate ()
            {
                if (m_CollimatorPlateList != null)
                    m_UserInterface.SetCollimatorPlateList(m_CollimatorPlateList);
                if (m_DrivePlateList != null)
                    m_UserInterface.SetDriverPlateList(m_DrivePlateList);
                if (m_PresetList != null)
                    m_UserInterface.SetPresetList(m_PresetList);
                m_UserInterface.LogFromAnotherThread("UI Updated");
            });
        }

        private int SendFunctionRequest(ApiFunction request)
        {
            string serializedFunctionRequest = m_JsonSerializer.Serialize<ApiFunction>(ref request);
            int retVal = m_TcpClient.Send(serializedFunctionRequest);
            switch (retVal) {
                case 0:
                    return 0;
                case -1:
                    Console.WriteLine("Not connected to server!");
                    break;
                case -2:
                    Console.WriteLine("Socket exception occurred! Connection closed.");
                    break;
                case -3:
                    Console.WriteLine("IO exception occurred! Connection closed.");
                    break;
                case -4:
                    Console.WriteLine("Server closed the connection.");
                    break;
            }
            return -1;
        }

        private void ConnectToServer()
        {
            int result = m_TcpClient.Connect();
            if (result == 0)
            {
                m_UserInterface.LogMessage("Connected to server.");
                m_TcpClient.StartReceiving(OnMessageReceived);
            }
            else if (result < -1)
            {
                m_UserInterface.LogMessage("Could not connect to server");
            }
        }

        private int OnMessageReceived(string message)
        {
            ApiFunction functionResponse = m_JsonSerializer.Deserialize<ApiFunction>(message);
            if (functionResponse == default(ApiFunction) || functionResponse.Function == null || functionResponse.Function.ReturnType != "Response")
            {
                m_UserInterface.LogFromAnotherThread("Invalid data received");
                return -1;
            }
            HandleFunctionResponse(functionResponse);
            return 0;
        }

        private void HandleFunctionResponse(ApiFunction functionResponse)
        {
            ApiFunctionParameter[] parameterList = functionResponse.Function.Parameters;
            foreach (ApiFunctionParameter parameter in parameterList)
            {
                if (parameter.Name == "ReturnValue")
                {
                    try
                    {
                        ReturnStatus status = (ReturnStatus)Enum.Parse(typeof(ReturnStatus), parameter.Value);
                        if (status != ReturnStatus.OK)
                        {
                            ReceivedErrorStatus(status);
                            return;
                        }
                    }
                    catch (ArgumentException ex)
                    {
                        Console.WriteLine(ex);
                        return;

                    }
                    switch (functionResponse.Function.FunctionName)
                    {
                        case "UploadPreset":
                            foreach (ApiFunctionParameter param in parameterList)
                            {
                                if (param.Name == "TBD")
                                    ApplyNewConfiguration(param.Value);                                    
                            }
                            break;
                        case "PlateToCollimator":
                            foreach(ApiFunctionParameter param in parameterList)
                            {
                                if (param.Name == "plateID")
                                    PlateToCollimator(int.Parse(param.Value));
                            }
                            break;
                        case "PlateToDrive":
                            foreach (ApiFunctionParameter param in parameterList)
                            {
                                if (param.Name == "plateID")
                                    PlateToDrive(int.Parse(param.Value));
                            }
                            break;
                        case "ResetSystem":
                            ResetSystem();
                            break;
                        case "SetPreset":
                            foreach (ApiFunctionParameter param in parameterList)
                            {
                                if (param.Name == "presetID")
                                    SetPreset(int.Parse(param.Value));
                            }
                            break;
                        default:
                            m_UserInterface.LogFromAnotherThread("Response: " + functionResponse.Function.FunctionName + " " + parameter.Value);
                            break;
                    }
                    this.UpdateUserInterface();
                }
            }
        }

        private void ApplyNewConfiguration(string config)
        {
            ApiPlateList newPlateList = m_JsonSerializer.Deserialize<ApiPlateList>(config);
            if (newPlateList == default(ApiPlateList))
            {
                List<Preset> newPresetList = m_JsonSerializer.Deserialize<List<Preset>>(config);
                if (newPresetList != default(List<Preset>))
                    m_PresetList = newPresetList;
            }
            else if (newPlateList.PlateList == "m_DriveList")
            {
                m_DrivePlateList = newPlateList.Plates;
            }
            else if (newPlateList.PlateList == "m_CollimatorList")
            {
                m_CollimatorPlateList = newPlateList.Plates;
            }
            UpdateUserInterface();
        }

        private void ReceivedErrorStatus(ReturnStatus status)
        {
            switch (status)
            {
                case ReturnStatus.ERR_UNKNOWN_FUNC:
                    m_UserInterface.LogFromAnotherThread("Request failed: Server can't handle request");
                    break;
                case ReturnStatus.ERR_UNKNOWN:
                    m_UserInterface.LogFromAnotherThread("Request failed: Unknown error appeared on server");
                    break;
                case ReturnStatus.ERR_PARSE:
                    m_UserInterface.LogFromAnotherThread("Request failed: Parsing error on server");
                    break;
                case ReturnStatus.ERR_HW:
                    m_UserInterface.LogFromAnotherThread("Request failed: Hardware error");
                    break;
                case ReturnStatus.ERR_TIMEOUT:
                    m_UserInterface.LogFromAnotherThread("Request failed: Timeout");
                    break;
            }
        }

        private void PlateToCollimator(int plateId)
        {
            foreach(Plate plate in m_DrivePlateList)
            {
                if (plate.GetID() == plateId)
                {
                    m_CollimatorPlateList.Add(plate);
                    m_DrivePlateList.Remove(plate);
                    break;
                }
            }
        }

        private void PlateToDrive(int plateId)
        {
            foreach (Plate plate in m_CollimatorPlateList)
            {
                if (plate.GetID() == plateId)
                {
                    m_DrivePlateList.Add(plate);
                    m_CollimatorPlateList.Remove(plate);
                    break;
                }
            }
        }

        private void SetPreset(int presetId)
        {
            ResetSystem();
            foreach(Preset preset in m_PresetList)
            {
                if (preset.GetID() == presetId)
                {
                    foreach(Plate plate in preset.GetPlates())
                    {
                        PlateToCollimator(plate.GetID());
                    }
                }
            }
        }

        private void ResetSystem()
        {
            foreach(Plate plate in m_CollimatorPlateList)
            {
                m_DrivePlateList.Add(plate);
            }
            m_CollimatorPlateList.Clear();
        }

        private void TESTgenerateTestData()
        {
            m_CollimatorPlateList = new List<Plate>();
            m_DrivePlateList = new List<Plate>();
            m_DrivePlateList.Add(new Plate(1, "Lead", 2.5));
            m_DrivePlateList.Add(new Plate(2, "Lead", 5));
            m_DrivePlateList.Add(new Plate(3, "Alluminium", 3.1));
            m_DrivePlateList.Add(new Plate(4, "Nothing", 2));
            m_DrivePlateList.Add(new Plate(5, "Copper", 0.5));
            m_DrivePlateList.Add(new Plate(6, "Copper", 1));
            m_DrivePlateList.Add(new Plate(7, "A lot", 1.25));
            m_DrivePlateList.Add(new Plate(8, "Random Stuff", 2));
            m_DrivePlateList.Add(new Plate(9, "More stuff", 5.25));
            m_DrivePlateList.Add(new Plate(10, "Plutonium", 1.5));
            m_DrivePlateList.Add(new Plate(11, "Anti-matter", -3));
            m_PresetList = new List<Preset>();
            List<Plate> preset1Plates = new List<Plate>();
            preset1Plates.Add(m_DrivePlateList[0]);
            preset1Plates.Add(m_DrivePlateList[2]);
            preset1Plates.Add(m_DrivePlateList[3]);
            List<Plate> preset2Plates = new List<Plate>();
            preset2Plates.Add(m_DrivePlateList[1]);
            preset2Plates.Add(m_DrivePlateList[2]);
            preset2Plates.Add(m_DrivePlateList[5]);
            List<Plate> preset3Plates = new List<Plate>();
            preset3Plates.Add(m_DrivePlateList[0]);
            preset3Plates.Add(m_DrivePlateList[1]);
            preset3Plates.Add(m_DrivePlateList[4]);
            List<Plate> preset4Plates = new List<Plate>();
            preset3Plates.Add(m_DrivePlateList[5]);
            preset3Plates.Add(m_DrivePlateList[1]);
            preset3Plates.Add(m_DrivePlateList[4]);
            preset3Plates.Add(m_DrivePlateList[8]);
            preset3Plates.Add(m_DrivePlateList[9]);
            preset3Plates.Add(m_DrivePlateList[10]);
            m_PresetList.Add(new Preset(1, "Preset 1", preset1Plates));
            m_PresetList.Add(new Preset(2, "Preset 2", preset2Plates));
            m_PresetList.Add(new Preset(3, "Preset 3", preset3Plates));
            m_PresetList.Add(new Preset(4, "Preset 4", preset3Plates));
        }
    }
}
