#include "LG_Polygon.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Polygon::LG_Polygon()
	{
		m_pNodeVector.clear();
	}

	//! Default Destructor.
	LG_Polygon::~LG_Polygon()
	{
		Destroy();
	}

	//! This function release the memory of the object.
	void LG_Polygon::Destroy()
	{
		/// Repeat this until the vector is empty.
		while (m_pNodeVector.size() != 0)
		{
			m_pNodeVector[m_pNodeVector.size() - 1]->Destroy();
			delete m_pNodeVector[m_pNodeVector.size() - 1];
			m_pNodeVector[m_pNodeVector.size() - 1] = nullptr;
			m_pNodeVector.pop_back();
		}

		m_pNodeVector.clear();
	}

	//! This function add a edge to the vector of edges.
	void LG_Polygon::InsertNodeToVector(LG_Node* pNewNode)
	{
		m_pNodeVector.push_back(pNewNode);
	}
}
