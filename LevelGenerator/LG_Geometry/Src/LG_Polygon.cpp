#include "LG_Polygon.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Polygon::LG_Polygon()
	{
		m_bIsCorner = false;
	}

	//! Default Destructor.
	LG_Polygon::~LG_Polygon()
	{
		Destroy();
	}

	//! 
	void LG_Polygon::Destroy()
	{
		m_bIsCorner = false;
	}

	//! This function add a edge to the vector of edges.
	void LG_Polygon::InsertNodeToVector(std::shared_ptr<LG_Node> pNewNode)
	{
		m_pNodeVector.push_back(pNewNode);
	}
}
