#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Polygon.h>
#include <LG_Rect.h>
#include <LG_Vector2D.h>

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
		Vector<std::shared_ptr<LG_Polygon>> m_FinalHallways;
		//Vector<LG_Polygon*> m_FinalHallways;

		/**
		 *	@var Where we store the rooms in the scene. They're used to check collision with the hallways as they're generated.
		 */
		Vector<LG_Rect*>* m_pRooms;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Initializes the member variables of the class.
		 *	@param float fCorridorWidth: the width that the corridor will have.
		 *	@param Vector<LG_Rect*>* pRooms: The rooms generated, with their size, position, etc.
		 */
		void Init(float fCorridorWidth, Vector<LG_Rect*>* pRooms);

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate Hallways.
		 *	@param Vector<LG_Edge*> Connections: The connections upon we build the hallways.
		 *	@param Vector<LG_Rect*>* pRooms: The rectangles that represent the rooms.
		 *	@param float fCorridorWidth: the given width to generate the hallways.
		 */
		void Run(Vector<LG_Rect*>* pRooms, float fCorridorWidth);

	private:

		/**
		 *	@brief Creates a vertical hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the vertical hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the vertical hallway.
		 *	@param LG_Vector3D MidPoint: we'll use this midpoint's X position to place the hallway.
		 */
		void GenerateVerticalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2, LG_Vector3D MidPoint);

		/**
		 *	@brief Creates a horizontal hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the horizontal hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the horizontal hallway.
		 *	@param LG_Vector3D MidPoint: we'll use this midpoint's Y position to place the hallway.
		 */
		void GenerateHorizontalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2, LG_Vector3D MidPoint);

		/**
		 *	@brief Creates a L shaped hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the horizontal hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the horizontal hallway.
		 */
		void GenerateCornerHallway(LG_Rect* pRoom1, LG_Rect* pRoom2);
	};
}