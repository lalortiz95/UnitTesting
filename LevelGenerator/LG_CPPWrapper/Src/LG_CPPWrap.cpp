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
		newGenerate->Run(iRoomAmount, vMin,vMax);
		return (void*)newGenerate;
	}

	//! This functions get the size of the vector rooms in the generate level object.
	int GetRoomAmount(void * pGenerate)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return  pTempGenerate->m_RoomsVector.size();
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
	float GetRoomPosition_X(void * pGenerate, int RoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[RoomArrayPosition]->m_CenterNode.m_Position.X;
	}

	//!
	float GetRoomPosition_Y(void * pGenerate, int RoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[RoomArrayPosition]->m_CenterNode.m_Position.Y;
	}

	//!
	float GetRoomPosition_Z(void * pGenerate, int RoomArrayPosition)
	{
		LevelGenerator::LG_Generate* pTempGenerate = reinterpret_cast<LevelGenerator::LG_Generate*>(pGenerate);
		return pTempGenerate->m_RoomsVector[RoomArrayPosition]->m_CenterNode.m_Position.Z;
	}
}