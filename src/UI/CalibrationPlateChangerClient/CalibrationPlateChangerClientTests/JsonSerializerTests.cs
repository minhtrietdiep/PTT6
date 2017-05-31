using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace CalibrationPlateChangerClient.Tests {
    [TestClass()]
    public class JsonSerializerTests {
        [TestMethod()]
        public void JsonSerializerTest() {
            JsonSerializer serializer = new JsonSerializer();
            Assert.IsNotNull(serializer, "serializer is null");
            Assert.IsInstanceOfType(serializer, typeof(JsonSerializer), "serializer not type of JsonSerializer"); 
        }

        [TestMethod()]
        public void SerializeFunctionRequestParameterTest() {
            JsonSerializer serializer = new JsonSerializer();
            ApiFunctionParameter requestParameter = new ApiFunctionParameter("nameOfParam", "dataTypeOfParam", "valueOfParam");
            string serializedRequestParam = serializer.Serialize(ref requestParameter);
            Assert.AreEqual("{\"Name\":\"nameOfParam\",\"DataType\":\"dataTypeOfParam\",\"Value\":\"valueOfParam\"}", serializedRequestParam, "FunctionRequestParameter incorrectly serialized");
        }

        [TestMethod()]
        public void SerializeFunctionRequestPropertiesTest() {
            JsonSerializer serializer = new JsonSerializer();
            ApiFunctionProperties requestProperties = new ApiFunctionProperties("1", "192.168.0.142", "SetPreset", "void", new ApiFunctionParameter[0]);
            string serializedRequestProperties = serializer.Serialize(ref requestProperties);
            Assert.AreEqual("{\"Priority\":\"1\",\"Sender\":\"192.168.0.142\",\"FunctionName\":\"SetPreset\",\"ReturnType\":\"void\",\"Parameters\":[]}", serializedRequestProperties, "RequestProperties incorrectly serialized");
        }

        [TestMethod()]
        public void SerializeFunctionRequestTest() {
            JsonSerializer serializer = new JsonSerializer();
            ApiFunctionParameter requestParameter = new ApiFunctionParameter("param_1", "int", "123");
            ApiFunctionProperties requestProperties = new ApiFunctionProperties("1", "ip", "MyFunction1", "int", new ApiFunctionParameter[] { requestParameter });
            ApiFunction functionRequest = new ApiFunction(requestProperties);
            string serializedRequest = serializer.Serialize(ref functionRequest);
            Assert.AreEqual("{\"Function\":{\"Priority\":\"1\",\"Sender\":\"ip\",\"FunctionName\":\"MyFunction1\",\"ReturnType\":\"int\",\"Parameters\":[{\"Name\":\"param_1\",\"DataType\":\"int\",\"Value\":\"123\"}]}}", serializedRequest);
        }

        [TestMethod()]
        public void DeserializeTest() {
            JsonSerializer serializer = new JsonSerializer();
            string serializedRequestParam = "{\"Name\":\"nameOfParam\",\"DataType\":\"dataTypeOfParam\",\"Value\":\"valueOfParam\"}";
            ApiFunctionParameter requestParameter = serializer.Deserialize<ApiFunctionParameter>(serializedRequestParam);
            Assert.AreEqual("nameOfParam", requestParameter.Name, "Deserialized RequestParameter has incorrect name");
            Assert.AreEqual("dataTypeOfParam", requestParameter.DataType, "Deserialized RequestParameter has incorrect datatype");
            Assert.AreEqual("valueOfParam", requestParameter.Value, "Deserialized RequestParameter has incorrect value");
        }
    }
}