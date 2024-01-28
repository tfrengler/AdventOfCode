using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace AdventOfCode2023.Year2023
{
    [NonParallelizable]
    [TestFixture]
    public class Day03
    {
        enum Direction
        {
            NONE, N, S, E, W, NE, NW, SE, SW
        }

        const int ColumnWidth = 140;

        readonly struct Symbol
        {
            public Symbol(char value, int position)
            {
                Value = value;
                Position = position;
            }

            public readonly char Value;
            public readonly int Position;

            public override string ToString()
            {
                return $"Value: {Value} | Position: {Position}";
            }
        }

        public readonly struct PartNumber
        {
            public PartNumber(int value, int position, int row, char symbol, int symbolPosition)
            {
                Value = value;
                Position = position;
                Row = row;
                Symbol = symbol;
                SymbolPosition = symbolPosition;
            }

            public int Value { get; }
            public int Position { get; }
            public int Row { get; }
            public char Symbol { get; }
            public int SymbolPosition { get; }

            public override string ToString()
            {
                return $"Value: {Value} | Position = x:{Position}, r:{Row} | Symbol: {Symbol} ({SymbolPosition})";
            }
        }

        readonly char[] Input;

        public Day03()
        {
            Input = File.ReadAllText("Year2023/03.txt").Where(c => c != '\n' && c != '\r').ToArray();
        }

        [TestCase]
        public void Part01()
        {
            var Result = Part01_Result();
            Console.WriteLine(Result);
            Trace.Assert(Result.Item1 == 538046, "Expected solution to be 538046 but it was " + Result);
        }

        public ValueTuple<int, List<PartNumber>> Part01_Result()
        {
            // string Input = "467..114.....*........35..633.......#...617*...........+.58...592...........755....$.*.....664.598..";
            var Schematic = new List<PartNumber>();

            char[] NumberBuffer = new char[3];
            bool InNumber = false;
            int NumberOffset = 0;
            int NumberStartIndex = 0;
            int FinalValue = 0;

            for (int Index = 0; Index<Input.Length; Index++)
            {
                char Current = Input[Index];

                if (IsNumber(Current))
                {
                    if (!InNumber)
                    {
                        InNumber = true;
                        NumberStartIndex = Index;
                    }

                    NumberBuffer[NumberOffset] = Current;
                    NumberOffset++;
                    continue;
                }

                if (!InNumber) continue;
                InNumber = false;

                if (HasSymbol(NumberStartIndex, NumberOffset, out Symbol result))
                {
                    int Number = int.Parse(NumberBuffer);
                    FinalValue += Number;
                    Schematic.Add(new PartNumber(Number, NumberStartIndex, NumberStartIndex / ColumnWidth, result.Value, result.Position));
                }

                NumberBuffer[0] = char.MinValue;
                NumberBuffer[1] = char.MinValue;
                NumberBuffer[2] = char.MinValue;
                NumberOffset = 0;
                NumberStartIndex = 0;
            }

            return ValueTuple.Create(FinalValue, Schematic);
        }

        [TestCase]
        public void Part02()
        {
            var GearSum = Part01_Result()
                .Item2
                .Where(x => x.Symbol == '*')
                .GroupBy(x => x.SymbolPosition)
                .Where(x => x.Count() == 2)
                .Select(x => x.ElementAt(0).Value * x.ElementAt(1).Value)
                .Sum();

            Console.WriteLine(GearSum);
            Trace.Assert(GearSum == 81709807, "Expected solution to be 81709807 but it was " + GearSum);
        }

        bool HasSymbol(int startIndex, int length, out Symbol result)
        {
            var CurrentRow = startIndex / ColumnWidth;

            for (int index = 0; index < length; index++)
            {
                var currentIndex = startIndex + index;
                var CurrentColumn = currentIndex - (CurrentRow * ColumnWidth);

                var N = currentIndex - ColumnWidth;
                var S = currentIndex + ColumnWidth;
                var W = currentIndex - 1;
                var E = currentIndex + 1;
                var NE = currentIndex - ColumnWidth + 1;
                var NW = currentIndex - ColumnWidth - 1;
                var SE = currentIndex + ColumnWidth + 1;
                var SW = currentIndex + ColumnWidth - 1;

                if (N > 0)
                {
                    if (IsSymbol(Input[N])) { result = new(Input[N], N); return true; }
                    if (CurrentColumn < (ColumnWidth - 1))
                    {
                        if (IsSymbol(Input[NE])) { result = new(Input[NE], NE); return true; }
                        if (IsSymbol(Input[NW])) { result = new(Input[NW], NW); return true; }
                    }
                }

                if (S < Input.Length)
                {
                    if (IsSymbol(Input[S])) { result = new(Input[S], S); return true; }
                    if (CurrentColumn > 0)
                    {
                        if (IsSymbol(Input[SE])) { result = new(Input[SE], SE); return true; }
                        if (IsSymbol(Input[SW])) { result = new(Input[SW], SW); return true; }
                    }
                }

                if (CurrentColumn > 0 && IsSymbol(Input[W])) { result = new(Input[W], W); return true; }
                if (CurrentColumn < (ColumnWidth - 1) && IsSymbol(Input[E])) { result = new(Input[E], E); return true; }
            }

            result = new();
            return false;
        }

        static readonly char[] ValidNumbers = new char[] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        static readonly char[] NonSymbols = new char[] { '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        static bool IsNumber(char input) => Array.IndexOf(ValidNumbers, input) > -1;
        static bool IsSymbol(char input) => Array.IndexOf(NonSymbols, input) == -1;
    }
}
