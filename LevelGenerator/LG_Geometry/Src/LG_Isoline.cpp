#include "LG_Isoline.h"


namespace LevelGenerator
{
	//! Default Constructor.
	LG_Isoline::LG_Isoline()
	{
	}

	//! Default Destructor.
	LG_Isoline::~LG_Isoline()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Isoline::Init()
	{
		Destroy();
	}

	//! This function free all memory of the class.
	void LG_Isoline::Destroy()
	{
		/// Clear the node's vector.
		m_NodeVector.clear();
	}

	//! This function adds a node to the isoline in a given position.
	void LG_Isoline::AddNode(LG_Vector3D Position)
	{
		/// Insert the node in the node's vector.
		m_NodeVector.push_back(LG_Node(Position));
	}
}