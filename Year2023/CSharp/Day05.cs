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
    [NonParallelizable]
    public class Day05
    {
        readonly string[] Input;

        Regex DigitRegex = new Regex(@"(\d+)");

        long[] Seeds;

        List<ValueTuple<long, long, long>> SeedToSoilMap;
        List<ValueTuple<long, long, long>> SoilToFertilizerMap;
        List<ValueTuple<long, long, long>> FertilizerToWaterMap;
        List<ValueTuple<long, long, long>> WaterToLightMap;
        List<ValueTuple<long, long, long>> LightToTemperatureMap;
        List<ValueTuple<long, long, long>> TemperatureToHumidityMap;
        List<ValueTuple<long, long, long>> HumidityToLocationMap;

        List<ValueTuple<long, long, long>>[] RefsToMapsInOrder;

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
            SeedToSoilMap = new List<ValueTuple<long, long, long>>();
            SoilToFertilizerMap = new List<ValueTuple<long, long, long>>();
            FertilizerToWaterMap = new List<ValueTuple<long, long, long>>();
            WaterToLightMap = new List<ValueTuple<long, long, long>>();
            LightToTemperatureMap = new List<ValueTuple<long, long, long>>();
            TemperatureToHumidityMap = new List<ValueTuple<long, long, long>>();
            HumidityToLocationMap = new List<ValueTuple<long, long, long>>();

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

                RefsToMapsInOrder = new[]
                {
                    SeedToSoilMap,
                    SoilToFertilizerMap,
                    FertilizerToWaterMap,
                    WaterToLightMap,
                    LightToTemperatureMap,
                    TemperatureToHumidityMap,
                    HumidityToLocationMap
                };
            }
        }

        long[] ParseAndCalculateLocations(IList<long> seeds)
        {
            long[] Locations = new long[seeds.Count];

            for (int SeedIndex = 0; SeedIndex < seeds.Count; SeedIndex++)
            {
                long DestinationIndex = seeds[SeedIndex];

                for (int ChainIndex = 0; ChainIndex < RefsToMapsInOrder.Length; ChainIndex++)
                {
                    DestinationIndex = CalculateDestinationIndex(RefsToMapsInOrder[ChainIndex], DestinationIndex);
                }

                Locations[SeedIndex] = DestinationIndex;
            }

            return Locations;
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

            Span<long> Locations = ParseAndCalculateLocations(Seeds);

            long FinalValue = Locations.ToArray().Min();
            Console.WriteLine(FinalValue);
            Trace.Assert(FinalValue == 389056265, $"Expected final score to be 389056265 but it was {FinalValue}");
        }

        [TestCase]
        public void Part02()
        {
            ParseSeeds();
            ParseMaps();

            List<long> ParsedSeedsBasedOnRange = new List<long>();
            long FinalValue = long.MaxValue;

            for (int Index = 0; Index < Seeds.Length; Index += 2)
            {
                long SeedStart = Seeds[Index];
                long SeedRange = Seeds[Index + 1];

                for(long RangeIndex = 0; RangeIndex < SeedRange; RangeIndex++)
                {
                    ParsedSeedsBasedOnRange.Add(SeedStart + RangeIndex);
                }

                long[] Locations = ParseAndCalculateLocations(ParsedSeedsBasedOnRange);
                ParsedSeedsBasedOnRange.Clear();
                long MinValue = Locations.Min();

                FinalValue = MinValue < FinalValue ? MinValue : FinalValue;
            }

            Console.WriteLine(FinalValue);
            //Trace.Assert(FinalValue == 46, $"Expected final score to be 46 but it was {FinalValue}");
        }
    }
}
