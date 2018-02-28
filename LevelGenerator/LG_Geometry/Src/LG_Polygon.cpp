#include "LG_Polygon.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Polygon::LG_Polygon()
	{
	}

	//! Default Destructor.
	LG_Polygon::~LG_Polygon()
	{
	}

	//! 
	void LG_Polygon::Destroy()
	{
	//TODO: Liberar memoria.
	}

	//! This function add a edge to the vector of edges.
	void LG_Polygon::InsertNodeToVector(std::shared_ptr<LG_Node> pNewNode)
	{
		m_pNodeVector.push_back(pNewNode);
	}
}
