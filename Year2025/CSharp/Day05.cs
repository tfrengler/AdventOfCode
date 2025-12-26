using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AdventOfCode2025;

[TestFixture]
[NonParallelizable]
public sealed class Day05 : Day
{
    public Day05() : base(5)
    {
        LoadInputAsLines();
        
        //_inputAsLines = [
        //    "3-5",
        //    "10-14",
        //    "16-20",
        //    "12-18",
        //    "",
        //    "1",
        //    "5",
        //    "8",
        //    "11",
        //    "17",
        //    "32"
        //];

        bool doingRanges;

        foreach(string currentLine in _inputAsLines)
        {
            if (currentLine.Length == 0) continue;
            doingRanges = currentLine.Contains('-');

            if (doingRanges)
            {
                var freshIdParts = currentLine.Split('-');

                _freshIdRanges.Add(new(
                    Convert.ToInt64(freshIdParts[0]),
                    Convert.ToInt64(freshIdParts[1])
                ));

                continue;
            }

            _ingredientIds.Add(Convert.ToInt64(currentLine));
        }
    }

    private List<ValueTuple<long, long>> _freshIdRanges = [];
    private readonly List<long> _ingredientIds = [];

    [TestCase]
    public void Part01()
    {
        long result = 0;
        foreach (long currentIngredientId in _ingredientIds)
        {
            foreach ((long freshIdStart, long freshIdEnd) in _freshIdRanges)
            {
                if (currentIngredientId >= freshIdStart && currentIngredientId <= freshIdEnd)
                {
                    result++;
                    break;
                }
            }
        }

        AssertPartAnswer(635, result);
    }

    [TestCase]
    public void Part02()
    {
        long result = 0;

        _freshIdRanges.Sort((first, second) =>
        {
            if (first.Item1 == second.Item1) return 0;
            if (first.Item1 > second.Item1) return 1;
            return -1;
        });

        List<Tuple<long, long>> mergedRanges = [];
        (long currentStart, long currentEnd) = _freshIdRanges[0];

        for (int index = 1; index < _freshIdRanges.Count; index++)
        {
            (long startNext, long endNext) = _freshIdRanges[index];

            if (startNext <= currentEnd)
            {
                currentEnd = Math.Max(currentEnd, endNext);
                continue;
            }

            mergedRanges.Add(new(currentStart, currentEnd));
            currentStart = startNext;
            currentEnd = endNext;
        }

        mergedRanges.Add(new(currentStart, currentEnd));

        foreach ((long start, long end) in mergedRanges)
        {
            result += (end + 1) - start;
        }

        AssertPartAnswer(369761800782619, result);
    }
}
