#include "LG_Dijkstra.h"

namespace LevelGenerator
{
	LG_Dijkstra::LG_Dijkstra()
	{
	}


	LG_Dijkstra::~LG_Dijkstra()
	{
	}

	//! This function initialize dijkstra algorithm.
	void LG_Dijkstra::Init(Vector<LG_Node>* pNodeCloud, LG_Node* pStartNode, LG_Node* pEndNode)
	{
		m_pNodesCloud = pNodeCloud;
		m_pStartNode = pStartNode;
		m_pActualNode = m_pStartNode;
		m_pEndNode = pEndNode;
		SetNodesAsFalse();
		m_PathNodes.push_back(m_pStartNode);
	}

	//! This function runs the algorithm and finds the shortest path.
	void LG_Dijkstra::Run()
	{
		/// The actual distance.
		float fActualDistance;
		/// The new distance.
		float fNewDistance = 0;
		/// The old weight of the node.
		float fOldWeight = 0;

		/// Flag to determinate when a node has the longest distance.
		bool bIsTheLongest = true;

		/// Initialize the first iterator as the begin of the nodes pointer from the start node.
		Vector<LG_Node*>::iterator itt_1 = m_pStartNode->m_PointerNodes.begin();
		/// Init the actual node as the front of the path nodes.
		m_pActualNode = m_PathNodes.front();
		/// Init the actual distance.
		fActualDistance = m_pActualNode->m_fWeight;

		/// End the while when the actual node is the same that the end node.
		while (m_pActualNode != m_pEndNode)
		{
			/// Iterating the actual's pointer nodes to get the smaller distance.
			for (; itt_1 != m_pActualNode->m_PointerNodes.end(); ++itt_1)
			{
				/// Obtain the distance between the actual node and the iterating node.
				fNewDistance = GetDistance(m_pActualNode, (*itt_1));
				/// The weight of the node is determined by the distance between the current and the iterating node plus the weight of the current node.
				(*itt_1)->m_fWeight = m_pActualNode->m_fWeight + fNewDistance;

				if (fNewDistance < fActualDistance)
				{
					/// Actualize as the new distance.
					fActualDistance = fNewDistance;
					/// Insert the node at the begin of the vector.
					m_PathNodes.insert(m_PathNodes.begin(), *itt_1);
				}

				else
				{

					/// Iterating the path nodes.
					for (int32 i = 0; i < m_PathNodes.size(); ++i)
					{
						/// Compare what weight is less than the other.
						if ((*itt_1)->m_fWeight < m_PathNodes[i]->m_fWeight)
						{
							/// Insert the first iterator before the second iterator, because the first is smaller.
							m_PathNodes.insert(m_PathNodes.begin() + i, *itt_1);
							/// Change the flag to determinate that this node isn't the longest distance.
							bIsTheLongest = false;
							/// End the for.
							break;
						}
					}


					/// If this flag is true, insert the node at the end of the vector.
					if (bIsTheLongest)
					{
						m_PathNodes.push_back(*itt_1);
					}
					/// Otherwise reset the flag.
					else
					{
						bIsTheLongest = true;
					}
				}

			}
			/// Set the actual node as checked.
			m_pActualNode->m_bIsChecked = true;
			/// Insert the actual node to the best path.
			m_BesthPath.push_back(m_pActualNode);
			/// Set the new actual node.
			SetActualNode();
			/// Reset the iterator.
			itt_1 = m_pActualNode->m_PointerNodes.begin();
		}
	}

	//! This function release all memory used in the object class.
	void LG_Dijkstra::Destroy()
	{
	}

	//! This function get the distance between 2 nodes.
	float LG_Dijkstra::GetDistance(LG_Node * pFirstNode, LG_Node * pSecondNode)
	{
		/// Calculate the distance of 2 nodes, and return it.
		LG_Vector3D Direction = pSecondNode->m_Position - pFirstNode->m_Position;
		return Direction.Magnitude();
	}

	//! This function set all nodes' flags as false.
	void LG_Dijkstra::SetNodesAsFalse()
	{
		for (int32 i = 0; i < m_pNodesCloud->size(); ++i)
		{
			(*m_pNodesCloud)[i].m_bIsChecked = false;
		}
	}

	//! This function set the new actual node.
	void LG_Dijkstra::SetActualNode()
	{
		/// Find the new actual node.
		for (Vector<LG_Node*>::iterator itt = m_PathNodes.begin(); itt != m_PathNodes.end(); ++itt)
		{
			if (!(*itt)->m_bIsChecked)
			{
				/// Asign the new actual node.
				m_pActualNode = (*itt);
				m_PathNodes.erase(itt);
				/// End the for.
				break;
			}
		}
	}

	//! This function check if the iterating node is not in the path nodes.
	bool LG_Dijkstra::ExistInPathNodes(LG_Node * pIteratingNode)
	{
		/// Iterating the path nodes to find the node given.
		for (int32 i = 0; i < m_PathNodes.size(); ++i)
		{
			/// If the iterating node is the same that the given node.
			if (m_PathNodes[i] == pIteratingNode)
				return true;
		}
		/// If not find the given node return false.
		return false;
	}
}