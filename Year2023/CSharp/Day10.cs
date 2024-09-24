#define TRACE
#define DEBUG

using Microsoft.VisualStudio.TestPlatform.CommunicationUtilities.ObjectModel;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.Metrics;
using System.IO;

namespace AdventOfCode.Year2023
{
    enum Directions: byte
    {
        NtS, EtW, NtE, NtW,
        StW, StE, G,   S
    }

    [TestFixture]
    [NonParallelizable]
    public sealed class Day10
    {
        private readonly Dictionary<char, Directions> DirectionMap = new()
        {
            { '|', Directions.NtS },
            { '-', Directions.EtW },
            { 'L', Directions.NtE },
            { 'J', Directions.NtW },
            { '7', Directions.StW },
            { 'F', Directions.StE },
            { '.', Directions.G },
            { 'S', Directions.S }
        };

        private readonly char[] Maze;
        private readonly int StartPosition = 0;

        public Day10()
        {
            List<char> Maze = new List<char>();
            StringReader InputFile = new(File.ReadAllText("Input/10.txt"));
            int CurrentIndex = -1;

            while(true)
            {
                CurrentIndex++;
                int CurrentChar = InputFile.Read();
                if (CurrentChar == -1)
                {
                    break;
                }

                if (CurrentChar == '\n' || CurrentChar == '\r')
                {
                    continue;
                }

                Maze.Add(Convert.ToChar(CurrentChar));
            }

            this.Maze = Maze.ToArray();

            StartPosition = Array.IndexOf(this.Maze, 'S');
            Debug.Assert(StartPosition != 0, "Start position not found :(");
        }

        /*
            H: 140 | W: 140
            To get line from char: floor(char index / H)
            To get column from char: char index mod W
        */

        private const int MazeWidth = 140;
        private const int MazeHeight = 140;
        private List<int> Visited = new();

        [TestCase(TestName = "Day10_1")]
        public void Part01()
        {
            TestContext.Out.WriteLine($"Found start position at {StartPosition}");

            Span<int> PossibleDirections = stackalloc int[2];
            int PreviousPosition = StartPosition;
            int CurrentPosition = StartPosition;
            PossibleDirections[0] = StartPosition - MazeWidth;
            PossibleDirections[1] = StartPosition - 1;
            int StepsTaken = 0;

            while(true)
            {
                var NextPosition = PossibleDirections[0];

                if (Maze[NextPosition] == '.' || NextPosition == PreviousPosition || Visited.Contains(NextPosition))
                {
                    NextPosition = PossibleDirections[1];
                    if (NextPosition == PreviousPosition)
                    {
                        TestContext.Out.WriteLine("Wut?");
                        break;
                    }
                }

                PreviousPosition = CurrentPosition;
                CurrentPosition = NextPosition;
                // Visited.Add(CurrentPosition);
                char NextChar = Maze[NextPosition];
                StepsTaken++;

                if (NextChar == 'S')
                {
                    TestContext.Out.WriteLine("Found start again, steps taken: " + StepsTaken);
                    break;
                }

                switch(NextChar)
                {
                    case '|':
                        PossibleDirections[0] = CurrentPosition - MazeWidth;
                        PossibleDirections[1] = CurrentPosition + MazeWidth;
                        break;
                    case '-':
                        PossibleDirections[0] = CurrentPosition + 1;
                        PossibleDirections[1] = CurrentPosition - 1;
                        break;
                    case 'L':
                        PossibleDirections[0] = CurrentPosition - MazeWidth;
                        PossibleDirections[1] = CurrentPosition + 1;
                        break;
                    case 'J':
                        PossibleDirections[0] = CurrentPosition - MazeWidth;
                        PossibleDirections[1] = CurrentPosition - 1;
                        break;
                    case '7':
                        PossibleDirections[0] = CurrentPosition - 1;
                        PossibleDirections[1] = CurrentPosition + MazeWidth;
                        break;
                    case 'F':
                        PossibleDirections[0] = CurrentPosition + 1;
                        PossibleDirections[1] = CurrentPosition + MazeWidth;
                        break;
                }

                if (StepsTaken == 100_000_000)
                {
                    TestContext.Out.WriteLine("WARNING: Steps taken limit reached, aborting");
                    break;
                }
            }

            int PartAnswer = StepsTaken / 2;
            TestContext.Out.WriteLine("Part 1 answer: " + PartAnswer);
            Debug.Assert(PartAnswer == 6649);
        }
    }
}
