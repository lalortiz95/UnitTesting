#include "LG_Room.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Room::LG_Room()
	{
	}

	//! Parameter constructor
	LG_Room::LG_Room(LG_Vector3D vPosToSpawn, float fWidth, float fHeight)
	{
		Init(vPosToSpawn, fWidth, fHeight);
	}

	//! Default destructor
	LG_Room::~LG_Room()
	{
		/// Call the destroy function to release memory.
		Destroy();
	}

	//! This function initialize the area of the room.
	void LG_Room::Init(LG_Vector3D vPosToSpawn, float fWidth, float fHeight)
	{
		/// Assign memory to the room area using the constructor parameter of the rect.
		m_pRect = new LG_Rect(vPosToSpawn, fWidth, fHeight);
	}

	//! This function release all the memory that was used in the room.
	void LG_Room::Destroy()
	{
		/// 
		m_pRect->Destroy();
		delete m_pRect;
		m_pRect = nullptr;

		///  Clears the room's connections.
		if (m_RoomsConnections.size() != 0)
		{
			for (Vector<LG_Room*>::iterator itt = m_RoomsConnections.begin(); itt != m_RoomsConnections.end(); ++itt)
			{
				*itt = nullptr;
			}
			m_RoomsConnections.clear();
		}
		
		//TODO: La memoria de las puertas se libera en el pasillo no en el cuarto pero el cuarto se elimina primero que el pasillo.
		for (int32 i = 0; i < m_Doors.size(); i++)
		{
			m_Doors[i] = nullptr;
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
				if (RoomsVect[j]->m_pRect->m_CenterNode.m_Position == NodeConections[i]->m_Position)
				{
					m_RoomsConnections.push_back(RoomsVect[j]);
					break;
				}
			}
		}
	}
}
