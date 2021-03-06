#pragma once

#include "LG_GeometryPrerequisites.h"
#include "LG_Edge.h"
#include "LG_Circle.h"
#include <LG_Vector2D.h>
#include <LG_Vector4D.h>

namespace LevelGenerator
{
	/**
	*	@brief This class stores a triangle.
	*/
	class LG_GEOMETRY_EXPORT LG_Triangle
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Triangle();

		/**
		 *	@brief Constructor with parameters.
		 *	@param LG_Edge* pFirstEdge: The first edge of the triangle.
		 *	@param LG_Edge* pSecondEdge: The second edge of the triangle.
		 *	@param LG_Edge* pThirdEdge: The third edge of the triangle.
		 *	@param int32& iTriangleID: The id of the triangle.
		 */
		LG_Triangle(LG_Edge* pFirstEdge, LG_Edge* pSecondEdge, LG_Edge* pThirdEdge, int32& iTriangleID);

		/**
		 *	@brief Default destructor.
		 */
		~LG_Triangle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var each vertex that makes the triangle.
		 */
		LG_Node* m_pVertices[NODES_PER_TRIANGLE];

		/**
		 *	@var Where we store all of the triangle's edges.
		 */
		LG_Edge* m_pEdges[EDGES_PER_TRIANGLE];

		/**
		 *	@var Where we store the triangle's circumcircle circumference.
		 */
		LG_Circle m_CircumcircleCircumference;

		/**
		 *	@var True when all of the triangles inside of the triangle have already been checked.
		 */
		bool m_bIsChecked;

		/**
		 *	@var An array where we store the intrinsic angles.
		 */
		float m_fAngles[NODES_PER_TRIANGLE];

		/**
		 *	@var The triangle's ID.
		 */
		int32 m_iID;

		/**
		 *	@var The indiex of the three nodes in the triangle.
		 */
		int32 m_NodeIndex[INDEX_PER_TRIANGLE];

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param LG_Node* pFirstNode: The first node of the triangle.
		 *	@param LG_Node* pSecondNode: The second node of the triangle.
		 *	@param LG_Node* pThirdNode: The third node of the triangle.
		 */
		void Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);

		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param LG_Edge* pFirstEdge: The first edge of the triangle.
		 *	@param LG_Edge* pSecondEdge: The second edge of the triangle.
		 *	@param LG_Edge* pThirdEdge: The third edge of the triangle.
		 */
		void Init(LG_Edge* pFirstEdge, LG_Edge* pSecondEdge, LG_Edge* pThirdEdge);

		/**
		 *  @brief This function releases memory and clears the variables.
		 */
		void Destroy();

		/**
		 *  @brief This function tells if a given node is inside of the triangle.
		 *	@param LG_Node* pPointToCompare: The point that we want to know if is inside.
		 *	@return true if the node was inside, false otherwise.
		 */
		bool IsPointInside(LG_Node* pPointToCompare);

		/**
		 *	@brief This function compare if the index of the given triangle are the same.
		 *	@param const LG_Triangle& OtherTriangle: The triangle that we want to compare its index. 
		 *	@return true its index are the same, otherwise false.
		 */
		bool CompareIndex(const LG_Triangle& OtherTriangle);

		/**
		 *	@brief This function compare if the index of given nodes are the same.
		 *	@param LG_Node* pFirstNode: The first node that we want to check it ID.
		 *	@param LG_Node* pSecondNode: The second node that we want to check it ID.
		 *	@param LG_Node* pThirdNode: The third node that we want to check it ID.
		 *	@return true if its the same index, otherwise false.
		 */
		bool CompareIndex(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);

		/**
		 *	@brief This function compare if the index of given node with the index of the triangle.
		 *	@param LG_Node* pOtherNode: The node that we want to check it ID.
		 *	@return true if the ID of the given node is the same that one of the triangle index.
		 */
		bool CompareOneIndex(LG_Node* pOtherNode);

		/**
		 *	@brief This function see if it contains a given node.
		 *	@param LG_Edge* EdgeToCompare: the edge that we want to find out if it's in the triangle.
		 *	@return true when the edge was part of the triangle.
		 */
		bool HasEdgeInside(LG_Edge* EdgeToCompare);

		/**
		 *	@brief Calculates the triangle's circumcentre.
		 */
		void CalculateCircumcenter();

		/**
		 *	@brief Calculates the triangle's intrinsic angles.
		 */
		void CalculateAngles();

	private:

		/**
		 *	@brief This function finds the angle between 2 edges.
		 *	@param const LG_Edge& NodeA: The first edge.
		 *	@param const LG_Edge& NodeB: The second edge.
		 *	@return the angle between the vectors.
		 */
		float GetAngle(const LG_Edge& NodeA, const LG_Edge& NodeB);

		/**
		 *  @brief Performs a cross product between the edges.
		 *	@param LG_Node* pNodeToCompare: Node that doesn't belong to the triangle.
		 *	@param LG_Node* pNode1: First node taken from the triangle.
		 *	@param LG_Node* pNode2: Second node taken from the triangle.
		 *	@return The cross product of a 2D vector.
		 */
		float Sign(LG_Node* pNodeToCompare, LG_Node* pNode1, LG_Node* pNode2);

		/**
		 *	@brief This function find the middle point between 2 position.
		 *	@param const LG_Node& NodeA: The first node.
		 *	@param const LG_Node& NodeB: The second node.
		 *	@return the middle point between the given vectors.
		 */
		LG_Vector3D FindMiddlePoint(const LG_Node& NodeA, const LG_Node& NodeB);

		/**
		 *	@brief This function find the middle point between 2 position.
		 *	@param const LG_Vector2D& PositionA: The first position.
		 *	@param const LG_Vector2D& PositionB: The second position.
		 *	@return the middle point between the given vectors.
		 */
		LG_Vector3D FindMiddlePoint(const LG_Vector2D& PositionA, const LG_Vector2D& PositionB);

		/**
		 *	@brief This function find the slope between 2 position.
		 *	@param const LG_Node& NodeA: The first node.
		 *	@param const LG_Node& NodeB: The second node.
		 *	@return the middle point between the given vectors.
		 */
		float FindSlope(const LG_Node& NodeA, const LG_Node& NodeB);

		/**
		 *	@brief This function find the slope between 2 position.
		 *	@param const LG_Vector2D& PositionA: The first position.
		 *	@param const LG_Vector2D& PositionB: The second position.
		 *	@return the middle point between the given vectors.
		 */
		float FindSlope(const LG_Vector2D& PositionA, const LG_Vector2D& PositionB);

		/**
		 *	@brief Generates the triangle's circumcircle circumference.
		 *	@param const LG_Vector3D& Position: The position of center of the circle.
		 */
		void GenerateCircle(const LG_Vector3D& Position);

		///************************************************************************/
		///*					Compound Assignment Operators.				      */
		///************************************************************************/
	public:
		/**
		 *	@brief This operator compares that 2 triangles are the same.
		 *	@param const LG_Triangle& OtherTriangle: The triangle to compare with this.
		 *	@return true if the triangle is the same that this, otherwise false.
		 */
		bool operator==(const LG_Triangle& OtherTriangle) const;
	
	};
}