using System;
using System.Collections.Generic;

class Program
{
    public class gramm
    {
        public char Condition { get; set; }
        public List<(char, HashSet<char>)> Transitions { get; set; }

        public gramm(char condition)
        {
            Condition = condition;
            Transitions = new List<(char, HashSet<char>)>();
        }
    }

    static void Main(string[] args)
    {
        List<char> set = new List<char> { 'H', 'S', 'R', 'N', 'G' };
        List<List<char>> subsets = FindSubsets(set);

        List<gramm> table = new();

        gramm item = new gramm('H');
        item.Transitions.Add(('#', new HashSet<char> { '-' }));
        item.Transitions.Add(('h', new HashSet<char> { 'R', 'G' }));
        item.Transitions.Add(('x', new HashSet<char> { '-' }));
        item.Transitions.Add(('z', new HashSet<char> { '-' }));

        table.Add(item);

        item.Condition = 'R';
        item.Transitions[0] = ('#', new HashSet<char> { 'S' });
        item.Transitions[0] = ('h', new HashSet<char> { '-' });
        item.Transitions[0] = ('x', new HashSet<char> { 'R' });
        item.Transitions[0] = ('z', new HashSet<char> { 'R', 'N' });

        table.Add(item);

        item.Condition = 'S';
        item.Transitions[0] = ('#', new HashSet<char> { '-' });
        item.Transitions[0] = ('h', new HashSet<char> { '-' });
        item.Transitions[0] = ('x', new HashSet<char> { '-' });
        item.Transitions[0] = ('z', new HashSet<char> { '-' });

        table.Add(item);

        item.Condition = 'N';
        item.Transitions[0] = ('#', new HashSet<char> { '-' });
        item.Transitions[0] = ('h', new HashSet<char> { 'N', 'R', 'G' });
        item.Transitions[0] = ('x', new HashSet<char> { '-' });
        item.Transitions[0] = ('z', new HashSet<char> { '-' });

        table.Add(item);

        item.Condition = 'G';
        item.Transitions[0] = ('#', new HashSet<char> { 'S' });
        item.Transitions[0] = ('h', new HashSet<char> { 'G' });
        item.Transitions[0] = ('x', new HashSet<char> { 'R', 'G' });
        item.Transitions[0] = ('z', new HashSet<char> { '-' });

        table.Add(item);

        List<List<char>> plenty = new();
        foreach (var subset in subsets)
        {
            subset.Add('#');
            plenty.Add(subset);
        }

        foreach (var subset in subsets)
        {
            subset.Remove('#');
            subset.Add('h');
            plenty.Add(subset);
        }

        foreach (var subset in subsets)
        {
            subset.Remove('h');
            subset.Add('x');
            plenty.Add(subset);
        }

        foreach (var subset in subsets)
        {
            subset.Remove('x');
            subset.Add('z');
            plenty.Add(subset);
        }

        foreach (var subset in plenty)
        {
            HashSet<char> result = new();
            foreach (var condition in subset)
            {

            }
            Console.WriteLine(string.Join("", subset));
        }
    }

    static List<List<char>> FindSubsets(List<char> set)
    {
        List<List<char>> subsets = new List<List<char>>();
        FindSubsets(set, 0, new List<char>(), subsets);
        return subsets;
    }

    static void FindSubsets(List<char> set, int index, List<char> current, List<List<char>> subsets)
    {
        if (index == set.Count)
        {
            subsets.Add(new List<char>(current));
            return;
        }

        // Не включаем элемент
        FindSubsets(set, index + 1, current, subsets);

        // Включаем элемент
        current.Add(set[index]);
        FindSubsets(set, index + 1, current, subsets);

        // Убираем элемент после использования, чтобы вернуться к предыдущему состоянию
        current.RemoveAt(current.Count - 1);
    }
}