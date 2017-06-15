

namespace CalibrationPlateChangerClient {
    class FunctionRequest {
        public string Priority;
        public string Sender;
        public string FunctionName;
        public string ReturnType;
        public FunctionRequestParameter[] Parameters;

        public FunctionRequest(string priority, string sender, string functionName,
            string returnType, FunctionRequestParameter[] parameters) {
            this.Priority = priority;
            this.Sender = sender;
            this.FunctionName = functionName;
            this.ReturnType = returnType;
            this.Parameters = parameters;
        }

        public FunctionRequest() {

        }
    }
}
