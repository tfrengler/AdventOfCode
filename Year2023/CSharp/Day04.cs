using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AdventOfCode2023.Year2023
{
    [NonParallelizable]
    [TestFixture]
    public sealed class Day04
    {
        readonly string[] Input;
        readonly Dictionary<int, int> Cards;

        public Day04()
        {
            Input = File.ReadAllLines("Input/04.txt");
            Cards = new Dictionary<int, int>(Input.Length);
        }

        [TestCase]
        public void Part01()
        {
            int FinalScore = 0;
            int InputIndex = 0;

            foreach (string currentLine in Input)
            {
                string[] Parts = currentLine.Split('|', StringSplitOptions.TrimEntries);
                var DigitMatch = new Regex(@"(\d+)");

                var IdAndWinnerParts = Parts[0].Split(':', StringSplitOptions.TrimEntries);
                var CardNumber = Convert.ToInt32(DigitMatch.Matches(IdAndWinnerParts[0])[0].Captures[0].Value);
                var WinningNumbers = DigitMatch.Matches(IdAndWinnerParts[1]).Select(x => Convert.ToInt32(x.Captures[0].Value)).ToArray();
                var ActualNumbers = DigitMatch.Matches(Parts[1]).Select(x => Convert.ToInt32(x.Captures[0].Value)).ToArray();

                int Score = 0;
                int ScoringNumbers = 0;

                for (int Index = 0; Index < ActualNumbers.Length; Index++)
                {
                    if (WinningNumbers.Contains(ActualNumbers[Index]))
                    {
                        ScoringNumbers++;
                        Score = Score == 0 ? 1 : Score * 2;
                    }
                }

                FinalScore += Score;

                Cards[InputIndex] = ScoringNumbers;
                InputIndex++;
            }

            Console.WriteLine("First solution: " + FinalScore);
            Trace.Assert(FinalScore == 26218, $"Expected final score to be 26218 but it was {FinalScore}");
        }

        [TestCase]
        public void Part02()
        {
            int TotalScratchCards = 0;

            void ProcessWinningCards(int cardId)
            {
                if (cardId >= Input.Length) return;

                TotalScratchCards++;
                int CardsToTake = Cards[cardId];
                for (int index = cardId + 1; CardsToTake > 0; index++)
                {
                    ProcessWinningCards(index);
                    CardsToTake--;
                }
            }

            var Timer = Stopwatch.StartNew();
            foreach (var currentCard in Cards)
            {
                ProcessWinningCards(currentCard.Key);
            }

            Console.WriteLine($"Second solution: {TotalScratchCards} ({Timer.Elapsed})");
            Trace.Assert(TotalScratchCards == 9997537, $"Expected total scratch cards to be 9997537 but it was {TotalScratchCards}");
        }
    }
}
