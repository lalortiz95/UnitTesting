#include "LG_CPPWrap.h"


extern "C"
{


	//! This functions create a generate level object and return it.
	void * GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z)
	{
		LevelGenerator::LG_Vector3D vMin(iMinSizeRoom_X, iMinSizeRoom_Y, iMinSizeRoom_Z);
		LevelGenerator::LG_Vector3D vMax(iMaxSizeRoom_X, iMaxSizeRoom_Y, iMaxSizeRoom_Z);
		LevelGenerator::LG_Generate* newGenerate = new LevelGenerator::LG_Generate();
		newGenerate->Run(iRoomAmount, vMin, vMax);
		return (void*)newGenerate;
	}

	//! This functions get the size of the vector rooms in the generate level object.
	int GetRoomAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return  pTempGenerate->m_RoomsVector.size();
	}

	int GetHallwayAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways.size();
	}

	//!
	int GetRoomID(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_CenterNode.m_iID;
	}

	//!
	int GetRoomsParentID(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_CenterNode.m_pParentNode->m_iID;
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
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_RoomsConnections[iRoomConectionPosition]->m_CenterNode.m_iID;
	}

	//!
	float GetRoomWidth(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_fWidth;
	}

	//!
	float GetRoomHeight(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_fHeight;
	}

	//!
	float GetRoomPosition_X(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_CenterNode.m_Position.X;
	}

	//!
	float GetRoomPosition_Y(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_CenterNode.m_Position.Y;
	}

	//!
	float GetRoomPosition_Z(void * pGenerate, int iRoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_CenterNode.m_Position.Z;
	}

	//!
	float GetRoomNodePosition_X(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopLeft.m_Position.X;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopRight.m_Position.X;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomRight.m_Position.X;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomLeft.m_Position.X;
		}
		else return 0;
	}

	//!
	float GetRoomNodePosition_Y(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopLeft.m_Position.Y;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopRight.m_Position.Y;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomRight.m_Position.Y;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomLeft.m_Position.Y;
		}
		else return 0;
	}

	//!
	float GetRoomNodePosition_Z(void * pGenerate, int iRoomArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopLeft.m_Position.Z;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_TopRight.m_Position.Z;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomRight.m_Position.Z;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_RoomsVector[iRoomArrayPosition]->m_BottomLeft.m_Position.Z;
		}
		else return 0;
	}



	//!
	float GetHallwayWidth(void * pGenerate, int iHallwayArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_fWidth;
	}

	//!
	float GetHallwayHeight(void * pGenerate, int iHallwayArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_fHeight;
	}

	//!
	float GetHallwayPosition_X(void * pGenerate, int iHallwayArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_CenterNode.m_Position.X;
	}

	//!
	float GetHallwayPosition_Y(void * pGenerate, int iHallwayArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_CenterNode.m_Position.Y;
	}

	//!
	float GetHallwayPosition_Z(void * pGenerate, int iHallwayArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_CenterNode.m_Position.Z;
	}

	//!
	float GetHallwayNodePosition_X(void * pGenerate, int iHallwayArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopLeft.m_Position.X;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopRight.m_Position.X;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomRight.m_Position.X;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomLeft.m_Position.X;
		}
		else return 0;
	}

	//!
	float GetHallwayNodePosition_Y(void * pGenerate, int iHallwayArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopLeft.m_Position.Y;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopRight.m_Position.Y;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomRight.m_Position.Y;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomLeft.m_Position.Y;
		}
		else return 0;
	}

	//!
	float GetHallwayNodePosition_Z(void * pGenerate, int iHallwayArrayPosition, int iNumOfNode)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);


		if (0 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopLeft.m_Position.Z;
		}
		else if (1 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_TopRight.m_Position.Z;
		}
		else if (2 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomRight.m_Position.Z;
		}
		else if (3 == iNumOfNode)
		{
			return pTempGenerate->m_HG.m_FinalHallways[iHallwayArrayPosition]->m_BottomLeft.m_Position.Z;
		}
		else return 0;
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
		return pTempGenerate->m_Dijkstra.m_BesthPath.size();
	}

	 int GetPath_DIJKSTRA_OneByOne(void * pGenerate, int iPathArrayPosition)
	{
		 LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		 return pTempGenerate->m_Dijkstra.m_BesthPath[iPathArrayPosition]->m_iID;
	}
}