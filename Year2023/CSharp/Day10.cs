using NUnit.Framework;
using System.Collections.Generic;

namespace AdventOfCode.Year2023
{
    [TestFixture]
    [NonParallelizable]
    public sealed class Day10
    {
        private enum Directions
        {
            NS, EW, NE, NW,
            SW, SE, G,  S
        }

        private Dictionary<char, Directions> DirectionMap = new()
        {
            { '|', Directions.NS },
            { '-', Directions.NS },
            { 'L', Directions.NS },
            { 'J', Directions.NS },
            { '7', Directions.NS },
            { 'F', Directions.NS },
            { '.', Directions.NS },
            { 'S', Directions.NS }
        };
    }
}
