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
            OriginalData.preparatory_stage();
            OriginalData.form_basis();

            bool work = true;
            while (work)
            {
                OriginalData.calculate_deltas();
                //Console.WriteLine(OriginalData.ToString());
                if (OriginalData.check_optimality())
                {
                    work = false;
                    if (OriginalData.check_artificial_variables_in_basis())
                    {
                        return null;
                    }
                }
                else
                {
                    if (!OriginalData.move_to_optimal_solution())
                    {
                        return null;
                    }
                }
            }

            return OriginalData.get_result();
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

        private static int GetLineMaxFraction(SimplexData data)
        {
            double max = 0.0;
            int index = -1;

            for (int i = 0; i < data.num_of_constraints; i++)
            {
                double f = GetFraction(data.constraints_coefficients[i][data.num_of_vars]);

                if (f > max)
                {
                    max = f;
                    index = i;
                }
            }
            return index;
        }

        private static void FormConstraint(SimplexData data, int line)
        {
            double right = GetFraction(data.constraints_coefficients[line][data.num_of_vars]);
            List<double> left = new List<double>();

            for (int i = 0; i < data.num_of_vars; i++)
            {
                left.Add(GetFraction(data.constraints_coefficients[line][i]));
            }
            left.Add(-1);

            data.add_constraint(left, "=", right);
        }

        private static double GetFraction(double f)
        {
            double integer = Math.Floor(f);
            double res = Math.Abs(integer - f);

            if (IsInteger(res))
            {
                return 0.0;
            }

            return res;
        }

        public static void GomoryMethod(SimplexData data)
        {
            SimplexData inputData = new SimplexData(data);

            bool search = true;
            while (search)
            {
                SimplexResult result = SimplexMethod(inputData);
                Console.WriteLine("========================================");
                if (result != null)
                {
                    //Console.WriteLine(inputData);
                    //Console.WriteLine("----------------------------------------\n");
                    result.Print();
                    if (!CheckVecInteger(result.vec))
                    {
                        int line = GetLineMaxFraction(inputData);
                        FormConstraint(inputData, line);
                        //Console.WriteLine(inputData);
                        //Console.WriteLine("----------------------------------------\n");
                    }
                    else
                    {
                        Console.WriteLine("========================================\n");
                        if (IsInteger(result.f))
                        {
                            Console.WriteLine("Result:");
                            result.Print();
                        }
                        else
                        {
                            Console.WriteLine("Solution does not exist, F is not integer");
                        }
                        search = false;
                    }
                }
                else
                {
                    Console.WriteLine("========================================\n");
                    Console.WriteLine("Solution does not exist");
                    search = false;
                }
            }
        }

        private static bool CheckVecInteger(List<double> vec)
        {
            foreach (double item in vec)
            {
                if (!IsInteger(item))
                {
                    return false;
                }
            }

            return true;
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

            GomoryMethod(data);
        }
    }
}
