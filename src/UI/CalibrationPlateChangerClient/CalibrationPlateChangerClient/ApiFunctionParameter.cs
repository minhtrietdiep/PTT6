
namespace CalibrationPlateChangerClient {
    /*Everything must be public for JSON serializer*/

    public class ApiFunctionParameter
    {
        public string Name;
        public string DataType;
        public string Value;

        public ApiFunctionParameter(string name, string dataType, string value)
        {
            this.Name = name;
            this.DataType = dataType;
            this.Value = value;
        }

        public ApiFunctionParameter()
        {

        }
    }
}
