#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Rect.h"

namespace LevelGenerator
{
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
		 *	@var A vector of nodes that makes the shape wanted.
		 */
		Vector<std::shared_ptr<LG_Node>> m_pNodeVector;

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
		 //bool CheckCollision(LG_Rect* pOtherRect);

		 /**
		  *	@brief	This function check if the polygon collision with other polygon.
		  *	@param	LG_Polygon* pOtherPolygon: The other polygon
		  *	@return	true if exist a collision, otherwise false.
		  */
		  //bool CheckCollision(LG_Polygon* pOtherPolygon);


	};
}

