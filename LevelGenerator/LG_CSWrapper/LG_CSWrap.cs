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

        public LG_Vector3 MidPoint(LG_Vector3 OtherVector)
        {
            return new LG_Vector3((X + OtherVector.X) / 2, (Y + OtherVector.Y) / 2, (Z + OtherVector.Z) / 2);
        }
    }

    public class LG_CSRect
    {
        public LG_CSRect()
        {

        }

        public LG_CSRect(LG_Vector3 CenterPos, float fHeight, float fWidth)
        {
            m_CenterPosition = CenterPos;
            m_fHeight = fHeight;
            m_fWidth = fWidth;
        }

        ~LG_CSRect()
        {

        }

        public LG_Vector3 m_CenterPosition;

        public float m_fHeight;
        public float m_fWidth;
        public bool m_bIsHorizontal;
    }

    public class LG_CSPolygon
    {
        public LG_CSPolygon()
        {
            m_pNodesPosition = new List<LG_Vector3>();
        }

        ~LG_CSPolygon()
        {
            m_pNodesPosition = new List<LG_Vector3>();
        }

        /**
       *  @var
       */
        public List<LG_Vector3> m_pNodesPosition;
    }

    public class LG_CSHallway
    {
        public LG_CSHallway()
        {
            HallwayShape = new LG_CSPolygon();
            iFirstParentRoom = 0;
            iSecondParentRoom = 0;

            m_Walls = new List<LG_CSRect>();
            m_Floors = new List<LG_CSRect>();
            m_Ceilings = new List<LG_CSRect>();

            bIsCorner = false;
        }

        ~LG_CSHallway()
        {
            iFirstParentRoom = 0;
            iSecondParentRoom = 0;
            bIsCorner = false;
        }

        /**
         *  @var
         */
        public LG_CSPolygon HallwayShape;

        /**
         *  @var
         */
        public List<LG_CSRect> m_Walls;

        /**
         *  @var
         */
        public List<LG_CSRect> m_Floors;

        /**
         *  @var
         */
        public List<LG_CSRect> m_Ceilings;

        /**
         *  @var
         */
        public bool bIsCorner;

        public int iFirstParentRoom;
        public int iSecondParentRoom;
    }

    public class LG_CSDoor
    {
        public LG_CSDoor()
        {
            m_Door = new LG_CSRect();
        }

        ~LG_CSDoor()
        {

        }

        LG_CSRect m_Door;
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
            m_Walls = new List<LG_CSRect>();
            m_Floor = new LG_CSRect();
            m_Ceiling = new LG_CSRect();
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
        public List<LG_CSRect> m_Walls;

        /**
         *  @var
         */
        public LG_CSRect m_Floor;

        /**
         *  @var
         */
        public LG_CSRect m_Ceiling;



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

    //TODO: cargar las nuevas funciones y borrar las antiguas.
    public class LG_CSWrap
    {
        [DllImport("LG_CPPWrapper", EntryPoint = "GenerateLevel", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y,
                                                    int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, 
                                                    int iSeed, int iSeparationRange, int iHallwayWidth);


        ///************************************************************************/
        ///*                           Rooms Functions.			                  */
        ///************************************************************************/ 
        ///
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomsParentID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomsParentID(IntPtr pGenerate, int iRoomArrayPosition);

        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWidth", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomWidth(IntPtr pGenerate, int iRoomArrayPosition);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomHeight", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomHeight(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomConectionsSize", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomConectionsSize(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetOneRoomConectionID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetOneRoomConectionID(IntPtr pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);


        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomWallsAmount(IntPtr pGenerate, int iRoom);


        /// The flag that states if the wall is vertical or horizontal.
        [DllImport("LG_CPPWrapper", EntryPoint = "IsRoomWallHorizontal", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsRoomWallHorizontal(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        /// The center positions of a room's wall.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWallCenterPosition_X(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWallCenterPosition_Y(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWallCenterPosition_Z(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        /// The width and height of a room's wall.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWallHeight(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomWallWidth(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);


        /// The center positions of a room's floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomFloorCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomFloorCenterPosition_X(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomFloorCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomFloorCenterPosition_Y(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomFloorCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomFloorCenterPosition_Z(IntPtr pGenerate, int iRoomArrPos);

        /// The width and height of a room's floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomFloorHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomFloorHeight(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomFloorWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomFloorWidth(IntPtr pGenerate, int iRoomArrPos);


        /// The center positions of a room's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomCeilingCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomCeilingCenterPosition_X(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomCeilingCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomCeilingCenterPosition_Y(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomCeilingCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomCeilingCenterPosition_Z(IntPtr pGenerate, int iRoomArrPos);

        /// The width and height of a room's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomCeilingHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomCeilingHeight(IntPtr pGenerate, int iRoomArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomCeilingWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetRoomCeilingWidth(IntPtr pGenerate, int iRoomArrPos);


        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_X", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomPosition_X(IntPtr pGenerate, int iRoomArrayPosition);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Y", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomPosition_Y(IntPtr pGenerate, int iRoomArrayPosition);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomPosition_Z", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomPosition_Z(IntPtr pGenerate, int iRoomArrayPosition);



        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_X", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomNodePosition_X(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_Y", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomNodePosition_Y(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetRoomNodePosition_Z", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetRoomNodePosition_Z(IntPtr pGenerate, int iRoomArrayPosition, int iNumOfNode);




        ///************************************************************************/
        ///*                            Hallway Functions.		                  */
        ///************************************************************************/

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayWallsAmount(IntPtr pGenerate, int iHallway);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayFloorsAmount(IntPtr pGenerate, int iHallway);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayCeilingsAmount(IntPtr pGenerate, int iHallway);

        //[DllImport("LG_CPPWrapper", EntryPoint = "GetNodeAmountFromHallway", CallingConvention = CallingConvention.Cdecl)]
        //private static extern int GetNodeAmountFromHawllway(IntPtr pGenerate, int iHallway);

        [DllImport("LG_CPPWrapper", EntryPoint = "IsCorner", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsCorner(IntPtr pGenerate, int iHallway);

        /// The center positions of a hallway's wall.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayWallCenterPosition_X(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayWallCenterPosition_Y(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayWallCenterPosition_Z(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        /// The width and height of a hallway's wall.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayWallHeight(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayWallWidth(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "IsHallwayWallHorizontal", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsHallwayWallHorizontal(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);


        /// The center positions of a hallway's Floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_X(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_Y(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_Z(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        /// The width and height of a hallway's floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorHeight(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorWidth(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);


        /// The center positions of a hallway's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_X(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_Y(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_Z(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

        /// The width and height of a hallway's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingHeight(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingWidth(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);


        //[DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_X", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetHallwayPosition_X(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_Y", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetHallwayPosition_Y(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);
        //
        //[DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayNodePosition_Z", CallingConvention = CallingConvention.Cdecl)]
        //private static extern float GetHallwayPosition_Z(IntPtr pGenerate, int iHallwayArrayPosition, int iNode);





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


        public IntPtr CS_GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, int iSeed, int iSeparationRange, int iHallwayWidth)
        {
            IntPtr pGenerateLevel = GenerateLevel(iRoomAmount, iMinSizeRoom_X, iMinSizeRoom_Y, iMaxSizeRoom_X, iMaxSizeRoom_Y, iHeight, iSeed, iSeparationRange, iHallwayWidth);

            int RoomAmount = GetRoomAmount(pGenerateLevel);
            int iHallwayAmount = GetHallwayAmount(pGenerateLevel);
            int iNodeAmount = 0;

            LG_CSHallway newHallway = null;
            LG_Vector3 newVector = null;
            // Used to initialize walls, floors, and ceilings.
            LG_CSRect TempRect = null;
            LG_CSRoom newRoom = null;

            for (int i = 0; i < iHallwayAmount; ++i)
            {
                /// We allocate memory for a new hallway that is going to be generated.
                newHallway = new LG_CSHallway();

                iNodeAmount = GetHallwayWallsAmount(pGenerateLevel, i);

                for (int j = 0; j < iNodeAmount; ++j)
                {
                    newVector = new LG_Vector3();

                    /// Here we store the position of every node, from every hallway
                    newVector.X = GetHallwayWallCenterPosition_X(pGenerateLevel, i, j);
                    newVector.Y = GetHallwayWallCenterPosition_Z(pGenerateLevel, i, j);
                    newVector.Z = GetHallwayWallCenterPosition_Y(pGenerateLevel, i, j);

                    /// A new rect representing the tridimensional wall is now generated.
                    TempRect = new LG_CSRect(newVector, GetHallwayWallHeight(pGenerateLevel, i, j), GetHallwayWallWidth(pGenerateLevel, i, j));

                    ///
                    TempRect.m_bIsHorizontal = IsHallwayWallHorizontal(pGenerateLevel, i, j);

                    /// Now the wall is added to the list.
                    newHallway.m_Walls.Add(TempRect);
                }

                ///
                iNodeAmount = GetHallwayFloorsAmount(pGenerateLevel, i);

                for (int j = 0; j < iNodeAmount; j++)
                {
                    /// We allocate memory for a new hallway that is going to be generated.
                    //newHallway = new LG_CSHallway();
                    /// At this point we allocate new memory to the vector and the rectangle to re use the variables, and fill with that information the floor. Eventually the ceiling.
                    newVector = new LG_Vector3();
                    newVector.X = GetHallwayFloorCenterPosition_X(pGenerateLevel, i, j);
                    newVector.Y = GetHallwayFloorCenterPosition_Z(pGenerateLevel, i, j);
                    newVector.Z = GetHallwayFloorCenterPosition_Y(pGenerateLevel, i, j);

                    TempRect = new LG_CSRect(newVector, GetHallwayFloorHeight(pGenerateLevel, i, j), GetHallwayFloorWidth(pGenerateLevel, i, j));

                    newHallway.m_Floors.Add(TempRect);
                }

                /// 
                iNodeAmount = GetHallwayCeilingsAmount(pGenerateLevel, i);

                for (int j = 0; j < iNodeAmount; j++)
                {
                    /// We allocate memory for a new hallway that is going to be generated.
                    //newHallway = new LG_CSHallway();

                    /// We once again recycle our variables to complete the loop by storing the ceilings.
                    newVector = new LG_Vector3();
                    newVector.X = GetHallwayCeilingCenterPosition_X(pGenerateLevel, i, j);
                    newVector.Y = GetHallwayCeilingCenterPosition_Z(pGenerateLevel, i, j);
                    newVector.Z = GetHallwayCeilingCenterPosition_Y(pGenerateLevel, i, j);

                    TempRect = new LG_CSRect(newVector, GetHallwayCeilingHeight(pGenerateLevel, i, j), GetHallwayCeilingWidth(pGenerateLevel, i, j));

                    newHallway.m_Ceilings.Add(TempRect);
                }

                /// A flag that stores if the hallway is a corner.
                newHallway.bIsCorner = IsCorner(pGenerateLevel, i);

                /// The hallway is inserted to the list of hallways.
                m_Hallway.Add(newHallway);
            }


            //TODO: moficiar esto para que tenga la nueva estructura de los cuartos.
            for (int i = 0; i < RoomAmount; i++)
            {
                /// 
                newRoom = new LG_CSRoom();
                /// We assign the room's ID.
                newRoom.m_iID = GetRoomID(pGenerateLevel, i);

                ///
                iNodeAmount = GetRoomWallsAmount(pGenerateLevel, i);
                /// 
                for (int j = 0; j < iNodeAmount; j++)
                {
                    newVector = new LG_Vector3();
                    /// the center node position is now stored.
                    newVector.X = GetRoomWallCenterPosition_X(pGenerateLevel, i, j);
                    newVector.Y = GetRoomWallCenterPosition_Z(pGenerateLevel, i, j);
                    newVector.Z = GetRoomWallCenterPosition_Y(pGenerateLevel, i, j);

                    TempRect = new LG_CSRect(newVector, GetRoomWallHeight(pGenerateLevel, i, j), GetRoomWallWidth(pGenerateLevel, i, j));

                    /// We store if the rect is supposed to be stretched in the X, or Z axis.
                    TempRect.m_bIsHorizontal = IsRoomWallHorizontal(pGenerateLevel, i, j);

                    newRoom.m_Walls.Add(TempRect);
                    //newRoom.m_Walls[j].m_CenterPosition.X = GetRoomWallCenterPosition_X(pGenerateLevel, i, j);
                    //newRoom.m_Walls[j].m_CenterPosition.Y = GetRoomWallCenterPosition_Y(pGenerateLevel, i, j);
                    //newRoom.m_Walls[j].m_CenterPosition.Z = GetRoomWallCenterPosition_Z(pGenerateLevel, i, j);

                    //newRoom.m_Walls[j].m_fHeight = GetRoomWallHeight(pGenerateLevel, i, j);
                    //newRoom.m_Walls[j].m_fWidth = GetRoomWallWidth(pGenerateLevel, i, j);
                }

                //TODO: llenar la infomación en temporales y después agregarlas al floor?
                newVector = new LG_Vector3();
                /// Here the floor is stored in the iterating new room.
                newVector.X = GetRoomFloorCenterPosition_X(pGenerateLevel, i);
                newVector.Y = GetRoomFloorCenterPosition_Z(pGenerateLevel, i); 
                newVector.Z = GetRoomFloorCenterPosition_Y(pGenerateLevel, i);

                TempRect = new LG_CSRect(newVector, GetRoomFloorHeight(pGenerateLevel, i), GetRoomFloorWidth(pGenerateLevel, i));
                newRoom.m_Floor = TempRect;
                //newRoom.m_Floor.m_CenterPosition.X = GetRoomFloorCenterPosition_X(pGenerateLevel, i);
                //newRoom.m_Floor.m_CenterPosition.Y = GetRoomFloorCenterPosition_Y(pGenerateLevel, i);
                //newRoom.m_Floor.m_CenterPosition.Z = GetRoomFloorCenterPosition_Z(pGenerateLevel, i);

                /// Here the floor is stored in the iterating new room.
                newVector = new LG_Vector3();
                newVector.X = GetRoomCeilingCenterPosition_X(pGenerateLevel, i);
                newVector.Y = GetRoomCeilingCenterPosition_Z(pGenerateLevel, i);
                newVector.Z = GetRoomCeilingCenterPosition_Y(pGenerateLevel, i);

                TempRect = new LG_CSRect(newVector, GetRoomCeilingHeight(pGenerateLevel, i), GetRoomCeilingWidth(pGenerateLevel, i));

                newRoom.m_Ceiling = TempRect;

                int iConnectionSize = GetRoomConectionsSize(pGenerateLevel, i);

                for (int j = 0; j < iConnectionSize; j++)
                {
                    newRoom.m_pArrayConectionsID.Add(GetOneRoomConectionID(pGenerateLevel, i, j));
                }

                m_Rooms.Add(newRoom);

                /// Stores the room's Width.
                //newRoom.m_fWidth = GetRoomWidth(pGenerateLevel, i);
                /// Stores the room's height.
                //newRoom.m_fHeight = GetRoomHeight(pGenerateLevel, i);
                //
                /// Coordinates change to work under unity's coordinates system.
                //newRoom.m_Position.X = GetRoomPosition_X(pGenerateLevel, i);
                //newRoom.m_Position.Y = GetRoomPosition_Z(pGenerateLevel, i);
                //newRoom.m_Position.Z = GetRoomPosition_Y(pGenerateLevel, i);
                //
                //newRoom.m_TopLeftPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 0);
                //newRoom.m_TopLeftPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 0);
                //newRoom.m_TopLeftPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 0);
                //
                //newRoom.m_TopRightPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 1);
                //newRoom.m_TopRightPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 1);
                //newRoom.m_TopRightPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 1);
                //
                //newRoom.m_BottomLeftPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 2);
                //newRoom.m_BottomLeftPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 2);
                //newRoom.m_BottomLeftPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 2);
                //
                //newRoom.m_BottomRightPosition.X = GetRoomNodePosition_X(pGenerateLevel, i, 3);
                //newRoom.m_BottomRightPosition.Y = GetRoomNodePosition_Z(pGenerateLevel, i, 3);
                //newRoom.m_BottomRightPosition.Z = GetRoomNodePosition_Y(pGenerateLevel, i, 3);
            }

            return pGenerateLevel;
        }
    }
}
