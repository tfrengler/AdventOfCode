using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace AdventOfCode2025;

[TestFixture]
[NonParallelizable]
public sealed class Day06 : Day
{
    public Day06() : base(6)
    {
        LoadInputAsLines();
    }

    private sealed record Problem
    {
        public List<long> Numbers { get; } = [];
        public char Operator { get; set; }
    }

    [TestCase]
    public void Part01()
    {
        //_inputAsLines = [
        //    "123 328  51 64 ",
        //    " 45 64  387 23 ",
        //    "  6 98  215 314",
        //    "*   +   *   +  ",
        //];

        int height = _inputAsLines.Length-1;

        List<char> operatorList = _inputAsLines[height]
            .Split(' ', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
            .Select(Convert.ToChar)
            .ToList();

        int width = operatorList.Count;
        Debug.Assert(width == 1000);
        List<List<long>> numberGrid = [];

        List<long> numbersBufferPerRow = [];
        List<char> charBuffer = new(20);

        List<Problem> listOfProblems = [];

        for(int index = 0; index < height; index++)
        {
            string currentInputRow = _inputAsLines[index];
            foreach (char currentChar in currentInputRow)
            {
                // If buffer has chars and space is encountered: convert to number, clear buffer
                // If buffer has no chars and space is encountered: skip
                // If char is encountered: add to buffer
                if (charBuffer.Count > 0 && !char.IsAsciiDigit(currentChar))
                {
                    numbersBufferPerRow.Add(Convert.ToInt64(new string(charBuffer.ToArray())));
                    charBuffer.Clear();
                    continue;
                }

                if (charBuffer.Count == 0 && currentChar == ' ')
                {
                    continue;
                }

                charBuffer.Add(currentChar);
            }

            if (charBuffer.Count > 0)
            {
                numbersBufferPerRow.Add(Convert.ToInt64(new string(charBuffer.ToArray())));
            }

            numberGrid.Add(numbersBufferPerRow.ToList());
            numbersBufferPerRow.Clear();
        }

        for(int columnIndex = 0; columnIndex < width; columnIndex++)
        {
            var problem = new Problem()
            {
                Operator = operatorList[columnIndex]
            };

            for (int rowIndex = 0; rowIndex < height; rowIndex++)
            {
                problem.Numbers.Add(numberGrid[rowIndex][columnIndex]);
            }

            listOfProblems.Add(problem);
        }

        long result = 0;

        foreach(var currentProblem in listOfProblems)
        {
            long problemResult = currentProblem.Numbers[0];
            for(int index = 1; index < currentProblem.Numbers.Count; index++)
            {
                switch(currentProblem.Operator)
                {
                    case '*': problemResult *= currentProblem.Numbers[index]; break;
                    case '+': problemResult += currentProblem.Numbers[index]; break;
                    default: throw new Exception("Wait what?");
                }
            }
            result += problemResult;
        }

        AssertPartAnswer(6299564383938, result);
    }
}
