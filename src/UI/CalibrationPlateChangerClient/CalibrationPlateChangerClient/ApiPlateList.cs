using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// This class must be public, otherwise serialization won't work
    /// </summary>

    public class ApiPlateList
    {
        public string Name { get; set; }
        public List<ApiPlate> Plates { get; set; }

        public ApiPlateList()
        {

        }
    }
}
