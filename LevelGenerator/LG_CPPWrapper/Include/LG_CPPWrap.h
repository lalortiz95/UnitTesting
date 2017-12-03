#pragma once
#include "LG_CPPWrapperPrerequisites.h"
#include <LG_Generate.h>


#define LG_WRAPPER_EXPORT __declspec(dllexport)

extern "C"
{
	/**
	 *	@brief This functions create a generate level object and return it.
	 *	@param int iRoomAmount: The number of rooms that we want to create.
	 *	@param int iMinSizeRoom_X:
	 *	@param int iMinSizeRoom_Y:
	 *	@param int iMinSizeRoom_Z:
	 *	@param int iMaxSizeRoom_X:
	 *	@param int iMaxSizeRoom_Y:
	 *	@param int iMaxSizeRoom_Z:
	 *	@return The generate level object as void*.
	 */
	LG_WRAPPER_EXPORT void* GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y, int iMinSizeRoom_Z,
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iMaxSizeRoom_Z);


	///************************************************************************/
	///*                           Rooms Functions.			                  */
	///************************************************************************/ 


	/**
	 *	@brief This functions get the size of the vector rooms in the generate level object.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@return size of vector rooms.
	 */
	LG_WRAPPER_EXPORT int GetRoomAmount(void* pGenerate);

	/**
	 *	@brief Returns the ID of an asked room.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that containts the one we want to get the information from. 
	 *	@return The room's ID.
	 */
	LG_WRAPPER_EXPORT int GetRoomID(void* pGenerate, int iRoomArrayPosition);

	/**
	 *	@brief Returns the asked room's ID.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that containts the one we want to get the information from. 
	 *	@return The room's parent ID.
	 */
	LG_WRAPPER_EXPORT int GetRoomsParentID(void* pGenerate, int iRoomArrayPosition);

	LG_WRAPPER_EXPORT float GetRoomWidth(void* pGenerate, int iRoomArrayPosition);
	LG_WRAPPER_EXPORT float GetRoomHeight(void*pGenerate, int iRoomArrayPosition);

	LG_WRAPPER_EXPORT int GetRoomConectionsSize(void* pGenerate, int iRoomArrayPosition);
	LG_WRAPPER_EXPORT int GetOneRoomConectionID(void* pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);

	LG_WRAPPER_EXPORT float GetRoomPosition_X(void* pGenerate, int iRoomArrayPosition);
	LG_WRAPPER_EXPORT float GetRoomPosition_Y(void* pGenerate, int iRoomArrayPosition);
	LG_WRAPPER_EXPORT float GetRoomPosition_Z(void* pGenerate, int iRoomArrayPosition);

	LG_WRAPPER_EXPORT float GetRoomNodePosition_X(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);
	LG_WRAPPER_EXPORT float GetRoomNodePosition_Y(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);
	LG_WRAPPER_EXPORT float GetRoomNodePosition_Z(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);

	///************************************************************************/
	///*                            Hallway Functions.		                  */
	///************************************************************************/

	LG_WRAPPER_EXPORT int GetHallwayAmount(void* pGenerate);

	LG_WRAPPER_EXPORT float GetHallwayWidth(void* pGenerate, int iHallwayArrayPosition);
	LG_WRAPPER_EXPORT float GetHallwayHeight(void*pGenerate, int iHallwayArrayPosition);

	LG_WRAPPER_EXPORT float GetHallwayPosition_X(void* pGenerate, int iHallwayArrayPosition);
	LG_WRAPPER_EXPORT float GetHallwayPosition_Y(void* pGenerate, int iHallwayArrayPosition);
	LG_WRAPPER_EXPORT float GetHallwayPosition_Z(void* pGenerate, int iHallwayArrayPosition);

	LG_WRAPPER_EXPORT float GetHallwayNodePosition_X(void* pGenerate, int iHallwayArrayPosition, int iNumOfNode);
	LG_WRAPPER_EXPORT float GetHallwayNodePosition_Y(void* pGenerate, int iHallwayArrayPosition, int iNumOfNode);
	LG_WRAPPER_EXPORT float GetHallwayNodePosition_Z(void* pGenerate, int iHallwayArrayPosition, int iNumOfNode);

	///************************************************************************/
	///*                           Pathfinding Functions.                 */
	///************************************************************************/

	LG_WRAPPER_EXPORT void Pathfinding_DIJKSTRA(void* pGenerate, int iStartNode, int iEndNode);
	LG_WRAPPER_EXPORT int GetPathSize_DIJKSTRA(void* pGenerate);
	LG_WRAPPER_EXPORT int GetPath_DIJKSTRA_OneByOne(void* pGenerate, int iPathArrayPosition);
}