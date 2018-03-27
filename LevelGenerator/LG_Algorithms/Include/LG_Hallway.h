#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Room.h>
#include <LG_Polygon.h>
#include <LG_Door.h>

namespace LevelGenerator
{

	/**
	 *	@brief This enum is for use the nodes of the polygon like a rect.
	 */
	enum NODES
	{
		TOP_LEFT = 0,
		TOP_RIGHT = 1,
		BOTTOM_RIGHT = 2,
		BOTTOM_LEFT = 3,
	};

	/**
	 *
	 */
	enum CASES_FOR_CORNER
	{
		ROOM1_TOPRIGHT = 0,
		ROOM1_TOPLEFT = 1,
		ROOM1_BOTTOMRIGHT = 2,
		ROOM1_BOTTOMLEFT = 3
	};

	class LG_ALGORITHMS_EXPORT LG_Hallway
	{
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/
	public:

		/**
		*	@brief Default Constructor.
		*/
		LG_Hallway();

		/**
		*	@brief Default Destructor.
		*/
		~LG_Hallway();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

	public:

		/**
		 *	@var Use this var if the polygon is a corner.
		 */
		CASES_FOR_CORNER m_eCase;

		/**
		 * @var Indicates if the hallway is a corner or not.
		 */
		bool m_bIsCorner;

		/**
		 *	@var pointer to the first parent room.
		 */
		LG_Room* m_pParentRoom_1;

		/**
		*	@var pointer to the second parent room.
		*/
		LG_Room* m_pParentRoom_2;

		/**
		 *
		 */
		LG_Polygon* m_pPolygon;

		/**
		 *
		 */
		Vector<LG_Door*>* m_pDoors;

		/**
		 *
		 */
		Vector<LG_Rect*> m_Floors;

		/**
		 *
		 */
		Vector<LG_Rect*> m_Ceilings;

		///**************************************************************************/
		///*						  Class Functions.								*/
		///**************************************************************************/

	public:

		/**
		 *	@brief This function release the memory of the object.
		 */
		void Destroy();

		/**
		 *	@brief This function check if the hallway collision with other room.
		 *	@param	LG_Room* pOtherRoom: The room that we want to check the collision with this hallway.
		 *	@return true if the collision has exist, other wise return false.
		 */
		bool CheckCollisionWithRoom(LG_Room* pOtherRoom);

		/**
		*	@brief	This function check if the hallway collision with other hallway.
		*	@param	LG_Hallway* pOtherHallway: The other polygon
		*	@return	true if the collision has exist, other wise return false.
		*/
		bool CheckCollisionWithHallway(LG_Hallway* pOtherHallway);

	private:

		/**
		 *	@brief This function generates two temp rects from the hallway to determinate the collision.
		 *	@param LG_Rect& rHorizontal: The horizontal rect that we want to create to check the collision.
		 *	@param LG_Rect& rVertical: The vertical rect that we want to create to check the collision.
		 *  @param const LG_Hallway& pHallway: The hallway that we want to use to create both rects.
		 */
		void CreateTempRects(LG_Rect& rHorizontal, LG_Rect& rVertical, const LG_Hallway& pHallway);
	};
}

