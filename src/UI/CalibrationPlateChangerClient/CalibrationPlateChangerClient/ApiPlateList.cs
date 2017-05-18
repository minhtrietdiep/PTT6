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
        public string PlateList;
        public List<Plate> Plates;

        public ApiPlateList(string plateList, List<Plate> plates)
        {
            this.PlateList = plateList;
            this.Plates = plates;
        }

        public ApiPlateList()
        {
            
        }
    }
}
