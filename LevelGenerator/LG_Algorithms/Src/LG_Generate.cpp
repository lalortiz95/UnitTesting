#include "LG_Generate.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Generate::LG_Generate()
	{

	}

	//! Default destructor.
	LG_Generate::~LG_Generate()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Generate::Initialize()
	{
		/// A map to work with for our marching square algorithm.
		m_pMap = new LG_Grid();
		m_pMap->Init(20, 12);
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{

	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run()
	{
		//TODO: with the generated cases make an isoiline.
		//we apply then, RDP algorithm to reduce that isoloine.
		//Now we have a reduced set of points, that will be used to 
		//Generate delaunay triangulation.

		/// Initialize the variables.
		Initialize();
		/// The position where the circle will spawn.
		LG_Vector3D posToSpawnCircle = { 275, 275, 0 };

		/// We run marching square with the generated grid.
		m_MS.Run(50, posToSpawnCircle, 10, 10);

		/// Stores either a node that shares a position with the actual tile.
		LG_Node ActualNode;
		/// To have a more readable code.
		m_TileVector = m_MS.m_pMap->m_pListTilesInside;

		LG_Isoline ActualIsoline;

		bool bAreNewIsoline = false;
		bool bQuit = false;
		int32 iActualTile = 0;

		/// A cycle to generate an isoline upon the MS cases.
		while (!bQuit)
		{
			/// See if the current tile have not been checked.
			if (!m_TileVector[iActualTile]->m_bIsChecked)
			{
				/// Go through the lines of each tile.
				for (int32 j = 0; j < m_TileVector[iActualTile]->m_LinesVector.size(); ++j)
				{
					/// Make sure that the iterating line have not been inserted yet.
					if (!m_TileVector[iActualTile]->m_LinesVector[j].m_bIsInside)
					{
						/// Set which one is the next actual tile. The one that shares position.
						iActualTile = CompareTilesPosition(m_TileVector[iActualTile]->m_LinesVector[j], ActualIsoline, iActualTile);
					}
					/// If no node shared position.
					if (iActualTile == ERROR_CODE)
					{
						/// Sets the new actual tile.
						for (int32 i = 0; i < m_TileVector.size(); ++i)
						{
							if (!m_TileVector[i]->m_bIsChecked)
							{
								iActualTile = i;
								break;
							}
						}
						/// Go through the lines of the new actual tile.
						for (int k = 0; k < m_TileVector[iActualTile]->m_LinesVector.size(); ++k)
						{
							///Insert it's nodes to the isoline.
							ActualIsoline.AddNode(m_TileVector[iActualTile]->m_LinesVector[k].m_Nodes[0].m_Position);
							ActualIsoline.AddNode(m_TileVector[iActualTile]->m_LinesVector[k].m_Nodes[1].m_Position);
							if (k + 1 == m_TileVector[iActualTile]->m_LinesVector.size())
							{
								/// Set it's tile flag.
								m_TileVector[iActualTile]->m_bIsChecked = true;
							}
						}
						/// Add the isoline to the isoline vector.
						m_IsolineVector.push_back(ActualIsoline);
						/// Clear the isoline so that it starts to fill the next one in the same variable.
						ActualIsoline.Init();
					}
				}
			}

			int32 AmountOfTilesInside = 0;
			for (int32 i = 0; i < m_TileVector.size(); ++i)
			{
				if (m_TileVector[i]->m_bIsChecked)
				{
					++AmountOfTilesInside;
					if (AmountOfTilesInside == m_TileVector.size() - 1)
					{
						bQuit = true;
					}
				}
			}
		}

		/// We reduce our vector of isolines.
		for (int32 i = 0; i < m_IsolineVector.size(); ++i)
		{
			m_RDP.Run(0.01f, m_IsolineVector[i]);
		}
	}

	int32 LG_Generate::CompareTilesPosition(LG_Line ActualLine, LG_Isoline& ActualIsoline, int32 iteratingTile)
	{
		/// Iterates through the tiles list.
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			if (i == iteratingTile)
			{
				continue;
			}
			/// Checks if the actual tile has already been checked.
			if (!m_TileVector[i]->m_bIsChecked)
			{
				/// Iterate through every line of the iterating tile.
				for (int32 j = 0; j < m_TileVector[i]->m_LinesVector.size(); ++j)
				{
					/// Check if the iterating line has not been inserted.
					if (!m_TileVector[i]->m_LinesVector[j].m_bIsInside)
					{
						/// Compare the position of the line's nodes.
						if (ActualLine.m_Nodes[0].m_Position == m_TileVector[i]->m_LinesVector[j].m_Nodes[0].m_Position ||
							ActualLine.m_Nodes[0].m_Position == m_TileVector[i]->m_LinesVector[j].m_Nodes[1].m_Position)
						{
							/// Add the iterating node to the actual line.
							ActualIsoline.AddNode(m_TileVector[iteratingTile]->m_LinesVector[j].m_Nodes[0].m_Position);
							/// Set it's flag that it's been inserted in the list.
							m_TileVector[iteratingTile]->m_LinesVector[j].m_bIsInside = true;
							/// Check if we can assign the tile as checked.
							if (j + 1 == m_TileVector[iteratingTile]->m_LinesVector.size())
							{
								/// Set it's tile flag.
								m_TileVector[iteratingTile]->m_bIsChecked = true;
								/// The new actual ID, the tile with the line that shared position.
								return m_TileVector[i]->m_iID;
							}
						}
						else if (ActualLine.m_Nodes[1].m_Position == m_TileVector[i]->m_LinesVector[j].m_Nodes[0].m_Position ||
							ActualLine.m_Nodes[1].m_Position == m_TileVector[i]->m_LinesVector[j].m_Nodes[1].m_Position)
						{
							/// Add the iterating node to the actual line.
							ActualIsoline.AddNode(m_TileVector[iteratingTile]->m_LinesVector[j].m_Nodes[1].m_Position);
							/// Set it's flag that it's been inserted in the list.
							m_TileVector[iteratingTile]->m_LinesVector[j].m_bIsInside = true;
							/// Check if we can assign the tile as checked.
							if (j + 1 == m_TileVector[iteratingTile]->m_LinesVector.size())
							{
								/// Set it's tile flag.
								m_TileVector[iteratingTile]->m_bIsChecked = true;
								/// The new actual ID, the tile with the line that shared position.
								return m_TileVector[i]->m_iID;
							}
						}
					}
				}

			}
		}
		return ERROR_CODE;
	}
}