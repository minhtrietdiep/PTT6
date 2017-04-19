
namespace CalibrationPlateChangerClient {
    public class Plate {
        private int m_ID;
        private string m_Properties;
        private double m_Thickness;

        public Plate(int id, string properties, double thickness) {
            m_ID = id;
            m_Properties = properties;
            m_Thickness = thickness;
        }

        public int GetID() {
            return m_ID;
        }

        public string GetProperties() {
            return m_Properties;
        }

        public double GetThickness() {
            return m_Thickness;
        }

        public override string ToString() {
            return m_Properties + ": " + m_Thickness + "cm";
        }
    }
}
