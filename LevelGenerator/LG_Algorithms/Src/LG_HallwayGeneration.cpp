#include "LG_HallwayGeneration.h"

#include <LG_Math.h>
#include <LG_Rect.h>

namespace LevelGenerator
{
	//! Default constructor
	LG_HallwayGeneration::LG_HallwayGeneration()
	{

	}

	//! Default destructor
	LG_HallwayGeneration::~LG_HallwayGeneration()
	{
		Destroy();
	}

	//! Initializes the member variables of the class.
	void LG_HallwayGeneration::Init(float fCorridorWidth, Vector<LG_Rect*> Rooms)
	{
		m_fHallwayWidth = fCorridorWidth;
		m_Rooms = Rooms;
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_HallwayGeneration::Destroy()
	{
		m_fHallwayWidth = 0;
	}

	//! This function is the only one you need to generate Hallways.
	void LG_HallwayGeneration::Run(Vector<LG_Edge*> Connections, Vector<LG_Rect*> Rooms, float fCorridorWidth)
	{
		Init(fCorridorWidth, Rooms);

		/// Iterates through all of the connections, to make each one of them a hallway.
		for (int32 i = 0; i < Connections.size(); ++i)
		{
			//TODO: calcular el ángulo de la conexión actual, y ver que clase de pasillo debe generar.
			// TODO: probar las funciones que generan los pasillos.
		}
	}

	//! Creates a vertical hallway between two rooms.
	void LG_HallwayGeneration::MakeVerticalHallway(LG_Edge* Connection)
	{
		/// Where we store the generated room.
		LG_Rect FinalRoom;
		/// The middle position in the X axis between both rooms.
		float fMiddlePos;
	
		fMiddlePos = 
			LG_Math::Max(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X) -
			LG_Math::Min(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X);
		
		/// We have the difference between both room's positions in the X axis, We just add it to the lowest position
		/// to get the middle point in the X axis where we will generate the hallway.
		fMiddlePos += LG_Math::Min(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X);

		/// We create a new rectangle with the desired positions and it's width.
		FinalRoom.Init(
			LG_Vector3D(fMiddlePos, Connection->m_pFirstNode->m_Position.Y, 0), 
			LG_Vector3D(fMiddlePos, Connection->m_pSecondNode->m_Position.Y, 0), 
			fMiddlePos);

		/// We store the generated room.
		m_FinalHallways.push_back(&FinalRoom);
	}

	//! Creates a horizontal hallway between two rooms.
	void LG_HallwayGeneration::MakeHorizontalHallway(LG_Edge* Connection)
	{
		/// Where we store the generated room.
		LG_Rect FinalRoom;
		/// The middle position in the X axis between both rooms.
		float fMiddlePos;

		fMiddlePos =
			LG_Math::Max(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y) -
			LG_Math::Min(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y);

		/// We have the difference between both room's positions in the Y axis, We just add it to the lowest position
		/// to get the middle point in the Y axis where we will generate the hallway.
		fMiddlePos += LG_Math::Min(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y);

		/// We create a new rectangle with the desired positions and it's width.
		FinalRoom.Init(
			LG_Vector3D(fMiddlePos, Connection->m_pFirstNode->m_Position.X, 0),
			LG_Vector3D(fMiddlePos, Connection->m_pSecondNode->m_Position.X, 0),
			fMiddlePos);

		/// We store the generated room.
		m_FinalHallways.push_back(&FinalRoom);
	}

	//! Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
	void LG_HallwayGeneration::MakeCornerHallway(LG_Edge* Connection)
	{
		/// The position that will be used to generate straight hallways between the connected rooms.
		LG_Node Corner;
		/// The visual representation of the hallway, 2 rectangles that makes the new connection.
		LG_Rect Hallway1, Hallway2;

		/// We store the minimum positions value in X, and Y axis.
		Corner.m_Position.X = LG_Math::Min(
			Connection->m_pFirstNode->m_Position.X,
			Connection->m_pSecondNode->m_Position.X);

		Corner.m_Position.Y = LG_Math::Min(
			Connection->m_pFirstNode->m_Position.Y,
			Connection->m_pSecondNode->m_Position.Y);

		/// This is used to prevent that the corner becomes one of the rooms.
		if (Corner.m_Position.X == Connection->m_pFirstNode->m_Position.X &&
			Corner.m_Position.Y == Connection->m_pFirstNode->m_Position.Y)
		{
			Corner.m_Position.Y = Connection->m_pSecondNode->m_Position.Y;
		}
		else if (Corner.m_Position.X == Connection->m_pSecondNode->m_Position.X &&
			Corner.m_Position.Y == Connection->m_pSecondNode->m_Position.Y)
		{
			Corner.m_Position.Y = Connection->m_pFirstNode->m_Position.Y;
		}

		/// We generate the rectangles that represents the hallways between the rooms and the corner.
		Hallway1.Init(Connection->m_pFirstNode->m_Position, Corner.m_Position, m_fHallwayWidth);
		Hallway2.Init(Connection->m_pSecondNode->m_Position, Corner.m_Position, m_fHallwayWidth);

		//TODO: checar  colisiones contra todos los cuartos, y los demás pasillos.
		for (int32 j = 0; j < m_Rooms.size(); ++j)
		{
			/// See if the iterating rooms collides with the hallway.
			if (m_Rooms[j]->CheckCollision(Hallway1) || m_Rooms[j]->CheckCollision(Hallway2))
			{
				//TODO. calcular rectangulos con maximum positions.
			}
		}
	}
}