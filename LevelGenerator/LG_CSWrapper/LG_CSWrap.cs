using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;


namespace LG_CSWrapper
{


    public class LG_CSWrap
    {

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr MyClass();

        [DllImport("LG_CPPWrapper",  CallingConvention = CallingConvention.Cdecl)]
        public static extern int multiplyvalue(int ivalue);

        [DllImport("LG_CPPWrapper",  CallingConvention = CallingConvention.Cdecl)]
        public static extern void Run(int iRoomAmount);

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomID(int iPlaceInArray);

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetRoomPosition(int iPlaceInArray, ref float fx, ref float fy, ref float fz);


        public static IntPtr CSMyClass()
        {
            return MyClass();
        }

        public static int CSMulty(int ivalue)
        {
            return multiplyvalue(ivalue);
        }

        public static void CSRun(int iRoomAmount)
        {
            Run(iRoomAmount);
        }

        public static int CSGetRoomID(int iPlace)
        {
            return GetRoomID(iPlace);
        }

        public static void CSGetRoomPosition(int iPlace, ref float fx, ref float fy, ref float fz)
        {
            GetRoomPosition(iPlace, ref fx, ref fy, ref fz);
        }
    }
}
