using NUnit.Framework;
using System;
using System.IO;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day11
    {
        readonly char[,] Input;

        public Day11()
        {
            string[] FileContent = File.ReadAllLines("Input/11.txt");
            Input = new char[FileContent.Length, FileContent.Length];

            for(int index = 0; index < FileContent.Length; index++)
            {
                string current = FileContent[index];
                for(int charIndex = 0; charIndex < current.Length; charIndex++)
                {
                    Input[index, charIndex] = current[charIndex];
                }
            }
        }

        static int manhattanDist(int X1, int Y1, int X2, int Y2)
        {
            int dist = Math.Abs(X2 - X1) + Math.Abs(Y2 - Y1);
            return dist;
        }

        // Num galaxy pairs = (Galaxies - 1) + (Galaxies - 2) until 1

        [TestCase]
        public void Part01()
        {
            TestContext.Out.WriteLine("0,21: " + Input[0, 21]);
            TestContext.Out.WriteLine("6,2: " + Input[6, 2]);
        }
    }
}
