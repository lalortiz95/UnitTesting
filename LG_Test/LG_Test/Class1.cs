using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace LG_Test
{
    public struct LG_Vector3D
    {
        /// @var Variables to store the positions in X, Y, and Z axis.
        float X;
        float Y;
        float Z;

        /// Parameter constructor.
        public LG_Vector3D(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }

    public struct LG_Node
    {
        /// The position of the node.
        LG_Vector3D position;
    }

    public struct LG_Rect
    {
        /// @var
        float fWidth;
        float fHeight;
        LG_Node CenterPosition;
    }

    public class TestCSharpLib
    {
        [DllImport("LG_Algorithms.dll")]
        static extern IntPtr GenerateLevel(int RoomsAmount, LG_Vector3D minSizeRoom, LG_Vector3D maxSizeRoom);

        [DllImport("LG_Algorithms.dll")]
        static extern LG_Rect[] GetRooms();

        public static IntPtr SharpGenerateLevel(int RoomsAmount, LG_Vector3D minSizeRoom, LG_Vector3D maxSizeRoom)
        {
            return GenerateLevel(RoomsAmount, minSizeRoom, maxSizeRoom);
        }

        //! This function returns a vector where we store the rooms.
        public static LG_Rect[] SharpGetRooms()
        {
            return GetRooms();
        }
    }
}

