using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IO_laba_5
{
    public class CGraph
    {
        public Dictionary<int, Dictionary<int, int>> Edges { get; set; }
        public int NumberOfVertices { get; set; }
    }

    public class CAlgorithms
    {
        private static LinkedList<int> GetRoad(Dictionary<int, Dictionary<int, int>> edges, Dictionary<int, int> verticesCosts, int target, int cost)
        {
            var road = new LinkedList<int>();
            if (cost != 0)
            {
                var ct = cost;
                var v = target;
                road.AddLast(v);
                while (ct != 0)
                {
                    var c = ct;
                    foreach (var (key, value) in edges)
                    {
                        if (value.TryGetValue(v, out var a))
                        {
                            if (verticesCosts.TryGetValue(key, out var t))
                            {
                                if ((c - a) == t)
                                {
                                    v = key;
                                    ct = c - a;
                                }
                            }
                        }
                    }
                    road.AddFirst(v);
                }
            }
            return road;
        }

        public static void PrintTabTitle(int number)
        {
            string tab1 = "";
            string tab2 = "";
            string tab3 = "";
            for (int i = 0; i < number; i++)
            {
                tab1 = tab1 + " " + i;
                tab2 = tab2 + " -";
            }
            for (int i = 0; i < number - 1; i++)
            {
                tab3 = tab3 + " i";
            }
            Console.WriteLine("n | w |" + tab1 + " |" + tab1 + "\n0   -   0" + tab3 + "  " + tab2);
        }

        public static void PrintTabLine(int number, int iteration, int w, List<int?> parents, Dictionary<int, int> verticesCosts)
        {
            string tab1 = "";
            string tab2 = "";
            for (int i = 0; i < number; i++)
            {
                if (verticesCosts[i] == int.MaxValue)
                {
                    tab1 = tab1 + "i ";
                }
                else
                {
                    tab1 = tab1 + string.Join("", $"{verticesCosts[i],-2}");
                }

                if (parents[i] == null)
                {
                    tab2 = tab2 + "- ";
                }
                else
                {
                    tab2 = tab2 + string.Join("", $"{parents[i],-2}"); ;
                }
            }

            Console.WriteLine(iteration + "   " + w + "   " + tab1 + "  " + tab2);
        }

        public static (LinkedList<int>, int) FindShortcut(CGraph graph, int start, int target)
        {
            Console.WriteLine("Алгоритм Дейкстры начало:\n");
            var road = new LinkedList<int>();
            var cost = 0;

            Dictionary<int, int> verticesCosts = new();
            List<int?> parents = new();
            HashSet<int> notvisited = new();
            for (int i = 0; i < graph.NumberOfVertices; i++)
            {
                notvisited.Add(i);
                parents.Add(null);
                verticesCosts[i] = int.MaxValue;
            }

            if (verticesCosts.TryGetValue(start, out var s))
            {
                verticesCosts[start] = 0;
            }

            PrintTabTitle(graph.NumberOfVertices);

            for (int iteration = 1; iteration < graph.NumberOfVertices; iteration++)  //вывод таблички нужно сделать
            {
                int minvalue = int.MaxValue;
                int w = 0;
                for (int i = 0; i < graph.NumberOfVertices; i++)
                {
                    if ((verticesCosts[i] <= minvalue) && notvisited.Contains(i))
                    {
                        minvalue = verticesCosts[i];
                        w = i;
                    }
                }
                notvisited.Remove(w);
                
                if (graph.Edges.ContainsKey(w))
                {
                    foreach (var (index, c) in graph.Edges[w])
                    {
                        var a = verticesCosts[w];
                        var b = verticesCosts[index];

                        if (a != int.MaxValue)
                        {
                            if (b > (a + c))
                            {
                                verticesCosts[index] = a + c;
                                parents[index] = w;
                            }
                        }
                    }
                }

                PrintTabLine(graph.NumberOfVertices, iteration, w, parents, verticesCosts);
            }

            if (verticesCosts.TryGetValue(target, out var t))
            {
                cost = t;
                road = GetRoad(graph.Edges, verticesCosts, target, cost);
            }

            Console.WriteLine($"\nМинимальный путь из {start} в {target} найден:");
            Console.WriteLine(string.Join("", road.Select(item => $"{item,-2}")));
            Console.WriteLine($"Стоимость: {cost}");
            return (road, cost);
        }

        /*public static (LinkedList<int>, int) FindShortcut(Dictionary<int, Dictionary<int, int>> graph, int start, int target)
        {
            var list = new LinkedList<int>();
            if (graph.TryGetValue(start, out var startVertices))
            {
                foreach (var item in startVertices)
                {
                    list.AddFirst(item.Key);
                }
            }
            else
            {
                return (new LinkedList<int>(), 0);
            }

            var road = new LinkedList<int>();
            var verticesCosts = new Dictionary<int, int>
            {
            { start, 0 }
            };

            while (list.Count > 0)
            {
                var vertice = list.Last.Value;
                list.RemoveLast();

                if (!verticesCosts.ContainsKey(vertice))
                {
                    var notCalculated = new List<int>();
                    var min = int.MaxValue;
                    foreach (var (a, b) in graph)
                    {
                        if (b.TryGetValue(vertice, out var value))
                        {
                            if (verticesCosts.TryGetValue(a, out var cost))
                            {
                                if (cost != int.MaxValue)
                                {
                                    if ((cost + value) < min && a != vertice)
                                    {
                                        min = cost + value;
                                    }
                                }
                            }
                            else
                            {
                                notCalculated.Add(a);
                            }
                        }
                    }
                    if (notCalculated.Count == 0)
                    {
                        if (min == int.MaxValue)
                        {
                            verticesCosts[vertice] = int.MaxValue;
                        }
                        else
                        {
                            verticesCosts[vertice] = min;
                            if (vertice != target && graph.TryGetValue(vertice, out var vertices))
                            {
                                foreach (var item in vertices)
                                {
                                    if (!verticesCosts.ContainsKey(item.Key))
                                    {
                                        list.AddFirst(item.Key);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        list.AddLast(vertice);
                        foreach (var item in notCalculated)
                        {
                            list.AddLast(item);
                        }
                    }
                }
            }

            var finalcost = 0;
            if (verticesCosts.TryGetValue(target, out var c))
            {
                finalcost = c;
                road = GetRoad(graph, verticesCosts, target, finalcost);
            }

            return (road, finalcost);
        }*/

    }
}
