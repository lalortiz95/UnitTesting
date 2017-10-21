#include "LG_Generate.h"
#include <LG_Rect.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_Generate::LG_Generate()
	{
		m_pActualTile = nullptr;
		m_bInsertFront = false;
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
	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run()
	{
		/// Initialize the variables.
		Initialize();

		/// 
		GenerateRooms(100, LG_Vector3D(20, 20, 0), LG_Vector3D(50, 50, 0));

		/// Generate an isoline from the cases generated on marching squares.
		GenerateIsoline();

		/// We reduce our vector of isolines.
		for (int32 i = 0; i < m_IsolineVector.size(); ++i)
		{
			m_RDP.Run(0.1f, m_IsolineVector[i]);
			m_FinalIsolineVector.push_back(m_RDP.m_FinalIsoline);
			m_RDP.Destroy();
		}

		m_DT.Run(m_MS.m_pMap->m_iWidth,
			m_MS.m_pMap->m_iHeight,
			m_MS.m_pMap->m_MapCenter.m_Position,
			m_FinalIsolineVector);

		m_MST.Run(m_DT.m_pEdgeVector, m_DT.m_pTrianglesVector);
	}

	//! This function generate a isoline from Marching Square Cases.
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
					SetLineAs(m_pActualTile->m_LinesVector[FIRST_LINE]);

					/// If the tile have lines inside.
					if (m_pActualTile->m_LinesVector.size() > 1)
					{
						/// Check if the tile's information has already been inserted in the final isoline.
						bCheckTile = CheckTile(*m_TileVector[i]);
						/// See if it can already set the line as checked.
						SetLineAs(m_pActualTile->m_LinesVector[SECOND_LINE]);
					}

					/// See if we can already set 
					SetTileAs(*m_pActualTile);
					/// if it's true change the actual tile.
					if (bCheckTile)
					{
						/// Set new actual tile.
						m_pActualTile = m_TileVector[i];
						break;
					}
				}
			}

			/// If the actual tile didn't have any concidences of positions.
			if (!bCheckTile)
			{
				/// Check if there is an actual tile.
				if (m_pActualTile != nullptr)
				{

					bool bChangeActualTile = false;
					///Didn't find a node sharing position with the actual tile's nodes.
					/// Inserts the edge node.
					InsertEdgeNode(FIRST_LINE);
					/// Check if the isoline have been filled.
					bChangeActualTile = CheckIfIsolineIsFinished(FIRST_LINE);

					/// If the actual tile have more than 1 line.
					if (m_pActualTile->m_LinesVector.size() > 1)
					{
						/// Inserts the edge node.
						InsertEdgeNode(SECOND_LINE);
						/// Check if the isoline have been filled.
						bChangeActualTile = CheckIfIsolineIsFinished(SECOND_LINE);
					}
				}
			}
			/// If all the tiles with cases have already been set to a isoline.
			bQuit = AllTilesAreChecked();
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
					/// Set the iterating node flag.
					NodeToCheck.m_bIsInside = true;

					/// See if we insert the node at the front or the back of the isoline.
					if (!m_bInsertFront)
					{
						/// Add the actual node in the back of the actual line.
						m_ActualIsoline.AddNodeBack(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_Position);
					}
					else
					{
						/// Add the actual node in the front of the actual line.
						m_ActualIsoline.AddNodeFront(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[iCountNode].m_Position);
					}
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
			SetLineAs(IteratingTile.m_LinesVector[FIRST_LINE]);
			/// If it didn't have any sharing position's node, and the iterating tile's got another line.
			if (!bCheckLine && IteratingTile.m_LinesVector.size() > 1)
			{
				/// We check if that other line's got a node that shares position.
				bCheckLine = CheckLineIsInside(SECOND_LINE, IteratingTile.m_LinesVector[SECOND_LINE]);
				SetLineAs(IteratingTile.m_LinesVector[SECOND_LINE]);
			}

		}

		SetTileAs(IteratingTile);
		/// Return the flag.
		return bCheckLine;
	}

	//! This function check if a isoline is finished.
	bool LG_Generate::CheckIfIsolineIsFinished(int32 iCountLine)
	{
		/// Go through the lines of each tile.
		for (int32 i = 0; i < m_TileVector.size(); ++i)
		{
			/// Check if the tile isn't checked.
			if (!m_TileVector[i]->m_bIsChecked && (m_pActualTile->m_iID != m_TileVector[i]->m_iID))
			{
				/// If any of the line's nodes has already been checked.
				if (m_TileVector[i]->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_bIsInside ||
					m_TileVector[i]->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_bIsInside)
				{
					/// Set the flag that will allow to insert the nodes at the front of the vector.
					m_bInsertFront = true;
					/// Set the new actual tile.
					m_pActualTile = m_TileVector[i];
					return true;
				}
			}
		}
		return false;
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
	}

	//! This functions inserts the edge node of a isoline.
	void LG_Generate::InsertEdgeNode(int32 iCountLine)
	{
		/// Checks that the first node of the actual tile have already been set.
		if (m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_bIsInside)
		{
			/// Checks if the second node of the actual tile have already been set.
			if (!m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_bIsInside)
			{
				/// Set the flag of the node.
				m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_bIsInside = true;
				/// See if we insert the node at the front or the back of the isoline.
				if (!m_bInsertFront)
				{
					/// Add the actual node in the back of the actual line.
					m_ActualIsoline.AddNodeBack(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_Position);
				}
				else
				{
					/// Add the actual node in the front of the actual line.
					m_ActualIsoline.AddNodeFront(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_Position);
				}
			}

			else
			{
				/// Add the finished isoline to the isoline vector.
				m_IsolineVector.push_back(m_ActualIsoline);
				/// Cleans the isoline so that it can be filled again.
				m_ActualIsoline.Destroy();
				/// Find a new actual tile to start filling another isoline.
				SetActualTile();
				/// Set the flag that define if we can insert in back of the line.
				m_bInsertFront = false;
			}
		}
		/// Checks that the second node of the actual tile have already been set.
		else if (m_pActualTile->m_LinesVector[iCountLine].m_Nodes[SECOND_NODE].m_bIsInside)
		{
			/// Checks that the first node of the actual tile have already been set.
			if (!m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_bIsInside)
			{
				/// Set the flag of the node.
				m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_bIsInside = true;
				/// See if we insert the node at the front or the back of the isoline.
				if (!m_bInsertFront)
				{
					/// Add the actual node in the back of the actual line.
					m_ActualIsoline.AddNodeBack(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_Position);
				}
				else
				{
					/// Add the actual node in the front of the actual line.
					m_ActualIsoline.AddNodeFront(m_pActualTile->m_LinesVector[iCountLine].m_Nodes[FIRST_NODE].m_Position);
				}
			}
			else
			{
				/// Add the finished isoline to the isoline vector.
				m_IsolineVector.push_back(m_ActualIsoline);
				/// Cleans the isoline so that it can be filled again.
				m_ActualIsoline.Destroy();
				/// Find a new actual tile to start filling another isoline.
				SetActualTile();
				/// Set the flag that define if we can insert in back of the line.
				m_bInsertFront = false;
			}
		}
	}

	//! Generates random positions for the rectangles, and separates them.
	void LG_Generate::GenerateRooms(int32 iRoomAmount, LG_Vector3D MinSize, LG_Vector3D MaxSize)
	{
		//TODO: definir un área para spawnear los cuartos, asegurarse de revisar el peso de cada uno para definir el tamaño delos cuartos
		// una vez que se tengan todos los rectangulos en sus respectivas posiciones, con sus tamaños correspondientes
		// separarlos de tal manera que ninguno choque con ninguno.
		// Triangular con los puntos generados.


		/// The area within we will generate random positions for our nodes.
		LG_Rect SpawnZone;
		/// Create a area to spawn the dots.
		//TODO: hacer que el tamaño dependa de la cantidad de cuartos. Quiza que el área para spawn que sea un circulo.
		SpawnZone.Init(LG_Vector3D(0, 0, 0), 1000.f, 1000.f);

		m_RoomsVector.resize(iRoomAmount);

		/// The rectangle object that we use to fill the vector.
		LG_Rect* NewRect = nullptr;

		/// We store the minimum and maximum values to generate random positions for our rooms.
		LG_Vector3D PosToSpawn(0, 0, 0);
		int32 fMinX = SpawnZone.m_Position.X - (SpawnZone.m_fWidth / 2);
		int32 fMaxX = SpawnZone.m_Position.X + SpawnZone.m_fWidth;

		int32 fMinY = SpawnZone.m_Position.Y - (SpawnZone.m_fHeight / 2);
		int32 fMaxY = SpawnZone.m_Position.Y + SpawnZone.m_fHeight;

		/// Where we store the random room size.
		LG_Vector3D RoomSize;

		for (int32 i = 0; i < iRoomAmount; ++i)
		{
			/// We find a random position for the room we are about to create.
			PosToSpawn.X = rand() % fMaxX + fMinX;
			PosToSpawn.Y = rand() % fMaxY + fMinY;
			/// We find a random size for the rectangles upon the given boundaries. 
			RoomSize.X = rand() % (int32)MaxSize.X + (int32)MinSize.X;
			RoomSize.Y = rand() % (int32)MaxSize.Y + (int32)MinSize.Y;

			/// initialize the new room.
			NewRect = new LG_Rect(PosToSpawn, RoomSize.X, RoomSize.Y);
			/// Add the room to the room's vector.
			m_RoomsVector[i] = NewRect;
		}

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
	void LG_Generate::SetLineAs(LG_Line& LineToChangeFlag)
	{

		/// See if both nodes of the line have already been set as checked.
		if (LineToChangeFlag.m_Nodes[FIRST_NODE].m_bIsInside &&
			LineToChangeFlag.m_Nodes[SECOND_NODE].m_bIsInside)
		{
			/// If so, we also set the line as checked.
			LineToChangeFlag.m_bIsInside = true;
		}
	}

	//! This function set a tile as true if 1 or 2 lines of the tile are true.
	void LG_Generate::SetTileAs(LG_Tile& TileToChangeFlag)
	{
		/// If the tile has got any lines.
		if (TileToChangeFlag.m_LinesVector.size() > 1)
		{
			/// If both lines of the tile have been checked.
			if (TileToChangeFlag.m_LinesVector[FIRST_LINE].m_bIsInside &&
				TileToChangeFlag.m_LinesVector[SECOND_LINE].m_bIsInside)
			{
				/// Then we set the tile as true.
				TileToChangeFlag.m_bIsChecked = true;
			}
		}
		else
		{
			/// If the tile's line has already been checked.
			if (TileToChangeFlag.m_LinesVector[FIRST_LINE].m_bIsInside)
			{
				/// Set the actual tile as true.
				TileToChangeFlag.m_bIsChecked = true;
			}
		}
	}

	void LG_Generate::SeparationRooms()
	{

	}

}