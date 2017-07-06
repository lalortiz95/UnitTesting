#include "LG_Circle.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Circle::LG_Circle()
	{

	}

	//!Default destructor.
	LG_Circle::~LG_Circle()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Circle::Init(LG_Vector3D vPosition, float fRadius)
	{
		m_fRadius = fRadius;
		m_Position = vPosition;
	}

	//! This function frees all the memory, and deletes the member variables. 
	void LG_Circle::Destroy()
	{

	}
}