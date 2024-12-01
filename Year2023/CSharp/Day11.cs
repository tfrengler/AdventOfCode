using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

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

        Galaxy[] StarMap = [];

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
        ];

        public void SetUp()
        {
            string[] FileContent = File.ReadAllLines("Input/11.txt");
            TestInput = FileContent;

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
            int xExpansions = 0;
            // X-axis expansion
            StarMap = StarMapInterim.ToArray();

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
                xExpansions++;

                for (int galaxyIndex = 0; galaxyIndex < StarMapInterim.Count; galaxyIndex++)
                {
                    Galaxy currentGalaxy = StarMapInterim[galaxyIndex];
                    if (currentGalaxy.X > x)
                    {
                        var CopyGalaxy = StarMap[galaxyIndex];
                        var NewGalaxy = new Galaxy(CopyGalaxy.X + 1, CopyGalaxy.Y);
                        StarMap[galaxyIndex] = NewGalaxy;
                    }

                }
            }
        }

        void VisualizeStarMap(int xWidth, int yWidth)
        {
            char[,] Map = new char[yWidth, xWidth];
            for(int index1 = 0; index1 < Map.GetLength(0); index1++)
            {
                for (int index2 = 0; index2 < Map.GetLength(1); index2++)
                {
                    Map[index1, index2] = '.';
                }
            }

            for (int galaxyIndex = 0; galaxyIndex < StarMap.Length; galaxyIndex++)
            {
                Galaxy currentGalaxy = StarMap[galaxyIndex];
                Map[currentGalaxy.Y, currentGalaxy.X] = '#';
            }

            var Output = new StringBuilder();
            for (int index1 = 0; index1 < Map.GetLength(0); index1++)
            {
                for (int index2 = 0; index2 < Map.GetLength(1); index2++)
                {
                    Output.Append(Map[index1, index2]);
                }
                Output.AppendLine();
            }

            Console.WriteLine(Output.ToString());
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
            Trace.Assert(Sum == 9233514);
        }
    }
}
