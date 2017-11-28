using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;


namespace LG_CSWrapper
{
   

    public class LG_CSWrap
    {

      

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
       public static extern void Run(int iRoomAmount);

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomID(int iPlaceInArray);

        [DllImport("LG_CPPWrapper", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetRoomPosition(int iPlaceInArray, ref float fx, ref float fy, ref float fz);


        public static void CSRun(int iRoomAmount)
        {
            Run(iRoomAmount);
        }

        public static int CSGetRoomID(int iPlaceInArray)
        {
            return GetRoomID(iPlaceInArray);
        }

        public static void CSGetRoomPosition(int iPlaceInArray, ref float fx, ref float fy, ref float fz)
        {
            GetRoomPosition(iPlaceInArray,ref fx, ref fy,ref fz);
        }

        public static void CSStart()
        {

        }
    }
}
