using System;

public struct TGraphic
{
    public string Paymentsdate; // дата платежа
    public int Quantitydays; // количество дней прошедших с даты получения кредита
    public string DayName; // название дня
    public double Amount; // сумма платежа
    public double Repayment; // переплата
    public double Percentages; // проценты
    public double Loanbalance; // остаток кредита
}

public class TPSK
{
    private static double Solve(int n, TGraphic[] G, double bp) // составление и решение уравнения
    {
        double function(double x) // составление уравнения
        {
            double y = G[0].Loanbalance;
            double Q = 1;
            int q = 0;
            for (int j = 1; j <= n; j++)
            {
                int tmp = (int)Rounding.RoundDown((decimal)(G[j].Quantitydays / bp), 0);
                if (tmp > q)
                {
                    q = tmp;
                    Q = Q * (1 + x);
                }
                double e = (G[j].Quantitydays - G[j - 1].Quantitydays - bp) / bp;
                y = y + (G[j].Amount / ((1 + e * x) * Q));
            }
            return y;
        }

        bool Sign(double x) // определение знака числа
        {
            if (x >= 0) { return true; }
            else { return false; }
        }

        bool interval(double x, double y) // определение присутсвия корня
        {
            double fx = function(x);
            double fy = function(y);
            if (Sign(fx) != Sign(fy)) { return true; }
            else { return false; }
        }

        bool IIsola(double x, double y) // определение интервала изоляции
        {
            double f1x = (function(x + 0.1) - function(x - 0.1)) / 0.2;
            double f1y = (function(y + 0.1) - function(y - 0.1)) / 0.2;
            if (Sign(f1x) != Sign(f1y)) { return false; }
            else { return true; }
        }

        double a = 0;
        double b = 1;
        if ((IIsola(a, b) == false) || (interval(a, b) == false))
        {
            while (interval(a, b) == false)
            {
                b = b + 1;
            }
            while (IIsola(a, b) == false)
            {
                b = b - 0.01;
            }
        }

        do {
            double c = (a * function(b) - b * function(a)) / (function(b) - function(a));
            if (interval(a, c) == true) { b = c; }
            else { a = c; }
        } while (Math.Abs(a - b) > 2 * 0.0001);

        return a;
    }

    public static double Calculate(int n, TGraphic[] G) // вычисление полной стоимости кредита
    {
        double bp = (double)G[n].Quantitydays / n;
        double cbp = 365 / bp;
        double i = Solve(n, G, bp);
        return cbp * i * 100;
    }
}
