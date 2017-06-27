#include "Circle.h"

namespace LevelGenerator
{
	//! Default constructor.
	CCircle::CCircle()
	{

	}

	//!Default destructor.
	CCircle::~CCircle()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LevelGenerator::CCircle::Init(CVector3D vPosition, float fRadius)
	{
		m_fRadius = fRadius;
		m_Position = vPosition;
	}

	//! This function frees all the memory, and deletes the member variables. 
	void LevelGenerator::CCircle::Destroy()
	{

	}
}