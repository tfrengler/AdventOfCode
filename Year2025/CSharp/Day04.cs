using AdventOfCode2025.lib;
using NUnit.Framework;

namespace AdventOfCode2025
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day04: Day
    {
        public Day04(): base(4)
        {

        }

        [TestCase]
        public void Part01()
        {
            string[] paperRollGrid = [
                "..@@.@@@@.",
                "@@@.@.@.@@",
                "@@@@@.@.@@",
                "@.@@@@..@.",
                "@@.@@@@.@@",
                ".@@@@@@@.@",
                ".@.@.@.@@@",
                "@.@@@.@@@@",
                ".@@@@@@@@.",
                "@.@.@@@.@.",
            ];
        }
    }
}
