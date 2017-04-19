using System;
using System.Web.Script.Serialization;

namespace CalibrationPlateChangerClient {
    class JsonSerializer
    {
        private JavaScriptSerializer m_Serializer;

        public JsonSerializer() {
            m_Serializer = new JavaScriptSerializer();
        }

        public string Serialize<T>(ref T data) {
            string serializedData = null;
            try {
                serializedData = m_Serializer.Serialize(data);
            }
            catch (InvalidOperationException ex) {
                Console.WriteLine(ex);
            }
            return serializedData;
        }

        public T Deserialize<T>(string serializedData) {
            T deserializedData = default(T);
            try {
                deserializedData = m_Serializer.Deserialize<T>(serializedData);
            }
            catch (InvalidOperationException ex) {
                Console.WriteLine(ex);
            }
            return deserializedData;
        }
    }
}
