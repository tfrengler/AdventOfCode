using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.IO;

namespace AdventOfCode2025;

[TestFixture]
[NonParallelizable]
public sealed class Day07: Day
{
    public Day07(): base(7)
    {
        LoadInputAsLines();
        _inputAsLines[0] = _inputAsLines[0].Replace('S', '|');
    }

    [TestCase]
    public void Part01()
    {
        //var manifold = new Grid([
        //    ".......|.......",
        //    "...............",
        //    ".......^.......",
        //    "...............",
        //    "......^.^......",
        //    "...............",
        //    ".....^.^.^.....",
        //    "...............",
        //    "....^.^...^....",
        //    "...............",
        //    "...^.^...^.^...",
        //    "...............",
        //    "..^...^.....^..",
        //    "...............",
        //    ".^.^.^.^.^...^.",
        //    "...............",
        //]);

        var manifold = new Grid(_inputAsLines);
        manifold.BoundaryCrossingIsFatal = false;
        int result = 0;

        foreach(GridPoint point in manifold.EnumerateGrid())
        {
            if (point.Value == '|')
            {
                SpawnBeamBelowMaybe(manifold, point);
                continue;
            }

            if (point.Value == '^')
            {
                var north = manifold.GetNorth(point);
                if (north.Value == '|')
                {
                    var west = manifold.GetWest(point);
                    var east = manifold.GetEast(point);

                    if (west.Value != '|')
                    {
                        west = manifold.SetPoint(west, '|');
                        SpawnBeamBelowMaybe(manifold, west);
                    }

                    if (east.Value != '|')
                    {
                        east = manifold.SetPoint(east, '|');
                        SpawnBeamBelowMaybe(manifold, east);
                    }

                    result++;
                }
            }
        }

        //PrintManifold(manifold);
        AssertPartAnswer(1516, result);
    }

    private static void SpawnBeamBelowMaybe(Grid grid, GridPoint point)
    {
        var south = grid.GetSouth(point);
        if (!south.IsValid || south.Value == '^') return;
        grid.SetPoint(south, '|');
    }

    private static void PrintManifold(Grid manifold)
    {
        var outputFile = Path.Combine(AppContext.BaseDirectory, "input/debug.txt");
        Console.WriteLine(outputFile);
  
        using (StreamWriter outputfile = File.CreateText(outputFile))
        {
            int charCounter = 0;

            foreach (var point in manifold.EnumerateGrid())
            {
                outputfile.Write(point.Value);
                charCounter++;

                if (charCounter % manifold.Width == 0)
                {
                    outputfile.Write(Environment.NewLine);
                }
            }
        }
    }
}
