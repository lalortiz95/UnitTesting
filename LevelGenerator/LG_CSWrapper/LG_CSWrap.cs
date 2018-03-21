using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;


namespace LG_CSWrapper
{
    public class LG_Vector3
    {
        public LG_Vector3()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        public LG_Vector3(float fPosX, float fPosY, float fPosZ)
        {
            X = fPosX;
            Y = fPosY;
            Z = fPosZ;
        }

        ~LG_Vector3()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        public float X;
        public float Y;
        public float Z;
    }

    public class LG_CSPolygon
    {
        public LG_CSPolygon()
        {

        }

        ~LG_CSPolygon()
        {

        }

        /**
       *  @var
       */
        public List<LG_Vector3> m_pNodesPosition;

        public int iFirstParentRoom;
        public int iSecondParentRoom;
    }

    public class LG_CSHallway
    {
        /**
         *  @var
         */
        public LG_CSPolygon HallwayShape;

        /**
         *  @var
         */
        public bool bIsCorner;
    }

    public class LG_CSRoom
    {
        public LG_CSRoom()
        {
            m_Position = new LG_Vector3(0.0f, 0.0f, 0.0f);
            m_TopLeftPosition = new LG_Vector3(0.0f, 0.0f, 0.0f);
            m_TopRightPosition = new LG_Vector3(0.0f, 0.0f, 0.0f);
            m_BottomLeftPosition = new LG_Vector3(0.0f, 0.0f, 0.0f);
            m_BottomRightPosition = new LG_Vector3(0.0f, 0.0f, 0.0f);
            m_iID = 0;
            m_iParentID = 0;
            m_pArrayConectionsID = new List<int>();
            m_fWidth = 0.0f;
            m_fHeight = 0.0f;
        }

        ~LG_CSRoom()
        {
            m_fHeight = 0.0f;
            m_fWidth = 0.0f;
            m_pArrayConectionsID = new List<int>();
            m_iParentID = 0;
            m_iID = 0;

        }

        /**
         *  @var
         */
        public LG_Vector3 m_Position;

        /**
       *  @var
       */
        public LG_Vector3 m_TopLeftPosition;

        /**
         *  @var
         */
        public LG_Vector3 m_TopRightPosition;

        /**
         *  @var
         */
        public LG_Vector3 m_BottomLeftPosition;

        /**
         *  @var
         */
        public LG_Vector3 m_BottomRightPosition;

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
        public List<int> m_pArrayConectionsID;

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
        private static extern int GetRoomID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomsParentID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomsParentID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWidth(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomHeight(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomConectionsSize", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomConectionsSize(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetOneRoomConectionID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetOneRoomConectionID(IntPtr pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GenerateLevel", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z, int iSeed, int iSeparationRange);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomPosition_X(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomPosition_Y(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomPosition_Z(IntPtr pGenerate, int iRoomArrayPosition);



        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomNodePosition_X(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomNodePosition_Y(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomNodePosition_Z(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);


        //TODO:
        //  Generar clase de Pasillo que tenga propiedades similares a las definidas en el código de C++. Para con este llenar variables en sus respectivas funciones.
        //  Y llenar una lista de pasillos con las que se pueda trabjar en el espacio tridimensional para representar la escena adecuadamente.
        //TODO: darle cuerpo a la función para la cantidad de nodos de cada pasillo.

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetNodeAmountFromHallway", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetNodeAmountFromHawllway(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayPosition_X(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayPosition_Y(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayPosition_Z(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);





        [DllImport("LG_CPPWrapper", EntryPoint = "Pathfinding_DIJKSTRA", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Pathfinding_DIJKSTRA(IntPtr pGenerate, int iStartNode, int iEndNode);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetPathSize_DIJKSTRA", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetPathSize_DIJKSTRA(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetPath_DIJKSTRA_OneByOne", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetPath_DIJKSTRA_OneByOne(IntPtr pGenerate, int iPathArrayPosition);





        public List<LG_CSRoom> m_Rooms = new List<LG_CSRoom>();
        public List<LG_CSHallway> m_Hallway = new List<LG_CSHallway>();

        public int[] CS_Pathfinding_DIJKSTRA(IntPtr pGenerate, int iStartNode, int iEndNode)
        {
            int iPathSize = 0;
            int[] pPath = null;

            Pathfinding_DIJKSTRA(pGenerate, iStartNode, iEndNode);
            iPathSize = GetPathSize_DIJKSTRA(pGenerate);

            for (int i = 0; i < iPathSize; i++)
            {
                pPath[i] = GetPath_DIJKSTRA_OneByOne(pGenerate, i);
            }

            return pPath;
        }


        public IntPtr CS_GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z, int iSeed, int iSeparationRange)
        {
            IntPtr pGenerateLevel = GenerateLevel(iRoomAmount, iMinSizeRoom_X, iMinSizeRoom_Y, iMinSizeRoom_Z, iMaxSizeRoom_X, iMaxSizeRoom_Y, iMaxSizeRoom_Z, iSeed, iSeparationRange);

            int RoomAmount = GetRoomAmount(pGenerateLevel);
            int iHallwayAmount = GetHallwayAmount(pGenerateLevel);
            int iNodeAmount = GetNodeAmountFromHawllway(pGenerateLevel);

            LG_CSHallway newHallway;

            for (int i = 0; i < iHallwayAmount; ++i)
            {
                /// We allocate memory for a new hallway that is going to be generated.
                newHallway = new LG_CSHallway();

                for (int j = 0; j < iNodeAmount; ++j)
                {
                    /// Here we store the position of every node, from every hallway
                    newHallway.HallwayShape.m_pNodesPosition[j].X = GetHallwayPosition_X(pGenerateLevel, i, j);
                    newHallway.HallwayShape.m_pNodesPosition[j].Y = GetHallwayPosition_Y(pGenerateLevel, i, j);
                    newHallway.HallwayShape.m_pNodesPosition[j].Z = GetHallwayPosition_Z(pGenerateLevel, i, j);
                }

                //TODO: guardar si es corner, y el resto de las variables necesarias para generar los pasillos.
                //newHallway.bIsCorner = 

                m_Hallway.Add(newHallway);
            }


            for (int i = 0; i < RoomAmount; i++)
            {

                LG_CSRoom newRoom = new LG_CSRoom();
                //    /// We assign the room's ID.
                newRoom.m_iID = GetRoomID(pGenerateLevel, i);

                /// Stores the room's Width.
                newRoom.m_fWidth = GetRoomWidth(pGenerateLevel, i);
                /// Stores the room's height.
                newRoom.m_fHeight = GetRoomHeight(pGenerateLevel, i);

                /// Coordinates change to work under unity's coordinates system.
                newRoom.m_Position.X = GetRoomPosition_X(pGenerateLevel, i);
                newRoom.m_Position.Y = GetRoomPosition_Z(pGenerateLevel, i);
                newRoom.m_Position.Z = GetRoomPosition_Y(pGenerateLevel, i);

                newRoom.m_TopLeftPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 0);
                newRoom.m_TopLeftPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 0);
                newRoom.m_TopLeftPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 0);

                newRoom.m_TopRightPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 1);
                newRoom.m_TopRightPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 1);
                newRoom.m_TopRightPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 1);

                newRoom.m_BottomLeftPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 2);
                newRoom.m_BottomLeftPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 2);
                newRoom.m_BottomLeftPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 2);

                newRoom.m_BottomRightPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 3);
                newRoom.m_BottomRightPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 3);
                newRoom.m_BottomRightPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 3);


                int iConnectionSize = GetRoomConectionsSize(pGenerateLevel, i);

                for (int j = 0; j < iConnectionSize; j++)
                {
                    newRoom.m_pArrayConectionsID.Add(GetOneRoomConectionID(pGenerateLevel, i, j));
                }

                m_Rooms.Add(newRoom);
            }

            return pGenerateLevel;
        }
    }
}
