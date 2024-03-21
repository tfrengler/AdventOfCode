using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;

namespace AdventOfCode.Year2023
{
    // https://www.reddit.com/r/adventofcode/comments/18cq5j3/2023_day_7_part_1_two_hints_for_anyone_stuck/
    // https://www.reddit.com/r/adventofcode/comments/18cr4xr/2023_day_7_better_example_input_not_a_spoiler/

    [TestFixture]
    [NonParallelizable]
    public sealed class Day07
    {
        readonly string[] Input;

        struct Hand
        {
            public HandType Type { get; set; }
            public byte[] CardValues { get; set; }
            public short Bid { get; set; }
            public string CardString { get; set; }
        }

        enum HandType : byte
        {
            NONE = 0,
            FiveOfaKind = 7,
            FourOfaKind = 6,
            FullHouse = 5,
            ThreeOfaKind = 4,
            TwoPair = 3,
            OnePair = 2,
            HighCard = 1
        }

        Dictionary<char, byte> CardValues;

        readonly Hand[] Hands;

        public Day07()
        {
            Input = File.ReadAllLines("Input/07.txt");

            // Part 1 test data
            /*Input = new string[]
            {
                "2345A 1",      // 00 High card
                "Q2KJJ 13",     // 01 One pair
                "Q2Q2Q 19",     // 02 Full house
                "T3T3J 17",     // 03 Two pairs
                "T3Q33 11",     // 04 Three of a kind
                "2345J 3",      // 05 High card
                "J345A 2",      // 06 High card
                "32T3K 5",      // 07 One pair
                "T55J5 29",     // 08 Three of a kind
                "KK677 7",      // 09 Two pairs
                "KTJJT 34",     // 10 Two pairs
                "QQQJA 31",     // 11 Three of a kind
                "JJJJJ 37",     // 12 Five of a kind
                "JAAAA 43",     // 13 Four of a kind
                "AAAAJ 59",     // 14 Four of a kind
                "AAAAA 61",     // 15 Five of a kind
                "2AAAA 23",     // 16 Four of a kind
                "2JJJJ 53",     // 17 Four of a kind
                "JJJJ2 41"      // 18 Four of a kind
            };*/

            // Part 1 = 6592 for test input

            Hands = new Hand[Input.Length];
        }

        [TestCase]
        public void Part01()
        {
            CardValues = new()
            {
                { 'A', 13 },
                { 'K', 12 },
                { 'Q', 11 },
                { 'J', 10 },
                { 'T', 9 },
                { '9', 8 },
                { '8', 7 },
                { '7', 6 },
                { '6', 5 },
                { '5', 4 },
                { '4', 3 },
                { '3', 2 },
                { '2', 1 }
            };

            int HandInsertIndex = 0;

            Span<byte> CardBuffer = stackalloc byte[13];
            Span<byte> Cards = stackalloc byte[5];

            foreach (string CurrentInput in Input)
            {
                ReadOnlySpan<char> CardLettersSlice = CurrentInput.AsSpan(0, 5);

                for(int Index = 0; Index < CardLettersSlice.Length; Index++)
                {
                    if (CardLettersSlice[Index] == 'A') CardBuffer[12]++;
                    else if (CardLettersSlice[Index] == 'K') CardBuffer[11]++;
                    else if (CardLettersSlice[Index] == 'Q') CardBuffer[10]++;
                    else if (CardLettersSlice[Index] == 'J') CardBuffer[9]++;
                    else if (CardLettersSlice[Index] == 'T') CardBuffer[8]++;
                    else if (CardLettersSlice[Index] == '9') CardBuffer[7]++;
                    else if (CardLettersSlice[Index] == '8') CardBuffer[6]++;
                    else if (CardLettersSlice[Index] == '7') CardBuffer[5]++;
                    else if (CardLettersSlice[Index] == '6') CardBuffer[4]++;
                    else if (CardLettersSlice[Index] == '5') CardBuffer[3]++;
                    else if (CardLettersSlice[Index] == '4') CardBuffer[2]++;
                    else if (CardLettersSlice[Index] == '3') CardBuffer[1]++;
                    else if (CardLettersSlice[Index] == '2') CardBuffer[0]++;

                    Cards[Index] = CardValues[CardLettersSlice[Index]];
                }

                var NewHand = new Hand()
                {
                    CardValues = Cards.ToArray(),
                    Bid = Convert.ToInt16(CurrentInput[6..])
                };

                HandType HandType = HandType.NONE;
                bool AnyCountOf3 = false;
                bool AnyCountOf2 = false;
                int CountsOfOne = 0;

                for (int Index = 0; Index < CardBuffer.Length; Index++)
                {
                    byte CurrentCardCount = CardBuffer[Index];
                    if (CurrentCardCount == 5)
                    {
                        HandType = HandType.FiveOfaKind;
                        break;
                    }

                    if (CurrentCardCount == 4)
                    {
                        HandType = HandType.FourOfaKind;
                        break;
                    }

                    if (CurrentCardCount == 3) AnyCountOf3 = true;
                    else if (CurrentCardCount == 2) AnyCountOf2 = true;
                    else if (CurrentCardCount == 1) CountsOfOne++;
                }

                if (HandType == HandType.NONE)
                {
                    if (AnyCountOf3 && AnyCountOf2) HandType = HandType.FullHouse;
                    else if (AnyCountOf3 && CountsOfOne > 0) HandType = HandType.ThreeOfaKind;
                    else if (AnyCountOf2 && CountsOfOne == 1) HandType = HandType.TwoPair;
                    else if (AnyCountOf2 && CountsOfOne == 3) HandType = HandType.OnePair;
                    else HandType = HandType.HighCard;
                }

                NewHand.Type = HandType;
                NewHand.CardString = new string(CardLettersSlice);

                CardBuffer.Clear();
                Cards.Clear();

                Hands[HandInsertIndex] = NewHand;
                HandInsertIndex++;
            }

            long FinalValue = 0;

            List<Hand> HandsOrdered = Hands.ToList();
            HandsOrdered.Sort((x, y) =>
            {
                byte xTypeValue = (byte)x.Type;
                byte yTypeValue = (byte)y.Type;
                if (xTypeValue < yTypeValue) return -1;
                if (xTypeValue > yTypeValue) return 1;

                for (int Index = 0; Index < x.CardValues.Length; Index++)
                {
                    if (x.CardValues[Index] < y.CardValues[Index]) return -1;
                    if (x.CardValues[Index] > y.CardValues[Index]) return 1;
                }

                return 0;
            });

            for(int Index = Hands.Length - 1; Index != -1; Index--)
            {
                var CurrentHand = HandsOrdered[Index];
                FinalValue += CurrentHand.Bid * (Index + 1);
            }

            Console.WriteLine($"Part one answer: " + FinalValue);
            Trace.Assert(FinalValue == 246424613, $"Expected answer to be 246424613 but it was {FinalValue}");
        }

        //[TestCase]
        public void Part02()
        {
            CardValues = new()
            {
                { 'A', 12 },
                { 'K', 11 },
                { 'Q', 10 },
                { 'T', 9 },
                { '9', 8 },
                { '8', 7 },
                { '7', 6 },
                { '6', 5 },
                { '5', 4 },
                { '4', 3 },
                { '3', 2 },
                { '2', 1 },
                { 'J', 0 }
            };

            throw new NotImplementedException("Not finished");
        }
    }
}
