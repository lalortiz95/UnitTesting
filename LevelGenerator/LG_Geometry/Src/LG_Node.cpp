#include "LG_Node.h"

namespace LevelGenerator
{
	//! Default Constructor.         
	LG_Node::LG_Node()
	{
		Init();
	}

	//! Default Destructor.
	LG_Node::~LG_Node()
	{
		/// Calls the destroy function.
		Destroy();
	}

	//!
	LG_Node::LG_Node(LG_Node * node)
	{
		*this = node;
	}

	//! 
	LG_Node::LG_Node(LG_Vector3D vPosition)
	{
		Init();
		m_Position = vPosition;
	}

	//! 
	LG_Node::LG_Node(float fx, float fy, float fz)
	{
		Init();
		m_Position = { fx, fy, fz };
	}

	//! Initialize resources of the node.
	void LG_Node::Init()
	{
		m_pParentNode = nullptr;
		m_bIsInside = false;
		m_bCanDeleted = true;
		m_bIsChecked = false;
		m_fWeight = 0.0f;
	}

	//! Free and delete memory.
	void LG_Node::Destroy()
	{
		if (m_PointerNodes.size() != 0)
		{
			for (Vector<LG_Node*>::iterator itt = m_PointerNodes.begin(); itt != m_PointerNodes.end(); ++itt)
			{
				*itt = nullptr;
			}
			m_PointerNodes.clear();
		}
	}

	//! This function stops pointing to the given node.
	void LG_Node::StopPointingNode(LG_Node * pNode)
	{
		for (Vector<LG_Node*>::iterator itt = m_PointerNodes.begin(); itt != m_PointerNodes.end(); ++itt)
		{
			if ((*itt) == pNode)
			{
				m_PointerNodes.erase(itt);
				return;
			}
		}
	}

	//! This operator assigns the values from other node to this node.
	LG_Node& LG_Node::operator=(const LG_Node & OtherNode)
	{
		this->m_iID = OtherNode.m_iID;
		this->m_Position = OtherNode.m_Position;
		this->m_bCanDeleted = OtherNode.m_bCanDeleted;
		this->m_bIsInside = OtherNode.m_bIsInside;
		this->m_bIsChecked = OtherNode.m_bIsChecked;
		this->m_fWeight = OtherNode.m_fWeight;
		return *this;
	}

	//! This operator compares that 2 Nodes are the same.
	bool LG_Node::operator==(const LG_Node & OtherNode) const
	{
		/// Return true if the given node is the same that this.
		return ((m_Position == OtherNode.m_Position) &&
			(m_iID == OtherNode.m_iID));
	}

}


