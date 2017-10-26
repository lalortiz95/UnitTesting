using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace LG_Test
{
    public struct Vector3D
    {
        float X;
        float Y;
        float Z;

        public Vector3D(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }

    public class TestCSharpLib
    {
        [DllImport("LG_Algorithms.dll")]
        static extern IntPtr GenerateLevel(int RoomsAmount, Vector3D minSizeRoom, Vector3D maxSizeRoom);

        public static IntPtr SharpGenerateLevel(int RoomsAmount, Vector3D minSizeRoom, Vector3D maxSizeRoom)
        {
            return GenerateLevel(RoomsAmount, minSizeRoom, maxSizeRoom);
        }
    }
}

