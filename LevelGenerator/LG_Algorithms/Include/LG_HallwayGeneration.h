#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Edge.h>
#include <LG_Rect.h>

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
		Vector<LG_Rect*> m_FinalHallways;

		/**
		 *	@var Where we store the rooms in the scene. They're used to check collision with the hallways as they're generated.
		 */
		Vector<LG_Rect*> m_Rooms;

		/**
		 *	@var Where we store the rooms tha belongs to the iterating connection.
		 */
		LG_Rect* m_pRoom1;

		/**
		 *	@var Where we store the rooms tha belongs to the iterating connection.
		 */
		LG_Rect* m_pRoom2;

		/**
		 *	@var a constant that defines 20 degrees in radians.
		 */
		static const float _20_DEGREES;

		/**
		 *	@var a constant that defines 160 degrees in radians.
		 */
		static const float _160_DEGREES;

		/**
		 *	@var a constant that defines 110 degrees in radians.
		 */
		static const float _110_DEGREES;
		
		/**
		 *	@var a constant that defines 70 degrees in radians.
		 */
		static const float _70_DEGREES;

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
		 *	@return the hallway that was created.
		 */
		LG_Rect* MakeVerticalHallway(LG_Edge* Connection, bool bIsCorner);

		/**
		 *	@brief Creates a horizontal hallway between two rooms.
		 *	@param LG_Edge* Connection: the connection between two rooms that will be transformed into a hallway.
		 */
		LG_Rect* MakeHorizontalHallway(LG_Edge* Connection, bool bIsCorner);

		/**
		 *	@brief Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
		 *	@param LG_Edge* Connection: the connection between two rooms that will be transformed into a hallway.
		 */
		void MakeCornerHallway(LG_Edge* Connection);

		/**
		 *	@brief returns the two rooms that have the iterating connection.
		 *	@param The first room that of the connection.
		 *	@param Second room from the connection.
		 */
		void GetConnectionsRooms(LG_Edge* Connection);

		/**
		 *	@brief Calculates a position for a corner between two connected rooms.
		 *	@param bool bIsMaximum: lets us know if we need to create the corner with the maximum or minimum positions.
		 *	@param LG_Rect& VerticalHall: out, the generated hallway.
		 *	@param LG_Rect& HorizontalHall: out, the generated hallway.
		 */
		void CalculateCornerPosition(bool bIsMaximum, LG_Rect*& VerticalHall, LG_Rect*& HorizontalHall, LG_Edge* Connection);
	};
}