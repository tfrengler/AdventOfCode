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
    }

    [TestCase]
    public void Part01()
    {
        _inputAsLines[0] = _inputAsLines[0].Replace('S', '|');
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
        var manifold = new Grid(_inputAsLines);
        var start = manifold.FindFirst('S');
        
        var quantumPathBuffer = new long[manifold.Height, manifold.Width];
        quantumPathBuffer[start.Y, start.X] = 1;

        manifold.BoundaryCrossingIsFatal = false;
        long result = 0;

        foreach (GridPoint point in manifold.EnumerateGrid())
        {
            if (quantumPathBuffer[point.Y, point.X] == 0 && (point.Value == '.' || point.Value == '^'))
            {
                continue;
            }

            var south = manifold.GetSouth(point);
            if (south.Value == '.')
            {
                CalculateAndSetPointValue(quantumPathBuffer, point, south);
                continue;
            }

            if (!south.IsValid)
            {
                result += quantumPathBuffer[point.Y, point.X];
                continue;
            }

            if (south.Value == '^')
            {
                var sw = manifold.GetSouthWest(point);
                var se = manifold.GetSouthEast(point);

                CalculateAndSetPointValue(quantumPathBuffer, point, sw);
                CalculateAndSetPointValue(quantumPathBuffer, point, se);
            }
        }

        //PrintManifold2(manifold, quantumPathBuffer);
        AssertPartAnswer(1393669447690, result);
    }

    private static void CalculateAndSetPointValue(long[,] quantumBuffer, GridPoint origin, GridPoint destination)
    {
        long destinationValue = quantumBuffer[destination.Y, destination.X];
        long originValue = quantumBuffer[origin.Y, origin.X];
        quantumBuffer[destination.Y, destination.X] = destinationValue + originValue;
    }

    private static void PrintManifold2(Grid manifold, int[,] quantumBuffer)
    {
        var outputFile = Path.Combine(AppContext.BaseDirectory, "input/debug.txt");
        Console.WriteLine(outputFile);

        using (StreamWriter outputfile = File.CreateText(outputFile))
        {
            int charCounter = 0;

            foreach (var point in manifold.EnumerateGrid())
            {
                int valueAtPoint = quantumBuffer[point.Y, point.X];
                string output = string.Empty;

                if (valueAtPoint > 0)
                {
                    output = Convert.ToString(valueAtPoint).PadLeft(2, '0');
                }
                else
                {
                    output = Convert.ToString(point.Value).PadLeft(2, point.Value);
                }

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
