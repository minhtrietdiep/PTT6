using System;

namespace CalibrationPlateChangerClient {
    class PlateChangerAPI : IPlateChangerAPI {
        private JsonSerializer jsonSerializer;
        private CommunicationClient tcpClient;

        public PlateChangerAPI(string serverIp, int serverPort) {
            jsonSerializer = new JsonSerializer();
            tcpClient = new CommunicationClient(serverIp, serverPort);
            tcpClient.Connect();
        }

        public int PlateToDrive(int plateID) {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[1];
            parameters[0] = new FunctionRequestParameter("plateID", "Int", plateID.ToString());
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("0", ipAddress, "PlateToDrive", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int PlateToCollimator(int plateID) {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[1];
            parameters[0] = new FunctionRequestParameter("plateID", "Int", plateID.ToString());
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("0", ipAddress, "PlateToCollimator", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int SetPreset(int presetID) {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[1];
            parameters[0] = new FunctionRequestParameter("presetID", "Int", presetID.ToString());
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("0", ipAddress, "SetPreset", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int CancelCurrentOperation() {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[0];
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("1", ipAddress, "CancelCurrentOperation", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int EmergencyStop() {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[0];
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("2", ipAddress, "EmergencyStop", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int ContinueSystem() {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[0];
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("1", ipAddress, "ContinueSystem", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }

        public int ResetSystem() {
            FunctionRequestParameter[] parameters = new FunctionRequestParameter[0];
            string ipAddress = tcpClient.GetLocalIPAddress();
            FunctionRequest functionRequest = new FunctionRequest("0", ipAddress, "ResetSystem", "void", parameters);
            if (SendFunctionRequest(functionRequest) == 0) {
                return 0;
            }
            return -1;
        }        

        public int UploadConfig() {
            throw new NotImplementedException();
        }

        public int DownloadConfig() {
            throw new NotImplementedException();
        }

        private int SendFunctionRequest(FunctionRequest functionRequest) {
            string serializedFunctionRequest = jsonSerializer.Serialize<FunctionRequest>(ref functionRequest);
            int retVal = tcpClient.Send(serializedFunctionRequest);
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

        
    }
}
