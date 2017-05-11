using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalibrationPlateChangerClient
{
    /*Everything must be public for JSON serializer*/

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
