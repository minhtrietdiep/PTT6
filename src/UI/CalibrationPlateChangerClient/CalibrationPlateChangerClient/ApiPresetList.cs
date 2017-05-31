using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// These classas must be public, otherwise serialization won't work
    /// </summary>

    public class MPlateID
    {
        public int ID { get; set; }
    }

    public class PresetList
    {
        public int m_PresetID { get; set; }
        public string m_PresetName { get; set; }
        public List<MPlateID> m_PlateIDs { get; set; }
    }

    public class ApiPresetList
    {
        public string Name { get; set; }
        public List<PresetList> PresetList { get; set; }
    }
}
