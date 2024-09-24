#define TRACE
#define DEBUG

using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        private int StepsInPath = 0;

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

        [TestCase(TestName = "Day10_1")]
        public void Part01()
        {
            TestContext.Out.WriteLine($"Found start position at {StartPosition}");
            List<int> PathIndices = new();

            Span<int> PossibleDirections = stackalloc int[2];
            int PreviousPosition = StartPosition;
            int CurrentPosition = StartPosition;
            PossibleDirections[0] = StartPosition - MazeWidth;
            PossibleDirections[1] = StartPosition - 1;
            int StepsTaken = 0;

            while(true)
            {
                var NextPosition = PossibleDirections[0];

                if (Maze[NextPosition] == '.' || NextPosition == PreviousPosition)
                {
                    NextPosition = PossibleDirections[1];
                    if (NextPosition == PreviousPosition)
                    {
                        TestContext.Out.WriteLine("Wut?");
                        break;
                    }
                }
                PathIndices.Add(NextPosition);

                PreviousPosition = CurrentPosition;
                CurrentPosition = NextPosition;
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

                if (StepsTaken == 1_000_000)
                {
                    TestContext.Out.WriteLine("WARNING: Steps taken limit reached, aborting");
                    break;
                }
            }

            StepsInPath = StepsTaken;
            ExportCleanMaze(PathIndices);

            int PartAnswer = StepsTaken / 2;
            TestContext.Out.WriteLine("Part 1 answer: " + PartAnswer);
            Debug.Assert(PartAnswer == 6649);
        }

        private void ExportCleanMaze(IEnumerable<int> indices)
        {
            char[] MazeCopy = new char[Maze.Length];
            Array.Fill(MazeCopy, '.');

            foreach (int PathIndex in indices)
            {
                MazeCopy[PathIndex] = Maze[PathIndex];
            }

            MazeCopy[StartPosition] = 'J';

            using (FileStream OutputFile = File.Create("C:/Temp/AoC_CleanMaze.txt"))
            {
                using (var OutputStream = new StreamWriter(OutputFile))
                {
                    for (int Index = 0; Index < MazeWidth; Index++)
                    {
                        int StartWriteIndex = Index * MazeWidth;
                        OutputStream.WriteLine(MazeCopy, StartWriteIndex, MazeWidth);
                    }
                }
            }

            int NewWidth = MazeWidth * 3;
            int NewSize = NewWidth * NewWidth;
            char[] ExpandedMaze = new char[NewSize];
            int ExpandedMazeIndex = -3;

            for(int Index = 0; Index < MazeCopy.Length; Index++)
            {
                ExpandedMazeIndex += 3;

                if (MazeCopy[Index] == '.')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '7')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '#';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '#';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '#';
                    continue;
                }

                if (MazeCopy[Index] == 'L')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '#';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '#';
                    continue;
                }

                if (MazeCopy[Index] == 'J')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '#';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '#';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '#';
                    continue;
                }

                if (MazeCopy[Index] == 'F')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '#';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '#';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '|')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '-')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + NewWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + NewWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 1] = '#';
                    ExpandedMaze[ExpandedMazeIndex + (NewWidth * 2) + 2] = '.';
                    continue;
                }
            }

            using (FileStream OutputFile = File.Create("C:/Temp/AoC_ExpandedMaze.txt"))
            {
                using (var OutputStream = new StreamWriter(OutputFile))
                {
                    for (int Index = 0; Index < NewWidth; Index++)
                    {
                        int StartWriteIndex = Index * NewWidth;
                        OutputStream.WriteLine(ExpandedMaze, StartWriteIndex, NewWidth);
                    }
                }
            }
        }

        //[TestCase(TestName = "Day10_2")]
        public void Part02()
        {
            /*var IndicesQueue = new Queue<uint>(MazeHeight * MazeWidth);
            IndicesQueue.Enqueue(0);
            List<uint> Visited = new();

            while(IndicesQueue.Count > 0)
            {
                var Next = IndicesQueue.Dequeue();
                if (Visited.Contains(Next))
                {
                    continue;
                }
                Visited.Add(Next);

                if (Next % MazeWidth != (MazeWidth - 1))
                {
                    uint East = Next + 1;
                    if (Maze[East] == '.')
                    {
                        IndicesQueue.Enqueue(East);
                    }
                }

                if (Next >= MazeWidth)
                {
                    uint North = Next - MazeWidth;
                    if (Maze[North] == '.' && !IndicesQueue.Contains(North))
                    {
                        IndicesQueue.Enqueue(North);
                    }
                }

                if (Next % MazeWidth != 0)
                {
                    uint West = Next - 1;
                    if (Maze[West] == '.')
                    {
                        IndicesQueue.Enqueue(West);
                    }
                }

                if (Next < (MazeWidth * MazeWidth) - MazeWidth)
                {
                    uint South = 0;
                    try
                    {
                        South = Next + MazeWidth;
                        if (Maze[South] == '.')
                        {
                            IndicesQueue.Enqueue(South);
                        }
                    }
                    catch(Exception)
                    {
                        throw new System.OverflowException($"Overflow getting south. Next: {Next} | South: {South}");
                    }
                }
            }*/

            /*foreach (uint PathIndex in Visited)
            {
                Maze[PathIndex] = '*';
            }

            using (FileStream OutputFile = File.Create("C:/Temp/AoCTemp2.txt"))
            {
                using (var OutputStream = new StreamWriter(OutputFile))
                {
                    for(int Index = 0; Index < MazeHeight; Index++)
                    {
                        int StartWriteIndex = Index * MazeHeight;
                        OutputStream.WriteLine(Maze, StartWriteIndex, 140);
                    }
                }
            }

            int PartAnswer = Maze.Length - Visited.Count - StepsInPath;
            TestContext.Out.WriteLine($"Outside the loop: " + PartAnswer);*/
        }
    }
}
