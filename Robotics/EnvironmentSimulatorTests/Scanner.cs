﻿using EnvironmentSimulator;
using System;
using System.Linq;
using Xunit;

namespace EnvironmentSimulatorTests
{
    public class Scanner
    {

        private Map map;
        private IEnvironment env;

        public Scanner()
        {
            map = new Map(100, 100);
            map.SetRect(10, 10, 20, 20, 1);
            env = new DefaultSimulator(map);
            env.Direction = 0.0;
        }

        [Fact]
        public void Instantiate()
        {
            map.SetRect(10, 10, 20, 20, 1);
            var scan = env.Scan(15, 9, 21, 15).ToArray();
            Assert.Equal(7, scan.Length);
            Assert.Equal(0, scan[0]);
            Assert.Equal(1, scan[2]);
            Assert.Equal(1, scan[5]);
            Assert.Equal(0, scan[6]);
        }

        [Fact]
        public void RelativePositionCalculation()
        {
            env.Position = new Point() { X = 0, Y = 0 };
            Point pLeft = env.GetLocationOfRelativePoint(-30.0, 10);
            Assert.Equal(-0.5 * 10.0, pLeft.X);
            Assert.Equal(Math.Round(-Math.Sqrt(3)/ 2.0 * 10.0), pLeft.Y);
            Point pRight = env.GetLocationOfRelativePoint(30.0, 10);
            Assert.Equal(0.5 * 10.0, pRight.X);
            Assert.Equal(Math.Round(-Math.Sqrt(3) / 2.0 * 10.0), pRight.Y);
        }

        [Fact]
        public void RelativePositionedScan()
        {
            map.SetRect(9, 0, 11, 20, 1); // Vertical strip
            env.Position = new Point() { X = 10, Y = 15 };

            var scan = env.ScanRelative(-30.0, 10, +30.0, 10).ToArray();
            Assert.Equal(11, scan.Length);
            for (int i = 0; i <= 3; i++)
                Assert.Equal(0, scan[i]);
            for (int i = 4; i <= 6; i++)
                Assert.Equal(1, scan[i]);
            for (int i = 7; i <= 10; i++)
                Assert.Equal(0, scan[i]);
        }
    }
}
