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
		///  A Temp vectors to store the doors.
		Vector<float> RightDoors, LeftDoors, TopDoors, BottomDoors;

		/// Iterate the vector of doors to find their sides counter clock-wise.
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

		
			std::sort(RightDoors.begin(), RightDoors.end());
			std::sort(LeftDoors.begin(), LeftDoors.end());
			std::sort(TopDoors.begin(), TopDoors.end());
			std::sort(BottomDoors.begin(), BottomDoors.end());
	
			//TODO: Se necesita generar una posicion temporal para cada nodo utilizando los de la lista de flotantes y los de el m_pFloor 
			// Los que se generan temporal deben de checarse a mano uno por uno.
		for (int32 i = 0; i < RightDoors.size(); ++i)
		{
			LG_Rect* pNewRect = new LG_Rect();
			//LG_Vector3D TempPosition = ;
			//pNewRect->Init(m_pFloor->m_BottomLeft, RightDoors[i],)
		}

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
}
