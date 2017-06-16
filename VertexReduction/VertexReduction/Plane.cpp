#include "Plane.h"


//! Default constructor.
CPlane::CPlane()
{
}

//! Default destructor.
CPlane::~CPlane()
{
}

//! Initializes the variables of the class.
void CPlane::Init(CVector3D vPosition, float fWidth, float fHeight)
{
	//! The Width and height of the plane is assigned, for future references.
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//! Give every Vertex on the array a position and index.
	for (int i = 0; i < 4; ++i)
	{
		m_Vertices[i].m_iID = i;
	}

	//! A vector to store each vertex position. Calculated with the width, height, and position of the first vertex.
	CVector3D TempPosition = vPosition;
	//! The position of each vertex is calculated upon the given position.
	//! Whe assign to the first vertex the given position.
	m_Vertices[0].m_Position = vPosition;
	//! Now we add the width to that position, so that it give us the next vertex position.
	TempPosition.X += fWidth;
	//! We assign the new position to the next vertex of the array, no to the right of the last one.
	m_Vertices[1].m_Position = TempPosition;
	//! Now the height is added to the Y component.
	TempPosition.Y += fHeight;
	//! That new position is asigned to the next vertex (Bottom right).
	m_Vertices[2].m_Position = TempPosition;
	//! We finally substract the width of the x component.
	TempPosition.X -= fWidth;
	//! And we assign that final position to the last vertex (Bottom left).
	m_Vertices[3].m_Position = TempPosition;
}
