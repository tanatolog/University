using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        double l0 = 0.1;
        List<double> lambda = new List<double> { 0.3846153, 0.05, 0.1, 0.13461 };
        List<double> v = new List<double> { 0.43, 0.24, 0.3, 0.9 };
        List<double> a = lambda.ConvertAll(l => Math.Round(l / l0, 10));
        List<int> k = new List<int> { 1, 1, 1, 2 };
        double ou = 3.74631;

        for (int i = 0; i < lambda.Count; i++)
        {
            Console.WriteLine("l(" + i + ") = " + lambda[i]);
        }

        double sum = 0;
        for (int i = 0; i < a.Count; i++)
        {
            Console.WriteLine("a(" + i + ") = " + a[i]);
        }
        Console.WriteLine("a = " + (a[0] + lambda[1]));

        for (int i = 0; i < lambda.Count; i++)
        {
            Console.WriteLine("stacionar(" + i + ") = " + (k[i] / (a[i] * v[i])));
        }

        List<double> b = new List<double>();
        for (int i = 0; i < lambda.Count; i++)
        {
            double bi = lambda[i] * v[i];
            Console.WriteLine("b(" + i + ") = " + bi);
            b.Add(bi);
        }

        List<double> pi = new List<double>();
        double PI = 1;
        for (int i = 0; i < k.Count; i++)
        {
            double p;
            if (k[i] == 1)
            {
                p = 1 - b[i];
                Console.WriteLine("P(" + i + ") = " + p);
            }
            else
            {
                p = 1 / (Math.Pow(b[i], 2) / (2 * (1 - b[i] / 2)) + 1 + b[i]);
                Console.WriteLine("P(" + i + ") = " + p);
            }
            pi.Add(Math.Round(p, 10));
            PI *= p;
        }

        Console.WriteLine("PI = " + PI);

        List<double> l = new List<double>();
        for (int i = 0; i < b.Count; i++)
        {
            double li = (Math.Pow(b[i], k[i] + 1) / (k[i] * k[i] * Math.Pow((1 - b[i] / k[i]), 2))) * pi[i];
            Console.WriteLine("l(" + i + ") = " + li);
            l.Add(Math.Round(li, 10));
        }
        sum = 0;
        foreach(double tmp in l)
        {
            sum = sum + tmp;
        }
        Console.WriteLine("L = " + sum);

        List<double> ro = new List<double>();
        for (int i = 0; i < b.Count; i++)
        {
            double roi = b[i] / k[i];
            ro.Add(roi);
        }

        List<double> m = new List<double>();
        for (int i = 0; i < ro.Count; i++)
        {
            double mi = l[i] + b[i];
            Console.WriteLine("m(" + i + ") = " + mi);
            m.Add(Math.Round(mi, 10));
        }
        sum = 0;
        foreach (double tmp in m)
        {
            sum = sum + tmp;
        }
        Console.WriteLine("M = " + sum);

        List<double> w = new List<double>();
        for (int i = 0; i < l.Count; i++)
        {
            double wi = l[i] / lambda[i];
            Console.WriteLine("w(" + i + ") = " + wi);
            w.Add(wi);
        }
        Console.WriteLine("W = " + a.Zip(w, (ai, wi) => ai * wi).Sum());

        List<double> u = new List<double>();
        for (int i = 0; i < m.Count; i++)
        {
            double ui = m[i] / lambda[i];
            Console.WriteLine("u(" + i + ") = " + ui);
            u.Add(ui);
        }
        double totalU = a.Zip(u, (ai, ui) => ai * ui).Sum();
        Console.WriteLine("U = " + totalU);

        double du = 100 - ((totalU * 100) / ou);
        Console.WriteLine("du = " + du);
    }
}