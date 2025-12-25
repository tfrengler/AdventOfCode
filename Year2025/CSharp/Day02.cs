using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Linq;

namespace AdventOfCode2025
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day02 : Day
    {
        public Day02(): base(2)
        {
            LoadInputAsString();
        }

        [TestCase]
        public void Part01()
        {
            string[] idRanges = _inputAsString.Split(',');
            long result = 0;
            
            foreach(var currentRange in idRanges)
            {
                string[] rangeParts = currentRange.Split('-');
                long startRange = Convert.ToInt64(rangeParts[0]);
                long endRange = Convert.ToInt64(rangeParts[1]);

                for(long index = startRange; !(index > endRange); index++)
                {
                    string currentId = Convert.ToString(index);
                    if (currentId.Length % 2 != 0) continue;

                    string firstHalf = new(currentId.Take(currentId.Length / 2).ToArray());
                    string secondHalf = new(currentId.Skip(currentId.Length / 2).ToArray());

                    if (firstHalf == secondHalf)
                    {
                        result += index;
                    }
                }
            }

            AssertPartAnswer(38310256125, result);
        }

        [TestCase]
        public void Part02()
        {
            /*
                A string s is composed of a repeating substring if and only if:

                s is a substring of (s + s) with the first and last characters removed.
                
                This is a classic string‑theory result.
             */

            string[] idRanges = _inputAsString.Split(',');
            long result = 0;

            foreach (var currentRange in idRanges)
            {
                string[] rangeParts = currentRange.Split('-');
                long startRange = Convert.ToInt64(rangeParts[0]);
                long endRange = Convert.ToInt64(rangeParts[1]);

                for (long index = startRange; !(index > endRange); index++)
                {
                    string currentId = Convert.ToString(index);

                    string doubled = currentId + currentId;
                    string trimmed = doubled[1..^1];
                    if (trimmed.Contains(currentId))
                    {
                        result += index;
                    }
                }
            }

            AssertPartAnswer(58961152806, result);
        }
    }
}
