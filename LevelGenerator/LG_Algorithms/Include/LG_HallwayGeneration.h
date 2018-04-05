#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Hallway.h>
#include <LG_Room.h>


namespace LevelGenerator
{
	/**
	 *	@brief This class Generates hallways between the rooms.
	 */
	class LG_ALGORITHMS_EXPORT LG_HallwayGeneration
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_HallwayGeneration();

		/**
		 *	@brief Default destructor.
		 */
		~LG_HallwayGeneration();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var The corridor's width.
		 */
		float m_fHallwayWidth;

		/**
		 *	@var Where we store the final hallways.
		 */
		Vector<LG_Hallway*> m_FinalHallways;
		
		/**
		 *	@var Where we store the rooms in the scene. They're used to check collision with the hallways as they're generated.
		 */
		Vector<LG_Room*>* m_pRooms;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Initializes the member variables of the class.
		 *	@param float fCorridorWidth: the width that the corridor will have.
		 *	@param Vector<LG_Room*>* pRooms: The rooms generated, with their size, position, etc.
		 */
		void Init(float fCorridorWidth, Vector<LG_Room*>* pRooms);

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate Hallways.
		 *	@param Vector<LG_Room*>* pRooms: The rectangles that represent the rooms.
		 *	@param float fCorridorWidth: the given width to generate the hallways.
		 *	@param float fHeight: The height for the hallways.
		 */
		void Run(Vector<LG_Room*>* pRooms, float fCorridorWidth, float fHeight);

	private:

		/**
		 *	@brief Creates a vertical hallway between two rooms.
		 *	@param LG_Room* pRoom1: the first room used to calculate the vertical hallway.
		 *	@param LG_Room* pRoom2: the second room used to calculate the vertical hallway.
		 *	@param LG_Vector3D MidPoint: we'll use this midpoint's X position to place the hallway.
		 *	@param float fHeight: The height of the hallway.
		 */
		void GenerateVerticalHallway(LG_Room* pRoom1, LG_Room* pRoom2, LG_Vector3D MidPoint, float fHeight);

		/**
		 *	@brief Creates a horizontal hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the horizontal hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the horizontal hallway.
		 *	@param LG_Vector3D MidPoint: we'll use this midpoint's Y position to place the hallway.
		 *	@param float fHeight: The height of the hallway.
		 */
		void GenerateHorizontalHallway(LG_Room* pRoom1, LG_Room* pRoom2, LG_Vector3D MidPoint, float fHeight);

		/**
		 *	@brief Creates a L shaped hallway between two rooms.
		 *	@param LG_Room* pRoom1: the first room used to calculate the horizontal hallway.
		 *	@param LG_Room* pRoom2: the second room used to calculate the horizontal hallway.
		 *	@param float fHeight: The height of the hallway.
		 */
		LG_Hallway* GenerateCornerHallway(LG_Room* pRoom1, LG_Room* pRoom2, float fHeight);

		/**
		 *	@brief Gets the longest distance from a polygon to it's parents corners.
		 *	@param CASES_FOR_CORNER eCase
		 *	@return float
		 */
		float GetLongestDistance(LG_Hallway* phallwayToMove);
		
		/**
		 *	@brief Depending on the corner's case, we move it so that it doesn't collide with anything else.
		 *	@param std::shared_ptr<LG_Polygon> CornerToMove: The corner that will be modified.
		 *	@param LG_Room* CollisionRoom: The room for check the collision with the polygon.
		 *	@return true if the polygon was able to move stopping the collision, if after moving it still collides return false.
		 */
		bool MoveCorner(LG_Hallway* pCornerToMove, LG_Room* CollisionRoom);

		/**
		 *
		 *
		 */
		LG_Hallway* ReorganizeCornerHallway(LG_Hallway* pCornerToMove, float fHeight);

	};
}