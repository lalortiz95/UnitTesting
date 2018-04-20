#include "LG_CPPWrap.h"


extern "C"
{


	//! This functions create a generate level object and return it.
	void * GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y,
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, int iSeed, int iSeparationRange, int iHallwayWidth)
	{
		LevelGenerator::LG_Vector3D vMin((float)iMinSizeRoom_X, (float)iMinSizeRoom_Y, 0);
		LevelGenerator::LG_Vector3D vMax((float)iMaxSizeRoom_X, (float)iMaxSizeRoom_Y, (float)iHeight);
		LevelGenerator::LG_Generate* newGenerate = new LevelGenerator::LG_Generate();
		newGenerate->Run(iRoomAmount, vMin, vMax, iSeed, (float)iSeparationRange, (float)iHallwayWidth);
		return (void*)newGenerate;
	}

	LG_WRAPPER_EXPORT void DestroyLevel(void* pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		pTempGenerate->Destroy();
	}

	//! This functions get the size of the vector rooms in the generate level object.
	LG_WRAPPER_EXPORT int GetRoomAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_RoomsVector.size();
	}

	LG_WRAPPER_EXPORT int GetRoomWallsAmount(void * pGenerate, int iRoom)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_RoomsVector[iRoom]->m_Walls.size();
	}

	LG_WRAPPER_EXPORT int GetHallwayAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways.size();
	}

	LG_WRAPPER_EXPORT int GetHallwayWallsAmount(void * pGenerate, int iHall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways[iHall]->m_Walls.size();
	}

	LG_WRAPPER_EXPORT int GetHallwayFloorsAmount(void * pGenerate, int iHall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways[iHall]->m_Floors.size();
	}

	LG_WRAPPER_EXPORT int GetHallwayCeilingsAmount(void * pGenerate, int iHall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways[iHall]->m_Ceilings.size();
	}

	int GetNodeAmountFromHallway(void * pGenerate, int iHallway)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_pPolygon->m_pNodeVector.size();
	}

	//!
	int GetRoomID(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pFloor->m_CenterNode.m_iID;
	}

	//!
	int GetRoomsParentID(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pFloor->m_CenterNode.m_pParentNode->m_iID;
	}

	//!
	int GetRoomConectionsSize(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_RoomsConnections.size();
	}

	//!
	int GetOneRoomConectionID(void * pGenerate, int iRoomArrayPosition, int iRoomConectionPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_RoomsConnections[iRoomConectionPosition]->m_pFloor->m_CenterNode.m_iID;
	}

	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_X(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pFloor->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_Y(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pFloor->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_Z(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pFloor->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetRoomFloorWidth(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pFloor->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetRoomFloorHeight(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pFloor->m_fHeight;
	}

	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_X(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pCeiling->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_Y(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pCeiling->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_Z(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pCeiling->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetRoomCeilingWidth(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pCeiling->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetRoomCeilingHeight(void * pGenerate, int iRoomArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_pCeiling->m_fHeight;
	}

	LG_WRAPPER_EXPORT bool IsRoomWallHorizontal(void * pGenerate, int iRoom, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoom]->m_Walls[iWall]->m_bIsHorizontal;
	}

	LG_WRAPPER_EXPORT bool GetStartRoom(void * pGenerate, int iRoom)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoom]->m_bIsStart;
	}
	LG_WRAPPER_EXPORT bool GetEndRoom(void * pGenerate, int iRoom)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoom]->m_bIsEnd;
	}

	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_X(void * pGenerate, int iRoomArrayPos, int iWallArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Walls[iWallArrayPos]->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_Y(void * pGenerate, int iRoomArrayPos, int iWallArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Walls[iWallArrayPos]->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_Z(void * pGenerate, int iRoomArrayPos, int iWallArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Walls[iWallArrayPos]->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetRoomWallWidth(void * pGenerate, int iRoomArrayPos, int iWallArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Walls[iWallArrayPos]->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetRoomWallHeight(void * pGenerate, int iRoomArrayPos, int iWallArrayPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Walls[iWallArrayPos]->m_fHeight;
	}

	LG_WRAPPER_EXPORT float GetDoorCenterPos_X(void * pGenerate, int iRoomArrayPos, int iDoorArrPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Doors[iDoorArrPos]->m_pRectDimension->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetDoorCenterPos_Y(void * pGenerate, int iRoomArrayPos, int iDoorArrPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Doors[iDoorArrPos]->m_pRectDimension->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetDoorCenterPos_Z(void * pGenerate, int iRoomArrayPos, int iDoorArrPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Doors[iDoorArrPos]->m_pRectDimension->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetDoorWidth(void * pGenerate, int iRoomArrayPos, int iDoorArrPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Doors[iDoorArrPos]->m_pRectDimension->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetDoorHeight(void * pGenerate, int iRoomArrayPos, int iDoorArrPos)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPos]->m_Doors[iDoorArrPos]->m_pRectDimension->m_fHeight;
	}

	//! If a hallway is a corner or a straight hall.
	bool IsCorner(void * pGenerate, int iHallway)
	{
		// 
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_eHallwayType == LevelGenerator::CORNER);
	}

	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_X(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_Y(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_Z(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetHallwayWallWidth(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetHallwayWallHeight(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_fHeight;
	}

	LG_WRAPPER_EXPORT bool IsHallwayWallHorizontal(void * pGenerate, int iHallway, int iWall)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Walls[iWall]->m_bIsHorizontal;
	}

	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_X(void * pGenerate, int iHallway, int iFloor)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Floors[iFloor]->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_Y(void * pGenerate, int iHallway, int iFloor)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Floors[iFloor]->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_Z(void * pGenerate, int iHallway, int iFloor)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Floors[iFloor]->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetHallwayFloorWidth(void * pGenerate, int iHallway, int iFloor)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Floors[iFloor]->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetHallwayFloorHeight(void * pGenerate, int iHallway, int iFloor)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Floors[iFloor]->m_fHeight;
	}

	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_X(void * pGenerate, int iHallway, int iCeiling)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Ceilings[iCeiling]->m_CenterNode.m_Position.X;
	}

	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_Y(void * pGenerate, int iHallway, int iCeiling)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Ceilings[iCeiling]->m_CenterNode.m_Position.Y;
	}

	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_Z(void * pGenerate, int iHallway, int iCeiling)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Ceilings[iCeiling]->m_CenterNode.m_Position.Z;
	}

	LG_WRAPPER_EXPORT float GetHallwayCeilingWidth(void * pGenerate, int iHallway, int iCeiling)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Ceilings[iCeiling]->m_fWidth;
	}

	LG_WRAPPER_EXPORT float GetHallwayCeilingHeight(void * pGenerate, int iHallway, int iCeiling)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_Ceilings[iCeiling]->m_fHeight;
	}



	//!
	void Pathfinding_DIJKSTRA(void * pGenerate, int iStartNode, int iEndNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		LevelGenerator::LG_Node* pStartNode = nullptr;
		LevelGenerator::LG_Node* pEndNode = nullptr;
	
		for (int i = 0; i < pTempGenerate->m_DT.m_pNodesCloud->size(); ++i)
		{
			if ((*pTempGenerate->m_DT.m_pNodesCloud)[i]->m_iID == iStartNode)
			{
				pStartNode = (*pTempGenerate->m_DT.m_pNodesCloud)[i];
			}
			if ((*pTempGenerate->m_DT.m_pNodesCloud)[i]->m_iID == iEndNode)
			{
				pEndNode = (*pTempGenerate->m_DT.m_pNodesCloud)[i];
			}
		}

		pTempGenerate->m_Dijkstra.Init(pTempGenerate->m_DT.m_pNodesCloud, pStartNode, pEndNode);
		pTempGenerate->m_Dijkstra.Run();
	}

	int GetPathSize_DIJKSTRA(void* pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_Dijkstra.m_BesthPath.size();
	}

	 int GetPath_DIJKSTRA_OneByOne(void * pGenerate, int iPathArrayPosition)
	{
		 LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		 return pTempGenerate->m_Dijkstra.m_BesthPath[iPathArrayPosition]->m_iID;
	}
}