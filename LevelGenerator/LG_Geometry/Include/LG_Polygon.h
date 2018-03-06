#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Rect.h"

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

	/**
	 *	@brief This class has a polygon.
	 */
	class LG_GEOMETRY_EXPORT LG_Polygon
	{
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/
	public:

		/**
		 *	@brief Default Constructor.
		 */
		LG_Polygon();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Polygon();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 * @var Indicates if the hallway is a corner or not.
		 */
		bool m_bIsCorner;

		/**
		 *	@var pointer to the first parent room.
		 */
		LG_Rect* m_pParentRoom_1;

		/**
		 *	@var pointer to the second parent room.
		 */
		LG_Rect* m_pParentRoom_2;

		/**
		 *	@var A vector of nodes that makes the shape wanted.
		 */
		Vector<std::shared_ptr<LG_Node>> m_pNodeVector;

		/**
		 *	@var Use this var if the polygon is a corner.
		 */
		CASES_FOR_CORNER m_eCase;

		///**************************************************************************/
		///*						  Class Functions.								*/
		///**************************************************************************/

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function add a Node to the vector of nodes.
		 *	@param std::shared_ptr<LG_Node> sptrNewNode: Node that we want to add to the vector.
		 */
		void InsertNodeToVector(std::shared_ptr<LG_Node> sptrNewNode);

		/**
		 *	@brief This function check if the polygon collision with other rect.
		 *	@param
		 *	@return
		 */
		 bool CheckCollision(LG_Rect pOtherRect);

		/**
		 *	@brief	This function check if the polygon collision with other polygon.
		 *	@param	LG_Polygon* pOtherPolygon: The other polygon
		 *	@return	true if exist a collision, otherwise false.
		 */
		 bool CheckCollision(std::shared_ptr<LG_Polygon> pOtherPolygon);

		/**
		 *	@brief This function generates two temp rects from the polygon to determinate the collision.
		 *	@param LG_Rect& rHorizontal: The horizontal rect that we want to create to check the collision.
		 *	@param LG_Rect& rVertical: The vertical rect that we want to create to check the collision.
		 *  @param std::shared_ptr<LG_Polygon> pPolygon: The polygon that we want to use to create both rects.
		 */
		 void CreateTempRects(LG_Rect& rHorizontal, LG_Rect& rVertical, LG_Polygon pPolygon);
	};
}

