#define TRACE
#define DEBUG

using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day10
    {
        private readonly int StartPosition = 0;
        private readonly char[] Maze;
        private readonly int[] PathIndices;
        private readonly int MazeWidthAndHeight = 0;

        public Day10()
        {
            const string InputFileName = "10.txt";
            List<char> Maze = new List<char>();
            MazeWidthAndHeight = File.ReadAllLines($"Input/{InputFileName}")[0].Length;
            StringReader InputFile = new(File.ReadAllText($"Input/{InputFileName}"));
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
            Debug.Assert(StartPosition > -1, "Start position not found :(");

            List<int> PathIndices = new();
            Span<int> PossibleDirections = stackalloc int[2];
            int PreviousPosition = StartPosition;
            int CurrentPosition = StartPosition;
            // ACTUAL
            PossibleDirections[0] = StartPosition - MazeWidthAndHeight;
            PossibleDirections[1] = StartPosition - 1;
            // DEBUG
            // PossibleDirections[0] = StartPosition - 1;
            // PossibleDirections[1] = StartPosition + MazeWidthAndHeight;

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

                if (NextChar == 'S')
                {
                    break;
                }

                switch(NextChar)
                {
                    case '|':
                        PossibleDirections[0] = CurrentPosition - MazeWidthAndHeight;
                        PossibleDirections[1] = CurrentPosition + MazeWidthAndHeight;
                        break;
                    case '-':
                        PossibleDirections[0] = CurrentPosition + 1;
                        PossibleDirections[1] = CurrentPosition - 1;
                        break;
                    case 'L':
                        PossibleDirections[0] = CurrentPosition - MazeWidthAndHeight;
                        PossibleDirections[1] = CurrentPosition + 1;
                        break;
                    case 'J':
                        PossibleDirections[0] = CurrentPosition - MazeWidthAndHeight;
                        PossibleDirections[1] = CurrentPosition - 1;
                        break;
                    case '7':
                        PossibleDirections[0] = CurrentPosition - 1;
                        PossibleDirections[1] = CurrentPosition + MazeWidthAndHeight;
                        break;
                    case 'F':
                        PossibleDirections[0] = CurrentPosition + 1;
                        PossibleDirections[1] = CurrentPosition + MazeWidthAndHeight;
                        break;
                }

                if (PathIndices.Count == 1_000_000)
                {
                    TestContext.Out.WriteLine("WARNING: Steps taken limit reached, aborting");
                    break;
                }
            }

            this.PathIndices = PathIndices.ToArray();

            /*char[] MazeCopy = new char[MazeWidthAndHeight * MazeWidthAndHeight];
            Array.Fill(MazeCopy, '.');

            foreach (int PathIndex in PathIndices)
            {
                MazeCopy[PathIndex] = Maze[PathIndex] switch
                {
                    '7' => '┐',
                    'F' => '┌',
                    'J' => '┘',
                    'L' => '└',
                    '-' => '-',
                    '|' => '|',
                    'S' => 'S',
                    _ => throw new Exception($"Bugger: {Maze[PathIndex]}")
                };
            }

            File.WriteAllText("C:/Temp/AoC_Maze.txt", new string(this.Maze));

            using (FileStream OutputFile = File.Create("C:/Temp/AoC_CleanMaze.txt"))
            {
                using (var OutputStream = new StreamWriter(OutputFile))
                {
                    for(int Index = 0; Index < MazeWidthAndHeight; Index++)
                    {
                        int StartWriteIndex = Index * MazeWidthAndHeight;
                        OutputStream.WriteLine(MazeCopy, StartWriteIndex, MazeWidthAndHeight);
                    }
                }
            }*/
        }

        [TestCase(TestName = "Day10_1")]
        public void Part01()
        {
            int PartAnswer = PathIndices.Length / 2;
            TestContext.Out.WriteLine("Part 1 answer: " + PartAnswer);
            Debug.Assert(PartAnswer == 6649);
        }

        // Spent days on this and I can't figure it out. I give up... :(
        // https://www.101computing.net/the-shoelace-algorithm/
        [TestCase(TestName = "Day10_2")]
        public void Part02()
        {
            TestContext.WriteLine($"Found start position at {StartPosition}");
            TestContext.WriteLine($"Maze width/weight is {MazeWidthAndHeight}");

            #region EXPAND MAZE
            char[] MazeCopy = new char[Maze.Length];
            Array.Fill(MazeCopy, '.');

            foreach (int PathIndex in PathIndices)
            {
                MazeCopy[PathIndex] = Maze[PathIndex];
            }

            // MazeCopy[StartPosition] = '7'; // DEBUG
            MazeCopy[StartPosition] = 'J'; // ACTUAL

            const int ExpandedMazeStride = 3;
            const int ExpansionFactor = ExpandedMazeStride * ExpandedMazeStride;
            int ExpandedMazeWidth = MazeWidthAndHeight * ExpandedMazeStride;
            int ExpandedMazeSize = ExpandedMazeWidth * ExpandedMazeWidth;
            char[] ExpandedMaze = new char[ExpandedMazeSize];
            int ExpandedMazeIndex = -3;

            for(int Index = 0; Index < MazeCopy.Length; Index++)
            {
                if (Index > 0 && Index % MazeWidthAndHeight == 0)
                {
                    ExpandedMazeIndex += (ExpandedMazeWidth * 2) + ExpandedMazeStride;
                }
                else
                {
                    ExpandedMazeIndex += ExpandedMazeStride;
                }

                if (MazeCopy[Index] == '.')
                {
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '7')
                {
                    /*
                        ...
                        ##.
                        .#.
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '-';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '┐';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == 'L')
                {
                    /*
                        .#.
                        .##
                        ...
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '└';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '-';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == 'J')
                {
                    /*
                        .#.
                        ##.
                        ...
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '-';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '┘';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == 'F')
                {
                    /*
                        ...
                        .##
                        .#.
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '┌';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '-';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '|')
                {
                    /*
                        .#.
                        .#.
                        .#.
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '.';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '|';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                    continue;
                }

                if (MazeCopy[Index] == '-')
                {
                    /*
                        ...
                        ###
                        ...
                    */
                    ExpandedMaze[ExpandedMazeIndex] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + 2] = '.';

                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth] = '-';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 1] = '-';
                    ExpandedMaze[ExpandedMazeIndex + ExpandedMazeWidth + 2] = '-';

                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2)] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 1] = '.';
                    ExpandedMaze[ExpandedMazeIndex + (ExpandedMazeWidth * 2) + 2] = '.';
                }
            }

            #endregion
            #region FLOOD FILL

            var IndicesQueue = new Queue<int>(ExpandedMazeSize);
            IndicesQueue.Enqueue(0);

            while(IndicesQueue.Count > 0)
            {
                var Next = IndicesQueue.Dequeue();
                if (ExpandedMaze[Next] == '*')
                {
                    continue;
                }
                ExpandedMaze[Next] = '*';

                if (Next % ExpandedMazeWidth != (ExpandedMazeWidth - 1))
                {
                    int East = Next + 1;
                    if (ExpandedMaze[East] == '.')
                    {
                        IndicesQueue.Enqueue(East);
                    }
                }

                if (Next >= ExpandedMazeWidth)
                {
                    int North = Next - ExpandedMazeWidth;
                    if (ExpandedMaze[North] == '.')
                    {
                        IndicesQueue.Enqueue(North);
                    }
                }

                if (Next % ExpandedMazeWidth != 0)
                {
                    int West = Next - 1;
                    if (ExpandedMaze[West] == '.')
                    {
                        IndicesQueue.Enqueue(West);
                    }
                }

                if (Next < (ExpandedMazeSize - ExpandedMazeWidth))
                {
                    int South = Next + ExpandedMazeWidth;
                    if (ExpandedMaze[South] == '.')
                    {
                        IndicesQueue.Enqueue(South);
                    }
                }
            }

            /*using (FileStream OutputFile = File.Create("C:/Temp/AoC_ExpandedFloodFilled.txt"))
            {
                using (var OutputStream = new StreamWriter(OutputFile))
                {
                    for(int Index = 0; Index < ExpandedMazeWidth; Index++)
                    {
                        int StartWriteIndex = Index * ExpandedMazeWidth;
                        OutputStream.WriteLine(ExpandedMaze, StartWriteIndex, ExpandedMazeWidth);
                    }
                }
            }*/

            #endregion

            int PartAnswer = ExpandedMaze.Count(x => x == '.');
            TestContext.Out.WriteLine("Part answer: " + (PartAnswer / ExpansionFactor));
        }
    }
}
