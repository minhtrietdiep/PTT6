

namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// Can be used as function request properties
    /// This class must be public, otherwise serialization won't work
    /// </summary>
    public class ApiFunctionProperties
    {
        public string Priority;
        public string Sender;
        public string FunctionName;
        public string ReturnType;
        public ApiFunctionParameter[] Parameters;

        public ApiFunctionProperties(string priority, string sender, string functionName,
            string returnType, ApiFunctionParameter[] parameters)
        {
            this.Priority = priority;
            this.Sender = sender;
            this.FunctionName = functionName;
            this.ReturnType = returnType;
            this.Parameters = parameters;
        }

        public ApiFunctionProperties()
        {

        }
    }
}
