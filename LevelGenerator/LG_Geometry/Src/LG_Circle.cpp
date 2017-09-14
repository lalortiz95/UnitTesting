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

	//! Checks if there is a dot inside of the circle.
	bool LG_Circle::IsDotInside(LG_Vector3D dotToCheck)
	{
		/// Generates a new vector between the dot and the circle's position.
		LG_Vector3D Mag = dotToCheck - m_Position;
		/// see if it's inside.
		return (Mag.Magnitude() <= m_fRadius);
	}
}