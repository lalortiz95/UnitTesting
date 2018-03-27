#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Node.h>
#include <LG_Math.h>

namespace LevelGenerator
{
	/**
	 *	@var This class use a path finding Dijkstra.
	 */
	class LG_ALGORITHMS_EXPORT LG_Dijkstra
	{
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

	public:

		/**
		 *	@brief Default Constructor.
		 */
		LG_Dijkstra();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Dijkstra();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var The cloud of nodes.
		 */
		Vector<LG_Node*>* m_pNodesCloud;

		/**
		 *	@var A pointer to the actual node.
		 */
		LG_Node* m_pActualNode;

		/**
		 *	@var The starting node where we will travel.
		 */
		LG_Node* m_pStartNode;

		/**
		 *	@var The node that we want to reach.
		 */
		LG_Node* m_pEndNode;

		/**
		 *	@var Vector to store the distances.
		 */
		Vector<float> m_fDistances;

		/**
		 *	@var Vector of nodes that define the path.
		 */
		Vector<LG_Node*> m_PathNodes;

		/**
		 *	@var Vector of nodes that define the best path.
		 */
		Vector<LG_Node*> m_BesthPath;


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

	public:

		/**
		 *	@brief This function initialize Dijkstra algorithm.
		 *	@param const Vector<LG_Node>& NodeCloud: The cloud of nodes that we want to travel.
		 *	@param LG_Node* pStartNode: The starting node.
		 *	@param LG_Node* pEndNode: The node that we want to reach.
		 */
		void Init(Vector<LG_Node*>* NodeCloud, LG_Node* pStartNode,LG_Node* pEndNode);

		/**
		 *	@brief This function runs the algorithm and finds the shortest path.
		 */
		void Run();

		/**
		 *	@brief This function release all memory used in the object class.
		 */
		void Destroy();

		/**
		 *	@brief This function get the distance between 2 nodes.
		 *	@param LG_Node* pFirstNode: The first node.
		 *	@param LG_Node* pSecondNode: The second node.
		 *	@return the distance between the given nodes.
		 */
		float GetDistance(LG_Node* pFirstNode, LG_Node* pSecondNode);

		/**
		 *	@brief This function set all nodes' flags as false.
		 */
		void SetNodesAsFalse();

		/**
		 *	@brief This function set the new actual node.
		 */
		void SetActualNode();

		/**
		 *	@brief This function check if the iterating node is not in the node's path.
		 *	@param LG_Node* pIteratingNode: The node that we want to check if it is in the node's path.
		 *	@return true if the node is in the path nodes, otherwise false.
		 */
		bool ExistInPathNodes(LG_Node* pIteratingNode);

		/**
		 *	@brief This function restructure the node's path.
		 */
		void RestructurePath();

	};
}

