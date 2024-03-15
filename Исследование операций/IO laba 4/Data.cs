using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CData
{
    public class Data
    {
        public List<List<int>> Costs { get; set; }
        public List<int> Reserves { get; set; }
        public List<int> Needs { get; set; }
        public int NumberOfProviders { get; set; }
        public int NumberOfClients { get; set; }
        public List<List<int>> Routes { get; set; }
        public HashSet<(int, int)> InvolvedRoutes { get; set; }
        public List<(int, int)> Epsilons { get; set; }

        public Data()
        {
            Costs = new List<List<int>>();
            Reserves = new List<int>();
            Needs = new List<int>();
            Routes = new List<List<int>>();
            InvolvedRoutes = new HashSet<(int, int)>();
            Epsilons = new List<(int, int)>();
        }

    public void AddFictitiousReserve(int reserve)
        {
            Reserves.Add(reserve);
            Costs.Add(new List<int>(Enumerable.Repeat(0, NumberOfClients)));
            Routes.Add(new List<int>(Enumerable.Repeat(0, NumberOfClients)));
        }

        public void AddFictitiousNeed(int need)
        {
            Needs.Add(need);
            for (int i = 0; i < Costs.Count; i++)
            {
                Costs[i].Add(0);
                Routes[i].Add(0);
            }
        }

        public int GetAmountReserves()
        {
            int amount = 0;
            foreach (var item in Reserves)
            {
                amount += item;
            }
            return amount;
        }

        public int GetAmountNeeds()
        {
            int amount = 0;
            foreach (var item in Needs)
            {
                amount += item;
            }
            return amount;
        }

        public int GetFunctionResult()
        {
            int result = 0;
            foreach (var tuple in InvolvedRoutes)
            {
                int a = tuple.Item1;
                int b = tuple.Item2;

                result += Costs[a][b] * Routes[a][b];
            }
            return result;
        }

        public Dictionary<int, HashSet<int>> GetInvolvedRoutes()
        {
            var result = new Dictionary<int, HashSet<int>>();
            foreach (var tuple in InvolvedRoutes)
            {
                int a = tuple.Item1;
                int b = tuple.Item2;

                if (result.ContainsKey(a))
                {
                    result[a].Add(b);
                }
                else
                {
                    result[a] = new HashSet<int> { b };
                }
            }
            return result;
        }

        public override string ToString()
        {
            StringBuilder result = new StringBuilder();
            result.AppendLine("\nЗадача:\n" + string.Join("", Needs.Select(item => $"{item,-5}")));
            result.AppendLine("--------------------");

            for (int i = 0; i < Costs.Count; i++)
            {
                result.Append(string.Join("", Costs[i].Select(item => $"{item,-5}")));
                result.Append("|");
                result.Append($"{Reserves[i],-5}");
                result.AppendLine();
            }

            result.AppendLine("--------------------");
            result.AppendLine("\nПлан:\n" + string.Join("", Needs.Select(item => $"{item,-5}")));
            result.AppendLine("--------------------");

            for (int i = 0; i < Routes.Count; i++)
            {
                result.Append(string.Join("", Routes[i].Select(item => $"{item,-5}")));
                result.Append("|");
                result.Append($"{Reserves[i],-5}");
                result.AppendLine();
            }

            result.AppendLine("--------------------\nЗначение функции: " + GetFunctionResult());

            result.AppendLine("====================");
            return result.ToString();
        }
    }
}
