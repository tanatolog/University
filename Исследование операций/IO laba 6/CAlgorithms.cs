using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IO_laba_6
{
    public class Data
    {
        public List<int> Attachments { get; set; }
        public List<List<int>> Profits { get; set; }
    }


    public class InvestorTask
    {
        public static void Resolve(Data data) 
        {
            Dictionary<int, List<(int, int, int)>> W = new();

            int functionF(int number, int parametr)
            {
                int index = 0;
                for (int i = 0; i < data.Attachments.Count; i++)
                {
                    if (data.Attachments[i] <= parametr)
                    {
                        index = i;
                    }
                    else
                    {
                        break;
                    }
                }
                return data.Profits[number][index];
            }

            int functionW(int number, int parametr)
            {
                for (int i = (W[number].Count - 1); i >= 0; i--)
                {
                    if (W[number][i].Item3 <= parametr)
                    {
                        return W[number][i].Item1;
                    }
                }
                return 0;
            }

            List<int> s = new(data.Attachments);
            if (s[0] == 0) 
            { 
                s.RemoveAt(0); 
            }

            List<List<int>> x = new();
            List<List<int>> s_x = new();
            W[data.Profits.Count] = new();
            for (int i = 1; i <= s.Count; i++)
            {
                W[data.Profits.Count].Add((0, 0, 0));
                x.Add(new List<int>());
                s_x.Add(new List<int>());
                for (int j = 0; j < (i + 1); j++)
                {
                    x[i - 1].Add(data.Attachments[j]);
                    s_x[i - 1].Add(s[i - 1] - x[i - 1][j]);
                }
            }

            for (int iteration = data.Profits.Count - 1; iteration >= 0; iteration--)
            {
                W[iteration] = new();
                for (int si = 0; si < s.Count; si++)
                {
                    List<int> d = new();
                    for (int j = 0; j < x[si].Count; j++)
                    {
                        d.Add(functionF(iteration, x[si][j]) + functionW(iteration + 1, s_x[si][j]));
                    }

                    for (int j = 0; j < d.Count; j++)
                    {
                        if (d[j] == d.Max())
                        {
                            W[iteration].Add((d[j], x[si][j], s[si]));
                        }
                    }
                }
            }

            List<(int, int)> plan = new();
            int sumAttachments = s.Last();
            int maxValue = 0;
            for (int Wnumber = 0; Wnumber < data.Profits.Count; Wnumber++)
            {
                int maxW = W[Wnumber][0].Item1;
                int index = 0;
                for (int i = 1; i < W[Wnumber].Count; i++)
                {
                    if ((maxW < W[Wnumber][i].Item1) && (sumAttachments >= s[i]))
                    {
                        maxW = W[Wnumber][i].Item1;
                        index = i;
                    }
                }

                if (Wnumber == 0) { maxValue = maxW; }

                plan.Add((Wnumber, W[Wnumber][index].Item2));
                sumAttachments = sumAttachments - W[Wnumber][index].Item2;
            }

            PrintTable(W);
            PrintResult(maxValue, plan);
        }

        static void PrintTable(Dictionary<int, List<(int, int, int)>> W)
        {

            for (int Wnumber = W.Count - 2; Wnumber >= 0; Wnumber--)
            {
                string s = $"s    x    W({Wnumber})\n";
                for (int i = 0; i < W[Wnumber].Count; i++)
                {
                    s = $"{s}{W[Wnumber][i].Item3, -5}{W[Wnumber][i].Item2,-5}{W[Wnumber][i].Item1,-5}\n";
                }
                Console.WriteLine(s);
            }
        }

        static void PrintResult(int maxValue, List<(int, int)> plan)
        {
            string s = $"Максимальная выгода: {maxValue}\nОптимальный план:\n";

            for (int i = 0; i < plan.Count; i++)
            {
                s = $"{s}[{plan[i].Item1}, {plan[i].Item2}]\n";
            }
            Console.WriteLine(s);
        }
    }

}
