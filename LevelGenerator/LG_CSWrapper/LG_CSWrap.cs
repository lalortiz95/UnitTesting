using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;


namespace LG_CSWrapper
{


    public class LG_CSRoom
    {
        /**
         *  @var This variable store the position of the room in the X axis. 
         */
        public float m_fPosX;

        /**
         *  @var This variable store the position of the room in the Y axis.
         */
        public float m_fPosY;

        /**
         *  @var
         */
        public float m_fPosZ;

        /**
         *  @var
         */
        public int m_iID;

        /**
         *  @var
         */
        public int m_iParentID;

        /**
         *  @var
         */
        public List<int> m_pArrayConectionsID = new List<int>();

        /**
         *  @var
         */
        public float m_fWidth;

        /**
         *  @var
         */
        public float m_fHeight;
    }


    public class LG_CSWrap
    {
    
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomID", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomsParentID", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomsParentID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWidth", CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetRoomWidth(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomHeight", CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetRoomHeight(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomConectionsSize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomConectionsSize(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetOneRoomConectionID", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetOneRoomConectionID(IntPtr pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GenerateLevel", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomAmount", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetRoomAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_X", CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetRoomPosition_X(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Y", CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetRoomPosition_Y(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Z", CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetRoomPosition_Z(IntPtr pGenerate, int iRoomArrayPosition);


        private static IntPtr CS_GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z)
        {
            return GenerateLevel(iRoomAmount, iMinSizeRoom_X, iMinSizeRoom_Y, iMinSizeRoom_Z, iMaxSizeRoom_X, iMaxSizeRoom_Y, iMaxSizeRoom_Z);
        }

        private static int CS_GetRoomAmount(IntPtr pGenerate)
        {
            return GetRoomAmount(pGenerate);
        }

        private static int CS_GetRoomID(IntPtr pGenerate, int iRoomArrayPosition)
        {
            return GetRoomID(pGenerate, iRoomArrayPosition);
        }

        private static int CS_GetRoomsParentID(IntPtr pGenerate, int iRoomArrayPosition)
        {
            return GetRoomsParentID(pGenerate, iRoomArrayPosition);
        }

        private static float CS_GetRoomWidth(IntPtr pGenerate, int iRoomArrayPosition)
        {
            return GetRoomWidth(pGenerate, iRoomArrayPosition);
        }

        private static float CS_GetRoomHeight(IntPtr pGenerate, int iRoomArrayPosition)
        {
            return GetRoomHeight(pGenerate, iRoomArrayPosition);
        }

        private static int CS_GetRoomConectionsSize(IntPtr pGenerate, int iRoomArrayPosition)
        {
            return GetRoomConectionsSize(pGenerate, iRoomArrayPosition);
        }


        private static int CS_GetOneRoomConectionID(IntPtr pGenerate, int iRoomArrayPosition, int iRoomConectionPosition)
        {
            return GetOneRoomConectionID(pGenerate, iRoomArrayPosition, iRoomConectionPosition);
        }


        private static float CS_GetRoomPosition_X(IntPtr pGenerate, int iRoomAmount)
        {
            return GetRoomPosition_X(pGenerate, iRoomAmount);
        }

        private static float CS_GetRoomPosition_Y(IntPtr pGenerate, int iRoomAmount)
        {
            return GetRoomPosition_Y(pGenerate, iRoomAmount);
        }

        private static float CS_GetRoomPosition_Z(IntPtr pGenerate, int iRoomAmount)
        {
            return GetRoomPosition_Z(pGenerate, iRoomAmount);
        }



        public List<LG_CSRoom> m_Rooms = new List<LG_CSRoom>();

        public  IntPtr CS_CreateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
                               int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z)
        {
           
            IntPtr pGenerateLevel = CS_GenerateLevel(iRoomAmount, iMinSizeRoom_X, iMinSizeRoom_Y, iMinSizeRoom_Z, iMaxSizeRoom_X, iMaxSizeRoom_Y, iMaxSizeRoom_Z);

            int RoomAmount = CS_GetRoomAmount(pGenerateLevel);

            m_Rooms.Clear();
            m_Rooms = new List<LG_CSRoom>(RoomAmount);

            for (int i = 0; i < RoomAmount; i++)
            {

                LG_CSRoom newRoom = new LG_CSRoom();
                /// We assign the room's ID.
                newRoom.m_iID = CS_GetRoomID(pGenerateLevel, i);

                /// Store the room's parent.
                newRoom.m_iParentID = CS_GetRoomsParentID(pGenerateLevel, i);

                /// Stores the room's Width.
                newRoom.m_fWidth = CS_GetRoomWidth(pGenerateLevel, i);
                /// Stores the room's height.
                newRoom.m_fHeight = CS_GetRoomHeight(pGenerateLevel, i);

                /// Coordinates change to work under unity's coordinates system.
                newRoom.m_fPosX = CS_GetRoomPosition_X(pGenerateLevel, i);
                newRoom.m_fPosZ = CS_GetRoomPosition_Z(pGenerateLevel, i);
                newRoom.m_fPosY = CS_GetRoomPosition_Y(pGenerateLevel, i);


                /// 
                int iConnectionSize = CS_GetRoomConectionsSize(pGenerateLevel, i);

                newRoom.m_pArrayConectionsID.Clear();
                newRoom.m_pArrayConectionsID = new List<int>(iConnectionSize);
                /// 
                for (int j = 0; j < iConnectionSize; j++)
                { 
                    newRoom.m_pArrayConectionsID.Add(CS_GetOneRoomConectionID(pGenerateLevel, i, j));
                }

                m_Rooms.Add(newRoom);
            }

            return pGenerateLevel;
        }
    }
}
