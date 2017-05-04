

namespace CalibrationPlateChangerClient {
    class Function
    {
        public string Priority;
        public string Sender;
        public string FunctionName;
        public string ReturnType;
        public FunctionRequestParameter[] Parameters;

        public Function()
        {
            
        }
    }

    class FunctionRequest {
        public Function Function;

        public FunctionRequest(string priority, string sender, string functionName,
            string returnType, FunctionRequestParameter[] parameters)
        {
            Function = new Function
            {
                Priority = priority,
                Sender = sender,
                FunctionName = functionName,
                ReturnType = returnType,
                Parameters = parameters
            };
        }

        public FunctionRequest() {

        }
    }
}
