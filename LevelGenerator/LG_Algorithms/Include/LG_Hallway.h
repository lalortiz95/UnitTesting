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
	 *	@brief This enum is to determinate where is the room 1.
	 */
	enum CASES_FOR_CORNER
	{
		ROOM1_TOPRIGHT = 0,
		ROOM1_TOPLEFT = 1,
		ROOM1_BOTTOMRIGHT = 2,
		ROOM1_BOTTOMLEFT = 3
	};

	/**
	 *	@brief This enum is for set the cas of the hallway.
	 */
	enum HALLWAY_CASE
	{
		VERTICAL = 1,
		HORIZONTAL = 2,
		CORNER = 3
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
		 *	@var Use this var if the hallway is a corner.
		 */
		CASES_FOR_CORNER m_eCaseCorner;

		/**
		 *	@var Use this var to determinate if the hallway is horizontal, vertical or corner.
		 */
		HALLWAY_CASE m_eHallwayType;

		/**
		 *	@var The height of the hallway.
		 */
		float m_fHeight;

		/**
		 *	@var pointer to the first parent room.
		 */
		LG_Room* m_pParentRoom_1;

		/**
		*	@var pointer to the second parent room.
		*/
		LG_Room* m_pParentRoom_2;

		/**
		 *	@var The polygon that define the nodes of the hallway.
		 */
		LG_Polygon* m_pPolygon;

		/**
		 *	@var The first door of the hallway.
		 */
		LG_Door* m_pFirstDoor;

		/**
		 *	@var The second door of the hallway.
		 */
		LG_Door* m_pSecondDoor;

		/**
		 *	@var A vector of floors for the hallway.
		 */
		Vector<LG_Rect*> m_Floors;

		/**
		 *	@var A vector of ceilings for the hallway.
		 */
		Vector<LG_Rect*> m_Ceilings;

		/**
		 *	@var A Vector to stores the walls of the hallway.
		 */
		Vector<LG_Wall*> m_Walls;

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

		/**
		 *	@brief This function create a doors for the hallway.
		 *	@param LG_Node* pFD_FP: The first position of the first door.
		 *	@param LG_Node* pFD_SP: The second position of the first door.
		 *	@param LG_Node* pSD_FP: The first position of the second door.
		 *	@param LG_Node* pSD_SP: The second position of the second door.
		 */
		void CreateDoors(LG_Node* pFD_FP, LG_Node* pFD_SP, LG_Node* pSD_FP, LG_Node* pSD_SP);

		/**
		 *	@brief This function create a ceilings for the hallway.
		 */
		void CreateCeilings();

		/**
		 *	@brief This function create a floors for the hallway.
		 */
		void CreateFloors();

		/**
		 *	@brief This function create a one wall for the hallway.
		 *	@param LG_Vector3D BottomLeft: The bottom left of the wall.
		 *	@param LG_Vector3D BottomRight: The bottom right of the wall.
		 *	@param bool bIsHorizontal: states if the wall is horizontal or vertical, as seen from upside down.
		 *	@return Thew wall that was created.
		 */
		LG_Wall* CreateWall(LG_Vector3D BottomLeft, LG_Vector3D BottomRight, bool bIsHorizontal);

		/**
		 *	@brief This function delete the walls of the hallway.
		 */
		void DestroyWalls();

		/**
		 *	@brief This function delete the floors of the hallway.
		 */
		void DestroyFloors();

		 /**
		  *	@brief This function delete the ceilings of the hallway.
		  */
		void DestroyCeilings();

		/**
		 *	@brief This function recreate the walls,floors and ceilings of the hallway.
		 *	@param CASES_FOR_CORNER eCase: The case of the corner for the hallway.
		 */
		void ReorganizeVariables(CASES_FOR_CORNER eCase);

		/**
		*
		*/
		void ReorganizeDoors(LG_Vector3D FD_FP, LG_Vector3D FD_SP, LG_Vector3D SD_FP, LG_Vector3D SD_SP);

		
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

