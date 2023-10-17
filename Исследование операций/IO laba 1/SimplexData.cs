using System;
using System.Collections.Generic;

namespace IO_laba_1
{
    public struct Optional<T>
    {
        private readonly T _value;
        public bool HasValue { get; }

        public Optional(T value)
        {
            _value = value;
            HasValue = true;
        }

        public T Value => HasValue ? _value : throw new InvalidOperationException("Optional<T> has no value.");

        public static implicit operator Optional<T>(T value)
        {
            return new Optional<T>(value);
        }

        public static explicit operator T(Optional<T> optional)
        {
            return optional.Value;
        }
    }

    public class SimplexData
    {
        public int num_of_vars_in_f;
        public int num_of_vars;
        public int num_of_constraints;
        public int direction;
        public List<double> coefficients;
        public List<List<double>> constraints_coefficients;
        public List<string> conditions;
        public List<Optional<int>> basis;
        public HashSet<int> artificial_variables;
        public List<double> deltas;
        public const double M = double.MaxValue;

        public SimplexData()
        {
            coefficients = new List<double>();
            constraints_coefficients = new List<List<double>>();
            conditions = new List<string>();
            basis = new List<Optional<int>>();
            artificial_variables = new HashSet<int>();
            deltas = new List<double>();
        }

        public void preparatory_stage()
        {
            for (int i = 0; i < constraints_coefficients.Count; i++)
            {
                var item = constraints_coefficients[i];
                if (item[num_of_vars] < 0.0)
                {
                    for (int j = 0; j < item.Count; j++)
                    {
                        item[j] = -item[j];
                    }
                    if (conditions[i] == ">=")
                    {
                        conditions[i] = "<=";
                    }
                    else if (conditions[i] == "<=")
                    {
                        conditions[i] = ">=";
                    }
                }
            }

            for (int i = 0; i < conditions.Count; i++)
            {
                var condition = conditions[i];
                if (condition == "<=" || condition == ">=")
                {
                    coefficients.Add(0.0);

                    for (int j = 0; j < constraints_coefficients.Count; j++)
                    {
                        var item = constraints_coefficients[j];
                        if (i == j)
                        {
                            if (condition == ">=")
                            {
                                item.Insert(num_of_vars, -1.0);
                                condition = "=";
                            }
                            else if (condition == "<=")
                            {
                                item.Insert(num_of_vars, 1.0);
                                basis[i] = num_of_vars;
                                condition = "=";
                            }
                        }
                        else
                        {
                            item.Insert(num_of_vars, 0.0);
                        }
                    }

                    num_of_vars++;
                }
            }
        }

        public void form_basis()
        {
            for (int i = 0; i < num_of_vars; i++)
            {
                int index = 0;
                int number_of_non_zeros = 0;
                for (int j = 0; j < num_of_constraints; j++)
                {
                    if (constraints_coefficients[j][i] != 0.0)
                    {
                        number_of_non_zeros++;
                        index = j;
                    }
                }
                if (number_of_non_zeros == 1 && constraints_coefficients[index][i] == 1.0)
                {
                    if (!basis[index].HasValue)
                    {
                        basis[index] = i;
                    }
                }
            }

            for (int i = 0; i < basis.Count; i++)
            {
                if (!basis[i].HasValue)
                {
                    basis[i] = num_of_vars;
                    for (int j = 0; j < num_of_constraints; j++)
                    {
                        if (i == j)
                        {
                            constraints_coefficients[j].Insert(num_of_vars, 1.0);
                        }
                        else
                        {
                            constraints_coefficients[j].Insert(num_of_vars, 0.0);
                        }
                    }
                    if (direction == 0)
                    {
                        coefficients.Insert(num_of_vars, M);
                    }
                    else if (direction == 1)
                    {
                        coefficients.Insert(num_of_vars, -M);
                    }
                    artificial_variables.Add(num_of_vars);
                    num_of_vars++;
                }
            }
        }

        public void calculate_deltas()
        {
            deltas.Clear();

            for (int i = 0; i < num_of_vars; i++)
            {
                double delta = 0.0;

                for (int j = 0; j < num_of_constraints; j++)
                {
                    delta += coefficients[basis[j].Value] * constraints_coefficients[j][i];
                }

                delta -= coefficients[i];
                delta = Math.Round(delta, 10);
                deltas.Add(delta);
            }
        }

        public bool check_optimality()
        {
            foreach (var delta in deltas)
            {
                if (direction == 1 && delta < 0.0)
                {
                    return false;
                }
                else if (direction == 0 && delta > 0.0)
                {
                    return false;
                }
            }

            return true;
        }

        public int get_resolving_column_index()
        {
            int min_index = -1;

            for (int i = 0; i < deltas.Count; i++)
            {
                if (min_index == -1 || deltas[i] < deltas[min_index])
                {
                    min_index = i;
                }
            }

            return min_index;
        }

        public bool move_to_optimal_solution()
        {
            List<(int, double)> Q = new List<(int, double)>();
            int column_index = get_resolving_column_index();

            for (int i = 0; i < num_of_constraints; i++)
            {
                double a = constraints_coefficients[i][column_index];
                double b = constraints_coefficients[i][num_of_vars];

                if (a > 0.0)
                {
                    Q.Add((i, b / a));
                }
            }

            if (Q.Count == 0)
            {
                return false;
            }

            int index = Q[Q.Count - 1].Item1;
            double min = Q[Q.Count - 1].Item2;

            if (index > 0)
            {
                for (int i = Q.Count - 2; i >= 0; i--)
                {
                    if (Q[i].Item2 <= min)
                    {
                        min = Q[i].Item2;
                        index = Q[i].Item1;
                    }
                }
            }

            basis[index] = column_index;
            double value = constraints_coefficients[index][column_index];

            for (int i = 0; i < num_of_vars + 1; i++)
            {
                constraints_coefficients[index][i] /= value;
            }

            for (int i = 0; i < num_of_constraints; i++)
            {
                if (i != index)
                {
                    double c = constraints_coefficients[i][column_index];

                    for (int j = 0; j <= num_of_vars; j++)
                    {
                        double v = constraints_coefficients[index][j];
                        constraints_coefficients[i][j] -= v * c;
                    }
                }
            }

            return true;
        }

        public bool check_artificial_variables_in_basis()
        {
            foreach (var artificialVarIndex in artificial_variables)
            {
                if (basis.Contains(artificialVarIndex))
                {
                    if (coefficients[artificialVarIndex] != 0.0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        public void print_result()
        {
            Console.Write("Optimal solution found:\nx = { ");

            for (int i = 0; i < num_of_vars-1; i++)
            {
                int basisIndex = basis.IndexOf(i);

                if (basisIndex != -1)
                {
                    Console.Write($"{constraints_coefficients[basisIndex][num_of_vars]:F}; ");
                }
                else
                {
                    Console.Write("0; ");
                }
            }

            if (basis.IndexOf(num_of_vars - 1) != -1)
            {
                Console.Write($"{constraints_coefficients[basis.IndexOf(num_of_vars - 1)][num_of_vars]:F}" + "}");
            }
            else
            {
                Console.Write("0 }");
            }

            double delta = 0.0;
            for (int j = 0; j < num_of_constraints; j++)
            {
                delta += coefficients[basis[j].Value] * constraints_coefficients[j][num_of_vars];
            }
            Console.WriteLine("\nObjective function value: " + $"{delta:F}");
        }

        public void _canonical_view()
        {
            for (int i = 0; i < num_of_constraints; i++)
            {
                if (conditions[i] == ">=")
                {
                    conditions[i] = "<=";

                    for (int j = 0; j < num_of_vars; j++)
                    {
                        constraints_coefficients[i][j] = -constraints_coefficients[i][j];
                    }
                }
            }

            for (int i = 0; i < num_of_constraints; i++)
            {
                if (conditions[i] == "<=")
                {
                    conditions[i] = "=";

                    coefficients.Add(0.0);

                    for (int j = 0; j <= num_of_vars; j++)
                    {
                        if (i == j)
                        {
                            constraints_coefficients[i].Insert(num_of_vars, 1.0);
                        }
                        else
                        {
                            constraints_coefficients[i].Insert(num_of_vars, 0.0);
                        }
                    }

                    num_of_vars++;
                }
            }
        }

        public bool _check_basis()
        {
            foreach (var item in basis)
            {
                if (!item.HasValue)
                {
                    return false;
                }
            }

            return true;
        }

        public bool check_many_solutions()
        {
            int count = 0;
            for (int i = 0; i < num_of_vars; i++)
            {
                if (deltas[i] == 0.0)
                {
                    count++;
                }
            }
            if (count > num_of_constraints)
            {
                return true;
            }

            return false;
        }

        public override string ToString()
        {
            string result = "";
            result += "========================================\n";
            result += $"number of variables: {num_of_vars}\n";
            result += $"number of constraints: {num_of_constraints}\n";
            result += $"min(0) or max(1): {direction}\n";
            result += "----------------------------------------\n";

            string coefficientsLine = "";
            foreach (var item in coefficients)
            {
                if (item > 10000) { coefficientsLine += $"{"M",8}"; }
                else if (item < -10000) { coefficientsLine += $"{"-M",8}"; }
                else { coefficientsLine += $"{item,8:F4}"; }
            }
            result += coefficientsLine + "\n";

            foreach (var vec in constraints_coefficients)
            {
                string constraintLine = "";
                foreach (var item in vec)
                {
                    constraintLine += $"{item,8:F4}";
                }
                result += constraintLine + "\n";
            }

            string basisString = "Basis: ";
            foreach (var item in basis)
            {
                if (item.HasValue)
                {
                    basisString += $"{item.Value,-5}";
                }
                else
                {
                    basisString += $"{'n',5}";
                }
            }
            result += basisString + "\n";

            string artificialVariablesString = "Artificial variables: ";
            foreach (var item in artificial_variables)
            {
                artificialVariablesString += $"{item,-8:F4}";
            }
            result += artificialVariablesString + "\n";

            string conditionsString = "Conditions: ";
            foreach (var item in conditions)
            {
                conditionsString += $"{item} ";
            }
            result += conditionsString + "\n";

            string deltasString = "Deltas:\n";       
            foreach (var item in deltas)
            {
                if (item > 10000) { deltasString += $"{"M "}"; }
                else if (item < -10000) { deltasString += $"{"-M "}"; }
                else { deltasString += $"{item:F} "; }
            }
            result += deltasString;

            return result;
        }
    }
}
