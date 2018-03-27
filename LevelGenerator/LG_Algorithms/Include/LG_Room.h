#pragma once
#include "LG_AlgorithmsPrerequisites.h"


#include <LG_Rect.h>
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
		 */
		LG_Room(LG_Vector3D vPosToSpawn, float fWidth, float fHeight);

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
		 *	@var Defines the room's case, being Top_Left, Bottom_Left, Top_Right, or Bottom_Right. See eRoomCases in HallwayGeneration.
		 */
		int32 m_iRoomCase;
		
		/**
		 *	@var The area of the room, X,Y y Z positions.
		 */
		LG_Rect* m_pRect;

		/**
		 *	@var The number of doors that have the room.
		 */
		Vector<LG_Door*> m_Doors;

		/**
		 *
		 */
		Vector<LG_Rect*> m_Floors;

		/**
		 *
		 */
		Vector<LG_Rect*> m_Ceilings;

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
		 */
		void Init(LG_Vector3D vPosToSpawn, float fWidth, float fHeight);
		
		/**
		 *	@brief This function release the memory that was using in the room.
		 */
		void Destroy();

		/**
		*	@brief This function stops pointing to the given room.
		*	@param LG_Room* pRoom: The room that we want to stop pointing at.
		*/
		void StopPointingToRoom(LG_Room* pRoom);

		/**
		 *	@brief This function assign the connections of the room.
		 *	@param const Vector<LG_Node*>& NodeConnections:
		 *	@param const Vector<LG_Room*>& RoomsVector:
		 */
		void AddRoomConnections(const Vector<LG_Node*>& NodeConnections, const Vector<LG_Room*>& RoomsVector);
	};
}

