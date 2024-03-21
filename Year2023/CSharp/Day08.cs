using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day08
    {
        private readonly string[] Input;
        private Dictionary<string, Tuple<string, string>> NodeMap;

        public Day08()
        {
            Input = File.ReadAllLines("./Input/08.txt");

            NodeMap = new();
            for (int Index = 2; Index < Input.Length; Index++)
            {
                string CurrentLine = Input[Index];
                string MapIndex = CurrentLine.Substring(0, 3);
                string MapValueL = CurrentLine.Substring(7, 3);
                string MapValueR = CurrentLine.Substring(12, 3);

                NodeMap.Add(MapIndex, new(MapValueL, MapValueR));
            }
        }

        [TestCase]
        public void Part01()
        {
            ReadOnlySpan<char> Instructions = Input[0].AsSpan();

            int InstructionIndex = 0;
            int StepsTaken = 0;
            Tuple<string, string> CurrentNodeSet = NodeMap["AAA"];

            while (true)
            {
                char NextInstruction = Instructions[InstructionIndex];
                string NextNode = NextInstruction == 'L' ? CurrentNodeSet.Item1 : CurrentNodeSet.Item2;
                StepsTaken++;

                if (NextNode == "ZZZ") break;

                CurrentNodeSet = NodeMap[NextNode];

                InstructionIndex++;
                InstructionIndex = InstructionIndex % Instructions.Length;
            }

            Console.WriteLine("Part one answer: " + StepsTaken);
            Trace.Assert(StepsTaken == 15517);
        }

        struct Node
        {
            public char Character;
            public ushort Left;
            public ushort Right;
        }

        // The dumb, bruteforce approach which still didn't finish after 5 minute runtime...
        //[TestCase]
        public void Part02_Bruteforce()
        {
            ReadOnlySpan<char> Instructions = Input[0].AsSpan();
            var InterimNodeMap = new Dictionary<string, ushort>();
            Span<Node> NodeMap = stackalloc Node[762];

            for (int Index = 2; Index < Input.Length; Index++)
            {
                string CurrentLine = Input[Index];
                string MapIndex = CurrentLine.Substring(0, 3);
                InterimNodeMap.Add(MapIndex, (ushort)(Index - 2));
            }

            for (int Index = 2; Index < Input.Length; Index++)
            {
                string CurrentLine = Input[Index];
                string MapIndex = CurrentLine.Substring(0, 3);
                string MapValueL = CurrentLine.Substring(7, 3);
                string MapValueR = CurrentLine.Substring(12, 3);

                NodeMap[Index-2] = new Node()
                {
                    Character = MapIndex[2],
                    Left = InterimNodeMap[MapValueL],
                    Right = InterimNodeMap[MapValueR]
                };
            }

            Debug.Assert(NodeMap[0].Character == 'X');
            Debug.Assert(NodeMap[0].Left == 266);
            Debug.Assert(NodeMap[0].Right == 489);

            Debug.Assert(NodeMap[49].Character == 'K');
            Debug.Assert(NodeMap[49].Left == 62);
            Debug.Assert(NodeMap[49].Right == 481);

            Debug.Assert(NodeMap[99].Character == 'F');
            Debug.Assert(NodeMap[99].Left == 394);
            Debug.Assert(NodeMap[99].Right == 378);

            Debug.Assert(NodeMap[149].Character == 'S');
            Debug.Assert(NodeMap[149].Left == 569);
            Debug.Assert(NodeMap[149].Right == 504);

            int InstructionIndex = 0;
            long StepsTaken = 0;
            Span<ushort> CurrentNodeSet = stackalloc ushort[]
            {
                InterimNodeMap["JVA"],
                InterimNodeMap["XLA"],
                InterimNodeMap["DNA"],
                InterimNodeMap["AAA"],
                InterimNodeMap["SHA"],
                InterimNodeMap["DLA"],
            };
            Span<ushort> NextNode = new ushort[6];

            var Timer = Stopwatch.StartNew();
            while (true)
            {
                char NextInstruction = Instructions[InstructionIndex];
                NextNode[0] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[0]].Left : NodeMap[CurrentNodeSet[0]].Right;
                NextNode[1] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[1]].Left : NodeMap[CurrentNodeSet[1]].Right;
                NextNode[2] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[2]].Left : NodeMap[CurrentNodeSet[2]].Right;
                NextNode[3] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[3]].Left : NodeMap[CurrentNodeSet[3]].Right;
                NextNode[4] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[4]].Left : NodeMap[CurrentNodeSet[4]].Right;
                NextNode[5] = NextInstruction == 'L' ? NodeMap[CurrentNodeSet[5]].Left : NodeMap[CurrentNodeSet[5]].Right;
                StepsTaken++;

                if (
                        NodeMap[NextNode[0]].Character == 'Z' &&
                        NodeMap[NextNode[1]].Character == 'Z' &&
                        NodeMap[NextNode[2]].Character == 'Z' &&
                        NodeMap[NextNode[3]].Character == 'Z' &&
                        NodeMap[NextNode[4]].Character == 'Z' &&
                        NodeMap[NextNode[5]].Character == 'Z'
                    )
                {
                    break;
                }

                CurrentNodeSet[0] = NextNode[0];
                CurrentNodeSet[1] = NextNode[1];
                CurrentNodeSet[2] = NextNode[2];
                CurrentNodeSet[3] = NextNode[3];
                CurrentNodeSet[4] = NextNode[4];
                CurrentNodeSet[5] = NextNode[5];
                InstructionIndex++;

                InstructionIndex = InstructionIndex % Instructions.Length;

                //if (StepsTaken == 1_000_000_000)
                //{
                //    break;
                //}
            }
            //Console.WriteLine($"Time taken: {Timer.Elapsed}");

            Console.WriteLine("Part two answer: " + StepsTaken);
            Trace.Assert(StepsTaken == 14_935_034_899_483);
        }

        [TestCase]
        public void Part02()
        {
            // This answer I had to look up. There was no way with my piss poor math skills that I could ever figure out
            // that the answer to this was using LCM (and I didn't even know what that was until now). And even then I still
            // don't understand why LCM is a solution to this.
            ReadOnlySpan<char> Instructions = Input[0].AsSpan();

            int InstructionIndex = 0;
            int StepsTaken = 0;
            Tuple<string, string>[] NodeSet = new[]
            {
                NodeMap["JVA"], // 13939
                NodeMap["XLA"], // 17621
                NodeMap["DNA"], // 19199
                NodeMap["AAA"], // 15517
                NodeMap["SHA"], // 12361
                NodeMap["DLA"]  // 20777
            };
            int[] NodeResults = new int[6];

            for(int Index = 0; Index < NodeSet.Length; Index++)
            {
                var CurrentNodeSet = NodeSet[Index];
                while (true)
                {
                    char NextInstruction = Instructions[InstructionIndex];
                    string NextNode = NextInstruction == 'L' ? CurrentNodeSet.Item1 : CurrentNodeSet.Item2;
                    StepsTaken++;

                    if (NextNode[2] == 'Z')
                    {
                        NodeResults[Index] = StepsTaken;
                        StepsTaken = 0;
                        InstructionIndex = 0;
                        break;
                    }

                    CurrentNodeSet = NodeMap[NextNode];

                    InstructionIndex++;
                    InstructionIndex = InstructionIndex % Instructions.Length;
                }
            }

            long FinalAnswer = lcm_of_array_elements(NodeResults);

            Console.WriteLine("Part two answer: " + FinalAnswer);
            Trace.Assert(FinalAnswer == 14935034899483);
        }

        // https://www.geeksforgeeks.org/lcm-of-given-array-elements/
        public static long lcm_of_array_elements(int[] element_array)
        {
            long lcm_of_array_elements = 1;
            int divisor = 2;

            while (true)
            {

                int counter = 0;
                bool divisible = false;
                for (int i = 0; i < element_array.Length; i++)
                {

                    // lcm_of_array_elements (n1, n2, ... 0) = 0.
                    // For negative number we convert into
                    // positive and calculate lcm_of_array_elements.
                    if (element_array[i] == 0)
                    {
                        return 0;
                    }
                    else if (element_array[i] < 0)
                    {
                        element_array[i] = element_array[i] * (-1);
                    }
                    if (element_array[i] == 1)
                    {
                        counter++;
                    }

                    // Divide element_array by devisor if complete
                    // division i.e. without remainder then replace
                    // number with quotient; used for find next factor
                    if (element_array[i] % divisor == 0)
                    {
                        divisible = true;
                        element_array[i] = element_array[i] / divisor;
                    }
                }

                // If divisor able to completely divide any number
                // from array multiply with lcm_of_array_elements
                // and store into lcm_of_array_elements and continue
                // to same divisor for next factor finding.
                // else increment divisor
                if (divisible)
                {
                    lcm_of_array_elements = lcm_of_array_elements * divisor;
                }
                else
                {
                    divisor++;
                }

                // Check if all element_array is 1 indicate 
                // we found all factors and terminate while loop.
                if (counter == element_array.Length)
                {
                    return lcm_of_array_elements;
                }
            }
        }
    }
}

/*
 unsigned int crc32b(unsigned char *message) {
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   while (message[i] != 0) {
      byte = message[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}
 */