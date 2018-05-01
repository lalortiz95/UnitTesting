#include "LG_Wall.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Wall::LG_Wall()
	{
		m_pRect = new LG_Rect();
	}

	//! Parameter Constructor.
	//LG_Wall::LG_Wall(LG_Node CenterNode, float fWidth, float fHeight)
	//{
	//	Init(CenterNode, fWidth, fHeight);
	//}

	//! Default destructor.
	LG_Wall::~LG_Wall()
	{
		Destroy();
	}

	//!
	//void LG_Wall::Init(LG_Node CenterNode, float fWidth, float fHeight)
	//{
	//	m_pWall = new LG_Rect(CenterNode, fWidth, fHeight);
	//}

	void LG_Wall::Destroy()
	{
		if (m_pRect != nullptr)
		{
			m_pRect->Destroy();
			delete m_pRect;
			m_pRect = nullptr;
		}
	}
}