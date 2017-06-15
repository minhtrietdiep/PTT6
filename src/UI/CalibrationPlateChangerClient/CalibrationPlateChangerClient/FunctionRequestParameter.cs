
namespace CalibrationPlateChangerClient {
    class FunctionRequestParameter {
        public string Name;
        public string DataType;
        public string Value;

        public FunctionRequestParameter(string name, string dataType, string value) {
            this.Name = name;
            this.DataType = dataType;
            this.Value = value;
        }

        public FunctionRequestParameter() {

        }
    }
}
