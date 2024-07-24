using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IO_laba_5
{
    class CInput
    {
        public static string Input()
        {
            StringBuilder inputBuilder = new StringBuilder();
            string buffer = string.Empty;

            while (buffer.ToLower() != "end")
            {
                buffer = Console.ReadLine();
                inputBuilder.Append(buffer);
            }

            return inputBuilder.ToString();
        }

        public static CGraph Parse(string input)
        {
            var edges = new Dictionary<int, Dictionary<int, int>>();
            int numberOfVertices = 0;
            input = new string(input.Where(c => char.IsDigit(c) || c == ';' || c == ',' || c == '-' || c == 'n').ToArray());
            string[] parts = input.Split(';');
            List<List<string>> tmpmatrix = parts.Select(item => item.Split(',').ToList()).ToList();
            List<List<int?>> matrix = new List<List<int?>>();

            tmpmatrix.RemoveAt(0);
            for (int i = 0; i < tmpmatrix.Count; i++)
            {
                tmpmatrix.RemoveAt(i);
            }

            for (int i = 0; i < tmpmatrix.Count; i++)
            {
                matrix.Add(new List<int?>());
                for (int j = 0; j < tmpmatrix[i].Count; j++)
                {
                    if (int.TryParse(tmpmatrix[i][j], out int r))
                    {
                        matrix[i].Add(r);
                    }
                    else
                    {
                        matrix[i].Add(null);
                    }
                }
            }

            if (matrix.Any())
            {
                numberOfVertices = matrix.First().Count;
            }

            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    if (matrix[i][j] != null)
                    {
                        if (edges.TryGetValue(i, out var vertex))
                        {
                            vertex[j] = (int)matrix[i][j];
                        }
                        else
                        {
                            edges[i] = new Dictionary<int, int> { { j, (int)matrix[i][j] } };
                        }
                    }
                }
            }

            return new CGraph
            {
                Edges = edges,
                NumberOfVertices = numberOfVertices
            };
        }
    }
}
