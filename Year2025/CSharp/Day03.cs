using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace AdventOfCode2025
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day03 : Day
    {
        public Day03() : base(3)
        {
            LoadInputAsLines();
        }

        [TestCase]
        public void Part01()
        {
            string[] banks = _inputAsLines;
            //string[] banks = [
            //    "987654321111111",
            //    "811111111111119",
            //    "234234234234278",
            //    "818181911112111"
            //];

            int totalOutputJoltage = 0;

            foreach (string bank in banks)
            {
                byte finalJoltage = 0;
                int startIndexSecondDigit = 1;

                foreach (char battery in bank)
                {
                    int index = startIndexSecondDigit;

                    while (index < bank.Length)
                    {
                        byte newJoltage = Convert.ToByte(new string([battery, bank[index]]));
                        if (newJoltage > finalJoltage)
                        {
                            finalJoltage = newJoltage;
                        }
                        index++;
                    }

                    startIndexSecondDigit++;
                }

                totalOutputJoltage += finalJoltage;
            }

            Console.WriteLine("Result: " + totalOutputJoltage);
            Debug.Assert(totalOutputJoltage == 17524, "Expected result to be 17524");
        }

        [TestCase]
        public void Part02()
        {
            string[] banks = _inputAsLines;
            //string[] banks = [
            //    "987654321111111",
            //    "811111111111119",
            //    "234234234234278",
            //    "818181911112111"
            //];

            long totalOutputJoltage = 0;

            foreach (string currentBank in banks)
            {
                var stack = new Stack<long>();
                int drops = banks[0].Length - 12;

                long[] batteryJoltages = currentBank.Select(x => Convert.ToInt64(x - '0')).ToArray();

                foreach (long digit in batteryJoltages)
                {
                    while (stack.Count > 0 && drops > 0 && stack.Peek() < digit)
                    {
                        stack.Pop();
                        drops--;
                    }

                    stack.Push(digit);
                }

                while (drops > 0 && stack.Count > 0)
                {
                    stack.Pop();
                    drops--;
                }

                long[] d = stack.ToArray();
                Array.Reverse(d);

                long result = Convert.ToInt64(string.Concat(d));
                totalOutputJoltage += result;
            }

            Console.WriteLine("Result: " + totalOutputJoltage);
            Debug.Assert(totalOutputJoltage == 173848577117276, "Expected result to be 173848577117276");
        }
    }
}
