#include "LG_Generate.h"
#include <LG_Rect.h>
#include <time.h>

namespace LevelGenerator
{
	//! Constant to use a separation force.
	const int32 LG_Generate::SEPARATION_FORCE = 30;

	//! Constant that define a max force.
	const int32 LG_Generate::MAX_FORCE = 10;

	//! Constant that define a min force.
	const int32 LG_Generate::MIN_FORCE = 2;

	//! This constant is used for generating an area to spwan the rooms. 
	const int32 LG_Generate::SPAWN_ZONE = 10;

	//! Default constructor.
	LG_Generate::LG_Generate()
	{
		m_pSpawnZone = nullptr;
		m_RoomsVector.clear();
		m_RoomsNodesCloud.clear();
	}

	//! Default destructor.
	LG_Generate::~LG_Generate()
	{
		Destroy();
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{
		/// Call the destroy function of the HallwayGenerator to erase the memory.
		m_HG.Destroy();
		/// Call the destroy function of the DelaunayTriangulation to erase the memory.
		m_DT.Destroy();

		/// Call the destroy function of the Rooms to erase the memory.
		while (m_RoomsVector.size() != 0)
		{
			/// Call the destroy function of the last element of the rooms vector.
			m_RoomsVector[m_RoomsVector.size() - 1]->Destroy();
			/// Delete the memory of the last element.
			delete m_RoomsVector[m_RoomsVector.size() - 1];
			/// pop the last element.
			m_RoomsVector.pop_back();
		}
		m_RoomsVector.clear();
	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run(uint32 iRoomAmount, LG_Vector3D MinSize, LG_Vector3D MaxSize, int32 iSeed, float fSeparationRange, float fHallwayWidth)
	{

		/// Initialize the seed.
		srand(iSeed);

		/// Generate rooms that we want to needed 
		GenerateRooms(iRoomAmount, MinSize, MaxSize, MaxSize.Z);

		/// We separate the rooms with a simple separation force, and a range. 
		while (!SeparationRooms(0.016f, fSeparationRange));

		/// Delaunay triangulation is applied.
		m_DT.Run(m_pSpawnZone->m_CenterNode.m_Position,
			&m_RoomsNodesCloud);

		/// minimum spanning tree
		m_MST.Run(m_DT.m_pEdgeVector, m_DT.m_pTrianglesVector);

		/// Now we make connections, meaning hallways, to the rooms.
		GenerateRoomsConnections();

		/// We run the hallway algorithm 
		m_HG.Run(&m_RoomsVector, fHallwayWidth, MaxSize.Z);

		/// 
		for (int32 i = 0; i < m_RoomsVector.size(); ++i)
		{
			m_RoomsVector[i]->CreateWalls();
		}

		/// Call the destroy function to release memory of the spawn zone.
		m_pSpawnZone->Destroy();
		/// Release memory.
		delete m_pSpawnZone;
		/// Restart as nullptr the spawn zone.
		m_pSpawnZone = nullptr;
	}

	//! This function separate the room objects.
	bool LG_Generate::SeparationRooms(float fDelta, float fSeparationRange)
	{
		bool bCanStopSeparate = true;
		/// Iterate the rooms vector to separate.
		for (Vector<LG_Room*>::iterator itt = m_RoomsVector.begin();
			itt != m_RoomsVector.end(); ++itt)
		{
			/// Calls the function separation rooms to separate the rooms.
			AverageRoom(*itt, fSeparationRange);
			/// Truncate the direction of the iterating room.
			(*itt)->m_pFloor->m_Direction = TruncateVector((*itt)->m_pFloor->m_Direction);
			/// If the magnitude of the direction vector is less than the min force.
			if ((*itt)->m_pFloor->m_Direction.Magnitude() <= MIN_FORCE)
			{
				(*itt)->m_pFloor->m_Direction = LG_Vector3D(0, 0, 0);
			}
			/// Else actualize the new position of the rect.
			else
			{
				/// Actualize the new position for the iterating room.
				(*itt)->m_pFloor->m_CenterNode.m_Position += (*itt)->m_pFloor->m_Direction * fDelta;
				/// Restructure the floor nodes' of the room.
				(*itt)->m_pFloor->RestructureNodes();
				/// Restructure the ceiling nodes' of the room.
				(*itt)->m_pCeiling->RestructureNodes((*itt)->m_pFloor->m_CenterNode.m_Position);
				/// Set this flag as false to determinate that algorithm has at least one rectangle without separating.
				bCanStopSeparate = false;
			}
		}
		/// Return the flag.
		return bCanStopSeparate;
	}

	//! Generates random positions for the rectangles, and separates them.
	void LG_Generate::GenerateRooms(uint32 uiRoomAmount, LG_Vector3D MinSize, LG_Vector3D MaxSize, float fHeight)
	{	
		//TODO: hacer techo que tenga las mismas posiciones que el piso (código de abajo) pero con otra posición en Z.
		///
		LG_Node PositionCenterSpawnZone;

		PositionCenterSpawnZone.m_Position = LG_Vector3D(300, 300, 0);
		/// Create a area to spawn the dots.
		m_pSpawnZone = new LG_Rect(PositionCenterSpawnZone, (float)uiRoomAmount * (float)SPAWN_ZONE, (float)uiRoomAmount * (float)SPAWN_ZONE);

		/// The rectangle object that we use to fill the vector.
		LG_Room* newRoom = nullptr;

		/// We store the minimum and maximum values to generate random positions for our rooms.
		LG_Vector3D PosToSpawn(0, 0, 0);
		int32 fMinX = (int32)m_pSpawnZone->m_CenterNode.m_Position.X - int32(m_pSpawnZone->m_fWidth / 2);
		int32 fMaxX = (int32)m_pSpawnZone->m_CenterNode.m_Position.X + int32(m_pSpawnZone->m_fWidth / 2);

		int32 fMinY = (int32)m_pSpawnZone->m_CenterNode.m_Position.Y - int32(m_pSpawnZone->m_fHeight / 2);
		int32 fMaxY = (int32)m_pSpawnZone->m_CenterNode.m_Position.Y + int32(m_pSpawnZone->m_fHeight / 2);

		/// Where we store the random room size.
		LG_Vector3D RoomSize;

		for (uint32 i = 0; i < uiRoomAmount; ++i)
		{
			/// We find a random position for the room we are about to create.
			PosToSpawn.X = float(rand() % (fMaxX - fMinX) + fMinX);
			PosToSpawn.Y = float(rand() % (fMaxY - fMinY) + fMinY);
			/// We find a random size for the rectangles upon the given boundaries. 
			RoomSize.X = float(rand() % ((int32)MaxSize.X - (int32)MinSize.X) + (int32)MinSize.X);
			RoomSize.Y = float(rand() % ((int32)MaxSize.Y - (int32)MinSize.Y) + (int32)MinSize.Y);

			/// We manage to keep this value as given, so that the hallways won't have any issues with the rooms heights.
			/// initialize the new room.
			newRoom = new LG_Room(PosToSpawn, RoomSize.X, fHeight, RoomSize.Y);
			/// Add the room to the room's vector.
			m_RoomsVector.push_back(newRoom);

			/// Assign 
			m_RoomsNodesCloud.push_back(&m_RoomsVector[i]->m_pFloor->m_CenterNode);
		}
	}



	//!
	void LG_Generate::AverageRoom(LG_Room* pActualRoom, float fSeparationRange)
	{
		/// A counter to count how many rects are in collision with the actual rect.
		int32 iNumRectsInRadius = 0;
		/// Create a temp vector to store a temporal direction.
		LG_Vector3D TempDirection;
		/// Create a vector to store the average.
		LG_Vector3D Average(0, 0, 0);

		/// Iterating the rooms vector.
		for (Vector<LG_Room*>::iterator itt = m_RoomsVector.begin();
			itt != m_RoomsVector.end(); ++itt)
		{
			/// If the iterating rect is different that the actual rect.
			if ((*itt) != pActualRoom)
			{
				/// We store the temp direction between the actual rect and the iterating rect.
				TempDirection = pActualRoom->m_pFloor->m_CenterNode.m_Position - (*itt)->m_pFloor->m_CenterNode.m_Position;

				/// Check if the iterating rect is collision.
				if (pActualRoom->m_pFloor->CheckCollision((*itt)->m_pFloor, fSeparationRange))
				{
					/// Add the temp vector to the average.
					Average += TempDirection;
					/// We increase the counter to know how many rects are in collision with the actual rect.
					++iNumRectsInRadius;
				}
			}
		}

		/// We make sure that at least there is a rectangle in collision with the actual rect and not to divide between 0.
		if (iNumRectsInRadius != 0)
		{
			/// Divide the average between the num of rects that are in collision with the actual rect.
			Average = Average / (float)iNumRectsInRadius;
			/// We make sure that the magnitude of the average is different to 0.
			if (Average.Magnitude() != 0)
			{
				/// Normalize the average because we only need the direction of the vector and multiply it by the separation force. 
				pActualRoom->m_pFloor->m_Direction += Average.Normalize() * (float)SEPARATION_FORCE;
				return;
			}
		}
		/// If the counter of rects in collision is 0 or the magnitude of the average is 0, set the direction of the actual rect to 0.
		pActualRoom->m_pFloor->m_Direction = LG_Vector3D(0, 0, 0);
	}

	//!
	void LG_Generate::GenerateRoomsConnections()
	{
		/// We assign the ID to the rectangles, associated with the node's ID.
		for (int32 i = 0; i < m_RoomsVector.size(); ++i)
		{
			for (int32 j = 0; j < m_RoomsNodesCloud.size(); ++j)
			{
				/// Once we find the node that shares position with the room, we associate the both vectors.
				if (m_RoomsVector[i]->m_pFloor->m_CenterNode.m_Position == m_RoomsNodesCloud[j]->m_Position)
				{
					m_RoomsVector[i]->AddRoomConnections(m_RoomsNodesCloud[j]->m_PointerNodes, m_RoomsVector);
				}
			}
		}
	}

	//! This function limits the strength of a given vector.
	LG_Vector3D LG_Generate::TruncateVector(LG_Vector3D VectorTruncate)
	{
		/// If the magnitude of the given vector is lees than the max force.
		if (VectorTruncate.Magnitude() < MAX_FORCE)
		{
			/// Return the same vector.
			return VectorTruncate;
		}

		/// Else Normalize the vector that we want to truncate and multiply it by the max force.
		else
		{
			/// Return the result vector.
			return VectorTruncate.Normalize() * (float)MAX_FORCE;
		}
	}

	//////////////////////////////////////////////////**************************************************************************/
	//////////////////////////////////////////////////*						 Currently this is not being used.				   */
	//////////////////////////////////////////////////**************************************************************************/	

	/*

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

	//!
	void LG_Generate::ReducedIsolines()
	{
		/// We reduce our vector of isolines.
		for (int32 i = 0; i < m_IsolineVector.size(); ++i)
		{
			m_RDP.Run(0.1f, m_IsolineVector[i]);
			m_FinalIsolineVector.push_back(m_RDP.m_FinalIsoline);
			m_RDP.Destroy();
		}
	}

	//!
	void LG_Generate::GetNoudesCloud()
	{
		/// Store in the nodes cloud all of the nodes in the isoline vector.
		for (int32 i = 0; i < m_FinalIsolineVector.size(); ++i)
		{
			for (int32 j = 0; j < m_FinalIsolineVector[i].m_NodeVector.size(); ++j)
			{
				m_FinalIsolineVector[i].m_NodeVector[j].Init();
				m_ReducedNoudCloud.push_back(&m_FinalIsolineVector[i].m_NodeVector[j]);
			}
		}
	}
	*/
}
