using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;


namespace IO_laba_1
{
    class Program
    {
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

        static void Main(string[] args)
        {
            string input = Input();
            var data = Parse(input);
            data.preparatory_stage();
            data.form_basis();

            bool work = true;
            while (work)
            {
                data.calculate_deltas();          
                Console.WriteLine(data);             
                if (data.check_optimality())
                {
                    work = false;
                    if (data.check_artificial_variables_in_basis())
                    {
                        string s = "It doesn't have a correct solution because the solution contains artificial variables!";
                        Console.WriteLine(s);
                    }
                    else
                    {
                        data.print_result();
                        if (data.check_many_solutions())         // Проверить много решений
                        {
                            Console.WriteLine("Many solutions!");
                        }
                    }
                }
                else
                {
                    if (!data.move_to_optimal_solution())
                    {
                        Console.WriteLine("The function is not limited. There is no optimal solution!");
                        work = false;
                    }
                }
            }
        }
    }
}
