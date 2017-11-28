#include "LG_CPPWrap.h"

extern "C"
{

	LG_CPPWrap::LG_CPPWrap()
	{
	}


	LG_CPPWrap::~LG_CPPWrap()
	{
	}

	void LG_CPPWrap::Run(int iRoomAmount)
	{
		//TODO: llamar al run de generate y guardar en la global todo lo generado
		//g_generate.Run(iRoomAmount,,);
	}

	int LG_CPPWrap::GetRoomID(int iPlaceInArray)
	{
		return g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_iID;
	}

	void LG_CPPWrap::GetRoomPosition(int iPlaceInArray, float & fx, float & fy, float & fz)
	{
		fx = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.X;
		fy = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.Y;
		fz = g_generate.m_RoomsNodesCloud[iPlaceInArray]->m_Position.Z;
	}
}