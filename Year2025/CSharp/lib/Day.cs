using System;
using System.IO;

namespace AdventOfCode2025.lib
{
    public abstract class Day
    {
        protected string[] _inputAsLines = [];
        protected string _inputAsString = string.Empty;
        private readonly FileInfo _inputFile;

        public Day(int number)
        {
            string inputFileAndPath = Path.Combine(AppContext.BaseDirectory, "input/" + Convert.ToString(number).PadLeft(2, '0') + ".txt");
            _inputFile = new FileInfo(inputFileAndPath);
            if (!_inputFile.Exists)
            {
                throw new FileNotFoundException($"Input file for day {number} not found:" + _inputFile.FullName);
            }
        }

        protected string[] LoadInputAsLines()
        {
            _inputAsLines = File.ReadAllLines(_inputFile.FullName);
            return _inputAsLines;
        }

        protected string LoadInputAsString()
        {
            _inputAsString = File.ReadAllText(_inputFile.FullName);
            return _inputAsString;
        }
    }
}
