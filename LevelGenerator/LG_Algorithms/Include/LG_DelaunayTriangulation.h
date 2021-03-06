#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Vector3D.h>
#include <LG_Isoline.h>
#include <LG_Triangle.h>
#include <LG_Polygon.h>
#include <LG_Rect.h>

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
		 *	@var where we store our triangulation.
		 */
		Vector<LG_Triangle*> m_pTrianglesVector;

		/**
		 *	@var A vector to store edges that we need for create a triangle.
		 */
		Vector<LG_Edge*> m_pEdgeVector;

		/**
		 *	@var The set of nodes that we want to triangulate.
		 */
		Vector<LG_Node*>* m_pNodesCloud;

		/**
		 *	@var A big triangle to make an initial triangulation from the nodes given.
		 */
		LG_Triangle* m_pBigTriangle;

		/**
		 *	@var The actual triangle being created.
		 */
		LG_Triangle* m_pActualTriangle;

		/**
		 *	@var Inside of this area are all of the nodes to triangulate with.
		 */
		LG_Rect m_AreaContainingRooms;

		/**
		 *	@var This variable counts the number of triangles created.
		 */
		int32 m_iTrianglesCount;

		/**
		 *	@var This variable counts the number of edges created.
		 */
		int32 m_iEdgesCount;

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
		void Init(LG_Vector3D GridCenter, Vector<LG_Node*>* pCloudNodes);

		/**
		 *  @brief This function releases memory and clears the variables.
		 */
		void Destroy();

		/**
		 *  @brief This function performs the algorithm.
		 *	@param LG_Vector3D:	The center of the grid.
		 *	@param Vector<LG_Isoline> PointsCloud: The nodes cloud that we used to generate a triangulation.
		 */
		void Run(LG_Vector3D GridCenter, Vector<LG_Node*>* pCloudNodes);

		/**
		 *	@brief This function performs an initial triangulation that works as a base for the rest of the algorithm.
		 */
		void IncrementalTriangulation();

		/**
		 *  @brief This function checks if the triangle is already checked.
		 *	@param LG_Triangle pActualTriangle: the triangle we want to see if is checked.
		 */
		void CheckIfTriangleIsChecked(LG_Triangle* pActualTriangle);

		/**
		 *	@brief This function create a big triangle.
		 *	@param int32 iWidth: The width of the grid.
		 *	@param int32 iHeight: The height of the grid.
		 *	@param LG_Vector3D GridCenter: The center of the grid.
		 */
		void CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter);

		/**
		 *	@brief This function sets all the triangles' flags in vector triangles as false.
		 */
		void SetTrianglesAsFalse();

		/**
		 *	@brief This function finds the polygon with the triangles given.
		 *	@param LG_Edge* pActualEdge: The iterating edge.
		 *	@param LG_Triangle* pFirstTriangle: The first triangle.
		 *	@param LG_Triangle* pSecondTriangle: The second triangle.
		 *	@param LG_Node** ppFirstNode: The first node that we want to found.
		 *	@param LG_Node** ppSecondNode: The second node that we want to found.
		 *	@return true if find 2 nodes to create a polygon, otherwise false.
		 */
		bool FindNodesToCreatePolygon(LG_Edge* pActualEdge, LG_Triangle* pFirstTriangle, LG_Triangle* pSecondTriangle, LG_Node** ppFirstNode, LG_Node** ppSecondNode);


		/**
		 *	@brief This function finds the triangles that we want to legalize it's edges.
		 *	@param LG_Edge* pActualEdge: The actual edge.
		 *	@param LG_Triangle** ppFirstTriangle: The firstTriangle.
		 *	@param LG_Triangle** ppThirdNode: The second triangle.
		 *	@return true if found 2 triangles, otherwise false.
		 */
		bool FindTrianglesToLegalize(LG_Edge* pActualEdge, LG_Triangle** ppFirstTriangle, LG_Triangle** ppSecondTriangle);

		/**
		 *  @brief This function determine when we can stop the triangulation.
		 *	@return true if all the triangles in the triangulation are true.
		 */
		bool CheckIfAllTrianglesAreTrue();

		/**
		 *	@brief This function delete all triangles that have one or more nodes of the big triangle.
		 *	@return true if we erase one triangle of the triangles' vector.
		 */
		bool DeleteTrianglesSharesBT();

		/**
		 *	@brief This function delete all edges that have one or more nodes of the big triangle.
		 *	@return true if we erase one edge of the edges' vector.
		 */
		bool DeleteEdgesSharesBT();

		/**
		 *	@brief Thisfunction delete all edges of the big triangle from the edges' vector
		 */
		void DeleteEdgesBT();

		/**
		 *	@brief This function delete all nodes of the big triangle and delete the big triangle.
		 */
		void DeleteBT();

		/**
		 *	@brief This function erase a triangle from the triangles' vector.
		 *	@param LG_Triangle* pTriangle: The triangle that we want to erase from the triangles' vector.
		 */
		void EraseTriangleFromVector(LG_Triangle* pTriangle);

		/**
		 *	@brief This function erase a edge from the edges' vector.
		 *	@param LG_Edge* pEdge: The edge that we want to erase from the edges' vector.
		 */
		void EraseEdgeFromVector(LG_Edge* pEdge);



		/**
		 *	@brief This function create a new triangle with the given nodes.
		 *	@param LG_Node* pFirstNode: The first node that we need to create a triangle.
		 *	@param LG_Node* pSecondNode: The second node that we need to create a triangle.
		 *	@param LG_Node* pThirdNode: The third node that we need to create a triangle.
		 *	@return The new triangle.
		 */
		LG_Triangle* CreateTriangle(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);

		/**
		 *	@brief This function check if the triangle is a good triangle with the given nodes.
		 *	@param LG_Node* pFirstNode: The first node that we need to create a triangle.
		 *	@param LG_Node* pSecondNode: The second node that we need to create a triangle.
		 *	@param LG_Node* pThirdNode: The third node that we need to create a triangle.
		 *	@return The triangle.
		 */
		LG_Triangle CheckIfIsAGoodTriangle(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);

	private:

		/**
		 *	@brief This function find the points in the nodes vector, that are furthest away from the center.
		 */
		void FindFurthestPoints(const LG_Vector3D& CenterPosition);
	};
}