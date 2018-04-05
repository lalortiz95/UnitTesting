#include "LG_Room.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Room::LG_Room()
	{
		m_bIsChecked = false;
		m_iRoomCase = 0;
		m_pFloor = nullptr;
		m_pCeiling = nullptr;
		m_Doors.clear();
	}

	//! Parameter constructor
	LG_Room::LG_Room(LG_Vector3D vPosToSpawn, float fWidth, float fHeight, float fDepth)
	{
		Init(vPosToSpawn, fWidth, fHeight, fDepth);
	}

	//! Default destructor
	LG_Room::~LG_Room()
	{
		/// Call the destroy function to release memory.
		Destroy();
	}

	//! This function initialize the area of the room.
	void LG_Room::Init(LG_Vector3D vPosToSpawn, float fWidth, float fHeight, float fDepth)
	{
		m_fHeight = fHeight;
		m_bIsChecked = false;
		m_iRoomCase = 0;
		m_pFloor = nullptr;
		m_pCeiling = nullptr;
		m_Doors.clear();

		/// 
		CreateFloor(vPosToSpawn, fWidth, fDepth);

		/// 
		CreateCeiling(vPosToSpawn, fWidth, fDepth, fHeight);
	}

	//! This function release all the memory that was used in the room.
	void LG_Room::Destroy()
	{
		/// If the pointer of ceiling is not nullptr.
		if (m_pCeiling != nullptr)
		{
			/// Call the destroy function of the ceiling.
			m_pCeiling->Destroy();
			/// Delete the memory .
			delete m_pCeiling;
			/// Set as nullptr.
			m_pCeiling = nullptr;
		}

		/// If the pointer of floor is not nullptr.
		if (m_pFloor != nullptr)
		{
			/// Call the destroy function of the m_pFloor.
			m_pFloor->Destroy();
			/// Delete the memory .
			delete m_pFloor;
			/// Set as nullptr.
			m_pFloor = nullptr;
		}

		/// Repeat until the vector of ceilings has empty.
		while (m_Doors.size() != 0)
		{

			/// Set as nullptr the last element.
			m_Doors[m_Doors.size() - 1] = nullptr;
			/// pop the last element.
			m_Doors.pop_back();
		}

		/// Reset the vector of doors.
		m_Doors.clear();

		/// Reset the value of this var.
		m_iRoomCase = 0;

		/// Reset this flag as false.
		m_bIsChecked = false;

		///  Clears the room's connections.
		if (m_RoomsConnections.size() != 0)
		{
			for (Vector<LG_Room*>::iterator itt = m_RoomsConnections.begin(); itt != m_RoomsConnections.end(); ++itt)
			{
				*itt = nullptr;
			}
			m_RoomsConnections.clear();
		}


	}

	//!
	void LG_Room::StopPointingToRoom(LG_Room * pRoom)
	{
		for (Vector<LG_Room*>::iterator itt = m_RoomsConnections.begin(); itt != m_RoomsConnections.end(); ++itt)
		{
			if ((*itt) == pRoom)
			{
				m_RoomsConnections.erase(itt);
				return;
			}
		}
	}

	//! 
	void LG_Room::AddRoomConnections(const Vector<LG_Node*>& NodeConections, const Vector<LG_Room*>& RoomsVect)
	{

		for (int32 i = 0; i < NodeConections.size(); ++i)
		{
			for (int32 j = 0; j < RoomsVect.size(); ++j)
			{
				/// Once we find the node that shares position with the room, we associate the both vectors.
				if (RoomsVect[j]->m_pFloor->m_CenterNode.m_Position == NodeConections[i]->m_Position)
				{
					m_RoomsConnections.push_back(RoomsVect[j]);
					break;
				}
			}
		}
	}

	//!
	void LG_Room::CreateWalls()
	{
		///  A Temp vectors to store the door's positions.
		Vector<float> RightDoors, LeftDoors, TopDoors, BottomDoors;

		/// Iterate the vector of doors to find their side. counter clock-wise.
		for (int32 i = 0; i < m_Doors.size(); ++i)
		{
			if (m_Doors[i]->m_pFirstPosition->m_Position.X == m_pFloor->m_TopLeft.m_Position.X)
			{
				LeftDoors.push_back(m_Doors[i]->m_pFirstPosition->m_Position.Y);
				LeftDoors.push_back(m_Doors[i]->m_pSecondPosition->m_Position.Y);
			}

			else if (m_Doors[i]->m_pFirstPosition->m_Position.Y == m_pFloor->m_BottomLeft.m_Position.Y)
			{
				BottomDoors.push_back(m_Doors[i]->m_pFirstPosition->m_Position.X);
				BottomDoors.push_back(m_Doors[i]->m_pSecondPosition->m_Position.X);
			}

			else if (m_Doors[i]->m_pFirstPosition->m_Position.X == m_pFloor->m_BottomRight.m_Position.X)
			{
				RightDoors.push_back(m_Doors[i]->m_pFirstPosition->m_Position.Y);
				RightDoors.push_back(m_Doors[i]->m_pSecondPosition->m_Position.Y);
			}

			else if (m_Doors[i]->m_pFirstPosition->m_Position.Y == m_pFloor->m_TopRight.m_Position.Y)
			{
				TopDoors.push_back(m_Doors[i]->m_pFirstPosition->m_Position.X);
				TopDoors.push_back(m_Doors[i]->m_pSecondPosition->m_Position.X);
			}
		}

		///we now sort the door nodes from the smallest to the biggest. For every wall, with that information we'll calculate the wall positions.
		std::sort(RightDoors.begin(), RightDoors.end());
		std::sort(LeftDoors.begin(), LeftDoors.end());
		std::sort(TopDoors.begin(), TopDoors.end());
		std::sort(BottomDoors.begin(), BottomDoors.end());

		/// The walls from all the room are now calculated and stored.
		CalculateWallNodes(RightDoors, m_pFloor->m_TopRight.m_Position, m_pFloor->m_BottomRight.m_Position, false);

		CalculateWallNodes(TopDoors, m_pFloor->m_TopLeft.m_Position, m_pFloor->m_TopRight.m_Position, true);

		CalculateWallNodes(LeftDoors, m_pFloor->m_TopLeft.m_Position, m_pFloor->m_BottomLeft.m_Position, false);

		CalculateWallNodes(BottomDoors, m_pFloor->m_BottomLeft.m_Position, m_pFloor->m_BottomRight.m_Position, true);

		/////  We now proceed to calculate the top room's doors.
		//for (int32 i = 0; i < TopDoors.size(); ++i)
		//{
		//	/// Allocate memory to the rectangle that will represent the wall.
		//	pNewRect = new LG_Rect();
		//
		//	///This is for the first iteration
		//	if (i < 1)
		//	{
		//		/// We store the position for the top left node of the wall.
		//		WallTopLeft = m_pFloor->m_TopLeft.m_Position;
		//		WallTopLeft.Z = m_fHeight;
		//		/// Now the top right is calculated.
		//		WallTopRight = WallTopLeft;
		//		WallTopRight.X = TopDoors[i];
		//
		//		///Bottom left node's position is now calculated.
		//		WallBottomLeft = m_pFloor->m_TopLeft.m_Position;
		//
		//		/// Here we calculate the position for the bottom right node of the wall.
		//		WallBottomRight = WallBottomLeft;
		//		WallBottomRight.X = TopDoors[i];
		//	}
		//	/// This is used in the last iteration
		//	else if (i > RightDoors.size() - 1)
		//	{
		//		/// The wall is being calculated between the last position from the list, and the floor bottom right corner.
		//		WallTopRight = m_pFloor->m_TopRight.m_Position;
		//		WallTopRight.Z = m_fHeight;
		//
		//		WallTopLeft = WallTopRight;
		//		WallTopLeft.X = TopDoors[i];
		//		WallBottomRight = m_pFloor->m_TopRight.m_Position;
		//		WallBottomLeft = WallBottomRight;
		//		WallBottomLeft.X = TopDoors[i];
		//	}
		//	/// All the iterations in between.
		//	else
		//	{
		//		WallBottomLeft = m_pFloor->m_TopLeft.m_Position;
		//		WallBottomLeft.X = TopDoors[i];
		//
		//		WallBottomRight = WallBottomLeft;
		//		WallBottomRight.X = TopDoors[i + 1];
		//
		//		WallTopLeft = WallBottomLeft;
		//		WallTopLeft.Z = m_fHeight;
		//
		//		WallTopRight = WallTopLeft;
		//		WallTopRight.Z = m_fHeight;
		//	}
		//	/// Now the wall is created with all of it's components.
		//	pNewRect->Init(m_pFloor->m_TopRight.m_Position, WallTopLeft, m_pFloor->m_TopRight.m_Position, WallBottomRight);
		//	/// We now store the new wall that has just been created.
		//	m_Walls.push_back(pNewRect);
		//}
	}

	//!
	void LG_Room::CreateFloor(LG_Vector3D vPosToSpawn, float fWidth, float fDepth)
	{
		/// Assign memory to the room area using the constructor parameter of the rect.
		m_pFloor = new LG_Rect(vPosToSpawn, fWidth, fDepth);

	}

	//!
	void LG_Room::CreateCeiling(LG_Vector3D vPosToSpawn, float fWidth, float fDepth, float fHeight)
	{
		/// First a copy of the floor is made.
		m_pCeiling = new LG_Rect(vPosToSpawn, fWidth, fDepth);

		/// Now the value in Z axis of every node is set to the height given.
		m_pCeiling->m_BottomLeft.m_Position.Z = fHeight;
		m_pCeiling->m_BottomRight.m_Position.Z = fHeight;
		m_pCeiling->m_TopLeft.m_Position.Z = fHeight;
		m_pCeiling->m_TopRight.m_Position.Z = fHeight;
		/// All of the nodes.
		m_pCeiling->m_CenterNode.m_Position.Z = fHeight;
	}

	//! This function calculates 4 nodes of a rectangle that will represent a wall, and then stores that wall in a vector.
	void LG_Room::CalculateWallNodes(Vector<float> sideDoors, LG_Vector3D FirstNode, LG_Vector3D SecondNode, bool bIsHorizontal)
	{
		LG_Vector3D WallTopLeft, WallTopRight, WallBottomLeft, WallBottomRight;
		LG_Rect* pNewRect = nullptr;

		if (sideDoors.size() == 0)
		{
			pNewRect = new LG_Rect();

			WallBottomLeft = FirstNode;
			WallBottomRight = SecondNode;

			WallTopLeft = WallBottomLeft;
			WallTopLeft.Z = m_fHeight;

			WallTopRight = WallBottomRight;
			WallTopRight.Z = m_fHeight;

			/// Now the wall is created with all of it's components.
			pNewRect->Init(WallTopLeft, WallTopRight, WallBottomLeft, WallBottomRight);
			/// We now store the new wall that has just been created.
			m_Walls.push_back(pNewRect);
		}

		//TODO: corregir cuando hay 2 puertas o más en un pasillo.
		/// Here we generate all the walls from the right side of the room. And they are stored in a wall vector.
		for (int32 i = 0; i < sideDoors.size(); ++i)
		{
			pNewRect = new LG_Rect();
			///This is for the first iteration
			if (i < 1)
			{
				/// We store the position for the top left node of the wall.
				WallTopLeft = FirstNode;
				WallTopLeft.Z = m_fHeight;

				/// Now the top right is calculated.
				WallTopRight = WallTopLeft;
				/// 
				if (bIsHorizontal)
					WallTopRight.X = sideDoors[i];
				else
					WallTopRight.Y = sideDoors[i];

				///Bottom left node's position is now calculated.
				WallBottomLeft = FirstNode;

				/// Here we calculate the position for the bottom right node of the wall.
				WallBottomRight = WallBottomLeft;
				/// 
				if (bIsHorizontal)
					WallBottomRight.X = sideDoors[i];
				else
					WallBottomRight.Y = sideDoors[i];
			}
			/// This is used in the last iteration
			else if (i + 1 >= sideDoors.size())
			{
				/// The wall is being calculated between the last position from the list, and the floor bottom right corner.
				WallTopRight = SecondNode;
				WallTopRight.Z = m_fHeight;

				WallTopLeft = WallTopRight;

				if (bIsHorizontal)
					WallTopLeft.X = sideDoors[i];
				else
					WallTopLeft.Y = sideDoors[i];

				WallBottomRight = SecondNode;

				WallBottomLeft = WallBottomRight;

				if (bIsHorizontal)
					WallBottomLeft.X = sideDoors[i];
				else
					WallBottomLeft.Y = sideDoors[i];
			}
			/// All the iterations in between.
			else
			{
				/// We skip all pair numbers to avoid writing walls over the doors.
				if (i % 2 == 0)
				{
					continue;
				}
				WallBottomLeft = FirstNode;

				/// We see in which axis we are affecting the wall's bottom left node.
				if (bIsHorizontal)	
					WallBottomLeft.X = sideDoors[i];
				else 
					WallBottomLeft.Y = sideDoors[i];

				/// 
				WallBottomRight = WallBottomLeft;

				/// 
				if (bIsHorizontal)
					WallBottomRight.X = sideDoors[i + 1];
				else
					WallBottomRight.Y = sideDoors[i + 1];

				/// 
				WallTopLeft = WallBottomLeft;
				WallTopLeft.Z = m_fHeight;
				/// 
				WallTopRight = WallTopLeft;
				WallTopRight.Z = m_fHeight;
			}

			/// Now the wall is created with all of it's components.
			pNewRect->Init(WallTopLeft, WallTopRight, WallBottomLeft, WallBottomRight);
			/// We now store the new wall that has just been created.
			m_Walls.push_back(pNewRect);
		}
	}
}
