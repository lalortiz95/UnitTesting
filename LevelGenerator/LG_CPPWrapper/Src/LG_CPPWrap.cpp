#include "LG_CPPWrap.h"


extern "C"
{


	//! This functions create a generate level object and return it.
	void * GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z, int iSeed, int iSeparationRange)
	{
		LevelGenerator::LG_Vector3D vMin((float)iMinSizeRoom_X, (float)iMinSizeRoom_Y, (float)iMinSizeRoom_Z);
		LevelGenerator::LG_Vector3D vMax((float)iMaxSizeRoom_X, (float)iMaxSizeRoom_Y, (float)iMaxSizeRoom_Z);
		LevelGenerator::LG_Generate* newGenerate = new LevelGenerator::LG_Generate();
		newGenerate->Run(iRoomAmount, vMin, vMax, iSeed, (float)iSeparationRange);
		return (void*)newGenerate;
	}

	//! This functions get the size of the vector rooms in the generate level object.
	int GetRoomAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return  (int)pTempGenerate->m_RoomsVector.size();
	}

	int GetHallwayAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return (int)pTempGenerate->m_HG.m_FinalHallways.size();
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
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_CenterNode.m_iID;
	}

	//!
	int GetRoomsParentID(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_CenterNode.m_pParentNode->m_iID;
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
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_RoomsConnections[iRoomConectionPosition]->m_pRect->m_CenterNode.m_iID;
	}

	//!
	float GetRoomWidth(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_fWidth;
	}

	//!
	float GetRoomHeight(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_fHeight;
	}

	//!
	float GetRoomPosition_X(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_CenterNode.m_Position.X;
	}

	//!
	float GetRoomPosition_Y(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_CenterNode.m_Position.Y;
	}

	//!
	float GetRoomPosition_Z(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_CenterNode.m_Position.Z;
	}

	//!
	float GetRoomNodePosition_X(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopLeft.m_Position.X;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopRight.m_Position.X;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomRight.m_Position.X;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomLeft.m_Position.X;
		}
		else return 0;
	}

	//!
	float GetRoomNodePosition_Y(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopLeft.m_Position.Y;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopRight.m_Position.Y;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomRight.m_Position.Y;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomLeft.m_Position.Y;
		}
		else return 0;
	}

	//!
	float GetRoomNodePosition_Z(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopLeft.m_Position.Z;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_TopRight.m_Position.Z;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomRight.m_Position.Z;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_pRect->m_BottomLeft.m_Position.Z;
		}
		else return 0;
	}


	//////////////////////////////////////////////////////////////////////////
	//PASILLOS

	float GetHallwayNodePosition_X(void* pGenerate, int iHallway, int iNode)
	{
		// 
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_pPolygon->m_pNodeVector[iNode]->m_Position.X;
	}

	float GetHallwayNodePosition_Y(void * pGenerate, int iHallway, int iNode)
	{
		// 
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_pPolygon->m_pNodeVector[iNode]->m_Position.Y;
	}

	float GetHallwayNodePosition_Z(void * pGenerate, int iHallway, int iNode)
	{
		// 
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_pPolygon->m_pNodeVector[iNode]->m_Position.Z;
	}

	//! If a hallway is a corner or a straight hall.
	bool IsCorner(void * pGenerate, int iHallway)
	{
		// 
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallway]->m_bIsCorner;
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