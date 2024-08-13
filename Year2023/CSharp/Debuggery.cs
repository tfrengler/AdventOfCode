
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

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
            uint hash = offsetBasis == 0 ? 2166136261 : offsetBasis;    // FNV offset basis. Should be anything but non-zero
            uint prime = 16777619;                                      // FNV prime for 32-bit hashes

            foreach (char currentChar in input)
            {
                unchecked
                {
                    hash = hash ^ currentChar;
                    hash = hash * prime;
                }
            }

            return hash;
        }

        public static uint Fnv1aHash(uint input, uint offsetBasis = 2166136261)
        {
            uint hash = offsetBasis == 0 ? 2166136261 : offsetBasis;    // FNV offset basis. Should be anything but non-zero
            uint prime = 16777619;                                      // FNV prime for 32-bit hashes

            foreach (byte currentChar in BitConverter.GetBytes(input))
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
            uint Size = (uint)Nodes.Count;
            var Buckets = new List<string>[Size];
            var G = new int[Size];
            var Values = new Tuple<string,string>[Size];

            for(int Index = 0; Index < Size; Index++)
            {
                Buckets[Index] = new List<string>();
            }

            foreach(var CurrentNode in Nodes)
            {
                uint HashIndex = Fnv1aHash(CurrentNode.Key) % Size;
                Buckets[HashIndex].Add(CurrentNode.Key);
            }

            Array.Sort(Buckets, (a, b) =>
            {
                if (a.Count > b.Count) return -1;
                if (a.Count < b.Count) return 1;

                return 0;
            });

            /*for(int Index = 0; Index < Buckets.Length; Index++)
            {
                Console.WriteLine($"Count ({Index}): " + Buckets[Index].Count);
            }*/

            //Console.WriteLine(Buckets[0]);

            for (int Index = 0; Index < Size; Index++)
            {
                List<string> CurrentBucket = Buckets[Index];
                if (CurrentBucket.Count <= 1) break;

                uint HashOffsetBasis = 1;
                var BucketIndex = 0;
                List<uint> SlotsInValueTable = [];
                int Iterations = 0;

                while (BucketIndex < CurrentBucket.Count)
                {
                    string CurrentKey = CurrentBucket[BucketIndex];

                    uint ValueSlot = Fnv1aHash(CurrentKey, HashOffsetBasis) % Size;
                    if (Values[ValueSlot] is not null || SlotsInValueTable.Contains(ValueSlot))
                    {
                        // Collision, reset and retry entire bucket with different offset
                        HashOffsetBasis++;
                        BucketIndex = 0;
                        SlotsInValueTable.Clear();
                    }
                    else
                    {
                        SlotsInValueTable.Add(ValueSlot);
                        BucketIndex++;
                    }

                    Iterations++;
                    if (Iterations > 100_000)
                    {
                        throw new Exception("Took more than 100k iterations to find hash value for bucket");
                    }
                }

                Debug.Assert(G[Fnv1aHash(CurrentBucket[0]) % Size] == 0, $"Expected G[{Fnv1aHash(CurrentBucket[0]) % Size}] to be null");
                G[Fnv1aHash(CurrentBucket[0]) % Size] = (int)HashOffsetBasis;

                for(int IndexInner = 0; IndexInner < CurrentBucket.Count; IndexInner++)
                {
                    Debug.Assert(Values[SlotsInValueTable[IndexInner]] == null, $"Expected Values[{SlotsInValueTable[IndexInner]}] to be null");
                    Values[SlotsInValueTable[IndexInner]] = Nodes[CurrentBucket[IndexInner]];
                }
            }

            for(int Index = 0; Index < G.Length; Index++)
            {
                //var d = G[Fnv1aHash(currentNode.Key) % Size];
                //if (d < 0) continue;
                //var Value = Values[Fnv1aHash(currentNode.Key, (uint)d) % Size];
                //if (Value is null) continue;
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
