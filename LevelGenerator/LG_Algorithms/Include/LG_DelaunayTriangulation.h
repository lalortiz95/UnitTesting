#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Vector3D.h>
#include <LG_Isoline.h>
#include <LG_Triangle.h>
#include <LG_Polygon.h>

namespace LevelGenerator
{
	/**
	 *	@brief This class manages and unificates all the algorithms in the project.
	 */
	class LG_ALGORITHMS_EXPORT LG_DelaunayTriangulation
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_DelaunayTriangulation();

		/**
		 *	@brief Default destructor.
		 */
		~LG_DelaunayTriangulation();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief where we store our triangulation.
		 */
		Vector<LG_Triangle*> m_pTrianglesVector;

		/**
		 *	@brief a vector to store the incorrect triangles.
		 */
		Vector<LG_Triangle*> m_pBadTriangles;

		/**
		 *	@brief The set of nodes that we want to triangulate.
		 */
		Vector<LG_Node> m_NodesCloud;

		/**
		 *	@brief A big triangle to make an initial triangulation from the nodes given.
		 */
		LG_Triangle* m_pBigTriangle;

		/**
		 *	@brief The Polygon to create.
		 */
		LG_Polygon m_Polygon;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/
		//TODO: Cambiar todos los parametros de funciones por un puntero a generate para usar el mismo objeto.

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param int32 iGridWidth: The width of the grid.
		 *	@param int32 iGridHeight: The height of the grid.
		 *	@param LG_Vector3D:	The center of the grid.
		 *	@param Vector<LG_Isoline> PointsCloud: The nodes cloud that we used to generate a triangulation.
		 */
		void Init(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> PointsCloud);

		/**
		 *  @brief This function releases memory and clears the variables.
		 */
		void Destroy();

		/**
		 *  @brief This function performs the algorithm.
		 *  @param int32 iGridWidth: The width of the grid.
		 *	@param int32 iGridHeight: The height of the grid.
		 *	@param LG_Vector3D:	The center of the grid.
		 *	@param Vector<LG_Isoline> PointsCloud: The nodes cloud that we used to generate a triangulation.
		 */
		void Run(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> NodesCloud);

	private:

		/**
		 *	@brief //! This function checks if one edge of the given trinagle is already in the polygon's edge vector.
		 *	@param LG_Triangle& IteratingTriangle: The triangle that we want to check.
		 */
		void CheckIfEdgeIsInside(LG_Triangle& IteratingTriangle);

		/**
		 *	@brief This function adds a bad triangle if it haves the iterating node inside of it.
		 *	@param const LG_Node& IteratingNode: the iterating node that will be compared.
		 */
		void SetTriangleAsBadTriangle(const LG_Node& IteratingNode);

		/**
		 *	@brief This function create a new triangles from the given node.
		 *	@param LG_Node* pIteratingNode: The node that we want to create a new triangles.
		 */
		void CreateNewTriangles(LG_Node* IteratingNode);

		/**
		 *	@brief This function create a big triangle.
		 *	@param int32 iWidth: The width of the grid.
		 *	@param int32 iHeight: The height of the grid.
		 *	@param LG_Vector3D GridCenter: The center of the grid.
		 */
		void CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter);

		/**
		 *	@brief This function deletes all of the triangles shared with the big triangle.
		 */
		void EliminateTriangles();

		/**
		 *	@brief This function create a polygon.
		 */
		void CreatePolygon();
	};
}