#include "LG_MarchingSquare.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_MarchingSquare::LG_MarchingSquare()
	{
	}

	//! Default destructor.
	LG_MarchingSquare::~LG_MarchingSquare()
	{
	}

	//! This function initilize all variables of the class.
	void LG_MarchingSquare::Init()
	{

	}

	//! This function free the memory of the class.
	void LG_MarchingSquare::Destroy()
	{

	}

	//! This function is the only one you need to generate marching squares algorithm.
	void LG_MarchingSquare::Run()
	{
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		///We go through the TileMap, checking each one of it's nodes with the scalar function of a circle.
		for (int i = 0; i < m_pMap->GetTilesX(); ++i)
		{
			for (int j = 0; j < m_pMap->GetTilesY(); ++j)
			{
				/// We iterate through every node in the tile.
				for (int k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside = GenerateTileCase(m_pMap->m_Grid[i][j].m_Nodes[k].m_Position);

				}
			}
		}
	}

	//! This function gives every tile a case, depending on it's vertices positions.
	bool LG_MarchingSquare::GenerateTileCase(LG_Vector3D vPosition)
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

	//! This function generates a vector of tiles that have cases different than 0.
	void LG_MarchingSquare::SetTilesInsideOfScalarFunction()
	{
		/// We store the tiles that have at least one of their nodes as true.
		for (int i = 0; i < m_pMap->GetTilesX(); ++i)
		{
			for (int j = 0; j < m_pMap->GetTilesY(); ++j)
			{
				for (int k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					if (m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside)
					{
						//TODO: checar que el nodo no esté adentro ya.
						m_pMap->m_ListTilesInside.push_back(m_pMap->m_Grid[i][j]);
					}
				}
			}
		}
	}
}