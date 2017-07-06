#include "LG_Node.h"

namespace LevelGenerator
{
	/**
	 *	@brief Default Constructor.
	 */
	LG_Node::LG_Node()
	{
		m_bIsInside = false;
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
	}

	/**
	 *	@brief Initialize resources of the node.
	 */
	void LG_Node::Init()
	{
	}


	/**
	 *	@brief Free and delete memory.
	 */
	void LG_Node::Destroy()
	{
	}

}


