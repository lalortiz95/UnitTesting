#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Node.h"
#include <LG_Vector4D.h>
#include "LG_Circle.h"

#define NUM_EDGES_PER_TRIANGLE 3

namespace LevelGenerator
{
	/**
	*	@brief This class stores a triangle.
	*/
	class LG_GEOMETRY_EXPORT LG_Triangle
	{
	public:
		/**
		 *	@brief The triangle's edge.
		 */
		class LG_GEOMETRY_EXPORT LG_Edge
		{
		public:
			///************************************************************************/
			///*                            Constructor & Destructor.                 */
			///************************************************************************/

			/**
			 *	@brief Default constructor.
			 */
			LG_Edge();

			/**
			 *	@brief Parameter constructor.
			 *	@param LG_Node* pFirstNode: The first pointer node of the arista.
			 *	@param LG_Node* pSecondNode: The second pointer node of the arista.
			 *	@param int32& EdgeID: The ID for the edge.
			 */
			LG_Edge(LG_Node* FirstNode, LG_Node* SecondNode, int32& EdgeID);

			/**
			 *	@brief Default destructor.
			 */
			~LG_Edge();

			///************************************************************************/
			///*                           Member Variables.		                  */
			///************************************************************************/

			/**
			 *	@brief First node pointer of the edge.
			 */
			LG_Node* m_pFirstNode;

			/**
			 *	@brief Second node pointer of the edge.
			 */
			LG_Node* m_pSecondNode;

			/**
			 *	@brief The edge's magnitude.
			 */
			float m_fDistance;

			/**
			 *	@brief The edge's ID.
			 */
			int32 m_iID;
			///************************************************************************/
			///*                           Class Functions.						      */
			///************************************************************************/

			/**
			 *  @brief This function initialize all variables of the class.
			 *	@param LG_Node* pFirstNode: The first pointer node of the arista.
			 *	@param LG_Node* pSecondNode: The second pointer node of the arista.
			 *	@param int32& EdgeID: The ID for the edge.
			 */
			void Init(LG_Node* pFirstNode, LG_Node* pSecondNode, int32& EdgeID);

			/**
			 *	@brief This function releases memory.
			 */
			void Destroy();

			/**
			 *	@brief This function compare if 2 edges are the same.
			 *	@param LG_Edge* EdgeToCompare: The edge that we want to compare with this.
			 *	@return true if the 2 edges are the same, otherwise false.
			 */
			bool CompareEdges(LG_Edge* EdgeToCompare);

			///************************************************************************/
			///*					Compound Assignment Operators.				      */
			///************************************************************************/

			/**
			 *	@brief This operator assign the values of the given edge in this edge.
			 *	@param LG_Edge& OtherEdge: The edge that we want to assign to this.
			 *	@return This edge with the new values.
			 */
			LG_Edge& operator=(const LG_Edge& OtherEdge);

		};

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
		Vector<LG_Node*> m_pVertices;

		/**
		 *	@brief Where we store all of the triangle's edges.
		 */
		LG_Edge m_Edges[3];

		/**
		 *	@brief Where we store the triangle's circumcenter.
		 */
		LG_Vector3D m_Circumcenter;

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

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param LG_Node* pFirstNode: The first node of the triangle.
		 *	@param LG_Node* pSecondNode: The second node of the triangle.
		 *	@param LG_Node* pThirdNode: The third node of the triangle.
		 *	@param int32& TriangleID: The id for the triangle.
		 *	@param int32& EdgeID: The id for the edge.
		 */
		void Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode, int32& TriangleID, int32& EdgeID);

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
		 *	@brief Calculates the triangle's circumcentre.
		 */
		void CalculateCircumcenter();

		///************************************************************************/
		///*					Compound Assignment Operators.				      */
		///************************************************************************/

		/**
		 *	@brief This operator compares that 2 triangles are the same.
		 *	@param const LG_Triangle& OtherTriangle: The triangle to compare with this.
		 *	@return true if the triangle is the same that this, otherwise false.
		 */
		bool operator==(const LG_Triangle& OtherTriangle) const;

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
		 */
		void GenerateCircle();
	};
}