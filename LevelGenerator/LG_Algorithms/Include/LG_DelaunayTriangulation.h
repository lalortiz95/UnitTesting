#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Triangle.h>
#include <LG_Vector3D.h>
#include <LG_Isoline.h>

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
		Vector<LG_Triangle> m_TrianglesVector;
		
		/**
		 *	@brief The set of nodes that we want to triangulate.
		 */
		Vector<LG_Node> m_NodesCloud;

		/**
		 *	@brief A big triangle to make an initial triangulation from the nodes given.
		 */
		LG_Triangle m_BigTriangle;

		/**
		 *	@brief This variable store a actual triangle.
		 */
		LG_Triangle m_ActualTriangle;


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

		/**
		 *  @brief This function create a triangle from one triangle and a node.
		 *	@param LG_Triangle ActualTriangle: The base triangle to generate 3 new triangles.
		 *	@param LG_Node* pNodeInside: The node used to make the 3 new triangles.
		 *	@param int32 iCountNode: The node number iteration that we want to use of the triangle.
		 */
		void CreateTriangle(LG_Triangle ActualTriangle, LG_Node* pNodeInside, int32 iCountNode);

		/**
		 *  @brief This function create a 3 triangles from one triangle and a node.
		 *	@param LG_Triangle ActualTriangle: The base triangle to generate 3 new triangles.
		 *	@param LG_Node* pNodeInside: The node used to make the 3 new triangles.
		 */
		void CreateTriangles(LG_Triangle ActualTriangle, LG_Node* pNodeInside);

		/**
		 *	@brief This function create a big triangle.
		 *	@param int32 iWidth: The width of the grid.
		 *	@param int32 iHeight: The height of the grid.
		 *	@param LG_Vector3D GridCenter: The center of the grid.
		 */
		void CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter);

		/**
		 *	@brief This function determine when we can stop the triangulation.
		 *	@return true if all nodes flags bInside are true, otherwise false.
		 */
		bool CheckifAllNodesAreTrue();

		/**
		 *	@brief This function compares the iterating node's position with any of the iterating triangle's node.
		 *	@param LG_Triangle IteratingTriangle: The actual triangle.
		 *	@param LG_Node IteratingNode: The actual iterating node.
		 *	@return true if one of the triangle's nodes shares position with the iterating node.
		 */
		bool CheckIfSharesPosition(LG_Triangle IteratingTriangle, LG_Node IteratingNode);

		/**
		 *	@brief This function set the triangle as check when it doesn't have any node inside.
		 *	@param LG_Triangle& IteratingTriangle: The actual triangle.
		 */
		void SetTriangleFlag(LG_Triangle& IteratingTriangle);
	};
}