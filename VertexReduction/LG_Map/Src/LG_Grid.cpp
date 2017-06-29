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
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Grid::Init(int iPlaneAmoutX, int iPlaneAmoutY)
	{
		/// Stores the width and height in the member variable for future references.
		m_iHeight = iPlaneAmoutX * LG_Tile::SIZE_OF_TILE;
		m_iWidth = iPlaneAmoutY * LG_Tile::SIZE_OF_TILE;

		/// First calculate the number of tiles in x and y axis.
		m_iNumberPlanesX = iPlaneAmoutX;
		m_iNumberPlanesY = iPlaneAmoutY;

		/// Then we assing memory for each tile in x.
		m_Grid = new LG_Tile*[m_iNumberPlanesX];

		/// For each tile in x array, we assing a new tile in y.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			m_Grid[i] = new LG_Tile[m_iNumberPlanesY];

		}

		LG_Vector3D tempVec(0, 0, 0);
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				m_Grid[i][j].Init(tempVec);
				tempVec.Y += LG_Tile::SIZE_OF_TILE;
			}
			tempVec.X += LG_Tile::SIZE_OF_TILE;
		}	

		LG_Vector3D tempPos(0, 0, 0);
		tempPos.X = rand() % m_iWidth;
		tempPos.Y = rand() % m_iHeight;

		float fTempRadius = 100;
		m_Cricle.Init(tempPos, fTempRadius);
	}

	//! This function free all memory and deletes the objects.
	void LG_Grid::Destroy()
	{
		/// If the memory of the array of tiles isn't nullptr.
		if (m_Grid != nullptr)
		{
			for (int i = m_iNumberPlanesX; i > 0; --i)
			{
				for (int j = m_iNumberPlanesY; i > 0; --j)
				{
					/// If the memory of the pointer isn't nullptr.
					if (m_Grid[i] != nullptr)
					{

						m_Grid[i][j].Destroy();
					}
				}
			}
		}
	}

	//! Calls necessary functions to generate the algorithm.
	void LG_Grid::MarchingSquare()
	{
		///We go through the TileMap, checking each one of it's nodes with the scalar function of a circle.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				/// We iterate through every node in the tile.
				for (int k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_Grid[i][j].m_Nodes[k].m_bIsInside = CalculateTileCase(m_Grid[i][j].m_Nodes[k].m_Position);
					
				}
			}
		}

		/// We store the tiles that have at least one of their nodes as true.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				for (int k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					if (m_Grid[i][j].m_Nodes[k].m_bIsInside)
					{
						m_ListTilesInside.push_back(m_Grid[i][j]);
					}
				}
			}
		}
	}
	
	//! This function Calculates each tiles case. It's done comparing a scalar function with each node's position.
	bool LG_Grid::CalculateTileCase(LG_Vector3D vPosition)
	{
		/// Check if the magnitud bettewn the circle position and the position of the nodes is
		/// less than the radius.
		if (vPosition.Magnitud(m_Cricle.m_Position - vPosition) < m_Cricle.m_fRadius)
		{
			/// If that is the case we return true.
			return true;
		}
	
		return false;
	}

	//! This function returns the number of tiles in the grid, in the X axis.
	int LG_Grid::GetTilesX()
	{
		/// The number of tiles in X Axis.
		return m_iNumberPlanesX;
	}

	//! This function returns the number of tiles in the grid, in the Y axis.
	int LG_Grid::GetTilesY()
	{
		/// The number of tiles in Y Axis.
		return m_iNumberPlanesY;
	}
}