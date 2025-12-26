using System;
using System.Collections.Generic;
using System.Linq;

namespace AdventOfCode2025.lib
{
    /// <summary>
    /// Represents a 2d grid composed of chars in a flat string. 
    /// </summary>
    public sealed class Grid
    {
        private readonly char[] _gridData;

        public int Width { get; }
        public int Height { get; }
        public int Size => Width * Height;
        public bool BoundaryCrossingIsFatal { get; set; } = true;

        public Grid(string gridData, int width, int height)
        {
            ArgumentException.ThrowIfNullOrWhiteSpace(gridData);

            _gridData = gridData.Trim().Replace("\n", "").ToCharArray();
            Width = width;
            Height = height;
        }

        public Grid(string[] gridData)
        {
            ArgumentNullException.ThrowIfNull(gridData);
            ArgumentOutOfRangeException.ThrowIfZero(gridData.Length);

            var trimmedGrid = gridData.Select(x => x.Trim());
            _gridData = string.Concat(trimmedGrid).ToCharArray();

            Width = trimmedGrid.First().Length;
            Height = gridData.Length;
        }

        public GridPoint GetPoint(GridPoint point) => GetPoint(point.X, point.Y);

        public GridPoint SetPoint(GridPoint point, char newValue) => SetPoint(point.X, point.Y, newValue);

        public GridPoint SetPoint(int x, int y, char newValue)
        {
            int index = CalculateIndexFromPoint(x, y);
            if (index == -1) return GridPoint.Invalid;

            _gridData[index] = newValue;
            return new(newValue, x, y);
        }

        public GridPoint GetPoint(int x, int y)
        {
            int index = CalculateIndexFromPoint(x, y);
            if (index == -1) return GridPoint.Invalid;

            return new GridPoint(_gridData[index], x, y);
        }

        public GridPoint GetRelativePoint(GridPoint point, GridDirection direction) => GetRelativePoint(point.X, point.Y, direction);

        public GridPoint GetRelativePoint(int x, int y, GridDirection direction)
        {
            var origin = GetPoint(x, y);
            (int relativeX, int relativeY) = GetRelativeCoordinates(direction, origin.X, origin.Y);
            return GetPoint(relativeX, relativeY);
        }

        public GridPoint GetNorthWest(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.NW);
        }

        public GridPoint GetNorth(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.N);
        }

        public GridPoint GetNorthEast(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.NE);
        }

        public GridPoint GetEast(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.E);
        }

        public GridPoint GetSouthEast(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.SE);
        }

        public GridPoint GetSouth(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.S);
        }

        public GridPoint GetSouthWest(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.SE);
        }

        public GridPoint GetWest(GridPoint input)
        {
            return GetRelativePoint(input.X, input.Y, GridDirection.W);
        }

        public GridPoint[] GetBox(GridPoint input)
        {
            var returnData = new GridPoint[8];

            returnData[0] = GetRelativePoint(input.X, input.Y, GridDirection.NW);
            returnData[1] = GetRelativePoint(input.X, input.Y, GridDirection.N);
            returnData[2] = GetRelativePoint(input.X, input.Y, GridDirection.NE);
            returnData[3] = GetRelativePoint(input.X, input.Y, GridDirection.E);
            returnData[4] = GetRelativePoint(input.X, input.Y, GridDirection.SE);
            returnData[5] = GetRelativePoint(input.X, input.Y, GridDirection.S);
            returnData[6] = GetRelativePoint(input.X, input.Y, GridDirection.SW);
            returnData[7] = GetRelativePoint(input.X, input.Y, GridDirection.W);

            return returnData;
        }

        public GridPoint[] GetStar(GridPoint input)
        {
            var returnData = new GridPoint[4];

            returnData[0] = GetRelativePoint(input.X, input.Y, GridDirection.NW);
            returnData[1] = GetRelativePoint(input.X, input.Y, GridDirection.NE);
            returnData[2] = GetRelativePoint(input.X, input.Y, GridDirection.SE);
            returnData[3] = GetRelativePoint(input.X, input.Y, GridDirection.SW);

            return returnData;
        }

        public GridPoint[] GetCross(GridPoint input)
        {
            var returnData = new GridPoint[4];

            returnData[0] = GetRelativePoint(input.X, input.Y, GridDirection.N);
            returnData[1] = GetRelativePoint(input.X, input.Y, GridDirection.E);
            returnData[2] = GetRelativePoint(input.X, input.Y, GridDirection.S);
            returnData[3] = GetRelativePoint(input.X, input.Y, GridDirection.W);

            return returnData;
        }

        public List<GridPoint> ToList()
        {
            List<GridPoint> returnData = [];
            foreach(var point in EnumerateGrid())
            {
                returnData.Add(point);
            }
            return returnData;
        }

        public IEnumerable<GridPoint> EnumerateGrid()
        {
            int index = 0;
            while (index < _gridData.Length)
            {
                (int x, int y) = CalculatePointFromIndex(index);
                index++;
                yield return GetPoint(x, y);
            }
        }

        private int CalculateIndexFromPoint(int x, int y)
        {
            if (x >= Width || x < 0)
            {
                if (!BoundaryCrossingIsFatal) return -1;
                throw new Exception($"X ({x}) is out of range of the grid width ({Width})");
            }

            if (y >= Height || y < 0)
            {
                if (!BoundaryCrossingIsFatal) return -1;
                throw new Exception($"Y ({y}) is out of range of the grid height ({Height})");
            }

            return (Width * y) + x;
        }

        private (int x, int y) CalculatePointFromIndex(int index)
        {
            int x = index % Width;
            int y = index / Width;

            return (x, y);
        }

        private static (int x, int y) GetRelativeCoordinates(GridDirection direction, int x, int y)
        {
            return direction switch
            {
                GridDirection.NW => (x - 1, y - 1),
                GridDirection.N => (x, y - 1),
                GridDirection.NE => (x + 1, y - 1),
                GridDirection.E => (x + 1, y),
                GridDirection.SE => (x + 1, y + 1),
                GridDirection.S => (x, y + 1),
                GridDirection.SW => (x - 1, y + 1),
                GridDirection.W => (x - 1, y),
                _ => throw new Exception("Wait what?")
            };
        }
    }

    public enum GridDirection
    {
        NONE, NW, N, NE, E, SE, S, SW, W
    }

    public struct GridPoint
    {
        public GridPoint(char value, int x, int y)
        {
            Value = value;
            X = x;
            Y = y;
        }

        public GridPoint(int x, int y)
        {
            Value = char.MinValue;
            X = x;
            Y = y;
        }

        public static GridPoint Invalid { get; } = new GridPoint(char.MinValue, -1, -1);

        public readonly bool IsValid => Value != char.MinValue;

        public char Value { get; set; }
        public int X { get; } = -1;
        public int Y { get; } = -1;

        public override readonly string ToString()
        {
            return string.Join(Environment.NewLine, [
                $"X     : {X}",
                $"Y     : {Y}",
                $"VALUE : {Value}"
            ]);
        }
    }
}
