using System;

namespace VVK_laba_2
{
class Program
    {
        static double Factorial(int n)
        {
            if (n == 0)
                return 1;
            else
                return n * Factorial(n - 1);
        }

        static double P_0(double R, int N)
        {
            double num = Math.Pow(R, N);
            double den = Factorial(N - 1) * (N - R);
            double s = 0;
            for (int n = 0; n < N; n++)
            {
                s += Math.Pow(R, n) / Factorial(n);
            }
            return 1 / (num / den + s);
        }

        static double P_n(double R, double n, int N)
        {
            if (n <= N)
                return P_0(R, N) * Math.Pow(R, n) / Factorial((int)Math.Round(n));
            else
                return P_0(R, N) * Math.Pow(R, n) / (Factorial(N) * Math.Pow(N, (n - N)));
        }

        static double P_0_1(int N, double p)
        {
            double num = Math.Pow(N, (N - 1)) * Math.Pow(p, N);
            double den = Factorial(N - 1) * (1 - p);
            double s = 0;
            for (int i = 0; i < N; i++)
            {
                s += Math.Pow(N, i) * Math.Pow(p, i) / Factorial(i);
            }
            return 1 / (num / den + s);
        }

        static double L(int N, double p)
        {
            double num = Math.Pow(N, (N - 1)) * Math.Pow(p, (N + 1)) * P_0_1(N, p);
            double den = Factorial(N - 1) * Math.Pow((1 - p), 2);
            return num / den;
        }

        static void Main(string[] args)
        {
            for (int n = 0; n <= 12; n++) {
                double t1 = P_n(1.9, n, 4);
                Console.WriteLine(Math.Round(t1, 8));
            }

            double t2 = P_n(2.7, 2.7, 4);
            Console.WriteLine(Math.Round(t2, 8)); 
        }
    }
}
