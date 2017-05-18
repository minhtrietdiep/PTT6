
namespace CalibrationPlateChangerClient {
    /// <summary>
    /// Can be used as a function request parameter
    /// This class must be public, otherwise serialization won't work
    /// </summary>
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
