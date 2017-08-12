#include "LG_Generate.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Generate::LG_Generate()
	{
		m_pActualTile = nullptr;
		m_pMap = nullptr;
	}

	//! Default destructor.
	LG_Generate::~LG_Generate()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Generate::Initialize()
	{
		/// We run marching square with the generated grid.
		m_MS.Run(2, 10, 10);
		/// To have a more readable code.
		m_TileVector = m_MS.m_pEdgeTiles;

		/// Assign the actual tile as the first object in the vector.
		if (m_pActualTile == nullptr)
			m_pActualTile = m_TileVector.front();
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{
		/// Releases memory.
		if (m_pActualTile != nullptr)
			m_pActualTile->Destroy();

		if (m_pMap != nullptr)
			m_pMap->Destroy();

	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run()
	{
		/// Initialize the variables.
		Initialize();

		/// Generate an isoline from the cases generated on marching squares.
		GenerateIsoline();

		/*/// We reduce our vector of isolines.
		for (int32 i = 0; i < m_IsolineVector.size(); ++i)
		{
			m_RDP.Run(0.f, m_IsolineVector[i]);
		}*/
		//Now we have a reduced set of points, that will be used to 
		//Generate delaunay triangulation.
	}

	void LG_Generate::GenerateIsoline()
	{

		/// Flag to end the cycle.
		bool bQuit = false;
		/// Flag that indicate if we can change the actual tile.
		bool bCheckTile = false;
	
		/// While will be broken once all the isolines are generated.
		while (!bQuit)
		{
			/// If it doesn't change we end the while cycle.
			bQuit = true;
			/// Go through the lines of each tile.
			for (int32 i = 0; i < m_TileVector.size(); ++i)
			{
				/// Check that we aren't comparing the same tile.
				if (m_pActualTile->m_iID != m_TileVector[i]->m_iID)
				{
					/// See if the iterating tile had a node that shared position
					/// With one of the actual tile.
					bCheckTile = CheckTile(*m_TileVector[i]);
					/// See if it can already set the line as checked.
					SetLineAs(FIRST_LINE);

					/// If the tile have lines inside.
					if (m_pActualTile->m_LinesVector.size() > 1)
					{
						/// Check if the tile's information has already been inserted in the final isoline.
						bCheckTile = CheckTile(*m_TileVector[i]);
						/// See if it can already set the line as checked.
						SetLineAs(SECOND_LINE);
					}

					/// See if we can already set 
					SetTileAs();
					/// if it's true change the actual tile.
					if (bCheckTile)
					{
						/// Set new actual tile.
						m_pActualTile = m_TileVector[i];
						break;
					}
				}
			}
			/*/// If it's false.
			if (CheckIfIsolineIsFinish())
			{
				/// Assign the actual isoline to the isoline vector.
				m_IsolineVector.push_back(m_ActualIsoline);
				/// Reset it's values.
				m_ActualIsoline.Destroy();
				/// Set a new Actual Tile.
				SetActualTile();
				break;
			}*/
			/// If all the tiles with cases have already been set to a isoline.
			bQuit = AllTilesAreChecked();
			// debugging purposes.
			m_ActualIsoline = m_ActualIsoline;
		}
	}

	//! Check the position of the actual tile's nodes against the iterating tile's nodes.
	bool LG_Generate::CheckNodePosition(int32 iCountLine, int32 iCountNode, LG_Node& NodeToCheck)
	{

		/// Check if the actual tile's nodes is not inside.
		if (!m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_bIsInside)
		{
			/// Check if the actual node position is the same that the iterating tile's node position.
			if (m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_Position ==
				NodeToCheck.m_Position)
			{
				/// Check if the node haven't been used.
				if (!NodeToCheck.m_bIsInside)
				{
					/// Set the flag of the node.
					m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_bIsInside = true;
					/// Add the actual node to the actual line.
					m_ActualIsoline.AddNode(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_Position);
					/// Returns true, meaning that it found a node that was sharing position.
					return true;
				}

				else
				{
					/// When it shares position with a node that has already been set.
					m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_bIsInside = true;
					/// Returns false, meaning it did not find a node that was sharing position.
					return false;
				}
			}
		}
		/// Returns false, meaning it did not find a node that was sharing position.
		return false;
	}

	//! This function check if the line isn't set yet.
	bool LG_Generate::CheckLineIsInside(int32 iCountLine, LG_Line& IteratingLine)
	{
		/// A flag that indicates if two nodes shared position.
		bool bCheckNode = false;
		/// If the iterating line isn't inside.
		if (!IteratingLine.m_bIsInside)
		{
			/// Check if the first node of the actual tile, is sharing position with the first node of the iterating tile.
			bCheckNode = CheckNodePosition(iCountLine, FIRST_NODE, IteratingLine.m_Nodes[FIRST_NODE]);
			/// If they didn't share position.
			if (!bCheckNode)
			{
				/// Check if the first node of the actual tile, is sharing position with the second node of the iterating tile.
				bCheckNode = CheckNodePosition(iCountLine, FIRST_NODE, IteratingLine.m_Nodes[SECOND_NODE]);
				/// And so it goes...
				if (!bCheckNode)
				{
					/// Check if the second node of the actual tile, is sharing position with the first node of the iterating tile.
					bCheckNode = CheckNodePosition(iCountLine, SECOND_NODE, IteratingLine.m_Nodes[FIRST_NODE]);
					if (!bCheckNode)
					{
						/// Check if the second node of the actual tile, is sharing position with the second node of the iterating tile.
						bCheckNode = CheckNodePosition(iCountLine, SECOND_NODE, IteratingLine.m_Nodes[SECOND_NODE]);
					}
				}
			}
		}
		/// Return the flag's final value.
		return bCheckNode;
	}

	//! This function check if the tile has already been checked.
	bool LG_Generate::CheckTile(LG_Tile& IteratingTile)
	{
		/// Indicates if the tile's got a line, that haves a node sharing position with the actual tile.
		bool bCheckLine = false;
		/// If the iterating tile have not been checked.
		if (!IteratingTile.m_bIsChecked)
		{
			/// Checks if the line's got nodes that shares position with the actual tile.
			bCheckLine = CheckLineIsInside(FIRST_LINE, IteratingTile.m_LinesVector[FIRST_LINE]);
			/// If it didn't have any sharing position's node, and the iterating tile's got another line.
			if (!bCheckLine && IteratingTile.m_LinesVector.size() > 1)
			{
				/// We check if that other line's got a node that shares position.
				bCheckLine = CheckLineIsInside(SECOND_LINE, IteratingTile.m_LinesVector[SECOND_LINE]);
			}

		}
		/// Return the flag.
		return bCheckLine;
	}


	//! This function tells if a isoline is finished.
	bool LG_Generate::CheckIfIsolineIsFinish()
	{
	
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			/// If the iterating tile have not been checked.
			if (!m_TileVector[i]->m_bIsChecked)
			{
				if (!m_TileVector[i]->m_LinesVector[FIRST_LINE].m_bIsInside)
				{
					if (m_TileVector[i]->m_LinesVector[FIRST_LINE].m_Nodes[FIRST_NODE].m_bIsInside ||
						m_TileVector[i]->m_LinesVector[FIRST_LINE].m_Nodes[SECOND_NODE].m_bIsInside)
					{
						m_pActualTile = m_TileVector[i];
						return true;
					}
				}
				/// Check for every line of the tile.
				if (m_TileVector[i]->m_LinesVector.size() > 1)
				{
					if (!m_TileVector[i]->m_LinesVector[SECOND_LINE].m_bIsInside)
					{
						if (m_TileVector[i]->m_LinesVector[SECOND_LINE].m_Nodes[FIRST_NODE].m_bIsInside ||
							m_TileVector[i]->m_LinesVector[SECOND_LINE].m_Nodes[SECOND_NODE].m_bIsInside)
						{
							m_pActualTile = m_TileVector[i];
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	//! This function set a new actual tile.
	void LG_Generate::SetActualTile()
	{
		/// Once it has completed filling an isoline, it looks for a new tile to start a new isoline.
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			///Check if the iterating tile haven't been checked.
			if (!m_TileVector[i]->m_bIsChecked)
			{
				/// If it haven't, it's set as the new actual tile.
				m_pActualTile = m_TileVector[i];
				/// Get out of the function.
				return;
			}
		}
	}

	//! This function that sets a line as true if the 2 nodes of the line are true.
	void LG_Generate::SetLineAs(int32 iCountLine)
	{
		/// If there's a actual tile.
		if (m_pActualTile != nullptr)
		{
			/// See if both nodes of the line have already been set as checked.
			if (m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_bIsInside &&
				m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_bIsInside)
			{
				/// If so, we also set the line as checked.
				m_pActualTile->m_LinesVector[iCountLine].m_bIsInside = true;
			}
		}
	}

	//! This function set a tile as true if 1 or 2 lines of the tile are true.
	void LG_Generate::SetTileAs()
	{
		/// If there is a actual tile.
		if (m_pActualTile != nullptr)
		{
			/// If the tile has got any lines.
			if (m_pActualTile->m_LinesVector.size() > 1)
			{
				/// If both lines of the tile have been checked.
				if (m_pActualTile->m_LinesVector[FIRST_LINE].m_bIsInside &&
					m_pActualTile->m_LinesVector[SECOND_LINE].m_bIsInside)
				{
					/// Then we set the tile as true.
					m_pActualTile->m_bIsChecked = true;
				}
			}
			else
			{
				/// If the tile's line has already been checked.
				if (m_pActualTile->m_LinesVector[FIRST_LINE].m_bIsInside)
				{
					/// Set the actual tile as true.
					m_pActualTile->m_bIsChecked = true;
				}
			}
		}
	}

	//! This function check if all tiles in the vector are checked.
	bool LG_Generate::AllTilesAreChecked()
	{
		/// Iterate to break the while if all the tiles in vector are checked.
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			/// If even one isn't we return false.
			if (!m_TileVector[i]->m_bIsChecked)
			{
				/// Told you.
				return false;
			}
		}
		/// If it get's to this point, that means that all the tiles have already been checked.
		return true;
		///Congratulations, algorithm is over.
	}

}