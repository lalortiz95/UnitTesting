#include "LG_MarchingSquare.h"
#include <LG_Math.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_MarchingSquare::LG_MarchingSquare()
	{
	}

	//! Default destructor.
	LG_MarchingSquare::~LG_MarchingSquare()
	{
		Destroy();
	}

	//! This function initilize all variables of the class.
	void LG_MarchingSquare::Init()
	{

		m_pMap = new LG_Grid();
		m_pMap->Init(20, 12);
		SetCircles();
	}

	//! This function free the memory of the class.
	void LG_MarchingSquare::Destroy()
	{
		if (m_pMap != nullptr)
		{
			m_pMap->Destroy();
			delete m_pMap;
			m_pMap = nullptr;
		}
	}

	//! This function is the only one you need to generate marching squares algorithm.
	void LG_MarchingSquare::Run()
	{
		Init();
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		/// 
		bool bFlag = false;
		///We go through the TileMap, checking each one of it's nodes with the scalar function of a circle.
		for (int i = 0; i < m_pMap->GetTilesX(); ++i)
		{
			for (int j = 0; j < m_pMap->GetTilesY(); ++j)
			{
				/// We iterate through every node in the tile.
				for (int k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside = IsTilesInsideOfCircles(m_pMap->m_Grid[i][j].m_Nodes[k]);

					/// If one node is true and the tile is not yet in the list, then we insert the tile in te list.
					if (m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside && !bFlag)
						/// Change the flag so that the tile isn't in the list more than once.
						bFlag = true;

				}
				if (bFlag)
					m_pMap->m_pListTilesInside.push_back(&m_pMap->m_Grid[i][j]);
				/// Change the flag back to false so that the next tile could get in the list.
				bFlag = false;
			}
		}
		SetTilesCases();
		m_pMap = m_pMap;
		m_CircleList = m_CircleList;
	}

	//! This function gives every tile a case, depending on it's vertices positions.
	void LG_MarchingSquare::SetTilesCases()
	{
		if (m_pMap->m_pListTilesInside.size() != 0)
		{
			for (int i = 0; i < m_pMap->m_pListTilesInside.size(); ++i)
			{
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_1;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_2;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_3;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_4;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_5;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_6;
					continue;
				}
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_7;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_8;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_9;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_10;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_11;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_12;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_13;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_14;
					continue;
				}
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_15;
					continue;
				}

			}
		}
	}

	//! This function generates a vector of tiles that have cases different than 0.
	bool LG_MarchingSquare::IsTilesInsideOfCircles(LG_Node ActualNode)
	{
		/// Iterates through the circle list.
		for (int i = 0; i < m_CircleList.size(); ++i)
		{
			/// Check if it's inside of the actual circle.
			if (ActualNode.m_Position.Magnitud(m_CircleList[i].m_Position - ActualNode.m_Position) <= m_CircleList[i].m_fRadius)
			{
				/// If that is the case we return true.
				return true;
			}
		}
		return false;
	}

	//! This function set a given number of circles.
	void LG_MarchingSquare::SetCircles()
	{
		/// This variable store the actual circle being created.
		LG_Circle NewCircle;
		/// The maximum size the radius could have.
		float fMaxRadius = 0;
		/// This variable sets a random number of circles.
		int iAmount = rand() % 5 + 10;
		/// We calculate the maximum size available for circle so that is not larger than the grid.
		fMaxRadius = LG_Math::Min((float)m_pMap->m_iWidth / 2, (float)m_pMap->m_iHeight / 2);

		for (int i = 0; i < iAmount; ++i)
		{
			/// This vector stores where will the circle spawn.
			LG_Vector3D SpawnPosition((float)(rand() % m_pMap->m_iWidth), (float)(rand() % m_pMap->m_iHeight), 0);
			/// We calculate a random radius from one to the maximun radius.
			float fTempRadius = rand() % (int)fMaxRadius;
			/// Set the position and the radius to the circle.
			NewCircle.Init(SpawnPosition, fTempRadius);
			/// Add the circle in the circles' list.
			m_CircleList.push_back(NewCircle);
		}
	}
}