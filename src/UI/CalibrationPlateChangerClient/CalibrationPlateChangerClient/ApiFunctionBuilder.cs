using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    class ApiFunctionBuilder : IPlateChanger
    {

        private const string m_ServerNetwork = "192.168.0.";

        public ApiFunction CancelCurrentOperation()
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[0];
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("1", ipAddress, "CancelCurrentOperation", "Request", parameters));
            return function;
        }

        public ApiFunction ContinueSystem()
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[0];
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("1", ipAddress, "ContinueSystem", "Request", parameters));
            return function;
        }

        public ApiFunction DownloadConfig()
        {
            throw new NotImplementedException();
        }

        public ApiFunction EmergencyStop()
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[0];
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("2", ipAddress, "EmergencyStop", "Request", parameters));
            return function;
        }

        public ApiFunction PlateToCollimator(int plateID)
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[1];
            parameters[0] = new ApiFunctionParameter("plateID", "int", plateID.ToString());
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("0", ipAddress, "PlateToCollimator", "Request", parameters));
            return function;
        }

        public ApiFunction PlateToDrive(int plateID)
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[1];
            parameters[0] = new ApiFunctionParameter("plateID", "int", plateID.ToString());
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("0", ipAddress, "PlateToDrive", "Request", parameters));
            return function;
        }

        public ApiFunction ResetSystem()
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[0];
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("0", ipAddress, "ResetSystem", "Request", parameters));
            return function;
        }

        public ApiFunction SetPreset(int presetID)
        {
            ApiFunctionParameter[] parameters = new ApiFunctionParameter[1];
            parameters[0] = new ApiFunctionParameter("presetID", "int", presetID.ToString());
            string ipAddress = GetLocalIPAddress();
            ApiFunction function = new ApiFunction(new ApiFunctionProperties("0", ipAddress, "SetPreset", "Request", parameters));
            return function;
        }

        public ApiFunction UploadConfig()
        {
            throw new NotImplementedException();
        }



        private string GetLocalIPAddress()
        {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    string[] ipNrsServer = m_ServerNetwork.Split('.');
                    string[] ipNrsHost = ip.ToString().Split('.');
                    if (ipNrsServer[0] == ipNrsHost[0] && ipNrsServer[1] == ipNrsHost[1] && ipNrsServer[2] == ipNrsHost[2])
                        return ip.ToString();
                }
            }
            //throw new Exception("Local IP Address Not Found!");
            return "";
        }
    }
}
