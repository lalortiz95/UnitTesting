#include "LG_MarchingSquare.h"
#include <LG_Math.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_MarchingSquare::LG_MarchingSquare()
	{
		/// Initialization.
		m_pMap = nullptr;
		m_pTilesWithCase.clear();
		m_pEdgeTiles.clear();
	}

	//! Default destructor.
	LG_MarchingSquare::~LG_MarchingSquare()
	{
		/// Release the memory.
		Destroy();
	}

	//! This function initilize all variables of the class.
	void LG_MarchingSquare::Init(LG_Grid* gridToWorkWith)
	{
		/// Assign memory and initialize the grid.
		m_pMap = gridToWorkWith;
		SetCircles(rand() % 5 + 10);
	}

	//! This function initialize all variables of the class.
	void LG_MarchingSquare::Init(const int32& tilesX, const int32& tilesY)
	{
		Destroy();
		/// Assign memory and initialize the grid.
		m_pMap = new LG_Grid();
		m_pMap->Init(tilesX, tilesY);

		SetCircles();
	}

	//! This function free the memory of the class.
	void LG_MarchingSquare::Destroy()
	{
		/// If the map is not null pointer.
		if (m_pMap != nullptr)
		{
			/// Call it's destroy, and delete de object.
			m_pMap->Destroy();
			delete m_pMap;
			m_pMap = nullptr;
		}
	}

	//! This function is the only one you need to generate marching squares algorithm.
	void LG_MarchingSquare::Run(LG_Grid* pGridToWorkWith)
	{
		/// Initialize the class' variables.
		Init(pGridToWorkWith);
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		/// Flag that indicates if a tile's got at least 1 node set as true.
		/// Meaning it's inside of one circle, and by so it's inserted in the it's list.
		bool bFlag = false;
		///We go through the TileMap, checking each one of it's nodes with a list circles.
		for (int32 i = 0; i < m_pMap->GetTilesX(); ++i)
		{
			for (int32 j = 0; j < m_pMap->GetTilesY(); ++j)
			{
				/// We iterate through every node in the tile.
				for (int32 k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside = IsTilesInsideOfCircles(m_pMap->m_Grid[i][j].m_Nodes[k]);

					/// If one node is true and the tile is not yet in the list, then we insert the tile in te list.
					if (m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside && !bFlag)
						/// Change the flag so that the tile is added to the list.
						bFlag = true;
				}
				///If there was a node set to true, we insert the tile in the list.
				if (bFlag)
				{
					m_pMap->m_Grid[i][j].m_iID = (int32)m_pTilesWithCase.size();
					m_pTilesWithCase.push_back(&m_pMap->m_Grid[i][j]);
				}
				/// Change the flag back to false so that the next tile could get in the list.
				bFlag = false;
			}
		}

		/// Set every tile's case.
		SetTilesCases();
	}

	//! This function is the only one you need to generate marching squares algorithm.
	void LG_MarchingSquare::Run(const int32& iNumTilesX, const int32& iNumTilesY)
	{
		/// Initialize the class' variables.
		Init(iNumTilesX, iNumTilesY);
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		/// Flag that indicates if a tile's got at least 1 node set as true.
		/// Meaning it's inside of one circle, and by so it's inserted in the inside's list.
		bool bFlag = false;
		///We go through the TileMap, checking each one of it's nodes with a list circles.
		for (int32 i = 0; i < m_pMap->GetTilesX(); ++i)
		{
			for (int32 j = 0; j < m_pMap->GetTilesY(); ++j)
			{
				/// We iterate through every node in the tile.
				for (int32 k = 0; k < LG_Tile::NUM_NODES_PER_TILE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside = IsTilesInsideOfCircles(m_pMap->m_Grid[i][j].m_Nodes[k]);

					/// If one node is true and the tile is not yet in the list, then we insert the tile in te list.
					if (m_pMap->m_Grid[i][j].m_Nodes[k].m_bIsInside && !bFlag)
						/// Change the flag so that the tile is added to the list.
						bFlag = true;
				}
				///If there was a node set to true, we insert the tile in the list.
				if (bFlag)
				{
					m_pMap->m_Grid[i][j].m_iID = (int32)m_pTilesWithCase.size();
					m_pTilesWithCase.push_back(&m_pMap->m_Grid[i][j]);
				}
				/// Change the flag back to false so that the next tile could get in the list.
				bFlag = false;
			}
		}

		/// Set every tile's case.
		SetTilesCases();
	}

	//! This function gives every tile a case, depending on it's vertices positions.
	void LG_MarchingSquare::SetTilesCases()
	{
		/// If we have tiles inside of the circles, we give them a case.
		if (m_pTilesWithCase.size() != 0)
		{
			/// We go through the tiles that are inside of the circles.
			for (int32 i = 0; i < m_pTilesWithCase.size(); ++i)
			{
				/// Marching square's case 1.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_1;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pDown,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 2.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_2;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pDown);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 3.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_3;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 4.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_4;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pRight);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 5.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_5;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pLeft,
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pDown);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 6.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_6;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pDown);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 7.
				if (!m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_7;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 8.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_8;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 9.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_9;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pDown);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 10.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_10;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pDown,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 11.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_11;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pUp,
						*m_pTilesWithCase[i]->m_pRight);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 12.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_12;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 13.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_13;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pRight,
						*m_pTilesWithCase[i]->m_pDown);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 14.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					!m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_14;
					/// Assign the lines of the tile.
					m_pTilesWithCase[i]->CreateLine(
						*m_pTilesWithCase[i]->m_pDown,
						*m_pTilesWithCase[i]->m_pLeft);
					m_pEdgeTiles.push_back(m_pTilesWithCase[i]);
					continue;
				}

				/// Marching square's case 15.
				if (m_pTilesWithCase[i]->m_Nodes[0].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[1].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[2].m_bIsInside &&
					m_pTilesWithCase[i]->m_Nodes[3].m_bIsInside)
				{
					/// Assign the case of the current tile.
					m_pTilesWithCase[i]->m_iCase = CASE_15;
					continue;
				}
			}
		}
	}

	//! This function generates a vector of tiles that have cases different than 0.
	bool LG_MarchingSquare::IsTilesInsideOfCircles(const LG_Node& ActualNode)
	{
		/// Stores the distance between a node and the circle's center.
		float fDistance;

		/// We check that there are circles to check with.
		if (0 == m_CircleList.size())
		{
			///If not, we return false.
			return false;
		}

		/// Iterates through the circle list.
		for (int32 i = 0; i < m_CircleList.size(); ++i)
		{
			/// We calculate the distance between the actual node, and all  the circles.
			fDistance = LG_Vector3D::Magnitude(m_CircleList[i].m_Position - ActualNode.m_Position);
			/// Check if it's inside of the actual circle.
			if (fDistance <= m_CircleList[i].m_fRadius)
			{
				/// If that is the case we return true.
				return true;
			}
		}
		///If it wasn't inside of any circle, then the return value is false.
		return false;
	}

	//! This function set a given number of circles.
	void LG_MarchingSquare::SetCircles(const int32& iCircleAmount)
	{
		/// This variable store the actual circle being created.
		LG_Circle NewCircle;
		/// The maximum size the radius could have.
		float fMaxRadius = 0;

		/// We calculate the maximum size available for circle so that is not larger than the grid.
		fMaxRadius = LG_Math::Min((float)m_pMap->m_iWidth / 2, (float)m_pMap->m_iHeight / 2);

		/// We create all the circles calculated previously.
		for (int32 i = 0; i < iCircleAmount; ++i)
		{
			/// This vector stores where will the circle spawn.
			LG_Vector3D SpawnPosition((float)(rand() % m_pMap->m_iWidth), (float)(rand() % m_pMap->m_iHeight), 0);
			/// We calculate a random radius from one to the maximun radius.
			float fTempRadius = (float)(rand() % (int32)fMaxRadius);
			/// Set the position and the radius to the circle.
			NewCircle.Init(SpawnPosition, fTempRadius);
			/// Add the circle in the circles' list.
			m_CircleList.push_back(NewCircle);
		}
	}

	void LG_MarchingSquare::SetCircles()
	{
		/// This variable store the actual circle being created.
		LG_Circle NewCircle;
		/// The maximum size the radius could have.
		float fRadius = 100;

		/// This vector stores where will the circle spawn.
		LG_Vector3D SpawnPosition(50, 50, 0);
		/// Set the position and the radius to the circle.
		NewCircle.Init(SpawnPosition, fRadius);
		/// Add the circle in the circles' list.
		m_CircleList.push_back(NewCircle);

		/// This vector stores where will the circle spawn.
		SpawnPosition = m_pMap->m_MapCenter.m_Position;
		/// Set the position and the radius to the circle.
		NewCircle.Init(SpawnPosition, fRadius);
		/// Add the circle in the circles' list.
		m_CircleList.push_back(NewCircle);

		/// This vector stores where will the circle spawn.
		SpawnPosition = { 150, 500, 0 };
		/// Set the position and the radius to the circle.
		NewCircle.Init(SpawnPosition, fRadius);
		/// Add the circle in the circles' list.
		m_CircleList.push_back(NewCircle);

		/// This vector stores where will the circle spawn.
		SpawnPosition = { 400, 150, 0 };
		/// Set the position and the radius to the circle.
		NewCircle.Init(SpawnPosition, fRadius);
		/// Add the circle in the circles' list.
		m_CircleList.push_back(NewCircle);
	}
}