using System;

namespace VVK_laba_2
{
class Program
    {
        static int Factorial(int n)
        {
            int factorial = 1;
            for (int i = 1; i <= n; i++)
                factorial *= i;

            return factorial;
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
            double TT = (P_0_1(N, p));
            double num = Math.Pow(N, (N - 1)) * Math.Pow(p, (N + 1)) * TT;
            double den = Factorial(N - 1) * Math.Pow((1 - p), 2);
            return num / den;
        }

        static void IV(double N, double B, double La, double T)
        {
            double V = T / B;
            Console.WriteLine("V = " + Math.Round(V, 6));
            double u = B / T;
            Console.WriteLine("u = " + Math.Round(u, 6));
            double p = (La * V) / N;
            Console.WriteLine("p = " + Math.Round(p, 6));
            double R = N * p;
            Console.WriteLine("R = " + Math.Round(R, 6));
            double l = L((int)Math.Round(N), p);
            Console.WriteLine("l = " + Math.Round(l, 6));
            double W = l / La;
            Console.WriteLine("W = " + Math.Round(W, 6));
            double U = (l + R) / La;
            Console.WriteLine("U = " + Math.Round(U, 6));
            return;
        }

        static void Main(string[] args)
        {
            IV(1, 210000, 8, 6000);
        }
    }
}
