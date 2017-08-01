#include "LG_Line.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Line::LG_Line()
	{
		m_bIsInside = false;
	}

	//! Default Destructor.
	LG_Line::~LG_Line()
	{
		Destroy();
	}

	//! This function initialize the member variables.
	void LG_Line::Init()
	{
		
	}

	//! This function releases memory and resources.
	void LG_Line::Destroy()
	{
		m_bIsInside = false;
	}
}