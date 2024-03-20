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

                if (InstructionIndex == Instructions.Length)
                {
                    InstructionIndex = 0;
                }

                if (StepsTaken > int.MaxValue / 2)
                {
                    throw new Exception("Endless loop detection");
                }
            }

            Console.WriteLine("Part one answer: " + StepsTaken);
            Trace.Assert(StepsTaken == 15517);
        }

        // The dumb, bruteforce approach which still didn't finish after 5 minute runtime...
        //[TestCase]
        public void Part02x()
        {
            ReadOnlySpan<char> Instructions = Input[0].AsSpan();

            int InstructionIndex = 0;
            long StepsTaken = 0;
            Tuple<string, string>[] CurrentNodeSet = new[]
            {
                NodeMap["JVA"],
                NodeMap["XLA"],
                NodeMap["DNA"],
                NodeMap["AAA"],
                NodeMap["SHA"],
                NodeMap["DLA"]
            };
            string[] NextNode = new string[6];

            while (true)
            {
                char NextInstruction = Instructions[InstructionIndex];
                NextNode[0] = NextInstruction == 'L' ? CurrentNodeSet[0].Item1 : CurrentNodeSet[0].Item2;
                NextNode[1] = NextInstruction == 'L' ? CurrentNodeSet[1].Item1 : CurrentNodeSet[1].Item2;
                NextNode[2] = NextInstruction == 'L' ? CurrentNodeSet[2].Item1 : CurrentNodeSet[2].Item2;
                NextNode[3] = NextInstruction == 'L' ? CurrentNodeSet[3].Item1 : CurrentNodeSet[3].Item2;
                NextNode[4] = NextInstruction == 'L' ? CurrentNodeSet[4].Item1 : CurrentNodeSet[4].Item2;
                NextNode[5] = NextInstruction == 'L' ? CurrentNodeSet[5].Item1 : CurrentNodeSet[5].Item2;
                StepsTaken++;

                if (
                        NextNode[0][2] == 'Z' &&
                        NextNode[1][2] == 'Z' &&
                        NextNode[2][2] == 'Z' &&
                        NextNode[3][2] == 'Z' &&
                        NextNode[4][2] == 'Z' &&
                        NextNode[5][2] == 'Z'
                    )
                {
                    break;
                }

                CurrentNodeSet[0] = NodeMap[NextNode[0]];
                CurrentNodeSet[1] = NodeMap[NextNode[1]];
                CurrentNodeSet[2] = NodeMap[NextNode[2]];
                CurrentNodeSet[3] = NodeMap[NextNode[3]];
                CurrentNodeSet[4] = NodeMap[NextNode[4]];
                CurrentNodeSet[5] = NodeMap[NextNode[5]];
                InstructionIndex++;

                if (InstructionIndex == Instructions.Length)
                {
                    InstructionIndex = 0;
                }
            }

            Console.WriteLine("Part two answer: " + StepsTaken);
            //Trace.Assert(StepsTaken == 10_668_805_667_831);
        }

        [TestCase]
        public void Part02()
        {
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

                    if (InstructionIndex == Instructions.Length)
                    {
                        InstructionIndex = 0;
                    }
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