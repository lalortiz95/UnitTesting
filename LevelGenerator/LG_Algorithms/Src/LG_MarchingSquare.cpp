#include "LG_MarchingSquare.h"
#include <LG_Math.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_MarchingSquare::LG_MarchingSquare()
	{
		/// Initialization.
		m_pMap = nullptr;
	}

	//! Default destructor.
	LG_MarchingSquare::~LG_MarchingSquare()
	{
		/// Release the memory.
		Destroy();
	}

	//! This function initilize all variables of the class.
	void LG_MarchingSquare::Init()
	{
		/// Assign memory and initialize the grid.
		m_pMap = new LG_Grid();
		m_pMap->Init(20, 12);
		/// Calculates how many circles there will be, which what sizes, and in which positions.
		SetCircles();
	}

	//! This function initialize all variables of the class.
	void LG_MarchingSquare::Init(float fRadius, LG_Vector3D position, int tilesX, int tilesY)
	{
		/// Assign memory and initialize the grid.
		m_pMap = new LG_Grid();
		m_pMap->Init(tilesX, tilesY);

		SetCircle(fRadius, position);
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
	void LG_MarchingSquare::Run()
	{
		/// Initialize the class' variables.
		Init();
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		/// Flag that indicates if a tile's got at least 1 node set as true.
		/// Meaning it's inside of one circle, and by so it's inserted in the it's list.
		bool bFlag = false;
		///We go through the TileMap, checking each one of it's nodes with a list circles.
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
						/// Change the flag so that the tile is added to the list.
						bFlag = true;
				}
				///If there was a node set to true, we insert the tile in the list.
				if (bFlag)
					m_pMap->m_pListTilesInside.push_back(&m_pMap->m_Grid[i][j]);
				/// Change the flag back to false so that the next tile could get in the list.
				bFlag = false;
			}
		}

		/// Set every tile's case.
		SetTilesCases();
	}

	//! This function is the only one you need to generate marching squares algorithm.
	void LG_MarchingSquare::Run(float fRadius, LG_Vector3D position, int iNumTilesX, int iNumTilesY)
	{
		/// Initialize the class' variables.
		Init(fRadius, position, iNumTilesX, iNumTilesY);
		///We see that the grid's got valid information.
		if (m_pMap == nullptr)	return;

		/// Flag that indicates if a tile's got at least 1 node set as true.
		/// Meaning it's inside of one circle, and by so it's inserted in the it's list.
		bool bFlag = false;
		///We go through the TileMap, checking each one of it's nodes with a list circles.
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
						/// Change the flag so that the tile is added to the list.
						bFlag = true;
				}
				///If there was a node set to true, we insert the tile in the list.
				if (bFlag)
					m_pMap->m_pListTilesInside.push_back(&m_pMap->m_Grid[i][j]);
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
		if (m_pMap->m_pListTilesInside.size() != 0)
		{
			/// We go through the tiles that are inside of the circles.
			for (int i = 0; i < m_pMap->m_pListTilesInside.size(); ++i)
			{
				/// Marching square's case 1.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_1;
					continue;
				}

				/// Marching square's case 2.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_2;
					continue;
				}

				/// Marching square's case 3.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_3;
					continue;
				}

				/// Marching square's case 4.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_4;
					continue;
				}

				/// Marching square's case 5.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_5;
					continue;
				}

				/// Marching square's case 6.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_6;
					continue;
				}

				/// Marching square's case 7.
				if (!m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_7;
					continue;
				}

				/// Marching square's case 8.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_8;
					continue;
				}

				/// Marching square's case 9.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_9;
					continue;
				}

				/// Marching square's case 10.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_10;
					continue;
				}

				/// Marching square's case 11.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_11;
					continue;
				}

				/// Marching square's case 12.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_12;
					continue;
				}

				/// Marching square's case 13.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_13;
					continue;
				}

				/// Marching square's case 14.
				if (m_pMap->m_pListTilesInside[i]->m_Nodes[0].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[1].m_bIsInside &&
					m_pMap->m_pListTilesInside[i]->m_Nodes[2].m_bIsInside &&
					!m_pMap->m_pListTilesInside[i]->m_Nodes[3].m_bIsInside)
				{
					m_pMap->m_pListTilesInside[i]->m_iCase = CASE_14;
					continue;
				}

				/// Marching square's case 15.
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
		/// Stores the distance between a node and the circle's center.
		float fDistance;

		/// We check that there are circles to check with.
		if (m_CircleList.size() <= 0)
		{
			///If not, we return false.
			return false;
		}

		/// Iterates through the circle list.
		for (int i = 0; i < m_CircleList.size(); ++i)
		{
			/// We calculate the distance between the actual node, and all  the circles.
			fDistance = ActualNode.m_Position.Magnitude(m_CircleList[i].m_Position - ActualNode.m_Position);
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

		/// We create all the circles calculated previously.
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

	//! This function set a random number of circles.
	void LG_MarchingSquare::SetCircle(float fRadius, LG_Vector3D position)
	{

		/// This variable store the actual circle being created.
		LG_Circle NewCircle;

		/// We initialize our new circle.
		NewCircle.Init(position, fRadius);
		/// We add it to the circle list.
		m_CircleList.push_back(NewCircle);
	}
}