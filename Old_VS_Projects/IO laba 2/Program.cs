using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace IO_laba_2
{
    class Program
    {
        static SimplexResult SimplexMethod(SimplexData OriginalData)
        {
            SimplexData data = new SimplexData(OriginalData);
            data.preparatory_stage();
            data.form_basis();

            bool work = true;
            while (work)
            {
                data.calculate_deltas();
                //Console.WriteLine(data.ToString());  
                if (data.check_optimality())
                {
                    work = false;
                    if (data.check_artificial_variables_in_basis())
                    {
                        return null;
                    }
                }
                else
                {
                    if (!data.move_to_optimal_solution())
                    {
                        return null;
                    }
                }
            }

            return data.get_result();
        }

        static string Input()
        {
            string[] lines = File.ReadAllLines("Task.txt");
            foreach (var line in lines) 
                Console.WriteLine(line); 

            string s = string.Empty;
            string input = string.Empty;
            int i = 0;

            while (s != "end")
            {
                s = string.Empty;
                s = lines[i];
                s = s.Trim();
                input += s;
                i += 1;
            }

            return input;
        }

        static SimplexData Parse(string s)
        {
            string[] lines = s.Split(';');
            List<string> trimmedLines = new List<string>(lines.Length);

            foreach (string line in lines)
            {
                trimmedLines.Add(line.Trim());
            }

            SimplexData data = new SimplexData();
            data.num_of_vars = int.Parse(string.Join("", trimmedLines[0].Where(c => char.IsDigit(c))));
            data.num_of_vars_in_f = int.Parse(string.Join("", trimmedLines[0].Where(c => char.IsDigit(c))));
            data.num_of_constraints = int.Parse(string.Join("", trimmedLines[1].Where(c => char.IsDigit(c))));
            data.direction = int.Parse(string.Join("", trimmedLines[2].Where(c => char.IsDigit(c))));

            trimmedLines[3] = trimmedLines[3].Remove(0, 32);
            data.coefficients = new List<double>(Array.ConvertAll(string.Join("", trimmedLines[3].Where(c => (char.IsDigit(c) || (c == '.') || (c == ' ') || (c == '-')))).Split(), double.Parse));

            trimmedLines[4] = trimmedLines[4].Remove(0, 25);
            for (int i = 4; i < 4 + data.num_of_constraints; i++)
            {
                string[] tokens = trimmedLines[i].Split();
                List<double> constraintCoefficients = new List<double>();

                for (int j = 0; j < data.num_of_vars; j++)
                {
                    constraintCoefficients.Add(double.Parse(tokens[j]));
                }

                data.conditions.Add(tokens[data.num_of_vars]);
                constraintCoefficients.Add(double.Parse(tokens[data.num_of_vars + 1]));

                data.constraints_coefficients.Add(constraintCoefficients);
                data.basis.Add(new Optional<int>());
            }
            return data;
        }

        static void branch_and_bound_method(SimplexData data)
        {
            if (data != null)
            {
                Console.WriteLine("========================================\n");
                List<SimplexResult> intResults = new List<SimplexResult>();
                LinkedList<SimplexData> list = new LinkedList<SimplexData>();
                list.AddFirst(data);

                SimplexData CurrentData = new SimplexData();
                SimplexResult CurrenResult = new SimplexResult();

                while (list.Count > 0)
                {
                        CurrentData = list.Last.Value;              
                        list.RemoveLast();                          
                        CurrenResult = SimplexMethod(CurrentData);  
                        if (CurrenResult != null)                   
                        {
                            CurrenResult.Print();
                            Console.WriteLine("----------------------------------------\n");
                            if (CheckResultForInteger(CurrenResult))
                            {
                                intResults.Add(CurrenResult);
                            }
                            else
                            {
                                bool BranchIsMax = true;
                                foreach (SimplexResult item in intResults)
                                {
                                    if (item.f > CurrenResult.f) { BranchIsMax = false; }
                                }
                                List<(int, double)> nonIntegerValues = GetNonIntegerValue(CurrenResult);
                                if ((nonIntegerValues.Count > 0) && BranchIsMax)
                                {
                                    
                                    int index = nonIntegerValues[0].Item1;
                                    double value = nonIntegerValues[0].Item2;

                                    SimplexData left = new SimplexData(CurrentData);
                                    SimplexData right = new SimplexData(CurrentData);
                                    left.add_condition(index, "<=", Math.Floor(value));
                                    right.add_condition(index, ">=", Math.Ceiling(value));
                                    list.AddFirst(left);
                                    list.AddFirst(right);
                                }
                                else
                                {
                                    Console.WriteLine("Branch has no solution");
                                    Console.WriteLine("----------------------------------------\n");
                                }
                            }
                        }
                        else
                        {
                            Console.WriteLine("Branch has no solution");
                            Console.WriteLine("----------------------------------------\n");
                        }
                }
                if (intResults.Count > 0)
                {
                    Console.WriteLine("Result:");
                    SimplexResult bestSolution = new SimplexResult();
                    if (data.direction == 1) { bestSolution = FindMaxSolution(intResults); }
                    else { bestSolution = FindMinSolution(intResults); }
                    bestSolution.Print();
                }
                else
                {
                    Console.WriteLine("Solution does not exist");
                }
            }
            else
            {
                Console.WriteLine("Solution does not exist");
            }
        }

        private static SimplexResult FindMaxSolution(List<SimplexResult> vec)
        {
            SimplexResult result = new SimplexResult();
            result.f = double.MinValue;
            foreach (SimplexResult item in vec)
            {
                if (item.f > result.f) { result = item; }
            }
            return result;
        }

        private static SimplexResult FindMinSolution(List<SimplexResult> vec)
        {
            SimplexResult result = new SimplexResult();
            result.f = double.MaxValue;
            foreach (SimplexResult item in vec)
            {
                if (item.f < result.f) { result = item; }
            }
            return result;
        }

        private static bool CheckResultForInteger(SimplexResult result)
        {
            foreach (double item in result.vec)
            {
                if (!IsInteger(item))
                {
                    return false;
                }
            }

            return IsInteger(result.f);
        }

        private static List<(int, double)> GetNonIntegerValue(SimplexResult result)
        {
            List<(int, double)> nonIntegerValues = new List<(int, double)>();

            for (int i = 0; i < result.vec.Count; i++)
            {
                double item = result.vec[i];
                if (!IsInteger(item))
                {
                    nonIntegerValues.Add((i, item));
                }
            }

            return nonIntegerValues;
        }

        private static bool IsInteger(double value)
        {
            double integer = Math.Round(value);
            const double EPS = 0.00000000001;
            if (Math.Abs(value - integer) < EPS)
            {
                return true;
            }
            return false;
        }

        static void Main(string[] args)
        {
            string input = Input();
            SimplexData data = Parse(input);

            branch_and_bound_method(data);
        }
    }
}
