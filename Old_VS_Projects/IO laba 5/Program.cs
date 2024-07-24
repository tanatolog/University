using System;

namespace IO_laba_5
{
    class Program
    {
        static void Main(string[] args)
        {
            string Taskn = @"
            n   1   2   3   4   5   6;   
        n;  n,  3,  9,  5,  n,  n,  n;
        1;  n,  n,  n,  2,  6,  n,  n;
        2;  n,  n,  n,  n,  n,  n,  n;
        3;  n,  n,  n,  n,  5,  1,  6;
        4;  n,  n,  n,  n,  n,  n,  2;
        5;  n,  n,  1,  n,  n,  n,  4;
        6;  n,  n,  n,  n,  n,  n,  n
        ";

            string Task1 = @"
            0   1   2   3   4   5   6   7;
        0;  1,  5,  1,  n,  2,  n,  n,  n;
        1;  n,  n,  n,  n,  1,  n,  n,  n;
        2;  n,  n,  n,  2,  n,  4,  n,  2;
        3;  2,  n,  n,  n,  n,  n,  1,  n;
        4;  n,  n,  n,  n,  n,  n,  3,  n;
        5;  n,  n,  n,  n,  n,  n,  1,  n;
        6;  n,  n,  n,  n,  n,  n,  n,  n;
        7;  1,  n,  n,  n,  n,  n,  n,  n
        ";

            Console.WriteLine(Task1);
            CGraph edges = CInput.Parse(Task1);
            CAlgorithms.FindShortcut(edges, 0, 6);
        }
    }
}
