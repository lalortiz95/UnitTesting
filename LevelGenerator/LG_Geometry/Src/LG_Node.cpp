#include "LG_Node.h"

namespace LevelGenerator
{
	/**
	 *	@brief Default Constructor.
	 */
	LG_Node::LG_Node()
	{
		m_bIsInside = false;
		m_bCanDeleted = true;
	}


	/**
	 *	@brief Default Destructor.
	 */
	LG_Node::~LG_Node()
	{
		//! Calls the destroy function.
		Destroy();
	}

	/**
	 *	@brief Parameter Constructor.
	 *	@param LG_Vector3D Is the wanted position for the node.
	 */
	LG_Node::LG_Node(LG_Vector3D vPosition)
	{
		m_Position = vPosition;
		m_bIsInside = false;
		m_bCanDeleted = true;
	}

	/**
	 *	@brief Initialize resources of the node.
	 */
	void LG_Node::Init()
	{
		m_bIsInside = false;
		m_bCanDeleted = true;
	}


	/**
	 *	@brief Free and delete memory.
	 */
	void LG_Node::Destroy()
	{

	}

	//! This operator assigns the values from other node to this node.
	LG_Node& LG_Node::operator=(const LG_Node & OtherNode)
	{
		this->m_bCanDeleted = OtherNode.m_bCanDeleted;
		this->m_bIsInside = OtherNode.m_bIsInside;
		this->m_iID = OtherNode.m_iID;
		this->m_Position = OtherNode.m_Position;
		return *this;
	}

}

