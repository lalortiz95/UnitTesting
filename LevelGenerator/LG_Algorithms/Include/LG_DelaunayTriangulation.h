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
		 *	@brief A vector to store edges that we need for create a triangle.
		 */
		Vector<LG_Edge*> m_pEdgeVector;

		/**
		 *	@brief The set of nodes that we want to triangulate.
		 */
		Vector<LG_Node> m_NodesCloud;

		/**
		 *	@brief A big triangle to make an initial triangulation from the nodes given.
		 */
		LG_Triangle* m_pBigTriangle;

		/**
		 *	@brief The actual triangle being created.
		 */
		LG_Triangle* m_pActualTriangle;

		/**
		 *	@brief The Polygon to create.
		 */
		LG_Polygon m_Polygon;

		/**
		 *	@brief This variable counts the number of triangles created.
		 */
		int32 m_iTrianglesCount;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/
	
		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param int32 iGridWidth: The width of the grid.
		 *	@param int32 iGridHeight: The height of the grid.
		 *	@param LG_Vector3D:	The center of the grid.
		 *	@param Vector<LG_Isoline> PointsCloud: The nodes cloud that we used to generate a triangulation.
		 */
		void Init(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> PointsCloud);

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param Vector<LG_Node> PointsCloud: The nodes cloud that we used to generate a triangulation.
		 *	@param LG_Vector3D:	The center of the grid.
		 *	@param int32 iGridWidth: The width of the grid.
		 *	@param int32 iGridHeight: The height of the grid.
		 */
		void Init(Vector<LG_Node> PointsCloud, LG_Vector3D GridCenter, int32 iGridWidth, int32 iGridHeight);

		
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

	//private:

		/**
		 *	@brief This function checks if one edge of the given triangle is already in the polygon's edge vector.
		 *	@param LG_Triangle* pIteratingTriangle: The triangle that we want to check.
		 */
		void CheckIfEdgeIsInside(LG_Triangle* pIteratingTriangle);

		/**
		 *  @brief This function create a triangle from one triangle and a node.
		 *  @param LG_Triangle ActualTriangle: The base triangle to generate 3 new triangles.
		 *  @param LG_Node* pNodeInside: The node used to make the 3 new triangles.
		 *  @param int32 iCountNode: The node number iteration that we want to use of the triangle.
		 */
		void CreateTriangle(LG_Triangle ActualTriangle, LG_Node* pNodeInside, int32 iCountNode);

		/**
		 *  @brief This function create a 3 triangles from one triangle and a node.
		 *  @param LG_Triangle ActualTriangle: The base triangle to generate 3 new triangles.
		 *  @param LG_Node* pNodeInside: The node used to make the 3 new triangles.
		 */
		void CreateTriangles(LG_Triangle ActualTriangle, LG_Node* pNodeInside);


		/**
		 *	@brief This function checks if the given edge is the same that anyone edge of the triangle's edges in Triangles Vector.
		 *	@param LG_Edge* pIteratingEdge: The Edge that we want to check.
		 *	@return true if the edge is the same that anyone, otherwise false.
		 */
		bool EdgeIsNotInTriangleVector(LG_Edge* pIteratingEdge);

		/**
		 *	@brief This function adds a bad triangle if it haves the iterating node inside of it.
		 *	@param const LG_Node& IteratingNode: the iterating node that will be compared.
		 *	@param return true if the bad Triangle Vector had changes, otherwise false.
		 */
		bool SetTriangleAsBadTriangle(const LG_Node& IteratingNode);

		/**
		 *  @brief This function determine when we can stop the triangulation.
		 *	@return true if all nodes flags bInside are true, otherwise false.
		 */
		bool CheckifAllNodesAreTrue();

		/**
		 *  @brief This function compares the iterating node's position with any of the iterating triangle's node.
		 *  @param LG_Triangle IteratingTriangle: The actual triangle.
		 *  @param LG_Node IteratingNode: The actual iterating node.
		 *  @return true if one of the triangle's nodes shares position with the iterating node.
		 */
		bool CheckIfSharesPosition(LG_Triangle IteratingTriangle, LG_Node IteratingNode);


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
		 *	@brief This function add edges to the polygon.
		 */
		void AddEdgesToPolygon();

		/**
		 *	@brief 
		 */
		LG_Triangle* ManageEdges(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);
	};
}