using System;
using System.Collections.Generic;
using System.Linq;
using CData;

namespace CTransportTask
{
    class TransportTask
    {
        public static Data MinElementMethod(Data data)
        {
            Console.WriteLine("Метод минимального элемента начат.");
            Console.WriteLine(data);
            List<(int, int, int)> sortedCosts = GetSortedCost(data.Costs);

            int difference = data.GetAmountReserves() - data.GetAmountNeeds();
            if (difference > 0)
            {
                data.AddFictitiousNeed(difference);
                for (int ii = 0; ii < data.NumberOfProviders; ii++)
                {
                    sortedCosts.Add((ii, data.NumberOfClients, 0));
                }
            }
            else if (difference < 0)
            {
                data.AddFictitiousReserve(Math.Abs(difference));
                for (int j = 0; j < data.NumberOfClients; j++)
                {
                    sortedCosts.Add((data.NumberOfProviders, j, 0));
                }
            }

            List<int> reserves = new List<int>(data.Reserves);
            List<int> needs = new List<int>(data.Needs);

            HashSet<int> possibleReserves = new HashSet<int>();
            HashSet<int> possibleNeeds = new HashSet<int>();
            bool reserve = false;
            int i = 0;
            while (i < sortedCosts.Count)
            {
                if (((reserves[sortedCosts[i].Item1] > 0) && (reserves[sortedCosts[i].Item1] <= needs[sortedCosts[i].Item2]))
                    || (possibleReserves.Contains(sortedCosts[i].Item1) &&
                        (possibleNeeds.Contains(sortedCosts[i].Item2) || needs[sortedCosts[i].Item2] > 0)))
                {
                    if (possibleReserves.Contains(sortedCosts[i].Item1))
                    {
                        data.Epsilons.Add((sortedCosts[i].Item1, sortedCosts[i].Item2));
                        possibleReserves.Remove(sortedCosts[i].Item1);
                        if (possibleNeeds.Contains(sortedCosts[i].Item2))
                        {
                            possibleNeeds.Remove(sortedCosts[i].Item2);
                        }
                    }

                    if ((reserves[sortedCosts[i].Item1] == needs[sortedCosts[i].Item2]) && reserves[sortedCosts[i].Item1] > 0)
                    {
                        if (reserve)
                        {
                            possibleReserves.Add(sortedCosts[i].Item1);
                            reserve = false;
                        }
                        else
                        {
                            possibleNeeds.Add(sortedCosts[i].Item2);
                            reserve = true;
                        }
                    }

                    data.Routes[sortedCosts[i].Item1][sortedCosts[i].Item2] = reserves[sortedCosts[i].Item1];
                    needs[sortedCosts[i].Item2] -= reserves[sortedCosts[i].Item1];
                    reserves[sortedCosts[i].Item1] = 0;
                    data.InvolvedRoutes.Add((sortedCosts[i].Item1, sortedCosts[i].Item2));
                }
                else if (((needs[sortedCosts[i].Item2] > 0) && (reserves[sortedCosts[i].Item1] >= needs[sortedCosts[i].Item2]))
                    || (possibleNeeds.Contains(sortedCosts[i].Item2) &&
                        (possibleReserves.Contains(sortedCosts[i].Item1) || reserves[sortedCosts[i].Item1] > 0)))
                {
                    if (possibleNeeds.Contains(sortedCosts[i].Item2))
                    {
                        data.Epsilons.Add((sortedCosts[i].Item1, sortedCosts[i].Item2));
                        possibleNeeds.Remove(sortedCosts[i].Item2);
                        if (possibleReserves.Contains(sortedCosts[i].Item1))
                        {
                            possibleReserves.Remove(sortedCosts[i].Item1);
                        }
                    }

                    if ((reserves[sortedCosts[i].Item1] == needs[sortedCosts[i].Item2]) && reserves[sortedCosts[i].Item1] > 0)
                    {
                        if (reserve)
                        {
                            possibleReserves.Add(sortedCosts[i].Item1);
                            reserve = false;
                        }
                        else
                        {
                            possibleNeeds.Add(sortedCosts[i].Item2);
                            reserve = true;
                        }
                    }

                    data.Routes[sortedCosts[i].Item1][sortedCosts[i].Item2] = needs[sortedCosts[i].Item2];
                    reserves[sortedCosts[i].Item1] -= needs[sortedCosts[i].Item2];
                    needs[sortedCosts[i].Item2] = 0;
                    data.InvolvedRoutes.Add((sortedCosts[i].Item1, sortedCosts[i].Item2));
                }
                i++;
            }
            Console.WriteLine("Метод минимального элемента конец. Первоначальное заполнение базиса.");
            Console.WriteLine(data);
            return data;
        }

        static List<(int, int, int)> GetSortedCost(List<List<int>> costs)
        {
            List<(int, int, int)> result = new List<(int, int, int)>();
            for (int i = 0; i < costs.Count; i++)
            {
                for (int j = 0; j < costs[i].Count; j++)
                {
                    result.Add((i, j, costs[i][j]));
                }
            }
            result.Sort((a, b) => a.Item3.CompareTo(b.Item3));
            return result;
        }

        static Data MoveReserve(Data data, (int, int) index)
        {
            /*Dictionary<int, (int, int)> InvolvedRoutes = new Dictionary<int, (int, int)>();
            int key = 0;
            foreach ((int, int) tmp in data.InvolvedRoutes)
            {
                InvolvedRoutes.Add(key, tmp);
                key++;
            }*/

            List<(int, int)> cycle = BuildCycle(data.GetInvolvedRoutes(), index);
            var min = int.MaxValue;

            for (int i = 1; i < cycle.Count; i += 2)
            {
                if (data.Routes[cycle[i].Item1][cycle[i].Item2] < min)
                {
                    min = data.Routes[cycle[i].Item1][cycle[i].Item2];
                }
            }

            for (int i = 0; i < cycle.Count; i++)
            {
                if (i % 2 == 0)
                {
                    data.Routes[cycle[i].Item1][cycle[i].Item2] += min;
                }
                else
                {
                    data.Routes[cycle[i].Item1][cycle[i].Item2] -= min;
                    if (data.Routes[cycle[i].Item1][cycle[i].Item2] == 0 && !data.Epsilons.Contains(cycle[i]))
                    {
                        data.InvolvedRoutes.Remove(cycle[i]);
                    }
                }
            }

            data.InvolvedRoutes.Add(index);

            return data;
        }

        /*static List<(int, int)> BuildCycle(Data data, (int, int) cell)
        {
            List<(int, int)> cycle = new List<(int, int)>();
            HashSet<(int, int)> visitedCells = new HashSet<(int, int)>();
            cycle.Add(cell);

            foreach (var tmp in data.InvolvedRoutes) 
            {
                bool rows = false;
                bool cols = false;
                for (int i = 0; i < data.NumberOfClients; i++) //rows
                {
                    if (((data.InvolvedRoutes.Contains((tmp.Item1, i))) && ((tmp.Item1, i) != tmp)) || (tmp.Item1 == cell.Item1))
                    {
                        rows = true;
                        break;
                    }
                }
                for (int i = 0; i < data.NumberOfProviders; i++) //cols
                {
                    if (((data.InvolvedRoutes.Contains((i, tmp.Item2))) && ((i, tmp.Item2) != tmp)) || (tmp.Item2 == cell.Item2))
                    {
                        cols = true;
                        break;
                    }
                }
                if ((rows == true) && (cols == true))
                {
                    cycle.Add(tmp);
                }
            }

            return (cycle);
        }*/

        public static List<(int, int)> BuildCycle(Dictionary<int, HashSet<int>> involvedRoutes, (int, int) target)
        {
            var list = new LinkedList<List<(int, int)>>();
            var results = new List<List<(int, int)>>();
            list.AddFirst(new List<(int, int)> { target });

            while (list.Count > 0)
            {
                var v = list.Last.Value;
                list.RemoveLast();

                if (v.Count % 2 == 1)
                {
                    var l = v.Last();
                    if (involvedRoutes.TryGetValue(l.Item1, out var s))     
                    {
                        foreach (var item in s)
                        {
                            if (item != l.Item2)
                            {
                                var vec = new List<(int, int)>(v);
                                vec.Add((l.Item1, item));
                                list.AddFirst(vec);
                            }
                        }
                    }
                }
                else
                {
                    var l = v.Last();
                    if (l.Item2 == target.Item2)
                    {
                        results.Add(v);
                    }
                    else
                    {
                        if (involvedRoutes.TryGetValue(l.Item1, out var tmp))
                        {
                            foreach (var (a, set) in involvedRoutes)
                            {
                                if (set.Contains(l.Item2) && a != l.Item1)
                                {
                                    var vec = new List<(int, int)>(v);
                                    vec.Add((a, l.Item2));
                                    list.AddFirst(vec);
                                }
                            }
                        }
                    }
                }
            }

            return results.Count > 0 ? results[0] : new List<(int, int)>();
        }

        static (int, int)? GetNegativeCell(List<List<int>> costs, HashSet<(int, int)> involvedRoutes)
        {
            var evaluations = GetEvaluations(costs, involvedRoutes);
            int minNegativeIndex = 0;
            int minNegative = 0;

            int i = 0;
            while (i < evaluations.Count)
            {
                if (evaluations[i].Item3 < minNegative)
                {
                    minNegative = evaluations[i].Item3;
                    minNegativeIndex = i;
                }
                i++;
            }

            if (minNegative != 0)
            {
                return (evaluations[minNegativeIndex].Item1, evaluations[minNegativeIndex].Item2);
            }
            else
            {
                return null;
            }
        }

        static List<(int, int, int)> GetEvaluations(List<List<int>> costs, HashSet<(int, int)> involvedRoutes)
        {
            var (reserves, needs) = GetPotentials(costs, involvedRoutes);
            var notInvolvedRoutes = new List<(int, int, int)>();

            for (int i = 0; i < costs.Count; i++)
            {
                for (int j = 0; j < costs[0].Count; j++)
                {
                    if (!involvedRoutes.Contains((i, j)))
                    {
                        notInvolvedRoutes.Add((i, j, 0));
                    }
                }
            }

            for (int i = 0; i < notInvolvedRoutes.Count; i++)
            {
                notInvolvedRoutes[i] = (notInvolvedRoutes[i].Item1, notInvolvedRoutes[i].Item2, costs[notInvolvedRoutes[i].Item1][notInvolvedRoutes[i].Item2] - (reserves[notInvolvedRoutes[i].Item1] + needs[notInvolvedRoutes[i].Item2]));
            }

            return notInvolvedRoutes;
        }

        static (List<int>, List<int>) GetPotentials(List<List<int>> costs, HashSet<(int, int)> involvedRoutes)
        {
            var needs = Enumerable.Repeat((int?)null, costs[0].Count).ToList();
            var reserves = Enumerable.Repeat((int?)null, costs.Count).ToList();

            reserves[0] = 0;

            int i = 0;
            int len = needs.Count + reserves.Count - 1;
            while (i < len)
            {
                foreach (var (a, b) in involvedRoutes)
                {
                    switch (needs[b])
                    {
                        case int p:
                            if (reserves[a] == null)
                            {
                                reserves[a] = costs[a][b] - p;
                                i++;
                            }
                            break;

                        case null:
                            if (reserves[a].HasValue)
                            {
                                needs[b] = costs[a][b] - reserves[a];
                                i++;
                            }
                            break;
                    }
                }
            }

            var needsList = needs.Select(a => a ?? throw new InvalidOperationException("Unexpected null value in needs.")).ToList();
            var reservesList = reserves.Select(a => a ?? throw new InvalidOperationException("Unexpected null value in reserves.")).ToList();

            return (reservesList, needsList);
        }

        public static Data PotentialMethod(Data data)
        {
            Console.WriteLine("Метод потенциалов начат.");
            Console.WriteLine(data);
            Console.WriteLine("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            while (GetNegativeCell(data.Costs, data.InvolvedRoutes) is (int row, int col))
            {
                data = MoveReserve(data, (row, col));
                Console.WriteLine(data);
                Console.WriteLine("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            }
            Console.WriteLine("Метод потенциалов конец. Найдено оптимальное решение.");
            return (data);
        }
    }
}
