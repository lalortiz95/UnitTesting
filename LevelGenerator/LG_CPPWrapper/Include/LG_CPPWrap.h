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
	 *	@param int iMaxSizeRoom_X:
	 *	@param int iMaxSizeRoom_Y:
	 *	@param int iHeight:
	 *	@param int iSeed: 
	 *  @param int iSeparateRange:
	 *	@return The generate level object as void*.
	 */
	LG_WRAPPER_EXPORT void* GenerateLevel(int iRoomAmount, int iMinSizeRoom_X, int iMinSizeRoom_Y,
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, int iSeed, int iSeparateRange);


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
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from. 
	 *	@return The room's ID.
	 */
	LG_WRAPPER_EXPORT int GetRoomID(void* pGenerate, int iRoomArrayPosition);

	/**
	 *	@brief Returns the asked room's ID.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from. 
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

	/**
	 *	@brief Returns the total amount of hallways in the dungeon.
	 *	@param void* pGenerate: A pointer of a generate level object.
	 *	@return The amount of hallways.
	 */
	LG_WRAPPER_EXPORT int GetHallwayAmount(void* pGenerate);

	/**
	 *	@brief A hall could have 4 or 6 nodes, depending on whether it's a corner or a straight hall. So this function tells you how many nodes does a hallway haves.
	 *	@param void* pGenerate: A pointer of a generate level object.
	 *	@param int iHallway: The position in the array of hallways that contains the one we want to get the information from.
	 *	@return The amount of nodes from the hall.
	 */
	LG_WRAPPER_EXPORT int GetNodeAmountFromHallway(void* pGenerate, int iHallway);

	/**
	 *	@brief Tells if a hallway is a corner or a straight hall.
	 *	@param void* pGenerate: A pointer of a generate level object.
	 *	@param int iHallway: The position in the array of hallways that contains the one we want to get the information from.
	 *	@return True if the corridor is a corner.
	 */
	LG_WRAPPER_EXPORT bool IsCorner(void * pGenerate, int iHallway);

	//TODO: comentiza perrona.

	LG_WRAPPER_EXPORT float GetHallwayNodePosition_X(void* pGenerate, int iHallway, int iNode);
	LG_WRAPPER_EXPORT float GetHallwayNodePosition_Y(void* pGenerate, int iHallway, int iNode);
	LG_WRAPPER_EXPORT float GetHallwayNodePosition_Z(void* pGenerate, int iHallway, int iNode);

	///************************************************************************/
	///*                           Pathfinding Functions.                 */
	///************************************************************************/

	LG_WRAPPER_EXPORT void Pathfinding_DIJKSTRA(void* pGenerate, int iStartNode, int iEndNode);
	LG_WRAPPER_EXPORT int GetPathSize_DIJKSTRA(void* pGenerate);
	LG_WRAPPER_EXPORT int GetPath_DIJKSTRA_OneByOne(void* pGenerate, int iPathArrayPosition);
}