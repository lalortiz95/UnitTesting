#include "LG_CPPWrap.h"


LG_CPPWrap::LG_CPPWrap()
{
}


LG_CPPWrap::~LG_CPPWrap()
{
}

extern "C"
{

	

	void * MyClass()
	{
		LevelGenerator::LG_Generate* newGenerate = new LevelGenerator::LG_Generate();
		return (void*)newGenerate;
	}

	int multiplyvalue(int ivalue)
	{
		return ivalue * 5;
	}

	void /*LG_CPPWrap::*/Run(int iRoomAmount)
	{

		
		//TODO: llamar al run de generate y guardar en la global todo lo generado
		g_generate.Run(iRoomAmount, LevelGenerator::LG_Vector3D(20, 20, 0), LevelGenerator::LG_Vector3D(70, 70, 0));
	}

	int /*LG_CPPWrap::*/GetRoomID(int iPlaceInArray)
	{
		return g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_iID;
	}

	void /*LG_CPPWrap::*/GetRoomPosition(int iPlaceInArray, float & fx, float & fy, float & fz)
	{
		fx = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.X;
		fy = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.Y;
		fz = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.Z;
	}
}