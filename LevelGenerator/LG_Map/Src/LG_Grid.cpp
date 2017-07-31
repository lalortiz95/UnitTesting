#include "LG_Grid.h"
#include <random>

namespace LevelGenerator
{
	//! Default constructor.
	LG_Grid::LG_Grid()
	{

	}

	//! Default destructor.
	LG_Grid::~LG_Grid()
	{
		/// Releases the memory.
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Grid::Init(int32 iPlaneAmoutX, int32 iPlaneAmoutY)
	{
		Destroy();
		/// Stores the width and height in the member variable for future references.
		m_iHeight = iPlaneAmoutX * LG_Tile::SIZE_OF_TILE;
		m_iWidth = iPlaneAmoutY * LG_Tile::SIZE_OF_TILE;

		/// Set the center of the grid.
		LG_Vector3D CenterPosition((float)(m_iWidth / 2), (float)(m_iHeight / 2), 0);
		m_MapCenter.m_Position = CenterPosition;

		/// First calculate the number of tiles in x and y axis.
		m_iNumberPlanesX = iPlaneAmoutX;
		m_iNumberPlanesY = iPlaneAmoutY;

		/// Then we assing memory for each tile in x.
		m_Grid = new LG_Tile*[m_iNumberPlanesX];
		LG_Vector3D SpawnPosition(0, 0, 0);
		for (int32 i = 0; i < m_iNumberPlanesX; ++i)
		{
			/// For each tile in x array, we assing a new tile in y.
			m_Grid[i] = new LG_Tile[m_iNumberPlanesY];
			for (int32 j = 0; j < m_iNumberPlanesY; ++j)
			{
				/// Initialization of each tile in the grid.
				m_Grid[i][j].Init(SpawnPosition);
				/// Adds the size of the tile to the Y position.
				SpawnPosition.Y += LG_Tile::SIZE_OF_TILE;
			}
			/// Restart the position in y axis.
			SpawnPosition.Y = 0;
			/// Adds the size of the tile to set the position in the next column of the grid. 
			SpawnPosition.X += LG_Tile::SIZE_OF_TILE;
		}	
	}

	//! This function free all memory and deletes the objects.
	void LG_Grid::Destroy()
	{
		/// If the memory of the array of tiles isn't nullptr.
		if (m_Grid != nullptr)
		{
			for (int32 i = m_iNumberPlanesX; i > 0; --i)
			{
				for (int32 j = m_iNumberPlanesY; i > 0; --j)
				{
					/// If the memory of the pointer isn't nullptr.
					if (m_Grid[i] != nullptr)
					{
						/// Releases the memory.
						m_Grid[i][j].Destroy();
					}
				}
			}
		}
	}

	//! This function returns the number of tiles in the grid, in the X axis.
	int32 LG_Grid::GetTilesX()
	{
		/// The number of tiles in X Axis.
		return m_iNumberPlanesX;
	}

	//! This function returns the number of tiles in the grid, in the Y axis.
	int32 LG_Grid::GetTilesY()
	{
		/// The number of tiles in Y Axis.
		return m_iNumberPlanesY;
	}
}