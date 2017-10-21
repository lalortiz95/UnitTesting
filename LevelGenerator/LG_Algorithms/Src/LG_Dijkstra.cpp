#include "LG_Dijkstra.h"

namespace LevelGenerator
{
	LG_Dijkstra::LG_Dijkstra()
	{
		m_BesthPath.clear();
		m_PathNodes.clear();
		m_pNodesCloud = nullptr;
		m_pStartNode = nullptr;
		m_pEndNode = nullptr;
		m_pActualNode = nullptr;
	}


	LG_Dijkstra::~LG_Dijkstra()
	{
		Destroy();
	}

	//! This function initialize dijkstra algorithm.
	void LG_Dijkstra::Init(Vector<LG_Node*>* pNodeCloud, LG_Node* pStartNode, LG_Node* pEndNode)
	{
		Destroy();
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
		/// A flag that tells if a node has already been inserted.
		bool bExists = false;
		/// Flag to determinate when a node has the longest distance.
		bool bIsTheLongest = true;

		/// Initialize the first iterator as the begin of the nodes pointer from the start node.
		Vector<LG_Node*>::iterator itt_1 = m_pStartNode->m_PointerNodes.begin();
		/// Init the actual node as the front of the path nodes.
		m_pActualNode = m_PathNodes.front();

		/// End the while when the actual node is the same that the end node.
		while (m_pActualNode != m_pEndNode)
		{
			/// Iterating the actual's pointer nodes to get the smaller distance.
			for (; itt_1 != m_pActualNode->m_PointerNodes.end(); ++itt_1)
			{
				/// Obtain the distance between the actual node and the iterating node.
				fActualDistance = GetDistance(m_pActualNode, (*itt_1));
				fNewDistance = m_pActualNode->m_fWeight + fActualDistance;

				if (ExistInPathNodes((*itt_1)))
				{
					if (fNewDistance < (*itt_1)->m_fWeight)
					{
						/// The weight of the node is determined by the distance between the current and the iterating node plus the weight of the current node.
						(*itt_1)->m_fWeight = fNewDistance;
						(*itt_1)->m_pParentNode = m_pActualNode;
						RestructurePath();
					}
				}

				else
				{
					/// The weight of the node is determined by the distance between the current and the iterating node plus the weight of the current node.
					(*itt_1)->m_fWeight = fNewDistance;
					for (int32 i = 0; i < m_PathNodes.size(); ++i)
					{
						/// Compare what weight is less than the other.
						if ((*itt_1)->m_fWeight < m_PathNodes[i]->m_fWeight)
						{
							/// Set the parent of the iterated node as the actual node.
							(*itt_1)->m_pParentNode = m_pActualNode;
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
						/// Set the parent of the iterated node as the actual node.
						(*itt_1)->m_pParentNode = m_pActualNode;
						/// 
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
			/// Set the new actual node.
			SetActualNode();
			/// Reset the iterator.
			itt_1 = m_pActualNode->m_PointerNodes.begin();
		}

		/// Add the actual node to the best nodes list.
		m_BesthPath.insert(m_BesthPath.begin(), m_pActualNode);
		/// Iterate until we've inserted all of the nodes.
		while (m_pActualNode != m_pStartNode)
		{
			/// insert the parent of the actual node, and change the actual to it's parent.
			m_BesthPath.insert(m_BesthPath.begin(), m_pActualNode->m_pParentNode);
			m_pActualNode = m_pActualNode->m_pParentNode;
		}
	}

	//! This function release all memory used in the object class.
	void LG_Dijkstra::Destroy()
	{

		if(m_BesthPath.size() != 0)
		{
			for (Vector<LG_Node*>::iterator itt = m_BesthPath.begin(); itt != m_BesthPath.end(); ++itt)
			{
				*itt = nullptr;
			}
			m_BesthPath.clear();
		}

		if (m_PathNodes.size() != 0)
		{
			for (Vector<LG_Node*>::iterator itt = m_PathNodes.begin(); itt != m_PathNodes.end(); ++itt)
			{
				*itt = nullptr;
			}
			m_PathNodes.clear();
		}
	
		if (m_pNodesCloud != nullptr)
		{
			m_pNodesCloud = nullptr;
		}

		if (m_pStartNode != nullptr)
		{
			m_pStartNode = nullptr;
		}

		if (m_pEndNode != nullptr)
		{
			m_pEndNode = nullptr;
		}

		if (m_pActualNode != nullptr)
		{
			m_pActualNode = nullptr;
		}
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
			(*m_pNodesCloud)[i]->m_bIsChecked = false;
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
				//m_PathNodes.erase(itt);
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

	//! This function restructure the node's path.
	void LG_Dijkstra::RestructurePath()
	{
		///
		LG_Node* pTemp = nullptr;
		Vector<LG_Node*> TempPathNodes;
		Vector<LG_Node*>::iterator ittErase = m_PathNodes.begin();

		int32 iInitialSize = m_PathNodes.size();
		float fActualWeight = LG_Math::INFINITE_NUM;

		TempPathNodes.resize(0);

		while (TempPathNodes.size() != iInitialSize)
		{
			
			for (Vector<LG_Node*>::iterator itt = m_PathNodes.begin(); itt != m_PathNodes.end(); ++itt)
			{
				if ((*itt)->m_fWeight < fActualWeight)
				{
					fActualWeight = (*itt)->m_fWeight;
					pTemp = (*itt);
					ittErase = itt;
				}
			}
			m_PathNodes.erase(ittErase);
			fActualWeight = LG_Math::INFINITE_NUM;
			TempPathNodes.push_back(pTemp);
		}
		///
		m_PathNodes = TempPathNodes;
	}
}