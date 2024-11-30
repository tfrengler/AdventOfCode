using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day11
    {
        struct Galaxy
        {
            public int X { get; set; }
            public int Y { get; set; }

            public Galaxy(int x, int y)
            {
                X = x;
                Y = y;
            }
        }

        Galaxy[] StarMap;

        string[] TestInput =
        [
            "...#......",
            ".......#..",
            "#.........",
            "..........",
            "......#...",
            ".#........",
            ".........#",
            "..........",
            ".......#..",
            "#...#.....",
            /*
            "....#........",
            ".........#...",
            "#............",
            ".............",
            ".............",
            "........#....",
            ".#...........",
            "............#",
            ".............",
            ".............",
            ".........#...",
            "#....#.......",*/
        ];

        public void SetUp()
        {
            //string[] FileContent = File.ReadAllLines("Input/11.txt");
            //TestInput = FileContent;
            var StarMapInterim = new List<Galaxy>();
            int yExpansionFactor = 0;

            for(int y = 0; y < TestInput.Length; y++)
            {
                string currentRow = TestInput[y];
                int EmptyCount = 0;

                for (int x = 0; x < currentRow.Length; x++)
                {
                    if (currentRow[x] == '.')
                    {
                        EmptyCount++;
                        continue;
                    }
                    StarMapInterim.Add(new Galaxy(x, y + yExpansionFactor));
                }

                if (EmptyCount == currentRow.Length)
                {
                    yExpansionFactor++;
                }
            }
            // X-axis expansion
            for (int x = 0; x < TestInput[0].Length; x++)
            {
                int EmptyCount = 0;
                for (int y = 0; y < TestInput.Length; y++)
                {
                    if (TestInput[y][x] == '.')
                    {
                        EmptyCount++;
                    }
                }

                if (EmptyCount != TestInput.Length) continue;

                for (int galaxyIndex = 0; galaxyIndex < StarMapInterim.Count; galaxyIndex++)
                {
                    Galaxy currentGalaxy = StarMapInterim[galaxyIndex];
                    if (currentGalaxy.X > x)
                    {
                        StarMapInterim[galaxyIndex] = new Galaxy(currentGalaxy.X + 1, currentGalaxy.Y);
                    }
                }
            }

            StarMap = StarMapInterim.ToArray();
        }

        static int CalculateManhattanDistance(int X1, int Y1, int X2, int Y2)
        {
            int dist = Math.Abs(X2 - X1) + Math.Abs(Y2 - Y1);
            return dist;
        }

        [TestCase]
        public void Part01()
        {
            SetUp();

            int Sum = 0;
            int Pairs = 0;

            for(int outerIndex = 0; outerIndex < StarMap.Length; outerIndex++)
            {
                Galaxy Current = StarMap[outerIndex];
                for (int innerIndex = outerIndex+1; innerIndex < StarMap.Length; innerIndex++)
                {
                    Pairs++;
                    Galaxy Partner = StarMap[innerIndex];
                    Sum += CalculateManhattanDistance(Current.X, Current.Y, Partner.X, Partner.Y);
                }
            }

            TestContext.Out.WriteLine($"Part 01 answer (based on {Pairs} pairs): " + Sum);
        }
    }
}
