using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode2025.lib
{
    public sealed class Grid
    {
        public int Width { get; }
        public int Height { get; }
        private readonly string _gridData;
        private bool _gridBoundaryCrossingIsFatal = true;

        public Grid(string gridData, int width, int height)
        {
            ArgumentException.ThrowIfNullOrWhiteSpace(gridData);

            _gridData = gridData.Replace("\n", "");
            Width = width;
            Height = height;
        }

        public Grid(string[] gridData)
        {
            ArgumentNullException.ThrowIfNull(gridData);
            ArgumentOutOfRangeException.ThrowIfZero(gridData.Length);

            _gridData = string.Concat(gridData);
            Width = gridData[0].Length;
            Height = gridData.Length;
        }

        public GridPoint GetPoint(int x, int y)
        {
            if (_gridBoundaryCrossingIsFatal)
            {
                if (x > Width && x < 0)
                    throw new Exception($"X ({x}) is out of range of the grid width ({Width})");

                if (y > Height && y < 0)
                    throw new Exception($"Y ({x}) is out of range of the grid height ({Height})");
            }

            int index = y > 1 ? Width * (y - 1) : 0;
            index += (x - 1);

            return new GridPoint(_gridData[index], x, y);
        }

        public GridPoint GetRelativePoint(int x, int y, GridDirection direction, bool throwIfOutsideGrid = false)
        {
            _gridBoundaryCrossingIsFatal = throwIfOutsideGrid;
            var origin = GetPoint(x, y);
            (int relativeX, int relativeY) = GetRelativeCoordinates(direction, origin.X, origin.Y);
            return GetPoint(relativeX, relativeY);
        }

        private (int x, int y) GetRelativeCoordinates(GridDirection direction, int x, int y)
        {
            return direction switch
            {
                GridDirection.NW => (x - 1, y - 1),
                GridDirection.NE => (x + 1, y - 1),
            };
        }
    }

    public enum GridDirection
    {
        NW, N, NE, E, SE, S, SW, W
    }

    public static class GridDirectionHelper
    {
        
    }

    public readonly struct GridPoint
    {
        public GridPoint(char value, int x, int y)
        {
            Value = value;
            X = x;
            Y = y;
        }

        public char Value { get; }
        public int X { get; }
        public int Y { get; }
    }
}
