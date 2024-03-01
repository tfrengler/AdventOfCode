using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.CompilerServices;
using System.Text.RegularExpressions;

namespace AdventOfCode2023.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public class Day05
    {
        readonly string[] Input;

        Regex DigitRegex = new Regex(@"(\d+)");

        long[] Seeds;

        ValueTuple<long, long, long>[] SeedToSoilMap;
        ValueTuple<long, long, long>[] SoilToFertilizerMap;
        ValueTuple<long, long, long>[] FertilizerToWaterMap;
        ValueTuple<long, long, long>[] WaterToLightMap;
        ValueTuple<long, long, long>[] LightToTemperatureMap;
        ValueTuple<long, long, long>[] TemperatureToHumidityMap;
        ValueTuple<long, long, long>[] HumidityToLocationMap;

        ValueTuple<long, long, long>[][] MapsInOrder;

        public Day05()
        {
            Input = File.ReadAllLines("Input/05.txt");

            /*Input = new[]
            {
                "seeds: 79 14 55 13",
                "",
                "seed-to-soil map:",
                "50 98 2",
                "52 50 48",
                "",
                "soil-to-fertilizer map:",
                "0 15 37",
                "37 52 2",
                "39 0 15",
                "",
                "fertilizer-to-water map:",
                "49 53 8",
                "0 11 42",
                "42 0 7",
                "57 7 4",
                "",
                "water-to-light map:",
                "88 18 7",
                "18 25 70",
                "",
                "light-to-temperature map:",
                "45 77 23",
                "81 45 19",
                "68 64 13",
                "",
                "temperature-to-humidity map:",
                "0 69 1",
                "1 0 69",
                "",
                "humidity-to-location map:",
                "60 56 37",
                "56 93 4"
            };*/
        }

        static long CalculateDestinationIndex(in List<ValueTuple<long, long, long>> map, long input)
        {
            long ReturnData = 0;

            foreach (var (dest, source, range) in map)
            {
                if (input >= source && input < (source + range))
                {
                    ReturnData = (dest - source) + input;
                    break;
                }
                else
                {
                    ReturnData = input;
                }
            }
            return ReturnData;
        }

        void ParseSeeds()
        {
            var DigitMatches = DigitRegex.Matches(Input[0]);
            Seeds = DigitMatches.Select(x => x.Groups[0].Value).Select(x => Convert.ToInt64(x)).ToArray();
        }

        void ParseMaps()
        {
            var SeedToSoilMap = new List<ValueTuple<long, long, long>>();
            var SoilToFertilizerMap = new List<ValueTuple<long, long, long>>();
            var FertilizerToWaterMap = new List<ValueTuple<long, long, long>>();
            var WaterToLightMap = new List<ValueTuple<long, long, long>>();
            var LightToTemperatureMap = new List<ValueTuple<long, long, long>>();
            var TemperatureToHumidityMap = new List<ValueTuple<long, long, long>>();
            var HumidityToLocationMap = new List<ValueTuple<long, long, long>>();

            List<ValueTuple<long, long, long>>? CurrentMap = null;
            for (int index = 1; index < Input.Length; index++)
            {
                string currentLine = Input[index];

                if (currentLine.Trim().Length == 0)
                {
                    continue;
                }

                if (char.IsLetter(currentLine[0]))
                {
                    CurrentMap = currentLine switch
                    {
                        "seed-to-soil map:" => SeedToSoilMap,
                        "soil-to-fertilizer map:" => SoilToFertilizerMap,
                        "fertilizer-to-water map:" => FertilizerToWaterMap,
                        "water-to-light map:" => WaterToLightMap,
                        "light-to-temperature map:" => LightToTemperatureMap,
                        "temperature-to-humidity map:" => TemperatureToHumidityMap,
                        "humidity-to-location map:" => HumidityToLocationMap,
                        _ => throw new InvalidDataException()
                    };
                    continue;
                }

                Trace.Assert(CurrentMap is not null);

                var Parts = currentLine.Split(' ');
                Trace.Assert(Parts.Length == 3);

                CurrentMap.Add(ValueTuple.Create(
                    Convert.ToInt64(Parts[0]),
                    Convert.ToInt64(Parts[1]),
                    Convert.ToInt64(Parts[2]))
                );
            }

            this.SeedToSoilMap = SeedToSoilMap.ToArray();
            this.SoilToFertilizerMap = SoilToFertilizerMap.ToArray();
            this.FertilizerToWaterMap = FertilizerToWaterMap.ToArray();
            this.WaterToLightMap = WaterToLightMap.ToArray();
            this.LightToTemperatureMap = LightToTemperatureMap.ToArray();
            this.TemperatureToHumidityMap = TemperatureToHumidityMap.ToArray();
            this.HumidityToLocationMap = HumidityToLocationMap.ToArray();

            MapsInOrder = new ValueTuple<long, long, long>[][]
            {
                this.SeedToSoilMap,
                this.SoilToFertilizerMap,
                this.FertilizerToWaterMap,
                this.WaterToLightMap,
                this.LightToTemperatureMap,
                this.TemperatureToHumidityMap,
                this.HumidityToLocationMap
            };
        }

        //[MethodImpl(MethodImplOptions.AggressiveInlining)]
        long CalculateLocation(long input)
        {
            long ReturnData = input;
            for (int ChainIndex = 0; ChainIndex < MapsInOrder.Length; ChainIndex++)
            {
                var CurrentMap = MapsInOrder[ChainIndex];
                for (int MapIndex = 0; MapIndex < CurrentMap.Length; MapIndex++)
                {

                    (long Dest, long Source, long Range) = CurrentMap[MapIndex];

                    if (ReturnData >= Source && ReturnData < (Source + Range))
                    {
                        ReturnData = (Dest - Source) + ReturnData;
                        break;
                    }
                }
            }

            return ReturnData;
        }

        [TestCase]
        public void Part01()
        {
            ParseSeeds();
            ParseMaps();

            /*
            Debug.Assert(Seeds.Length == 4);
            Debug.Assert(SeedToSoilMap.Count == 2, string.Join(Environment.NewLine, SeedToSoilMap));
            Debug.Assert(SeedToSoilMap[0] == ValueTuple.Create(50,98,2));
            Debug.Assert(SeedToSoilMap[1] == ValueTuple.Create(52,50,48));*/

            /* seeds: 79 14 55 13

            seed-to-soil map:
            dest 50 source 98 range 2
            dest 52 source 50 range 48

            Meaning for line 1:
            For SOURCES from 98 to 99, the DESTINATION is from 50 to 51

            So loop through each set in the map
            Check that X >= SOURCE && X < SOURCE + RANGE
            If so then calculate the destination thus: (DEST - SOURCE) + X

            Expected soil results: 81, 14, 57, 13
            */

            //Span<long> Locations = ParseAndCalculateLocations(Seeds);
            //long FinalValue = Locations.ToArray().Min();

            long Location;
            long FinalValue = long.MaxValue;

            foreach(long Seed in Seeds)
            {
                Location = CalculateLocation(Seed);
                FinalValue = Location < FinalValue ? Location : FinalValue;
            }

            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 389056265, $"Expected final score to be 389056265 but it was {FinalValue}");
        }

        [TestCase]
        public void Part02()
        {
            ParseSeeds();
            ParseMaps();

            Trace.Assert(Seeds.Length % 2 == 0);

            Span<ValueTuple<long, long>> SeedsAndRanges = stackalloc ValueTuple<long, long>[Seeds.Length / 2];
            long FinalValue = long.MaxValue;
            long Location;

            int SeedRangeIndex = 0;
            for (int Index = 0; Index < Seeds.Length; Index += 2, SeedRangeIndex++)
            {
                long SeedStart = Seeds[Index];
                long SeedRange = Seeds[Index + 1];

                SeedsAndRanges[SeedRangeIndex] = ValueTuple.Create(SeedStart, SeedRange);
            }

            int SeedIndex = 0;
            var Timer = Stopwatch.StartNew();

            foreach((long SeedStart, long SeedRange) in SeedsAndRanges)
            {
                long SeedMaxExclusive = SeedStart + SeedRange;
                for (long CurrentSeed = SeedStart; CurrentSeed < SeedMaxExclusive; CurrentSeed++)
                {
                    Location = CalculateLocation(CurrentSeed);
                    FinalValue = Location < FinalValue ? Location : FinalValue;
                }

                Console.WriteLine($"Seed range {SeedIndex + 1} ({SeedRange}): " + Timer.Elapsed);
                Timer.Restart();

                //if (SeedIndex == 1) break;
                SeedIndex++;
            }

            // 896125601 for seed range 0
            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 137516820, $"Expected final score to be 137516820 but it was {FinalValue}");
        }
    }
}
