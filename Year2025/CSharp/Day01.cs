using AdventOfCode2025.lib;
using NUnit.Framework;
using System;
using System.Diagnostics;

namespace AdventOfCode2025;

[TestFixture]
[NonParallelizable]
public sealed class Day01: Day
{
    public Day01(): base(1)
    {
        LoadInputAsLines();
    }

    [TestCase]
    public void Part01()
    {
        string[] rotations = _inputAsLines;
        Debug.Assert(rotations.Length == 4462);

        int dial = 50;
        int timesRotationHitZero = 0;

        foreach(string currentRotation in rotations)
        {
            int rotationAmount = Convert.ToInt32(currentRotation[1..]);
            if (rotationAmount > 100) rotationAmount = rotationAmount % 100;
            
            if (currentRotation[0] == 'L')
            {
                int subtractResult = dial - rotationAmount;
                dial = subtractResult < 0 ? 100 - Math.Abs(subtractResult) : subtractResult;
            }
            else if (currentRotation[0] == 'R')
            {
                int addResult = dial + rotationAmount;
                dial = addResult switch
                {
                    100 => 0,
                    > 100 => 0 + (addResult - 100),
                    _ => addResult
                };
            }
            else
            {
                throw new Exception("Wait what?");
            }

            Debug.Assert(dial < 100);
            if (dial == 0) timesRotationHitZero++;
        }

        AssertPartAnswer(1076, timesRotationHitZero);
    }

    [TestCase]
    public void Part02()
    {
        string[] rotations = _inputAsLines;
        Debug.Assert(rotations.Length == 4462);

        int dial = 50;
        int result = 0;

        foreach (string currentRotation in rotations)
        {
            int rotationAmount = Convert.ToInt32(currentRotation[1..]);
            for (int i = 1; i <= rotationAmount; i++)
            {
                if (currentRotation[0] == 'L')
                {
                    if (dial == 0)
                    {
                        dial = 99;

                    }
                    else
                    {
                        dial = dial - 1;
                    }
                }
                else
                {
                    if (dial == 99)
                    {
                        dial = 0;
                    }
                    else
                    {
                        dial = dial + 1;
                    }
                }
                if (dial == 0)
                {
                    result++;
                }
            }
        }

        AssertPartAnswer(6379, result);
    }
}
