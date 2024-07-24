using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using CData;

namespace CIOhelper
{
    class IOhelper
    {
        public static string Input(string filename)
        {
            string[] lines = File.ReadAllLines(filename);
            foreach (var line in lines)
                Console.WriteLine(line);

            string s = string.Empty;
            string input = string.Empty;
            int i = 0;

            while (s != "end")
            {
                s = lines[i];
                s = s.Trim();
                input += s;
                i += 1;
            }

            return input;
        }

        public static Data Parse(string input)
        {
            var costs = new List<List<int>>();
            var reserves = new List<int>();
            var needs = new List<int>();
            var numberOfProviders = 0;
            var numberOfClients = 0;
            var routes = new List<List<int>>();
            var involvedRoutes = new HashSet<(int, int)>();
            var epsilons = new List<(int, int)>();

            input = new string(input.Where(c => char.IsDigit(c) || c == ';' || c == ',').ToArray());

            var parts = input.Split(';');

            reserves = parts[0].Split(',').Select(item => int.Parse(item)).ToList();
            needs = parts[1].Split(',').Select(item => int.Parse(item)).ToList();

            numberOfProviders = reserves.Count;
            numberOfClients = needs.Count;

            var right = parts[2].Split(',').Select(item => int.Parse(item)).ToArray();
            var left = Array.Empty<int>();

            for (int i = 0; i < numberOfProviders; i++)
            {
                left = right.Take(numberOfClients).ToArray();
                right = right.Skip(numberOfClients).ToArray();
                costs.Add(left.ToList());
                routes.Add(Enumerable.Repeat(0, numberOfClients).ToList());
            }

            return new Data
            {
                Costs = costs,
                Reserves = reserves,
                Needs = needs,
                NumberOfProviders = numberOfProviders,
                NumberOfClients = numberOfClients,
                Routes = routes,
                InvolvedRoutes = involvedRoutes,
                Epsilons = epsilons
            };
        }
    }
}
