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
	}

	//! This function initialize all variables of the class.
	void LG_Isoline::Init()
	{
		m_NodeList.clear();
	}

	//! This function free all memory of the class.
	void LG_Isoline::Destroy()
	{

	}

	//! This function adds a node to the isoline in a given position.
	void LG_Isoline::AddNode(LG_Vector3D Position)
	{
		m_NodeList.push_back(LG_Node(Position));
		m_NodeVector.push_back(LG_Node(Position));
	}
}