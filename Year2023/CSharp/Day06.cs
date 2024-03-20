using NUnit.Framework;
using System;
using System.Diagnostics;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public class Day06
    {
        private readonly struct Race
        {
            public long TimeInMs { get; }
            public long BestDistance { get; }

            public Race(long time, long distance)
            {
                TimeInMs = time;
                BestDistance = distance;
            }
        }

        [TestCase]
        public void Part01()
        {
            var Input = new Race[]
            {
                new(56, 499),
                new(97, 2210),
                new(77, 1097),
                new(93, 1440)
            };

            int FinalAnswer = 1;

            foreach (Race CurrentRace in Input)
            {
                int WinningCombos = 0;

                for (int IndexMiliseconds = 1; IndexMiliseconds < CurrentRace.TimeInMs; IndexMiliseconds++)
                {
                    // (7 - 2) = (5 * 2) = (10 > 9) == True
                    long DistanceDone = (CurrentRace.TimeInMs - IndexMiliseconds) * IndexMiliseconds;
                    if (DistanceDone > CurrentRace.BestDistance)
                    {
                        WinningCombos++;
                    }
                }
                
                FinalAnswer *= WinningCombos;
            }

            Console.WriteLine("Part one answer: " + FinalAnswer);
            Trace.Assert(FinalAnswer == 1710720, $"Expected final answer to be 1710720 but it was {FinalAnswer}");
        }

        [TestCase]
        public void Part02()
        {
            long FinalAnswer;
            int WinningCombos = 0;
            Race CurrentRace = new(56977793, 499221010971440);

            // Seconds to hold * Max time - Seconds to hold squared > distance
            // S*T - S^2 > D
            for (int IndexMiliseconds = 1; IndexMiliseconds < CurrentRace.TimeInMs; IndexMiliseconds++)
            {
                long DistanceDone = (CurrentRace.TimeInMs - IndexMiliseconds) * IndexMiliseconds;
                if (DistanceDone > CurrentRace.BestDistance)
                {
                    WinningCombos++;
                }
            }

            FinalAnswer = WinningCombos;

            Console.WriteLine("Part two answer: " + FinalAnswer);
            Trace.Assert(FinalAnswer == 35349468, $"Expected final answer to be 35349468 but it was {FinalAnswer}");
        }
        
        [TestCase]
        public void Part02_Variation01()
        {
            long FinalAnswer;
            int WinningCombos = 0;
            Race CurrentRace = new(56977793, 499221010971440);

            // I know this thing is a quadratic equation but I massively suck at math so I always try for logical optimizations instead
            // The pattern I noticed is that the winning times appear near the middle so I reckon there's a curve of some kind.
            // Hence this optimization is to split the time in two, then with two loops go down and then until there are no winning moves anymore.
            var TimeInMS = CurrentRace.TimeInMs / 2;

            for (long IndexMiliseconds = TimeInMS; IndexMiliseconds > 1; IndexMiliseconds--)
            {
                long DistanceDone = (CurrentRace.TimeInMs - IndexMiliseconds) * IndexMiliseconds;
                if (DistanceDone > CurrentRace.BestDistance)
                {
                    WinningCombos++;
                    continue;
                }

                break;
            }

            for (long IndexMiliseconds = TimeInMS+1; IndexMiliseconds < CurrentRace.TimeInMs; IndexMiliseconds++)
            {
                long DistanceDone = (CurrentRace.TimeInMs - IndexMiliseconds) * IndexMiliseconds;
                if (DistanceDone > CurrentRace.BestDistance)
                {
                    WinningCombos++;
                    continue;
                }

                break;
            }

            FinalAnswer = WinningCombos;

            Console.WriteLine("Part two answer: " + FinalAnswer);
            Trace.Assert(FinalAnswer == 35349468, $"Expected final answer to be 35349468 but it was {FinalAnswer}");
        }

    }
}
