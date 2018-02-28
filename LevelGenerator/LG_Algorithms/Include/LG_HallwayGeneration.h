#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Polygon.h>
#include <LG_Rect.h>
#include <LG_Vector2D.h>

namespace LevelGenerator
{
	/**
	 *	@brief The possible cases that rooms have. It's used to identify which rooms could have a straight hallway instead of a corner one.
	 */
	enum eRoomCases
	{
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		CASE_NOT_SET
	};

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

		/**
		 *	@var a constant that defines 20 degrees in radians.
		 */
		static const float _20_DEGREES;

		/**
		 *	@var a constant that defines 70 degrees in radians.
		 */
		static const float _70_DEGREES;

		/**
		 *	@var a constant that defines 110 degrees in radians.
		 */
		static const float _110_DEGREES;

		/**
		 *	@var a constant that defines 160 degrees in radians.
		 */
		static const float _160_DEGREES;

		/**
		 *	@var a constant that defines 200 degrees in radians.
		 */
		static const float _200_DEGREES;

		/**
		 *	@var a constant that defines 250 degrees in radians.
		 */
		static const float _250_DEGREES;

		/**
		 *	@var a constant that defines 290 degrees in radians.
		 */
		static const float _290_DEGREES;

		/**
		*	@var a constant that defines 340 degrees in radians.
		*/
		static const float _340_DEGREES;


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

		/**
		 *	@brief Creates a vertical hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the vertical hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the vertical hallway.
		 *	@return the hallway that was created.
		 */
		LG_Polygon* MakeVerticalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2);

		/**
		 *	@brief Creates a horizontal hallway between two rooms.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the horizontal hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the horizontal hallway.
		 *	@return the hallway that was created.
		 */
		LG_Polygon* MakeHorizontalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2);

		/**
		 *	@brief Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the corner hallway.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the corner hallway.
		 *	@return the hallway that was created.
		 */
		void MakeCornerHallway(LG_Rect* pRoom1, LG_Rect* pRoom2);

		/**
		 *	@brief Calculates each room's cases.
		 *	@param LG_Rect* pRoom1: the first room used to calculate the case.
		 *	@param LG_Rect* pRoom2: the second room used to calculate the case.
		 */
		 bool SetRoomsCornerCases(LG_Rect* pRoom1, LG_Rect* pRoom2);

		 /**
		  *	@brief Calculates each room's cases.
		  *	@param LG_Rect* pRoom1: the first room used to calculate the case.
		  *	@param LG_Rect* pRoom2: the second room used to calculate the case.
		  *	@return
		  */
		 void SetRoomsCases(LG_Rect* pRoom1, LG_Rect* pRoom2);

		 /**
		  *	@brief Check if we can do an horizontal or vertical hallway depending on the room's case.
		  *	@param LG_Rect* pRoom1: the first room used to calculate.
		  *	@param LG_Rect* pRoom2: the second room used to calculate.
		  * @return true if we can do a vertical or horizontal hallway, otherwise return false.
		  */
		 bool CheckForStraightHallway(LG_Rect* pRoom1, LG_Rect* pRoom2);

		 /**
		  *	@brief Calculates a position for a corner between two connected rooms.
		  *	@param bool bIsMaximum: lets us know if we need to create the corner with the maximum or minimum positions.
		  *	@param LG_Rect& VerticalHall: out, the generated hallway.
		  *	@param LG_Rect& HorizontalHall: out, the generated hallway.
		  */
		void CalculateCornerPosition(bool bIsMaximum, LG_Rect*& VerticalHall, LG_Rect*& HorizontalHall, LG_Rect* Room1, LG_Rect* Room2);
	};
}