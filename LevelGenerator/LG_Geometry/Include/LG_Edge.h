#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{
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
		 *	@brief This flag is used to determinate when a edge is checked.
		 */
		bool m_bIsChecked;

		/**
		 *	@brief This flag is used to determinate when a edge is legal. That comes in handy when working with DT.
		 */
		bool m_bIsLegal;

		/**
		 *	@brief The edge's ID.
		 */
		int32 m_iID;

		/**
		 *	@brief The indiex of the both nodes in the edge.
		 */
		int32 m_NodeIndex[INDEX_PER_EDGE];

		///************************************************************************/
		///*                           Class Functions.						      */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param LG_Node* pFirstNode: The first pointer node of the arista.
		 *	@param LG_Node* pSecondNode: The second pointer node of the arista.
		 */
		void Init(LG_Node* pFirstNode, LG_Node* pSecondNode);

		/**
		 *	@brief This function releases memory.
		 */
		void Destroy();

		/**
		 *	@brief This function compare if 2 edges are the same.
		 *	@param const LG_Edge& EdgeToCompare: The edge that we want to compare with this.
		 *	@return true if the 2 edges are the same, otherwise false.
		 */
		bool CompareEdges(const LG_Edge& EdgeToCompare);

		/**
		 *	@brief This function compare if the index of the given edge is the same.
		 *	@param const LG_Edge& OtherEdge: The edge that contains the index that we want to compare.
		 *	@return true its index are the same, otherwise false.
		 */
		bool CompareIndex(const LG_Edge& OtherEdge);

		/**
		 *	@brief This function compare if one index of the given edge is the same.
		 *	@param LG_Node* pOtherEdge: The node that we want to compare.
		 *	@return true its index is the same, otherwise false.
		 */
		bool CompareOneIndex(LG_Node* pOtherEdge);

		/**
		 *	@brief This function change the values of the edge.
		 */
		void Legalize();

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
}

