#include "LG_Door.h"

namespace LevelGenerator
{

	//! Default constructor.
	LG_Door::LG_Door()
	{
		/// Set as 0 the width and height.
		m_fWidth = m_fHeight = 0;

		/// Set the pointers as nullptr.
		m_pFirstPosition = nullptr;
		m_pSecondPosition = nullptr;

		/// Set the ID as 0.
		m_iID = 0;

	}

	//! Parameter constructor.
	LG_Door::LG_Door(LG_Node * pFirstPosition, LG_Node * pSecondPosition)
	{
		/// Set the position of the nodes.
		m_pFirstPosition = pFirstPosition;
		m_pSecondPosition = pSecondPosition;
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
		/// Set as 0 the width and height.
		m_fWidth = m_fHeight = 0;

		/// Set the pointers as nullptr.
		m_pFirstPosition = nullptr;
		m_pSecondPosition = nullptr;

		/// Set the ID as 0.
		m_iID = 0;
	}
}
