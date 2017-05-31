using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// Can be used as a function request
    /// This class must be public, otherwise serialization won't work
    /// </summary>
    public class ApiFunction
    {

        public ApiFunctionProperties Function;

        public ApiFunction(ApiFunctionProperties request)
        {
            Function = request;
        }

        public ApiFunction()
        {

        }
    }
}
