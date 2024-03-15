using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IO_laba_6
{
    class Program
    {
        static void Main(string[] args)
        {
            string Task0 = @"
            x: 1, 3, 6 ;
            f: 1, 5, 4 ;
            f: 2, 3, 1 ;
            f: 7, 1, 4 
            ";

            string Task1 = @"
            x: 0, 80, 160, 240, 320, 400 ;
            f: 10, 13, 16, 21, 25, 25 ;
            f: 15, 20, 22, 25, 30, 32 ;
            f: 13, 17, 21, 26, 28, 30 ;
            f: 14, 16, 23, 25, 27, 32 
            ";

            InvestorTask.Resolve(CIOhelper.Parse(Task1));
        }
    }
}
