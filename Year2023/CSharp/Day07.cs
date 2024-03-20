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

            //for(int InputIndex = 0; InputIndex < Input.Length; InputIndex++)
            foreach (string CurrentInput in Input)
            {
                //string CurrentInput = Input[InputIndex];
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

                //int Strength = (NewHand.Card1 * 5) + (NewHand.Card2 * 4) + (NewHand.Card3 * 3) + (NewHand.Card4 * 2) + (NewHand.Card5 * 1);
                //NewHand.Strength = Strength;

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

            /*Debug.Assert(Hands[0].Type == HandType.HighCard);
            Debug.Assert(Hands[1].Type == HandType.OnePair);
            Debug.Assert(Hands[2].Type == HandType.FullHouse);
            Debug.Assert(Hands[3].Type == HandType.TwoPair);
            Debug.Assert(Hands[4].Type == HandType.ThreeOfaKind);
            Debug.Assert(Hands[5].Type == HandType.HighCard);
            Debug.Assert(Hands[6].Type == HandType.HighCard);
            Debug.Assert(Hands[7].Type == HandType.OnePair);
            Debug.Assert(Hands[8].Type == HandType.ThreeOfaKind);
            Debug.Assert(Hands[9].Type == HandType.TwoPair);
            Debug.Assert(Hands[10].Type == HandType.TwoPair);
            Debug.Assert(Hands[11].Type == HandType.ThreeOfaKind);
            Debug.Assert(Hands[12].Type == HandType.FiveOfaKind);
            Debug.Assert(Hands[13].Type == HandType.FourOfaKind);
            Debug.Assert(Hands[14].Type == HandType.FourOfaKind);
            Debug.Assert(Hands[15].Type == HandType.FiveOfaKind);
            Debug.Assert(Hands[16].Type == HandType.FourOfaKind);
            Debug.Assert(Hands[17].Type == HandType.FourOfaKind);
            Debug.Assert(Hands[18].Type == HandType.FourOfaKind);*/

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

            /*int TestIndex = 0;
            foreach (var test in HandsOrdered)
            {
                Console.WriteLine($"[{TestIndex}] = {test.Cards} ({test.Strength})");
                TestIndex++;
            }

            Debug.Assert(HandsOrdered[0].Cards == "2345J", $"Expected 0 to be 2345J but it was {HandsOrdered[0].Cards}");
            Debug.Assert(HandsOrdered[1].Cards == "2345A", $"Expected 1 to be 2345A but it was {HandsOrdered[1].Cards}");
            Debug.Assert(HandsOrdered[2].Cards == "J345A", $"Expected 2 to be J345A but it was {HandsOrdered[2].Cards}");
            Debug.Assert(HandsOrdered[3].Cards == "32T3K", $"Expected 3 to be 32T3K but it was {HandsOrdered[3].Cards}");
            Debug.Assert(HandsOrdered[4].Cards == "Q2KJJ", $"Expected 4 to be Q2KJJ but it was {HandsOrdered[4].Cards}");
            Debug.Assert(HandsOrdered[5].Cards == "T3T3J", $"Expected 5 to be T3T3J but it was {HandsOrdered[5].Cards}");
            Debug.Assert(HandsOrdered[6].Cards == "KTJJT", $"Expected 6 to be KTJJT but it was {HandsOrdered[6].Cards}");
            Debug.Assert(HandsOrdered[7].Cards == "KK677", $"Expected 7 to be KK677 but it was {HandsOrdered[7].Cards}");
            Debug.Assert(HandsOrdered[8].Cards == "T3Q33", $"Expected 8 to be T3Q33 but it was {HandsOrdered[8].Cards}");
            Debug.Assert(HandsOrdered[9].Cards == "T55J5", $"Expected 9 to be T55J5 but it was {HandsOrdered[9].Cards}");
            Debug.Assert(HandsOrdered[10].Cards == "QQQJA", $"Expected 10 to be QQQJA but it was {HandsOrdered[10].Cards}");
            Debug.Assert(HandsOrdered[11].Cards == "Q2Q2Q", $"Expected 11 to be Q2Q2Q but it was {HandsOrdered[11].Cards}");
            Debug.Assert(HandsOrdered[12].Cards == "2JJJJ", $"Expected 12 to be 2JJJJ but it was {HandsOrdered[12].Cards}");
            Debug.Assert(HandsOrdered[13].Cards == "2AAAA", $"Expected 13 to be 2AAAA but it was {HandsOrdered[13].Cards}");
            Debug.Assert(HandsOrdered[14].Cards == "JJJJ2", $"Expected 14 to be JJJJ2 but it was {HandsOrdered[14].Cards}");
            Debug.Assert(HandsOrdered[15].Cards == "JAAAA", $"Expected 15 to be JAAAA but it was {HandsOrdered[15].Cards}");
            Debug.Assert(HandsOrdered[16].Cards == "AAAAJ", $"Expected 16 to be AAAAJ but it was {HandsOrdered[16].Cards}");
            Debug.Assert(HandsOrdered[17].Cards == "JJJJJ", $"Expected 17 to be JJJJJ but it was {HandsOrdered[17].Cards}");
            Debug.Assert(HandsOrdered[18].Cards == "AAAAA", $"Expected 18 to be AAAAA but it was {HandsOrdered[18].Cards}");*/

            for(int Index = Hands.Length - 1; Index != -1; Index--)
            {
                var CurrentHand = HandsOrdered[Index];
                FinalValue += CurrentHand.Bid * (Index + 1);
            }

            Console.WriteLine($"Part one answer: " + FinalValue);
            Trace.Assert(FinalValue == 246424613, $"Expected answer to be 246424613 but it was {FinalValue}");
        }

        [TestCase]
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
