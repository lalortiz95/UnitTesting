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
            m_CenterPosition = new LG_Vector3();
            m_fHeight = 0.0f;
            m_fWidth = 0.0f;
        }

        public LG_CSRect(LG_Vector3 CenterPos, float fHeight, float fWidth)
        {
            m_CenterPosition = CenterPos;
            m_fHeight = fHeight;
            m_fWidth = fWidth;
        }

        ~LG_CSRect()
        {
            m_CenterPosition = null;
            m_fHeight = 0.0f;
            m_fWidth = 0.0f;
        }

        public LG_Vector3 m_CenterPosition = null;

        public float m_fHeight = 0.0f;
        public float m_fWidth = 0.0f;
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
            m_pNodesPosition = null;
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
            HallwayShape = null;
            m_Walls = null;
            m_Floors = null;
            m_Ceilings = null;
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
            m_Door = null;
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
            m_bIsStart = false;
            m_bIsEnd = false;
        }

        ~LG_CSRoom()
        {
            m_fHeight = 0.0f;
            m_fWidth = 0.0f;
            m_pArrayConectionsID = null;
            m_Position = null;
            m_TopLeftPosition = null;
            m_TopRightPosition = null;
            m_BottomLeftPosition = null;
            m_BottomRightPosition = null;
            m_iParentID = 0;
            m_iID = 0;
            m_Walls = null;
            m_Floor = null;
            m_Ceiling = null;
            m_bIsStart = false;
            m_bIsEnd = false;
        }

        /**
         *  @var
         */
        public bool m_bIsEnd;

        /**
         *  @var  
         */
        public bool m_bIsStart;

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


        [DllImport("LG_CPPWrapper", EntryPoint = "DestroyLevel", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr DestroyLevel(IntPtr pGenate);


        ///************************************************************************/
        ///*                           Rooms Functions.			                  */
        ///************************************************************************/ 
        ///
        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomID(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomsParentID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomsParentID(IntPtr pGenerate, int iRoomArrayPosition);


        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomConectionsSize", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetRoomConectionsSize(IntPtr pGenerate, int iRoomArrayPosition);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetOneRoomConectionID", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetOneRoomConectionID(IntPtr pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);


        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int CS_GetRoomAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetStartRoom", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool CS_GetStartRoom(IntPtr pGenerate, int iRoom);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetEndRoom", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool CS_GetEndRoom(IntPtr pGenerate, int iRoom);

        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the wall for every room.
        ////////////////////////////////////////////////////////////

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int CS_GetRoomWallsAmount(IntPtr pGenerate, int iRoom);

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
        private static extern float CS_GetRoomWallHeight(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetRoomWallWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float CS_GetRoomWallWidth(IntPtr pGenerate, int iRoomArrPos, int iWallArrPos);


        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the floor for every room.
        ////////////////////////////////////////////////////////////

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

        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the ceiling for every room.
        ////////////////////////////////////////////////////////////

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



        ///************************************************************************/
        ///*                            Hallway Functions.		                  */
        ///************************************************************************/

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayAmount(IntPtr pGenerate);

        [DllImport("LG_CPPWrapper", EntryPoint = "IsCorner", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsCorner(IntPtr pGenerate, int iHallway);

        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the wall for every hallway.
        ////////////////////////////////////////////////////////////

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayWallsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayWallsAmount(IntPtr pGenerate, int iHallway);

        [DllImport("LG_CPPWrapper", EntryPoint = "IsHallwayWallHorizontal", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool IsHallwayWallHorizontal(IntPtr pGenerate, int iHallArrPos, int iWallArrPos);

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

        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the floor for every hallway.
        ////////////////////////////////////////////////////////////

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayFloorsAmount(IntPtr pGenerate, int iHallway);

        /// The center positions of a hallway's Floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_X(IntPtr pGenerate, int iHallArrPos, int iFloorArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_Y(IntPtr pGenerate, int iHallArrPos, int iFloorArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorCenterPosition_Z(IntPtr pGenerate, int iHallArrPos, int iFloorArrPos);

        /// The width and height of a hallway's floor.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorHeight(IntPtr pGenerate, int iRoomArrPos, int iFloorArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayFloorWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayFloorWidth(IntPtr pGenerate, int iRoomArrPos, int iFloorArrPos);

        /////////////////////////////////////////////////////////////
        /// @brief Functions to export the dates of the ceiling for every hallway.
        ////////////////////////////////////////////////////////////

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingsAmount", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetHallwayCeilingsAmount(IntPtr pGenerate, int iHallway);


        /// The center positions of a hallway's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_X", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_X(IntPtr pGenerate, int iHallArrPos, int iCeilingArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_Y", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_Y(IntPtr pGenerate, int iHallArrPos, int iCeilingArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingCenterPos_Z", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingCenterPosition_Z(IntPtr pGenerate, int iHallArrPos, int iCeilingArrPos);

        /// The width and height of a hallway's ceiling.
        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingHeight", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingHeight(IntPtr pGenerate, int iRoomArrPos, int iCeilingArrPos);

        [DllImport("LG_CPPWrapper", EntryPoint = "GetHallwayCeilingWidth", CallingConvention = CallingConvention.Cdecl)]
        private static extern float GetHallwayCeilingWidth(IntPtr pGenerate, int iRoomArrPos, int iCeilingArrPos);


        ///************************************************************************/
        ///*                            DIJKSTRA Functions.		                  */
        ///************************************************************************/
        ///
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


        public IntPtr CS_GenerateLevel(int iRoom, int iMinSizeRoom_X, int iMinSizeRoom_Y,
        int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, int iSeed, int iSeparationRange, int iHallwayWidth)
        {
            IntPtr pGenerateLevel = GenerateLevel(iRoom, iMinSizeRoom_X, iMinSizeRoom_Y, iMaxSizeRoom_X, iMaxSizeRoom_Y, iHeight, iSeed, iSeparationRange, iHallwayWidth);

            int iRoomAmount = CS_GetRoomAmount(pGenerateLevel);
            int iHallwayAmount = GetHallwayAmount(pGenerateLevel);

            int iHallwayWallsAmount = 0;
            int iHallwayFloorsAmount = 0;
            int iHallwayCeilingAmount = 0;

            int iRoomWallsAmount = 0;

            LG_CSHallway newHallway = null;
            LG_Vector3 CenterPosition = null;
            // Used to initialize walls, floors, and ceilings.
            LG_CSRect Hallway_WallTemp = null;
            LG_CSRect Hallway_FloorTemp = null;
            LG_CSRect Hallway_CeilingTemp = null;
            /// 
            LG_CSRect Room_WallTemp = null;
            
            LG_CSRoom newRoom = null;

            for (int iCountHallway = 0; iCountHallway < iHallwayAmount; ++iCountHallway)
            {
                /// We allocate memory for a new hallway that is going to be generated.
                newHallway = new LG_CSHallway();

                /// A flag that stores if the hallway is a corner.
                newHallway.bIsCorner = IsCorner(pGenerateLevel, iCountHallway);
                iHallwayWallsAmount = GetHallwayWallsAmount(pGenerateLevel, iCountHallway);
                iHallwayFloorsAmount = GetHallwayFloorsAmount(pGenerateLevel, iCountHallway);
                iHallwayCeilingAmount = GetHallwayCeilingsAmount(pGenerateLevel, iCountHallway);

                for (int iCountWalls = 0; iCountWalls < iHallwayWallsAmount; ++iCountWalls)
                {
                    CenterPosition = new LG_Vector3();

                    /// Here we store the position of every node, from every hallway
                    CenterPosition.X = GetHallwayWallCenterPosition_X(pGenerateLevel, iCountHallway, iCountWalls);
                    CenterPosition.Y = GetHallwayWallCenterPosition_Z(pGenerateLevel, iCountHallway, iCountWalls);
                    CenterPosition.Z = GetHallwayWallCenterPosition_Y(pGenerateLevel, iCountHallway, iCountWalls);

                    /// A new rect representing the tridimensional wall is now generated.
                    Hallway_WallTemp = new LG_CSRect(CenterPosition, GetHallwayWallHeight(pGenerateLevel, iCountHallway, iCountWalls),
                        GetHallwayWallWidth(pGenerateLevel, iCountHallway, iCountWalls));

                    ///
                    Hallway_WallTemp.m_bIsHorizontal = IsHallwayWallHorizontal(pGenerateLevel, iCountHallway, iCountWalls);

                    /// Now the wall is added to the list.
                    newHallway.m_Walls.Add(Hallway_WallTemp);
                }

                for (int iCountFloors = 0; iCountFloors < iHallwayFloorsAmount; iCountFloors++)
                {
                    /// We allocate memory for a new hallway that is going to be generated.
                    //newHallway = new LG_CSHallway();
                    /// At this point we allocate new memory to the vector and the rectangle to re use the variables, and fill with that information the floor. Eventually the ceiling.
                    CenterPosition = new LG_Vector3();
                    CenterPosition.X = GetHallwayFloorCenterPosition_X(pGenerateLevel, iCountHallway, iCountFloors);
                    CenterPosition.Y = GetHallwayFloorCenterPosition_Z(pGenerateLevel, iCountHallway, iCountFloors);
                    CenterPosition.Z = GetHallwayFloorCenterPosition_Y(pGenerateLevel, iCountHallway, iCountFloors);

                    Hallway_FloorTemp = new LG_CSRect(CenterPosition, GetHallwayFloorHeight(pGenerateLevel, iCountHallway, iCountFloors),
                        GetHallwayFloorWidth(pGenerateLevel, iCountHallway, iCountFloors));

                    newHallway.m_Floors.Add(Hallway_FloorTemp);
                }

                for (int iCountCeiling = 0; iCountCeiling < iHallwayCeilingAmount; iCountCeiling++)
                {
                    /// We once again recycle our variables to complete the loop by storing the ceilings.
                    CenterPosition = new LG_Vector3();
                    CenterPosition.X = GetHallwayCeilingCenterPosition_X(pGenerateLevel, iCountHallway, iCountCeiling);
                    CenterPosition.Y = GetHallwayCeilingCenterPosition_Z(pGenerateLevel, iCountHallway, iCountCeiling);
                    CenterPosition.Z = GetHallwayCeilingCenterPosition_Y(pGenerateLevel, iCountHallway, iCountCeiling);

                    Hallway_CeilingTemp = new LG_CSRect(CenterPosition, GetHallwayCeilingHeight(pGenerateLevel, iCountHallway, iCountCeiling),
                        GetHallwayCeilingWidth(pGenerateLevel, iCountHallway, iCountCeiling));

                    newHallway.m_Ceilings.Add(Hallway_CeilingTemp);
                }

                /// The hallway is inserted to the list of hallways.
                m_Hallway.Add(newHallway);
            }


            //TODO: moficiar esto para que tenga la nueva estructura de los cuartos.
            for (int iCountRoom = 0; iCountRoom < iRoomAmount; iCountRoom++)
            {
                iRoomWallsAmount = 0;
                /// 
                newRoom = new LG_CSRoom();
                /// We assign the room's ID.
                newRoom.m_iID = GetRoomID(pGenerateLevel, iCountRoom);
                ///
                iRoomWallsAmount = CS_GetRoomWallsAmount(pGenerateLevel, iCountRoom);
                newRoom.m_bIsEnd = CS_GetEndRoom(pGenerateLevel, iCountRoom);
                newRoom.m_bIsStart = CS_GetStartRoom(pGenerateLevel, iCountRoom);

                /// 
                for (int iCountWalls = 0; iCountWalls < iRoomWallsAmount; iCountWalls++)
                {
                    CenterPosition = new LG_Vector3();
                    /// the center node position is now stored.
                    CenterPosition.X = GetRoomWallCenterPosition_X(pGenerateLevel, iCountRoom, iCountWalls);
                    CenterPosition.Y = GetRoomWallCenterPosition_Z(pGenerateLevel, iCountRoom, iCountWalls);
                    CenterPosition.Z = GetRoomWallCenterPosition_Y(pGenerateLevel, iCountRoom, iCountWalls);

                    Room_WallTemp = new LG_CSRect(CenterPosition, CS_GetRoomWallHeight(pGenerateLevel, iCountRoom, iCountWalls),
                        CS_GetRoomWallWidth(pGenerateLevel, iCountRoom, iCountWalls));

                    /// We store if the rect is supposed to be stretched in the X, or Z axis.
                    Room_WallTemp.m_bIsHorizontal = IsRoomWallHorizontal(pGenerateLevel, iCountRoom, iCountWalls);

                    newRoom.m_Walls.Add(Room_WallTemp);
                }

                //TODO: llenar la infomación en temporales y después agregarlas al floor?
                CenterPosition = new LG_Vector3();
                /// Here the floor is stored in the iterating new room.
                CenterPosition.X = GetRoomFloorCenterPosition_X(pGenerateLevel, iCountRoom);
                CenterPosition.Y = GetRoomFloorCenterPosition_Z(pGenerateLevel, iCountRoom);
                CenterPosition.Z = GetRoomFloorCenterPosition_Y(pGenerateLevel, iCountRoom);

                /// 
                newRoom.m_Floor = new LG_CSRect(CenterPosition, GetRoomFloorHeight(pGenerateLevel, iCountRoom),
                                GetRoomFloorWidth(pGenerateLevel, iCountRoom));

                /// Here the floor is stored in the iterating new room.
                CenterPosition = new LG_Vector3();
                CenterPosition.X = GetRoomCeilingCenterPosition_X(pGenerateLevel, iCountRoom);
                CenterPosition.Y = GetRoomCeilingCenterPosition_Z(pGenerateLevel, iCountRoom);
                CenterPosition.Z = GetRoomCeilingCenterPosition_Y(pGenerateLevel, iCountRoom);

                /// 
                newRoom.m_Ceiling = new LG_CSRect(CenterPosition, GetRoomCeilingHeight(pGenerateLevel, iCountRoom),
                    GetRoomCeilingWidth(pGenerateLevel, iCountRoom));

                int iConnectionSize = GetRoomConectionsSize(pGenerateLevel, iCountRoom);

                for (int j = 0; j < iConnectionSize; j++)
                {
                    newRoom.m_pArrayConectionsID.Add(GetOneRoomConectionID(pGenerateLevel, iCountRoom, j));
                }

                m_Rooms.Add(newRoom);
            }

            return pGenerateLevel;
        }

        public void CS_DestroyLevel(IntPtr pGenerate)
        {
            DestroyLevel(pGenerate);
        }
    }
}
