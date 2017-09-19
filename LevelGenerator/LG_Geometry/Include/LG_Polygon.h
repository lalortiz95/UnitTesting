#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Triangle.h"

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
		 *	@brief A vector of nodes.
		 */
		Vector<LG_Edge*> m_pEdgeVector;

		///**************************************************************************/
		///*						  Class Functions.								*/
		///**************************************************************************/

		/**
		 *	@brief This function add a edge to the vector of edges.
		 *	@param LG_Triangle::LG_Edge* EdgeToAdd: Edge that we want to add.
		 */
		void InsertEdgeToVector(LG_Edge* EdgeToAdd);

	};
}

