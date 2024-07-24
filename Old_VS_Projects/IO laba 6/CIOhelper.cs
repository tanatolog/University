using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IO_laba_6
{
    class CIOhelper
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

        public static Data Parse(string input)
        {
            List<int> attachments = new List<int>();
            List<List<int>> profits = new List<List<int>>();

            // Retain only digits, commas, and semicolons
            string cleanedString = new string(input.Where(c => char.IsDigit(c) || c == ',' || c == ';').ToArray());

            // Split by semicolon
            string[] parts = cleanedString.Split(';');

            // Process the first part as attachments
            if (parts.Length > 0)
            {
                attachments = parts[0].Split(',').Select(int.Parse).ToList();
                if (attachments.IndexOf(0) == -1) 
                {
                    attachments.Insert(0, 0); 
                }
            }

            // Process the remaining parts as profits
            for (int i = 1; i < parts.Length; i++)
            {
                List<int> tmp = parts[i].Split(',').Select(int.Parse).ToList();
                if (tmp.Count != attachments.Count)
                {
                    tmp.Insert(0, 0);
                }
                profits.Add(tmp);
            }

            Console.WriteLine("Задача:\n" + input);

            return new Data
            {
                Attachments = attachments,
                Profits = profits
            };
        }
    }
}
