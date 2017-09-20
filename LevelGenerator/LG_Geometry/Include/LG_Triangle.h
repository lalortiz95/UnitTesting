#pragma once

#include "LG_GeometryPrerequisites.h"
#include "LG_Edge.h"
#include "LG_Circle.h"
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
		 *	@brief Default destructor.
		 */
		~LG_Triangle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief each vertex that makes the triangle.
		 */
		LG_Node* m_pVertices[VERTEX_PER_TRIANGLE];

		/**
		 *	@brief Where we store all of the triangle's edges.
		 */
		LG_Edge* m_pEdges[EDGES_PER_TRIANGLE];

		/**
		 *	@brief Where we store the triangle's circumcircle circumference.
		 */
		LG_Circle m_CircumcircleCircumference;

		/**
		 *	@brief True when all of the triangles inside of the triangle have already been checked.
		 */
		bool m_bIsChecked;

		/**
		 *	@brief The triangle's ID.
		 */
		int32 m_iID;

		/**
		 *	@brief The indiex of the three nodes in the triangle.
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
		 *	@brief Calculates the triangle's circumcentre.
		 */
		void CalculateCircumcenter();

	private:

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
		*	@param LG_Node NodeA: The first node.
		*	@param LG_Node NodeB: The second node.
		*	@return the middle point between the given vectors.
		*/
		LG_Vector3D FindMiddlePoint(LG_Node NodeA, LG_Node NodeB);

		/**
		*	@brief This function find the slope between 2 position.
		*	@param LG_Node NodeA: The first node.
		*	@param LG_Node NodeB: The second node.
		*	@return the middle point between the given vectors.
		*/
		float FindSlope(LG_Node NodeA, LG_Node NodeB);

		/**
		*	@brief Generates the triangle's circumcircle circumference.
		*	@param LG_Vector3D Position: The position of center of the circle.
		*/
		void GenerateCircle(LG_Vector3D Position);

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