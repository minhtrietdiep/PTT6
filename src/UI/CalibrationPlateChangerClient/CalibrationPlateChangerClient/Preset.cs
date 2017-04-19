using System.Collections.Generic;

namespace CalibrationPlateChangerClient {
    public class Preset {
        private int m_ID;
        private string m_Name;
        private List<Plate> m_PlateList;

        public Preset(int id, string name, List<Plate> platelist) {
            m_ID = id;
            m_Name = name;
            m_PlateList = platelist;
        }

        public int GetID() {
            return m_ID;
        }

        public string GetName() {
            return m_Name;
        }

        public List<Plate> GetPlates() {
            return m_PlateList;
        }
    }
}
