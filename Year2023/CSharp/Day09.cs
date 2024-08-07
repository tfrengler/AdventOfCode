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
    public sealed class Day09
    {
        private int[][] Input;
        private readonly string[] InputContents;

        public Day09()
        {
            /*Input = new int[][]
            {
                [0,3,6,9,12,15],
                [1,3,6,10,15,21],
                [10,13,16,21,30,45]
            };
            return;*/

            InputContents = File.ReadAllLines("./Input/09.txt");
        }

        private int CalculateAnswer()
        {
            List<int[]> Sequences = new List<int[]>();
            int PartAnswer = 0;

            for (int OuterIndex = 0; OuterIndex < Input.Length; OuterIndex++)
            {
                int[] CurrentInput = Input[OuterIndex];

                while (true)
                {
                    int InputLengthMinOne = CurrentInput.Length - 1;
                    int[] CurrentSequence = new int[InputLengthMinOne];
                    Sequences.Add(CurrentSequence);
                    int Sum = 0;

                    for (int Index = 0; Index < InputLengthMinOne; Index++)
                    {
                        int Diff = CurrentInput[Index + 1] - CurrentInput[Index];
                        CurrentSequence[Index] = Diff;
                        Sum = Sum + Math.Abs(Diff);
                    }

                    if (Sum == 0) break;
                    CurrentInput = CurrentSequence;
                }

                int HistoryValue = 0;
                for (int Index = Sequences.Count - 1; Index >= 0; Index--)
                {
                    HistoryValue += Sequences[Index][^1];
                }

                HistoryValue += Input[OuterIndex][^1];
                PartAnswer += HistoryValue;
                Sequences.Clear();
            }

            return PartAnswer;
        }

        [TestCase]
        public void Part01()
        {
            int Index = 0;
            Input = new int[InputContents.Length][];
            foreach (string Current in InputContents)
            {
                Input[Index] = Current.Split(" ").Select(x => Convert.ToInt32(x)).ToArray();
                Index++;
            }

            int PartAnswer = CalculateAnswer();
            Trace.Assert(PartAnswer == 1974913025);
            Console.WriteLine("Part answer: " + PartAnswer);
        }

        [TestCase]
        public void Part02()
        {
            int Index = 0;
            Input = new int[InputContents.Length][];
            foreach (string Current in InputContents)
            {
                Input[Index] = Current.Split(" ").Select(x => Convert.ToInt32(x)).Reverse().ToArray();
                Index++;
            }

            int PartAnswer = CalculateAnswer();
            Trace.Assert(PartAnswer == 884);
            Console.WriteLine("Part answer: " + PartAnswer);
        }
    }
}
