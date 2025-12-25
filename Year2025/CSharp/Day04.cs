using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;

namespace AdventOfCode2025
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day04: Day
    {
        public Day04(): base(4)
        {
            LoadInputAsLines();
        }

        const char PaperRollChar = '@';

        [TestCase]
        public void Part01()
        {
            //string[] paperRollGrid = [
            //    "..@@.@@@@.",
            //    "@@@.@.@.@@",
            //    "@@@@@.@.@@",
            //    "@.@@@@..@.",
            //    "@@.@@@@.@@",
            //    ".@@@@@@@.@",
            //    ".@.@.@.@@@",
            //    "@.@@@.@@@@",
            //    ".@@@@@@@@.",
            //    "@.@.@@@.@.",
            //];
            //var grid = new Grid(paperRollGrid);

            var grid = new Grid(_inputAsLines);
            grid.BoundaryCrossingIsFatal = false;
            
            int result = 0;
            
            foreach(var currentPoint in grid.EnumerateGrid())
            {
                if (currentPoint.Value != PaperRollChar)
                {
                    continue;
                }

                var box = grid.GetBox(currentPoint);
                if (box.Sum(x => x.Value == PaperRollChar ? 1 : 0) > 3)
                {
                    continue;
                }

                result++;
            }

            Console.WriteLine("Part answer is: " + result);
            System.Diagnostics.Trace.Assert(result == 1367, "Expected part answer to be 1367");
        }

        [TestCase]
        public void Part02()
        {
            //string[] paperRollGrid = [
            //    "..@@.@@@@.",
            //    "@@@.@.@.@@",
            //    "@@@@@.@.@@",
            //    "@.@@@@..@.",
            //    "@@.@@@@.@@",
            //    ".@@@@@@@.@",
            //    ".@.@.@.@@@",
            //    "@.@@@.@@@@",
            //    ".@@@@@@@@.",
            //    "@.@.@@@.@.",
            //];
            //var grid = new Grid(paperRollGrid);

            var grid = new Grid(_inputAsLines);
            grid.BoundaryCrossingIsFatal = false;

            int result = 0;

            List<GridPoint> rollsToRemove = FindRollsToRemove(grid);
            
            while (rollsToRemove.Count > 0)
            {
                result += rollsToRemove.Count;

                foreach(var currentRoll in rollsToRemove)
                {
                    grid.SetPoint(currentRoll, '.');
                }

                rollsToRemove = FindRollsToRemove(grid);
            }

            Console.WriteLine("Part answer is: " + result);
            System.Diagnostics.Trace.Assert(result == 1367, "Expected part answer to be 1367");
        }

        private static List<GridPoint> FindRollsToRemove(Grid grid)
        {
            List<GridPoint> rollsToRemove = [];

            foreach (GridPoint currentPoint in grid.EnumerateGrid())
            {
                if (currentPoint.Value != PaperRollChar)
                {
                    continue;
                }

                GridPoint[] box = grid.GetBox(currentPoint);
                if (box.Sum(x => x.Value == PaperRollChar ? 1 : 0) > 3)
                {
                    continue;
                }

                rollsToRemove.Add(currentPoint);
            }

            return rollsToRemove;
        }
    }
}
