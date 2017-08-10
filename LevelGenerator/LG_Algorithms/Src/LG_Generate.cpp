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
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{
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
	
		/// We run marching square with the generated grid.
		m_MS.Run(2, 10, 10);

		/// Generate an isoline from the cases generated on marching squares.
		GenerateIsoline();

		/// We reduce our vector of isolines.
		for (int32 i = 0; i < m_IsolineVector.size(); ++i)
		{
			m_RDP.Run(0.f, m_IsolineVector[i]);
		}

		//Now we have a reduced set of points, that will be used to 
		//Generate delaunay triangulation.
	}

	void LG_Generate::GenerateIsoline()
	{
		/// To have a more readable code.
		m_TileVector = m_MS.m_pEdgeTiles;

		/// Assign the actual tile as the first object in the vector.
		if (m_pActualTile == nullptr)
			m_pActualTile = m_TileVector.front();

		/// Flag to end the cycle.
		bool bQuit = false;
		/// Flag that indicate if we can change the actual tile.
		bool bFlag = false;
		/// Flag that indicate if the isoline is finished.
		bool bFinishIsoline = false;
		/// Flag that indicate if we can break the first for.
		bool bBreakFirstFor = false;

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
					/// Check for every line of the tile.
					for (int32 j = 0; j < m_TileVector[i]->m_LinesVector.size(); ++j)
					{
						/// Check if the tile's information has already been inserted in the final isoline.
						bFlag = CheckTile(*m_TileVector[i], j);

						//TODO: Checar que se cree y se cambie la isolinea nueva
						// de acuerdo a lo planeado. (Esto no lo esta haciendo de la manera correcta)..

						/// if it's true change the actual tile.
						if (bFlag)
						{
							/// Set new actual tile.
							m_pActualTile = m_TileVector[i];
							/// Change the flag to break the first for.
							bBreakFirstFor = true;
							break;
						}
						else
						{
							/// Check if we can finished a isoline.
							bFinishIsoline = CheckIfIsolineIsFinish();
							/// If it's false.
							if (!bFinishIsoline)
							{
								/// Assign the actual isoline to the isoline vector.
								m_IsolineVector.push_back(m_ActualIsoline);
								/// Reset it's values.
								m_ActualIsoline.Destroy();
								/// Change the flag to break the first for.
								bBreakFirstFor = true;
								break;
							}

							else
							{
								/// Change the flag to false because in this part we can't finish the isoline.
								bFinishIsoline = false;
								/// Change the flag to break the first for.
								bBreakFirstFor = true;
								break;
							}						
						}
					}
					/// If it's true break the first for.
					if (bBreakFirstFor)
					{
						/// Set it back to false.
						bBreakFirstFor = false;
						break;
					}
				}		
			}
			
			/// Iterate for break the while if all tiles in vector are checked.
			for (int32 i = 0; i < m_TileVector.size(); ++i)
			{
				if (!m_TileVector[i]->m_bIsChecked)
				{
					///Change the flag to finished the while.
					bQuit = false;
					break;
				}
			}
		}
	}

	//! Check the position of the actual tile's nodes against the iterating tile's nodes.
	bool LG_Generate::CheckNodePosition(LG_Node& StartNode, LG_Node& EndNode, int32 iIteratingLine)
	{
		//TODO: Corregir esto los nodos no se interpretan bien y causa un bucle del cual no
		// pasa al siguiente tile, cambiar cual es el nodo que se inserta y cual es el que cambia
		// su bandera y debuguiar para ver si esto soluciona el problema... ;)

		/// Check if the actual tile's nodes is not inside.
		if (!m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[0].m_bIsInside)
		{
			/// Set the flag of the node.
			m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[0].m_bIsInside = true;
			/// Add the actual node to the actual line.
			m_ActualIsoline.AddNode(m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[0].m_Position);

			/// Check if the actual node position is the same that the iterating tile's node position.
			if (m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[0].m_Position == StartNode.m_Position)
			{
				StartNode.m_bIsInside = true;
				return true;
			}
		}

		/// Check if the actual tile's nodes is not inside.
		if (!m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[1].m_bIsInside)
		{
			/// Set the flag of the node.
			m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[1].m_bIsInside = true;
			/// Add the actual node to the actual line.
			m_ActualIsoline.AddNode(m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[1].m_Position);

			/// Check if the actual node position is the same that the iterating tile's node position.
			if (m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[1].m_Position == EndNode.m_Position)
			{
				EndNode.m_bIsInside = true;
				return true;
			}
		}
		return false;
	}

	//! This function check if the line isn't set yet.
	bool LG_Generate::CheckLineIsInside(LG_Line& IteratingLine, int32 iIteratingLine)
	{
		/// Check if there are shared positions between the nodes.
		bool bFlag = false;
		/// If the iterating line isn't inside.
		if (!IteratingLine.m_bIsInside)
		{
			/// Check for every node of the line.
			bFlag = CheckNodePosition(IteratingLine.m_Nodes[0], IteratingLine.m_Nodes[1], iIteratingLine);

			/// If both nodes of the line are already inside.
			if (m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[0].m_bIsInside &&
				m_pActualTile->m_LinesVector[iIteratingLine].m_Nodes[1].m_bIsInside)
			{
				/// Change the flag of the line.
				m_pActualTile->m_LinesVector[iIteratingLine].m_bIsInside = true;
			}
		}
		/// Return the flag.
		return bFlag;
	}

	//! This function check if the tile has already been checked.
	bool LG_Generate::CheckTile(LG_Tile& IteratingTile, int32 iIteratingTile)
	{
		/// Flag that defines if we are switching the actual tile.
		bool bFlag = false;

		/// If the iterating tile have not been checked.
		if (!IteratingTile.m_bIsChecked)
			bFlag = CheckLineIsInside(IteratingTile.m_LinesVector[iIteratingTile], iIteratingTile);

		/// If the actual tile vector lines if equal to 1.
		if (1 == m_pActualTile->m_LinesVector.size())
		{

			if (m_pActualTile->m_LinesVector[0].m_bIsInside)
				/// Set the actual tile flag like true.
				m_pActualTile->m_bIsChecked = true;
		}

		/// If the actual tile vector lines if equal to 2.
		else if (2 == m_pActualTile->m_LinesVector.size())
		{
			if (m_pActualTile->m_LinesVector[0].m_bIsInside &&
				m_pActualTile->m_LinesVector[1].m_bIsInside)
				/// Set the actual tile flag like true.
				m_pActualTile->m_bIsChecked = true;
		}

		/// Return the flag.
		return bFlag;
	}

	//! This function tells if a isoline is finished.
	bool LG_Generate::CheckIfIsolineIsFinish()
	{
		/// This flag define if we can change of isoline.
		bool bFlag = false;
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			/// If the iterating tile have not been checked.
			if (!m_TileVector[i]->m_bIsChecked)
			{
				/// Check for every line of the tile.
				for (int32 j = 0; j < m_TileVector[i]->m_LinesVector.size(); ++j)
				{
					if (!m_TileVector[i]->m_LinesVector[j].m_bIsInside)
					{
						if (m_TileVector[i]->m_LinesVector[j].m_Nodes[0].m_bIsInside ||
							m_TileVector[i]->m_LinesVector[j].m_Nodes[1].m_bIsInside)
						{
							m_pActualTile = m_TileVector[i];
							bFlag = true;
							return bFlag;
						}
					}
				}
			}
		}
		return bFlag;

	}


	/*/// The actual isoline being filled. Once it's done it's inserted in the isoline vector.
	LG_Isoline ActualIsoline;

	/// Indicates when to stop iterating.
	bool bQuit = false;
	int32 iActualTile = 0;

	/// To have a more readable code.
	m_TileVector = m_MS.m_pEdgeTiles;
	/// We set each tile's ID accordingly to our needs.
	for (int32 i = 0; i < m_TileVector.size(); ++i)
	{
		m_TileVector[i]->m_iID = i;
	}

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
					for (int32 k = 0; k < m_TileVector[iActualTile]->m_LinesVector.size(); ++k)
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
}*/

}