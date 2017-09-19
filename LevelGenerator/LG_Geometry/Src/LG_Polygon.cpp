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

	//! This function add a edge to the vector of edges.
	void LG_Polygon::InsertEdgeToVector(LG_Edge* EdgeToAdd)
	{
		m_pEdgeVector.push_back(EdgeToAdd);
	}
}
