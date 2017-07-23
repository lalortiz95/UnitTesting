#include "LG_Tile.h"

namespace LevelGenerator
{
	//! The constant that define the size per tile.
	const int32 LG_Tile::SIZE_OF_TILE = 50;
	//! The constant that define the number of nodes in the tile.
	const int32 LG_Tile::NUM_NODES_PER_TILE = 4;

	//! Default constructor.
	LG_Tile::LG_Tile()
	{
		m_pBottomLeft = 
		m_pTopLeft = 
		m_pTopRight = 
		m_pBottomRight = nullptr;
		m_iCase = 0;
	}

	//! Default destructor.
	LG_Tile::~LG_Tile()
	{
	}

	//! Initializes the variables of the class.
	void LG_Tile::Init(LG_Vector3D vPosition)
	{
		//! A vector to store each nodes position. Calculated with the width, height, and position of the first node.
		LG_Vector3D TempPosition = vPosition;

		//! The position of each node is calculated upon the given position.
		//! Whe assign to the first node the given position.
		m_Nodes[0].m_Position = TempPosition;
		m_pTopLeft = &m_Nodes[0];

		//! Now we add the width to that position, so that it give us the next node position.
		TempPosition.X += SIZE_OF_TILE;
		//! We assign the new position to the next node of the array, no to the right of the last one.
		m_Nodes[1].m_Position = TempPosition;
		m_pTopRight = &m_Nodes[1];

		//! Now the height is added to the Y component.
		TempPosition.Y += SIZE_OF_TILE;
		//! That new position is asigned to the next node (Bottom right).
		m_Nodes[2].m_Position = TempPosition;
		m_pBottomRight = &m_Nodes[2];

		//! We finally substract the width of the x component.
		TempPosition.X -= SIZE_OF_TILE;
		//! And we assign that final position to the last node (Bottom left).
		m_Nodes[3].m_Position = TempPosition;
		m_pBottomLeft = &m_Nodes[3];
	}

	//! This function realeases the memory of the class.
	void LG_Tile::Destroy()
	{
		/// Release the memory.
	}

	void LG_Tile::CheckPlaneCase()
	{
	}
}
