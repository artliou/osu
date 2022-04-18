using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Feature1
{
    public class Class1
    {
        public bool someFunction1(int a, int b)
        {
            return (a < b); 
        }

        public bool someFunction2(int a, int b)
        {
            return someFunction3(a, b);
        }

        private bool someFunction3(int a, int b)
        {
            return (a == b);
        }
    }
}
