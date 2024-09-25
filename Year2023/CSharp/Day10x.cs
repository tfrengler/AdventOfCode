using NUnit.Framework;
using System;
using System.IO;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day10x
    {
        private char[,] Maze;

        public Day10x()
        {
            
        }

        [TestCase]
        public void Test()
        {
            string[] TempMaze = File.ReadAllLines("Input/Debug.txt");
            Maze = new char[TempMaze.Length,TempMaze[0].Length];

            for (int OuterIndex = 0; OuterIndex < Maze.GetLength(0); OuterIndex++)
            {
                for (int InnerIndex = 0; InnerIndex < Maze.GetLength(1); InnerIndex++)
                {
                    Maze[OuterIndex, InnerIndex] = TempMaze[OuterIndex][InnerIndex];
                }
            }

            for (int OuterIndex = 0; OuterIndex < Maze.GetLength(0); OuterIndex++)
            {
                for (int InnerIndex = 0; InnerIndex < Maze.GetLength(1); InnerIndex++)
                {
                    Console.Write(Maze[OuterIndex, InnerIndex]);
                }
                Console.Write(Environment.NewLine);
            }
        }
    }
}
