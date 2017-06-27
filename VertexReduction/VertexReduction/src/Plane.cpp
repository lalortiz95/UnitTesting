#include "Plane.h"

namespace LevelGenerator
{
	//! The Width and height of the plane is assigned, for future references.
	const int  CPlane::SIZE_OF_PLANE = 25;
	//! The constant that define the number of vertices in the plane.
	const int CPlane::NUM_VERTEX_PER_PLANE = 3;

	//! Default constructor.
	CPlane::CPlane()
	{
	}

	//! Default destructor.
	CPlane::~CPlane()
	{
	}


	//! Initializes the variables of the class.
	void CPlane::Init(CVector3D vPosition)
	{

		//! A vector to store each vertex position. Calculated with the width, height, and position of the first vertex.
		CVector3D TempPosition = vPosition;
		//! The position of each vertex is calculated upon the given position.
		//! Whe assign to the first vertex the given position.
		m_Vertices[0].m_Position = TempPosition;
		//! Now we add the width to that position, so that it give us the next vertex position.
		TempPosition.X += SIZE_OF_PLANE;
		//! We assign the new position to the next vertex of the array, no to the right of the last one.
		m_Vertices[1].m_Position = TempPosition;
		//! Now the height is added to the Y component.
		TempPosition.Y += SIZE_OF_PLANE;
		//! That new position is asigned to the next vertex (Bottom right).
		m_Vertices[2].m_Position = TempPosition;
		//! We finally substract the width of the x component.
		TempPosition.X -= SIZE_OF_PLANE;
		//! And we assign that final position to the last vertex (Bottom left).
		m_Vertices[3].m_Position = TempPosition;
	}

	//! This function realeases the memory of the class.
	void CPlane::Destroy()
	{
		/// Release the memory.

	}

	void CPlane::CheckPlaneCase()
	{
		
	}
}
