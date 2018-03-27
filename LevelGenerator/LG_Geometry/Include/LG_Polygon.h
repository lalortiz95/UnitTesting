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
		 *	@var A vector of nodes that makes the shape wanted.
		 */
		Vector<LG_Node*> m_pNodeVector;

		

		///**************************************************************************/
		///*						  Class Functions.								*/
		///**************************************************************************/

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function add a Node to the vector of nodes.
		 *	@param LG_Node* pNewNode: Node that we want to add to the vector.
		 */
		void InsertNodeToVector(LG_Node* pNewNode);

	};
}

