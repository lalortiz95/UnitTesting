#pragma once
#include "LG_AlgorithmsPrerequisites.h"


#include "LG_Wall.h"
#include <LG_Door.h>

namespace LevelGenerator
{

	class LG_ALGORITHMS_EXPORT LG_Room
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Room();

		/**
		 *	@brief Parameter constructor.
		 *	@param LG_Vector3D iPosX: The position of the room.
		 *	@param float fWidth: The width of the room.
		 *	@param float fHeight: The height of the room.
		 *	@param float fDepth: The depth of the room.
		 */
		LG_Room(LG_Vector3D vPosToSpawn, float fWidth, float fHeight, float fDepth);

		/**
		 *	@brief Default destructor.
		 */
		~LG_Room();



		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var A flag to see whether or not the rectangle has been used or not.
		 */
		bool m_bIsChecked;

		/**
		 *	@var How tall the room is.
		 */
		float m_fHeight;

		/**
		 *	@var Defines the room's case, being Top_Left, Bottom_Left, Top_Right, or Bottom_Right. See eRoomCases in HallwayGeneration.
		 */
		int32 m_iRoomCase;

		/**
		 *	@var The rect that define the floor of the room.
		 */
		LG_Rect* m_pFloor;

		/**
		 *	@var The rect that define the ceiling of the room.
		 */
		LG_Rect* m_pCeiling;

		/**
		 *	@var Stores all the walls contained in the room. separated by corners or doors.
		 */
		Vector<LG_Wall*> m_Walls;

		/**
		 *	@var The doors that have the room.
		 */
		Vector<LG_Door*> m_Doors;

		/**
		 *	@var Stores the connections from every room.
		 */
		Vector<LG_Room*> m_RoomsConnections;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function initialize el area of the room.
		 *	@param LG_Vector3D iPosX: The position of the room.
		 *	@param float fWidth: The width of the room.
		 *	@param float fHeight: The height of the room.
		 *	@param float fDepth: The depth of the room.
		 */
		void Init(LG_Vector3D vPosToSpawn, float fWidth, float fHeight, float fDepth);

		/**
		 *	@brief This function release the memory that was using in the room.
		 */
		void Destroy();

		/**
		 *	@brief This function stops pointing to the given room. Used when releasing memory.
		 *	@param LG_Room* pRoom: The room that we want to stop pointing at.
		 */
		void StopPointingToRoom(LG_Room* pRoom);

		/**
		 *	@brief This function assign the connections of the room.
		 *	@param const Vector<LG_Node*>& NodeConnections:
		 *	@param const Vector<LG_Room*>& RoomsVector:
		 */
		void AddRoomConnections(const Vector<LG_Node*>& NodeConnections, const Vector<LG_Room*>& RoomsVector);

		/**
		 *	@brief This function assign the connections of the room.
		 */
		void CreateWalls();

	private:
		/**
		 *	@brief This function generates a floor object for the room.
		 *	@param LG_Vector3D vPosToSpawn: The center position of the rectangle that represents the floor.
		 *	@param float fWidth: the width of the floor.
		 *	@param float fDepth: the height of the floor.
		 */
		void CreateFloor(LG_Vector3D vPosToSpawn, float fWidth, float fDepth);

		/**
		 *	@brief This function generates a ceiling object for the room.
		 *	@param LG_Vector3D vPosToSpawn: The center position of the rectangle that represents the floor.
		 *	@param float fWidth: the width of the floor.
		 *	@param float fDepth: the height of the floor.
		 *	@param float fHeight: the height given by the user that states how tall a room is.
		 */
		void CreateCeiling(LG_Vector3D vPosToSpawn, float fWidth, float fDepth, float fHeight);

		/**
		 *	@brief This function calculates 4 nodes of a rectangle that will represent a wall, and then stores that wall in a vector.
		 *	@param Vector<float> sideDoors: the door's positions of 1 out of 4 walls available (top, right, bottom, left).
		 *	@param LG_Vector3D FristNode: one of the floor's nodes. A corner to start calculating the positions of the wall's nodes, is the one with the minimum value in the axis needed.
		 *	@param LG_Vector3D SecondNode: one of the floor's nodes. A corner to end calculating the positions of the wall's nodes, is the one with the maximum value in the axis needed.
		 *	@param bool bIsHorizontal: this is needed to see in which axis the wall will be calculated, being X or Y the possible options.
		 */
		void CalculateWallNodes(Vector<float> sideDoors, LG_Vector3D FirstNode, LG_Vector3D SecondNode, bool bIsHorizontal);
	};
}

