
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    public sealed class Debuggery
    {
        private readonly Dictionary<string,Tuple<string,string>> Nodes;

        public Debuggery()
        {
            string[] Input = File.ReadAllLines("./Input/08.txt");
            Nodes = new(762);

            int IndicesIndex = 0;
            for (int Index = 2; Index < Input.Length; Index++)
            {
                string CurrentLine = Input[Index];

                string MapIndex = CurrentLine.Substring(0, 3);
                string MapValueL = CurrentLine.Substring(7, 3);
                string MapValueR = CurrentLine.Substring(12, 3);

                Nodes[MapIndex] = new Tuple<string, string>(MapValueL, MapValueR);
                IndicesIndex++;
            }
        }

        public static uint Fnv1aHash(string input, uint offsetBasis = 2166136261)
        {
            return Fnv1aHash(Encoding.ASCII.GetBytes(input), offsetBasis);
        }

        public static uint Fnv1aHash(uint input, uint offsetBasis = 0)
        {
            return Fnv1aHash(BitConverter.GetBytes(input), offsetBasis);
        }

        private const uint DefaultOffsetBasis = 2166136261;

        public static uint Fnv1aHash(byte[] input, uint offsetBasis = DefaultOffsetBasis)
        {
            uint hash = offsetBasis == 0 ? DefaultOffsetBasis : offsetBasis;    // FNV offset basis. Should be anything but non-zero
            uint prime = 16777619;                                              // FNV prime for 32-bit hashes

            foreach (byte currentChar in input)
            {
                unchecked
                {
                    hash = hash ^ currentChar;
                    hash = hash * prime;
                }
            }

            return hash;
        }

        [TestCase]
        public void DoDebug2()
        {
            // Based on http://stevehanov.ca/blog/?id=119

            uint Size = (uint)Nodes.Count;
            var Buckets = new List<string>[Size];
            var Intermediate = new long[Size];
            var Values = new Tuple<string,string>[Size];

            // Create temp buckets to group the hashed values together in
            for(int Index = 0; Index < Buckets.Length; Index++)
            {
                Buckets[Index] = new List<string>();
            }

            // Loop through and hash all the values and find the index. Add to the buckets
            // This is how we detect collisions (values that hash to the same index) which we will resolve in step 2
            foreach(var CurrentNode in Nodes)
            {
                uint HashIndex = Fnv1aHash(CurrentNode.Key) % Size;
                Buckets[HashIndex].Add(CurrentNode.Key);
            }

            // Sorts buckets by amount of elements in them, from high to low
            Array.Sort(Buckets, (a, b) =>
            {
                if (a.Count > b.Count) return -1;
                if (a.Count < b.Count) return 1;

                return 0;
            });

            /*using (var BucketFile = File.Create("C:/Temp/Buckets.txt"))
            {
                for (int Index = 0; Index < Buckets.Length; Index++)
                {
                    BucketFile.Write(Encoding.UTF8.GetBytes($"{Index}: " + string.Join(',', Buckets[Index]) + Environment.NewLine));
                    //Console.WriteLine($"Count ({Index}): " + Buckets[Index].Count);
                }
                BucketFile.Flush();
            }*/

            //return;
            /* STEP 2: Parse buckets with multiple entries (duplicates), create and populate the intermediate- and final value table */
            int BucketsWithOneStartIndex = -1;
            for (int Index = 0; Index < Size; Index++)
            {
                List<string> CurrentBucket = Buckets[Index];
                if (CurrentBucket.Count <= 1) // No multiples? Then we are done parsing buckets
                {
                    BucketsWithOneStartIndex = Index;
                    break;
                }

                uint HashOffsetBasis = DefaultOffsetBasis;
                var BucketIndex = 0;
                int Iterations = 0;
                // Temp table containing all the computed indices
                // This is basically what maps bucket[index] => SlotsInValueTable[index] => final value table[value from SlotsInValueTable]
                List<uint> SlotsInValueTable = [];

                // Keep processing until there's no collisions basically
                while (BucketIndex < CurrentBucket.Count)
                {
                    // Get the current value that needs to be hashed and indexed
                    string CurrentKey = CurrentBucket[BucketIndex];

                    // Compute index in final value table (hash-algorithm mod final value table size)
                    uint ValueSlot = Fnv1aHash(CurrentKey, HashOffsetBasis) % Size;
                    // Check if final value table index we computed is occupoed OR temp index table contains an already computed index
                    if (Values[ValueSlot] is not null || SlotsInValueTable.Contains(ValueSlot))
                    {
                        // We have collision. Reset and retry entire bucket with different offset
                        HashOffsetBasis++;
                        BucketIndex = 0;
                        SlotsInValueTable.Clear();
                    }
                    else
                    {
                        // No collisions? Success! Add computed index to our temp table
                        SlotsInValueTable.Add(ValueSlot);
                        BucketIndex++;
                    }

                    // Safe-guard against infinite loops
                    Iterations++;
                    if (Iterations > 100_000)
                    {
                        throw new Exception($"Took more than 100k iterations to find hash value for bucket ({Index})");
                    }
                }

                //Debug.Assert(Intermediate[Fnv1aHash(CurrentBucket[0]) % Size] == 0, $"Expected Intermediate[{Fnv1aHash(CurrentBucket[0]) % Size}] to be null");
                /* Add the succesful hashoffset to the intermediate table based on the first value of the bucket (which value is ultimately irrelevant
                   since we know that all values in the bucket will yield the same index). This is how we map between:
                    value to look up:
                        => index in intermediate table
                        => hashoffset to use for value to get index for value in final value table
                */
                Intermediate[Fnv1aHash(CurrentBucket[0]) % Size] = HashOffsetBasis;

                // Loop through values in bucket and insert them into final value table based on indices we computed and stored in temp table
                for(int IndexInner = 0; IndexInner < CurrentBucket.Count; IndexInner++)
                {
                    Debug.Assert(Values[SlotsInValueTable[IndexInner]] == null, $"Expected Values[{SlotsInValueTable[IndexInner]}] to be null");
                    Values[SlotsInValueTable[IndexInner]] = Nodes[CurrentBucket[IndexInner]];
                }
            }

            /* STEP 3: Parse the remaining values that hashed to a unique value without duplicates and fit them into the holes in the table */

            // Iterate over the final value table and find empty slots
            int FreeSlotIndex = 0;
            var FreeSlotsList = new int[Size - (BucketsWithOneStartIndex + 1)];
            for (int Index = 0; Index < Size; Index++)
            {
                if (Values[Index] is null)
                {
                    FreeSlotsList[FreeSlotIndex] = Index;
                    FreeSlotIndex++;
                }
            }
            FreeSlotIndex = 0;

            // Iterate over the remaining buckets with just one item and assign them to the free slots
            for (int Index = BucketsWithOneStartIndex; Index < FreeSlotsList.Length; Index++)
            {
                List<string> CurrentBucket = Buckets[Index];
                // If we reach an empty bucket then quit. Since we have sorted buckets ASC we know the empty ones are at the end
                if (CurrentBucket.Count == 0) break;

                // Get the next free slot in the value table
                int ValueSlot = FreeSlotsList[FreeSlotIndex];
                FreeSlotIndex++;
                long IntermediateSlot = Fnv1aHash(CurrentBucket[0]) % Size;

                // Set the intermediate table value to the index in the value table.
                // However to indicate that it's a direct reference make it negative.
                // We subtract 1 to cover the case where the value table index is 0.
                Intermediate[IntermediateSlot] = (-ValueSlot) - 1;
                Values[ValueSlot] = Nodes[CurrentBucket[0]];
            }

            /*
             NOTE: An optimization for space/memory is to compress the intermediate table ie. removing the empty cells
             but that is for later.
             */

            /*using (var IntermediateTableOutputFile = File.Create("C:/Temp/IntermediateTable.txt"))
            {
                for (int Index = 0; Index < Intermediate.Length; Index++)
                {
                    IntermediateTableOutputFile.Write(Encoding.UTF8.GetBytes($"{Index}: " + Intermediate[Index] + Environment.NewLine));
                }
                IntermediateTableOutputFile.Flush();
            }*/


            // TESTING AND VALIDATION
            foreach(var currentNode in Nodes)
            {
                long HashOffset = Intermediate[Fnv1aHash(currentNode.Key) % Size];
                if (HashOffset == 0)
                {
                    throw new Exception($"Key {currentNode.Key} does not exist in hash table");
                }

                Tuple<string, string> Value;
                if (HashOffset > 0)
                {
                    Value = Values[Fnv1aHash(currentNode.Key, (uint)HashOffset) % Size];
                }
                else
                {
                    long ValueIndex = (-HashOffset) + 1;
                    Value = Values[ValueIndex];
                }

                Debug.Assert(currentNode.Value == Value, $"Expected key '{currentNode.Key}' to yield value '{currentNode.Value}' but found '{Value}'");
                //Console.WriteLine($"{currentNode.Key} = ({currentNode.Value.Item1},{currentNode.Value.Item2}) | ({Value.Item1},{Value.Item2})");
            }
        }

        [TestCase]
        public void DoDebug1()
        {
            //uint[]? Primes = JsonSerializer.Deserialize<uint[]>(File.ReadAllText("./Input/10kPrimes.json"));
            //System.Diagnostics.Debug.Assert(Primes is not null);
            /*
            var Map = new string[762];
            bool Collided = false;

            for (uint Index = 0; Index < 10_000_000; Index++)
            {
                foreach (string current in Indices)
                {
                    //string NumberString = $"{(int)current[0]}{(int)current[1]}{(int)current[2]}";
                    //uint AsInt1 = Convert.ToUInt32(NumberString);

                    int AsInt = current[0] * 100;
                    AsInt = AsInt + current[1];
                    AsInt = (AsInt * 100) + current[2];

                    uint Hash = Fnv1aHash((uint)AsInt + Index);
                    uint HashIndex = Hash % 762;

                    if (Map[HashIndex] != null)
                    {
                        Collided = true;
                        break;
                    }

                    Map[HashIndex] = current;
                }

                if (!Collided)
                {
                    Console.WriteLine($"No collision! " + Index);
                    for(int MapIndex = 0; MapIndex < Map.Length; MapIndex++)
                    {
                        Console.WriteLine($"{MapIndex} : {Map[MapIndex]}");
                    }
                    return;
                }

                Collided = false;
                Map = new string[762];
            }

            Console.WriteLine($"None worked :(");*/
        }
    }
}
