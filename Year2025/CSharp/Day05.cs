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

        //_freshIdRanges.Sort((first, second) =>
        //{
        //    if (first.Item1 == second.Item1) return 0;
        //    if (first.Item1 > second.Item1) return 1;
        //    return -1;
        //});

        _freshIdRanges = _freshIdRanges
            .OrderBy(x => x.Item1)
            .ThenBy(x => x.Item2)
            .ToList();

        List<Tuple<long, long>> mergedRanges = [];

        for (int outerIndex = 0; outerIndex < _freshIdRanges.Count; outerIndex++)
        {
            (long start, long end) = _freshIdRanges[outerIndex];
            // Last one? Nothing to compare to so just add it
            if (outerIndex + 1 == _freshIdRanges.Count)
            {
                mergedRanges.Add(new(start, end));
                break;
            }

            for (int innerIndex = outerIndex + 1; innerIndex < _freshIdRanges.Count; innerIndex++)
            {
                (long startNext, long endNext) = _freshIdRanges[innerIndex];

                // Next range completely within our current range?
                // Ignore
                if (start >= startNext && end <= endNext)
                {
                    continue;
                }

                // The next range's start is greater than our end
                // Therefore it is a greater range and we add the current range
                // and stop comparing ranges
                if (startNext >= end)
                {
                    mergedRanges.Add(new(start,end));
                    break;
                }
                // Is the end of the next range greater than our current?
                // Then we move our current range's end up to the new end
                if (endNext > end)
                {
                    end = endNext;
                }

                if (innerIndex+1 == _freshIdRanges.Count) mergedRanges.Add(new(start, end));
                // At this point we know that:
                // Start of next range is within current start and end
                // End of next range is greater than current end
                // Therefore increment outer index because we are going to merge that one
                // and it does not need to considered and compared
                outerIndex++;
            }
        }

        foreach((long start, long end) in mergedRanges)
        {
            result += (end + 1) - start;
        }

        AssertPartAnswer(0, result);
    }
}
