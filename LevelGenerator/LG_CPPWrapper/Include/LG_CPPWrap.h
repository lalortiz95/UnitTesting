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
		int iMaxSizeRoom_X, int iMaxSizeRoom_Y, int iHeight, int iSeed, int iSeparateRange, int iHallwayWidth);


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
	 *	@brief This functions get the size of the vector rooms in the generate level object.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@param int iRoom: the place in the vector of rooms that we want to consult.
	 *	@return size of vector rooms.
	 */
	LG_WRAPPER_EXPORT int GetRoomWallsAmount(void* pGenerate, int iRoom);

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

	//LG_WRAPPER_EXPORT float GetRoomWidth(void* pGenerate, int iRoomArrayPosition);
	//LG_WRAPPER_EXPORT float GetRoomHeight(void*pGenerate, int iRoomArrayPosition);

	LG_WRAPPER_EXPORT int GetRoomConectionsSize(void* pGenerate, int iRoomArrayPosition);
	LG_WRAPPER_EXPORT int GetOneRoomConectionID(void* pGenerate, int iRoomArrayPosition, int iRoomConectionPosition);

	/**
	 *	@brief Returns room's floor center node position. This is used when exporting since most engines use that center position to spawn the object.
	 *	@param void* pGenerate: A pointer of generate level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@return the position in the X axis of the center node.
	 */
	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_X(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_Y(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomFloorCenterPos_Z(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomFloorWidth(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomFloorHeight(void* pGenerate, int iRoomArrayPos);

	/**
	 *	@brief Returns room's ceiling center node position. This is used when exporting since most engines use that center position to spawn the object.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@return the position in the X axis of the center node.
	 */
	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_X(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_Y(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomCeilingCenterPos_Z(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomCeilingWidth(void* pGenerate, int iRoomArrayPos);
	LG_WRAPPER_EXPORT float GetRoomCeilingHeight(void* pGenerate, int iRoomArrayPos);

	/**
	 *	@brief Returns the center node of an asked wall. This is used when exporting since most engines use that center position to spawn the object.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@param int iWallArrayPos: the position in the vector of walls that we want to get the information from.
	 *	@return the position in the X axis of the wall's center node.
	 */
	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_X(void* pGenerate, int iRoomArrayPos, int iWallArrayPos);

	/**
	 *	@brief Tells whether a wall is vertical or horizontal.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@return if a asked wall is horizontal or vertical.
	 */
	LG_WRAPPER_EXPORT bool IsRoomWallHorizontal(void* pGenerate, int iRoom, int iWall);
	
	/**
	 *	@brief Returns the center node of an asked wall. This is used when exporting since most engines use that center position to spawn the object.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@param int iWallArrayPos: the position in the vector of walls that we want to get the information from.
	 *	@return the position in the Y axis of the wall's center node.
	 */
	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_Y(void* pGenerate, int iRoomArrayPos, int iWallArrayPos);
	
	/**
	 *	@brief Returns the center node of an asked wall. This is used when exporting since most engines use that center position to spawn the object.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@param int iWallArrayPos: the position in the vector of walls that we want to get the information from.
	 *	@return the position in the Z axis of the wall's center node.
	 */
	LG_WRAPPER_EXPORT float GetRoomWallCenterPos_Z(void* pGenerate, int iRoomArrayPos, int iWallArrayPos);

	/**
	 *	@brief Returns the width of an asked wall. This is used when exporting to an extern engine.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@param int iWallArrayPos: the position in the vector of walls that we want to get the information from.
	 *	@return The width of a rectangle that represents the wall.
	 */
	LG_WRAPPER_EXPORT float GetRoomWallWidth(void* pGenerate, int iRoomArrayPos, int iWallArrayPos);

	/**
	 *	@brief Returns the height of an asked wall. This is used when exporting to an extern engine.
	 *	@param void* pGenerate: A pointer of the generated level.
	 *	@param int iRoomArrayPosition: The position in the array of rooms that contains the one we want to get the information from.
	 *	@param int iWallArrayPos: the position in the vector of walls that we want to get the information from.
	 *	@return The height of a rectangle that represents the wall.
	 */
	LG_WRAPPER_EXPORT float GetRoomWallHeight(void* pGenerate, int iRoomArrayPos, int iWallArrayPos);

	//LG_WRAPPER_EXPORT float GetRoomPosition_X(void* pGenerate, int iRoomArrayPosition);
	//LG_WRAPPER_EXPORT float GetRoomPosition_Y(void* pGenerate, int iRoomArrayPosition);
	//LG_WRAPPER_EXPORT float GetRoomPosition_Z(void* pGenerate, int iRoomArrayPosition);
	//
	//LG_WRAPPER_EXPORT float GetRoomNodePosition_X(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);
	//LG_WRAPPER_EXPORT float GetRoomNodePosition_Y(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);
	//LG_WRAPPER_EXPORT float GetRoomNodePosition_Z(void* pGenerate, int iRoomArrayPosition, int iNumOfNode);

	///************************************************************************/
	///*									Doors.			                  */
	///************************************************************************/

	LG_WRAPPER_EXPORT float GetDoorCenterPos_X(void* pGenerate, int iRoomArrayPos, int iDoorArrPos);
	LG_WRAPPER_EXPORT float GetDoorCenterPos_Y(void* pGenerate, int iRoomArrayPos, int iDoorArrPos);
	LG_WRAPPER_EXPORT float GetDoorCenterPos_Z(void* pGenerate, int iRoomArrayPos, int iDoorArrPos);

	LG_WRAPPER_EXPORT float GetDoorWidth(void* pGenerate, int iRoomArrayPos, int iDoorArrPos);
	LG_WRAPPER_EXPORT float GetDoorHeight(void* pGenerate, int iRoomArrayPos, int iDoorArrPos);

	///************************************************************************/
	///*                            Hallway Functions.		                  */
	///************************************************************************/

	//**
	// *	@brief Returns the total amount of hallways in the dungeon.
	// *	@param void* pGenerate: A pointer of a generate level object.
	// *	@return The amount of hallways.
	// */
	//LG_WRAPPER_EXPORT int GetHallwayAmount(void* pGenerate);
	//
	//**
	// *	@brief A hall could have 4 or 6 nodes, depending on whether it's a corner or a straight hall. So this function tells you how many nodes does a hallway haves.
	// *	@param void* pGenerate: A pointer of a generate level object.
	// *	@param int iHallway: The position in the array of hallways that contains the one we want to get the information from.
	// *	@return The amount of nodes from the hall.
	// */
	//LG_WRAPPER_EXPORT int GetNodeAmountFromHallway(void* pGenerate, int iHallway);

	/**
	 *	@brief Tells if a hallway is a corner or a straight hall.
	 *	@param void* pGenerate: A pointer of a generate level object.
	 *	@param int iHallway: The position in the array of hallways that contains the one we want to get the information from.
	 *	@return True if the corridor is a corner.
	 */
	LG_WRAPPER_EXPORT bool IsCorner(void * pGenerate, int iHallway);

	//TODO: comentiza perrona.

	LG_WRAPPER_EXPORT int GetHallwayAmount(void* pGenerate);
	LG_WRAPPER_EXPORT int GetHallwayWallsAmount(void* pGenerate, int iHall);
	LG_WRAPPER_EXPORT int GetHallwayFloorsAmount(void* pGenerate, int iHall);
	LG_WRAPPER_EXPORT int GetHallwayCeilingsAmount(void* pGenerate, int iHall);

	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_X(void* pGenerate, int iHallway, int iWall);
	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_Y(void* pGenerate, int iHallway, int iWall);
	LG_WRAPPER_EXPORT float GetHallwayWallCenterPos_Z(void* pGenerate, int iHallway, int iWall);
	LG_WRAPPER_EXPORT float GetHallwayWallWidth(void* pGenerate, int iHallway, int iWall);
	LG_WRAPPER_EXPORT float GetHallwayWallHeight(void* pGenerate, int iHallway, int iWall);
	LG_WRAPPER_EXPORT bool IsHallwayWallHorizontal(void* pGenerate, int iHallway, int iWall);

	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_X(void* pGenerate, int iHallway, int iFloor);
	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_Y(void* pGenerate, int iHallway, int iFloor);
	LG_WRAPPER_EXPORT float GetHallwayFloorCenterPos_Z(void* pGenerate, int iHallway, int iFloor);
	LG_WRAPPER_EXPORT float GetHallwayFloorWidth(void* pGenerate, int iHallway, int iFloor);
	LG_WRAPPER_EXPORT float GetHallwayFloorHeight(void* pGenerate, int iHallway, int iFloor);

	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_X(void* pGenerate, int iHallway, int iCeiling);
	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_Y(void* pGenerate, int iHallway, int iCeiling);
	LG_WRAPPER_EXPORT float GetHallwayCeilingCenterPos_Z(void* pGenerate, int iHallway, int iCeiling);
	LG_WRAPPER_EXPORT float GetHallwayCeilingWidth(void* pGenerate, int iHallway, int iCeiling);
	LG_WRAPPER_EXPORT float GetHallwayCeilingHeight(void* pGenerate, int iHallway, int iCeiling);

	//LG_WRAPPER_EXPORT float GetHallwayNodePosition_X(void* pGenerate, int iHallway, int iNode);
	//LG_WRAPPER_EXPORT float GetHallwayNodePosition_Y(void* pGenerate, int iHallway, int iNode);
	//LG_WRAPPER_EXPORT float GetHallwayNodePosition_Z(void* pGenerate, int iHallway, int iNode);

	///************************************************************************/
	///*                           Pathfinding Functions.                 */
	///************************************************************************/

	LG_WRAPPER_EXPORT void Pathfinding_DIJKSTRA(void* pGenerate, int iStartNode, int iEndNode);
	LG_WRAPPER_EXPORT int GetPathSize_DIJKSTRA(void* pGenerate);
	LG_WRAPPER_EXPORT int GetPath_DIJKSTRA_OneByOne(void* pGenerate, int iPathArrayPosition);
}