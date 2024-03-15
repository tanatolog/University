using System;
using System.Collections.Generic;

namespace IO_laba_2
{
    public class SimplexResult
    {
        public List<double> vec;
        public double f;

        public SimplexResult()
        {
            vec = new List<double>();
        }

        public void Print()
        {
            string s = "";
            Console.Write("Optimal solution found:\nx = {");
            foreach (var item in vec)
            {
                s = string.Format("{0} {1,5:F3}", s, item);
            }
            Console.Write(s + " }");
            Console.WriteLine("\nObjective function value: " + $"{f:F}");

        }
    }
}
