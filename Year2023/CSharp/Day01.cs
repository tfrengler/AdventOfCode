using NUnit.Framework;
using System.Linq;
using System;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;

namespace AdventOfCode2023.Year2023
{
    [TestFixture]
    public class Day01
    {
        [TestCase]
        public void Part01()
        {
            string[] Input = File.ReadAllLines("Input/01.txt");
            string[] Input2 = new[]
            {
                "1abc2",
                "pqr3stu8vwx",
                "a1b2c3d4e5f",
                "treb7uchet",
            };
            int FinalValue = 0;

            int Index = 0;
            foreach (string current in Input)
            {
                // if (Index > 3) break;

                var Digits = current.Where(char.IsDigit);
                char[] Parts = new char[2];
                Parts[0] = Digits.First();
                Parts[1] = Digits.Last();

                FinalValue += Convert.ToInt32(new string(Parts));

                Index++;
            }

            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 55621, "Expected solution to be 55621 but it was " + FinalValue);
        }

        [TestCase]
        public void Part02()
        {
            string[] Input = File.ReadAllLines("Input/01.txt");
            // string[] Input = new[]
            // {
            //     "two1nine",
            //     "eightwothree",
            //     "abcone2threexyz",
            //     "xtwone3four",
            //     "4nineeightseven2",
            //     "zoneight234",
            //     "7pqrstsixteen",
            // };

            int SumCalibration = 0;

            foreach (string current in Input)
            {
                List<char> Digits = new();

                for (int index = 0; index < current.Length; index++)
                {
                    if (char.IsDigit(current[index]))
                    {
                        Digits.Add(current[index]);
                        continue;
                    }

                    int CharsToTake = current.Length - index;
                    if (CharsToTake < 3) continue;
                    string currentSubstring = current.Substring(index, CharsToTake);

                    char Value = currentSubstring switch
                    {
                        string x when x.StartsWith("one") => '1',
                        string x when x.StartsWith("two") => '2',
                        string x when x.StartsWith("three") => '3',
                        string x when x.StartsWith("four") => '4',
                        string x when x.StartsWith("five") => '5',
                        string x when x.StartsWith("six") => '6',
                        string x when x.StartsWith("seven") => '7',
                        string x when x.StartsWith("eight") => '8',
                        string x when x.StartsWith("nine") => '9',
                        _ => char.MinValue
                    };

                    if (Value != char.MinValue) Digits.Add(Value);
                }

                char[] Parts = new char[2];
                Parts[0] = Digits[0];
                Parts[1] = Digits.Last();

                string Calibration = new(Parts);
                // WriteLine(Calibration);
                SumCalibration += Convert.ToInt32(Calibration);

                // break;
            }

            Console.WriteLine(SumCalibration);
            Trace.Assert(SumCalibration == 53592, "Expected solution to be 53592 but it was " + SumCalibration);
        }
    }
}
