#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Edge.h>

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
		 *	@var the corridor's width.
		 */
		float m_fHallwayWidth;

		/**
		 *	@var where we store the final hallways.
		 */
		Vector<LG_Rect*> m_FinalHallways;

		/**
		 *	@var where we store the rooms in the scene. They're used to check collision with the hallways as they're generated.
		 */
		Vector<LG_Rect*> m_Rooms;

		 ///************************************************************************/
		 ///*						   Class Functions.							  */
		 ///************************************************************************/

		 /**
		  *	@brief Initializes the member variables of the class.
		  *	@param float fCorridorWidth: the width that the corridor will have.
		  *	@param Vector<LG_Rect*> m_Rooms: The rooms generated, with their size, position, etc.
		  */
		void Init(float fCorridorWidth, Vector<LG_Rect*> Rooms);

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate Hallways.
		 *	@param Vector<LG_Edge*> Connections: The connections upon we build the hallways.
		 *	@param float fCorridorWidth: the given width to generate the hallways.
		 *	@param Vector<LG_Rect*> Rooms: The rectangles that represent the rooms.
		 */
		void Run(Vector<LG_Edge*> Connections, Vector<LG_Rect*> Rooms, float fCorridorWidth);

	private:
		/**
		 *	@brief Creates a vertical hallway between two rooms.
		 *	@param LG_Edge* Connection: the connection between two rooms that will be transformed into a hallway.
		 */
		void MakeVerticalHallway(LG_Edge* Connection);

		/**
		 *	@brief Creates a horizontal hallway between two rooms.
		 *	@param LG_Edge* Connection: the connection between two rooms that will be transformed into a hallway.
		 */
		void MakeHorizontalHallway(LG_Edge* Connection);

		/**
		 *	@brief Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
		 *	@param LG_Edge* Connection: the connection between two rooms that will be transformed into a hallway.
		 */
		void MakeCornerHallway(LG_Edge* Connection);
	};
}