using System;
using System.Windows.Forms;

namespace PSK
{
    public partial class Form1 : Form  // класс формы
    {

        public Form1() // конструктор формы
        {
            InitializeComponent();
        }

        void СonstructionGraphic(int payments, TGraphic[] G) // вывод графика погашения кредита на экран
        {
            Grid1.Rows.Clear();
            Grid1.Rows.Add(0, G[0].Paymentsdate, G[0].DayName, G[0].Amount, "", "", -G[0].Loanbalance);
            for (int i = 1; i <= payments; i++)
            {
                Grid1.Rows.Add(i, G[i].Paymentsdate, G[i].DayName, G[i].Amount, G[i].Repayment, G[i].Percentages, G[i].Loanbalance);
            }
            Grid1.Rows.Add("C", G[payments].Quantitydays, "", Rounding.RoundUp((decimal)G[payments + 1].Amount, 2), Rounding.RoundUp((decimal)G[payments + 1].Repayment, 2), G[payments + 1].Percentages, "");
        }

        TGraphic[] СalculationDates(int payments, ref string receipt, TGraphic[] G) // расчет дат погашения кредита
        {
            TDate Original = new TDate(receipt);
            receipt = Original.String();
            TDate Next = new TDate(receipt);
            G[0].Paymentsdate = Original.String();
            G[0].DayName = Original.DayName();

            for (int i = 1; i <= payments; i++)
            {
                Next.day = Original.day;
                Next.month = Next.month + 1;
                if (Next.month == 13)
                {
                    Next.year = Next.year + 1;
                    Next.month = 1;
                }

                int tmp = Next.DaysinMonth();
                if (Next.day > tmp) { Next.day = Next.day - (Next.day - tmp); }

                while (Next.Nonworking())
                {
                    if (Next.DaysinMonth() > Next.day) { Next.day++; }
                    else
                    {
                        Next.day = 1;
                        if (Next.month != 12) { Next.month++; }
                        else
                        {
                            Next.month = 1;
                            Next.year++;
                        }
                    }
                }

                G[i].Paymentsdate = Next.String();
                G[i].DayName = Next.DayName();
                G[i].Quantitydays = Original.Quantity(Next.day, Next.month, Next.year);
            }
            return G;
        }

        double Payment(double S, double i, int n, TGraphic[] G) // расчет ежемесячного платежа
        {
            double I = i / 365;
            double V = 1 / (1 + I);
            double A = 0;
            for (int j = 1; j <= n; j++)
            {
                double tmp = Math.Pow(V, G[j].Quantitydays);
                A = A + tmp;
            }
            return S / A;
        }

        TGraphic[] СalculationGraphic(TGraphic[] G, int n, double i, out bool qual) // расчет графика погашения кредита
        {
            TGraphic[] Original = G;
            qual = true;
            TDate date = new TDate();
            double payment = (double)Rounding.RoundDown((decimal)G[0].Amount, 2);
            i = i / 365;

            for (int j = 1; j <= n - 1; j++)
            {
                date.Int(G[j - 1].Paymentsdate);
                double tmp = G[j - 1].Loanbalance * Math.Pow(i + 1, date.Quantity(G[j].Paymentsdate));
                G[j].Amount = payment;
                G[j].Percentages = (double)Rounding.RoundDown((decimal)(tmp - G[j - 1].Loanbalance), 2); 
                G[j].Repayment = (double)Rounding.RoundDown((decimal)(payment - G[j].Percentages), 2);
                if (payment - G[j].Percentages < 0) 
                {
                    qual = false;
                    return Original;
                }
                G[j].Loanbalance = (double)Rounding.RoundDown((decimal)(tmp - payment), 2);
            }

            date.Int(G[n - 1].Paymentsdate);
            double tmp2 = G[n - 1].Loanbalance * Math.Pow(i + 1, date.Quantity(G[n].Paymentsdate)) + ((G[0].Amount - payment) * n);
            G[n].Amount = (double)Rounding.RoundUp((decimal)tmp2, 2);
            G[n].Percentages = (double)Rounding.RoundUp((decimal)(tmp2 - G[n - 1].Loanbalance), 2);
            G[n].Repayment = (double)Rounding.RoundUp((decimal)(tmp2 - G[n].Percentages), 2);
            if (tmp2 - G[n].Percentages < 0)
            {
                qual = false;
                return Original;
            }
            G[n].Loanbalance = 0;

            G[0].Amount = payment;
            return G;
        }

        TGraphic[] CalculationOverpayment(TGraphic[] G, int n) // расчет переплаты
        {
            G[n + 1].Repayment = G[0].Loanbalance;
            G[0].Loanbalance = -G[0].Loanbalance;
            for (int j = 1; j <= n; j++)
            {
                G[n + 1].Amount = G[n + 1].Amount + G[j].Amount;
                G[n + 1].Percentages = G[n + 1].Percentages + G[j].Percentages;
            }

            labelPayment.Text = Convert.ToString((double)Rounding.RoundDown((decimal)G[n + 1].Amount, 2));
            labelRepayment.Text = Convert.ToString((double)Rounding.RoundDown((decimal)G[n + 1].Percentages, 2));
            labelPercent.Text = Convert.ToString((double)Rounding.RoundDown((decimal)((G[n + 1].Percentages * 100) / G[n + 1].Repayment), 2)) + "% от суммы платежей";
            return G;
        }

        private void btnCalculate_Click(object sender, EventArgs e) // реакция на нажатие кнопки btn
        {
            if (int.TryParse(TextBox1.Text, out int n) == false) { n = 0; }
            if (double.TryParse(TextBox3.Text, out double S) == false) { S = 0; }
            if (double.TryParse(TextBox4.Text, out double i) == false) { i = 0; }

            i = i / 100;

            TGraphic[] Graphic = { };

            bool quality = false;
            n = n + 1;
            while (quality == false)
            {
                n = n - 1;
                Graphic = new TGraphic[n + 2];

                string DateTest = TextBox2.Text;
                Graphic = СalculationDates(n, ref DateTest, Graphic);
                TextBox2.Text = DateTest;

                Graphic[0].Amount = Payment(S, i, n, Graphic);
                Graphic[0].Loanbalance = S;
                Graphic = СalculationGraphic(Graphic, n, i, out quality);
                if (quality == false) { continue; }
                Graphic = CalculationOverpayment(Graphic, n);
                labelPSK.Text = Convert.ToString((double)Rounding.RoundDown((decimal)TPSK.Calculate(n, Graphic), 2)) + "%";
                СonstructionGraphic(n, Graphic);
            }
        }
    }
}
