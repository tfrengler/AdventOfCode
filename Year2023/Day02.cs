using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AdventOfCode2023.Year2023
{
    [TestFixture]
    public class Day02
    {
        [TestCase]
        public void Part01()
        {
            int FinalValue = 0;
            string[] Input = File.ReadAllLines("Year2023/02.txt");
            /*
            string[] Input = new[]
            {
                "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
                "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
                "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
                "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
                "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green",
            };*/

            var ColorRegex = new Regex(@"(\d+?) (blue|red|green)");
            var GameIdRegex = new Regex(@"Game (\d+):");

            foreach (string currentInput in Input)
            {
                int GameId = int.Parse(GameIdRegex.Match(currentInput).Groups[1].ToString());

                var Greens = new List<int>();
                var Blues = new List<int>();
                var Reds = new List<int>();

                MatchCollection Matches = ColorRegex.Matches(currentInput);
                foreach(Match currentMatch in Matches)
                {
                    int ColorAmount = int.Parse(currentMatch.Groups[1].ToString());

                    switch(currentMatch.Groups[2].ToString())
                    {
                        case "green":
                            Greens.Add(ColorAmount);
                            break;

                        case "blue":
                            Blues.Add(ColorAmount);
                            break;

                        case "red":
                            Reds.Add(ColorAmount);
                            break;

                        default: throw new Exception("Not possible unless programmer = fubar");
            }
                }

                if (Reds.Max() <= 12 && Greens.Max() <= 13 && Blues.Max() <= 14) FinalValue += GameId;
            }

            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 2204, "Expected solution to be 2204 but it was " + FinalValue);
        }

        [TestCase]
        public void Part02()
        {
            int FinalValue = 0;
            string[] Input = File.ReadAllLines("Year2023/02.txt");
            /*
            string[] Input = new[]
            {
                "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
                "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
                "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
                "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
                "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green",
            };*/

            var ColorRegex = new Regex(@"(\d+?) (blue|red|green)");
            var GameIdRegex = new Regex(@"Game (\d+):");

            foreach (string currentInput in Input)
            {
                int GameId = int.Parse(GameIdRegex.Match(currentInput).Groups[1].ToString());

                var Greens = new List<int>();
                var Blues = new List<int>();
                var Reds = new List<int>();

                MatchCollection Matches = ColorRegex.Matches(currentInput);
                foreach (Match currentMatch in Matches)
                {
                    int ColorAmount = int.Parse(currentMatch.Groups[1].ToString());

                    switch (currentMatch.Groups[2].ToString())
                    {
                        case "green":
                            Greens.Add(ColorAmount);
                            break;

                        case "blue":
                            Blues.Add(ColorAmount);
                            break;

                        case "red":
                            Reds.Add(ColorAmount);
                            break;

                        default: throw new Exception("Not possible unless programmer = fubar");
                    }
                }

                int MinSets = Reds.Max() * Greens.Max() * Blues.Max();
                FinalValue += MinSets;
            }

            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 71036, "Expected solution to be 71036 but it was " + FinalValue);
        }
    }
}
