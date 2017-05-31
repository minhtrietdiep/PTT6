using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// Can be used as a plate
    /// This class must be public, otherwise serialization won't work
    /// </summary>

    public class ApiPlate
    {
        public int m_ID { get; set; }
        public int m_DrivePosition { get; set; }
        public int m_CollimatorPosition { get; set; }
        public string m_Property { get; set; }
        public double m_Thickness { get; set; }

        public ApiPlate()
        {

        }
    }
}
