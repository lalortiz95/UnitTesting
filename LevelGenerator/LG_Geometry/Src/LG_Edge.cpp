#include "LG_Edge.h"


namespace LevelGenerator
{
	//! Default constructor.
	LG_Edge::LG_Edge()
	{
		m_pFirstNode = nullptr;
		m_pSecondNode = nullptr;
		m_bIsChecked = false;
		m_fDistance = 0.0f;
	}

	//! Parameter constructor.
	LG_Edge::LG_Edge(LG_Node* pFirstNode, LG_Node* pSecondNode, int32& EdgeID)
	{
		Init(pFirstNode, pSecondNode);
		m_iID = EdgeID;
		++EdgeID;

		/// Calculate the magnitude of the arista, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! Default destructor.
	LG_Edge::~LG_Edge()
	{
		//Destroy();
	}

	//! This function initialize the variables in the edge class.
	void LG_Edge::Init(LG_Node* pFirstNode, LG_Node* pSecondNode)
	{
		bool bNodeIsTheSame = false;
		//Destroy();

		/// We assign the nodes.
		m_pFirstNode = pFirstNode;
		m_pSecondNode = pSecondNode;


		m_NodeIndex[FIRST_INDEX] = m_pFirstNode->m_iID;
		m_NodeIndex[SECOND_INDEX] = m_pSecondNode->m_iID;
		
		/// Assign the pointer of every node of the edge.
		for (int32 i = 0; i < m_pFirstNode->m_PointerNodes.size(); ++i)
		{
			if (m_pSecondNode == m_pFirstNode->m_PointerNodes[i])
			{
				bNodeIsTheSame = true;
			}
		}

		if (!bNodeIsTheSame)
		{
			m_pFirstNode->m_PointerNodes.push_back(m_pSecondNode);
			bNodeIsTheSame = false;
		}
		///Assign the pointer of every node of the edge.
		for (int32 i = 0; i < m_pSecondNode->m_PointerNodes.size(); ++i)
		{
			if (m_pFirstNode == m_pSecondNode->m_PointerNodes[i])
			{
				bNodeIsTheSame = true;
			}
		}
		if (!bNodeIsTheSame)
		{
			m_pSecondNode->m_PointerNodes.push_back(m_pFirstNode);
		}

		/// Calculate the magnitude of the edge, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! This function realeases memory.
	void LG_Edge::Destroy()
	{
		/// If the pointer is not nullptr.
		if (m_pFirstNode != nullptr)
		{
			/// Call it's destroy function to release memory of it's variables.
			m_pFirstNode->Destroy();
			/// Release memory.
			delete m_pFirstNode;
			/// Reset to nullptr.
			m_pFirstNode = nullptr;
		}

		if (m_pSecondNode != nullptr)
		{
			/// Call it's destroy function to release memory of it's variables.
			m_pSecondNode->Destroy();
			/// Release memory.
			delete m_pSecondNode;
			/// Reset to nullptr.
			m_pSecondNode = nullptr;
		}
		/// Reset the distance of the edges.
		m_fDistance = 0.0f;
	}

	//! This function compare if 2 edges are the same.
	bool LG_Edge::CompareEdges(const LG_Edge&  EdgeToCompare)
	{
		return ((m_pFirstNode == EdgeToCompare.m_pFirstNode ||
			m_pFirstNode == EdgeToCompare.m_pSecondNode) &&
			(m_pSecondNode == EdgeToCompare.m_pFirstNode ||
				m_pSecondNode == EdgeToCompare.m_pSecondNode));
	}

	//! This function compare if the index of the given edge are the same.
	bool LG_Edge::CompareIndex(const LG_Edge & OtherEdge)
	{
		return (((m_NodeIndex[FIRST_INDEX] == OtherEdge.m_NodeIndex[FIRST_INDEX]) ||
			(m_NodeIndex[FIRST_INDEX] == OtherEdge.m_NodeIndex[SECOND_INDEX])) &&
			((m_NodeIndex[SECOND_INDEX] == OtherEdge.m_NodeIndex[FIRST_INDEX]) ||
			(m_NodeIndex[SECOND_INDEX] == OtherEdge.m_NodeIndex[SECOND_INDEX])));
	}

	bool LG_Edge::CompareOneIndex(LG_Node* pOtherNode)
	{
		return ((m_NodeIndex[FIRST_INDEX] ==  pOtherNode->m_iID) ||
			(m_NodeIndex[SECOND_INDEX] == pOtherNode->m_iID));
	}

	//! This function chanfge the values of the edge.
	void LG_Edge::Legalize()
	{
		/// Assign the pointer of every node of the edge.
		for (Vector<LG_Node*>::iterator itt = m_pFirstNode->m_PointerNodes.begin(); itt != m_pFirstNode->m_PointerNodes.end(); ++itt)
		{
			if ((*itt) == m_pSecondNode)
			{
				LG_Node* pTemp = *itt;
				m_pFirstNode->m_PointerNodes.erase(itt);
				pTemp = nullptr;
				break;
			}
		}

		for (Vector<LG_Node*>::iterator itt = m_pSecondNode->m_PointerNodes.begin(); itt != m_pSecondNode->m_PointerNodes.end(); ++itt)
		{
			if ((*itt) == m_pFirstNode)
			{
				LG_Node* pTemp = *itt;
				m_pSecondNode->m_PointerNodes.erase(itt);
				pTemp = nullptr;
				break;
			}
		}
	}

	//! This operator assign the values of the given edge in this edge.
	LG_Edge& LG_Edge::operator=(const LG_Edge& OtherEdge)
	{
		m_fDistance = OtherEdge.m_fDistance;
		m_pFirstNode = OtherEdge.m_pFirstNode;
		m_pSecondNode = OtherEdge.m_pSecondNode;
		m_NodeIndex[FIRST_INDEX] = OtherEdge.m_NodeIndex[FIRST_INDEX];
		m_NodeIndex[SECOND_INDEX] = OtherEdge.m_NodeIndex[SECOND_INDEX];
		return *this;
	}
}