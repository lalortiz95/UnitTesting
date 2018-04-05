#include "LG_Door.h"

namespace LevelGenerator
{

	//! Default constructor.
	LG_Door::LG_Door()
	{

		/// Set the pointers as nullptr.
		m_pFirstPosition = nullptr;
		m_pSecondPosition = nullptr;

	}

	//! Parameter constructor.
	LG_Door::LG_Door(LG_Node * pFirstPosition, LG_Node * pSecondPosition, float fHeight)
	{
		/// Set the position of the nodes.
		m_pFirstPosition = pFirstPosition;
		m_pSecondPosition = pSecondPosition;
		m_pRectDimension = new LG_Rect();
		LG_Vector3D TopLeft, TopRight;
		TopLeft = m_pFirstPosition->m_Position;
		TopRight = m_pSecondPosition->m_Position;
		TopLeft.Z = fHeight;
		TopRight.Z = fHeight;

		m_pRectDimension->Init(TopLeft, TopRight, m_pFirstPosition->m_Position, m_pSecondPosition->m_Position);

	}

	//! Default destructor.
	LG_Door::~LG_Door()
	{
		/// Call the destroy function.
		Destroy();
	}

	//! This function release all the memory of the object.
	void LG_Door::Destroy()
	{
		if (m_pRectDimension != nullptr)
		{
			m_pRectDimension->Destroy();
			delete m_pRectDimension;
			m_pRectDimension = nullptr;
		}

		/// Set the pointers as nullptr.
		m_pFirstPosition = nullptr;
		m_pSecondPosition = nullptr;

	}
}
