using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;


namespace LG_CSWrapper
{
    struct LG_Vector3D
    {
        float X, Y, Z;
    }

    public class LG_CSWrap
    {
        // From c++ Dll (unmanaged)
        [DllImport("LG_Algorithms", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GenerateRooms(int iRoomAmount);
    }
}
