using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Diagnostics.CodeAnalysis;
using System.Drawing;
using System.IO;

namespace AdventOfCode2025;

[TestFixture]
[NonParallelizable]
public sealed class Day07: Day
{
    public Day07(): base(7)
    {
        LoadInputAsLines();
    }

    [TestCase]
    public void Part01()
    {
        _inputAsLines[0] = _inputAsLines[0].Replace('S', '|');

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

    [TestCase]
    public void Part02()
    {
        string[] testInput = [
            ".......S.......",
            "...............",
            ".......^.......",
            "...............",
            "......^.^......",
            "...............",
            ".....^.^.^.....",
            "...............",
            "....^.^...^....",
            "...............",
            "...^.^...^.^...",
            "...............",
            "..^...^.....^..",
            "...............",
            ".^.^.^.^.^...^.",
            "...............",
        ];
        testInput[0] = testInput[0].Replace('S', (char)0x01);
        var manifold = new Grid(testInput);
        var intManifold = new int[manifold.Height, manifold.Width];

        //_inputAsLines[0] = _inputAsLines[0].Replace('S', (char)0x01);
        //var manifold = new Grid(_inputAsLines);

        manifold.BoundaryCrossingIsFatal = false;
        int result = 0;

        foreach (GridPoint point in manifold.EnumerateGrid())
        {
            if (point.Value == '.' || point.Value == '^') continue;

            var south = manifold.GetSouth(point);
            if (south.Value != '^')
            {
                if (!south.IsValid)
                {
                    result += (int)point.Value;
                    continue;
                }
                CalculateAndSetPointValue(manifold, point, south);
                continue;
            }

            if (south.Value == '^')
            {
                var sw = manifold.GetSouthWest(point);
                var se = manifold.GetSouthEast(point);

                CalculateAndSetPointValue(manifold, point, sw);
                CalculateAndSetPointValue(manifold, point, se);
            }
        }

        //PrintManifold2(manifold);
        AssertPartAnswer(1393669447690, result);
    }

    private static GridPoint CalculateAndSetPointValue(Grid manifold, GridPoint origin, GridPoint destination)
    {
        int destinationVal = destination.Value == '.' ? (char)0 : destination.Value;
        int amountToAdd = (int)origin.Value;

        //Console.WriteLine($"Change destination value that is {destinationVal}, adding {amountToAdd}");
        return manifold.SetPoint(destination, (char)(destinationVal + amountToAdd));
    }

    private static void PrintManifold2(Grid manifold)
    {
        var outputFile = Path.Combine(AppContext.BaseDirectory, "input/debug.txt");
        Console.WriteLine(outputFile);

        using (StreamWriter outputfile = File.CreateText(outputFile))
        {
            int charCounter = 0;

            foreach (var point in manifold.EnumerateGrid())
            {
                string output = point.Value switch
                {
                    '^' or '.' => Convert.ToString(point.Value).PadLeft(2, point.Value),
                    _ => Convert.ToString((int)point.Value).PadLeft(2, '0')
                };

                outputfile.Write(output);
                charCounter++;

                if (charCounter % manifold.Width == 0)
                {
                    outputfile.Write(Environment.NewLine);
                }
            }
        }
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
