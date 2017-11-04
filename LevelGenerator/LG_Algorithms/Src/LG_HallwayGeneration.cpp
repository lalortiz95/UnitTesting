#include "LG_HallwayGeneration.h"

#include <LG_Math.h>
#include <LG_Rect.h>

namespace LevelGenerator
{
	const float LG_HallwayGeneration::_20_DEGREES = LG_Math::PI / 9;
	const float LG_HallwayGeneration::_160_DEGREES = (LG_Math::PI * 8) / 9;
	const float LG_HallwayGeneration::_110_DEGREES = (LG_Math::PI * 11) / 18;
	const float LG_HallwayGeneration::_70_DEGREES = (LG_Math::PI * 7) / 18;

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
		//TODO: Este ancho debe depender del minimo del cuarto mas chico de la coneccion.
		m_fHallwayWidth = fCorridorWidth;
		m_Rooms = Rooms;
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_HallwayGeneration::Destroy()
	{
		//TODO: liberar memoria.
		m_fHallwayWidth = 0;
	}

	//! This function is the only one you need to generate Hallways.
	void LG_HallwayGeneration::Run(Vector<LG_Edge*> Connections, Vector<LG_Rect*> Rooms, float fCorridorWidth)
	{
		Init(fCorridorWidth, Rooms);

		LG_Vector3D AngleVect;
		float fAngle;

		/// Iterates through all of the connections, to make each one of them a hallway.
		for (int32 i = 0; i < Connections.size(); ++i)
		{
			AngleVect = Connections[i]->m_pFirstNode->m_Position - Connections[i]->m_pSecondNode->m_Position;
			AngleVect.Normalize();

			fAngle = LG_Math::Acos(AngleVect.X);

			if (fAngle < _20_DEGREES && fAngle > -_20_DEGREES || fAngle > _160_DEGREES && fAngle < -_160_DEGREES)
			{
				/// If the angle of the connection is inside of this limits, we consider it a horizontal hallway.
				MakeHorizontalHallway(Connections[i]);
			}
			else if (fAngle > _70_DEGREES && fAngle < _110_DEGREES || fAngle < -_70_DEGREES && fAngle > -_110_DEGREES)
			{
				/// If the angle of the connection is inside of this limits, we consider it a vertical hallway.
				MakeVerticalHallway(Connections[i]);
			}
			else
			{
				/// Any other angle will be represented with a corner hallway.
				MakeCornerHallway(Connections[i]);
			}
		}
		m_fHallwayWidth = m_fHallwayWidth;
	}

	//! Creates a vertical hallway between two rooms.
	void LG_HallwayGeneration::MakeVerticalHallway(LG_Edge* Connection)
	{
		/// Where we store the generated room.
		LG_Rect* pFinalHallway = nullptr;
		/// The middle position in the X axis between both rooms.
		float fMiddlePosX = 0.0f;
		/// the distance between both rooms in the X axis.
		float fDistanceBetweenRooms = 0.0f;
		/// 
		float fTopPosY = 0.0f;
		/// 
		float fBottomPosY = 0.0f;

		/// Initialize thee final hallway.
		pFinalHallway = new LG_Rect();

		/// We find the maximum and minimum and maximum positions in the Y axis of the hallway.
		fBottomPosY = LG_Math::Max(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y);
		fTopPosY = LG_Math::Min(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y);

		/// We store the width and height of the hallway. The height depends on the distance between the rooms.
		pFinalHallway->m_fWidth = m_fHallwayWidth;
		pFinalHallway->m_fHeight = fBottomPosY - fTopPosY;

		/// We find the difference in distance on the X axis between both rooms. 
		fDistanceBetweenRooms =
			LG_Math::Max(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X) -
			LG_Math::Min(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X);

		/// If it isn't a straight line we divide the middle position, and then it will be added to the room that's 
		/// nearest to the origin in the X axis. Becoming the middle position between both rooms.
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the X axis, We just add it to the lowest position
		/// to get the middle point in the X axis where we will generate the hallway.
		fMiddlePosX = LG_Math::Min(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X) + fDistanceBetweenRooms;

		/// The bottom left node of the hallway's rect is assigned.
		pFinalHallway->m_BottomLeft.m_Position.X = fMiddlePosX - (m_fHallwayWidth / 2.0f);
		pFinalHallway->m_BottomLeft.m_Position.Y = fBottomPosY;
		pFinalHallway->m_BottomLeft.m_Position.Z = 0.0f;

		/// We initialize the bottom right node of the hallway's rect.
		pFinalHallway->m_BottomRight.m_Position = pFinalHallway->m_BottomLeft.m_Position;
		pFinalHallway->m_BottomRight.m_Position.X += m_fHallwayWidth;

		/// Calculates the top right node of the hallway.
		pFinalHallway->m_TopRight.m_Position = pFinalHallway->m_BottomRight.m_Position;
		pFinalHallway->m_TopRight.m_Position.Y -= pFinalHallway->m_fHeight;

		/// The top left node the hallway's is assigned.
		pFinalHallway->m_TopLeft.m_Position = pFinalHallway->m_TopRight.m_Position;
		pFinalHallway->m_TopLeft.m_Position.X = pFinalHallway->m_BottomLeft.m_Position.X;

		/// Assign the center of the hallway's rect.
		pFinalHallway->m_CenterNode.m_Position.X = fMiddlePosX;
		pFinalHallway->m_CenterNode.m_Position.Y = fTopPosY + ((fBottomPosY - fTopPosY) / 2.0f);
		pFinalHallway->m_CenterNode.m_Position.Z = 0.0f;

		/// We store the generated room.
		m_FinalHallways.push_back(pFinalHallway);
	}

	//! Creates a horizontal hallway between two rooms.
	void LG_HallwayGeneration::MakeHorizontalHallway(LG_Edge* Connection)
	{
		/// Where we store the generated room.
		LG_Rect* pFinalHallway = nullptr;
		/// The middle position in the X axis between both rooms.
		float fMiddlePosY = 0.0f;
		/// the distance between both rooms in the Y axis.
		float fDistanceBetweenRooms = 0.0f;
		/// 
		float fRightX = 0.0f;
		/// 
		float fLeftX = 0.0f;

		/// 
		pFinalHallway = new LG_Rect();
		/// 
		fRightX = LG_Math::Max(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X);
		fLeftX = LG_Math::Min(Connection->m_pFirstNode->m_Position.X, Connection->m_pSecondNode->m_Position.X);

		/// 
		pFinalHallway->m_fWidth = fRightX - fLeftX;
		pFinalHallway->m_fHeight = m_fHallwayWidth;
		/// 
		fDistanceBetweenRooms =
			LG_Math::Max(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y) -
			LG_Math::Min(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y);
		/// 
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the Y axis, We just add it to the lowest position
		/// to get the middle point in the Y axis where we will generate the hallway.
		fMiddlePosY = LG_Math::Min(Connection->m_pFirstNode->m_Position.Y, Connection->m_pSecondNode->m_Position.Y) + fDistanceBetweenRooms;

		pFinalHallway->m_BottomLeft.m_Position.X = fLeftX;
		pFinalHallway->m_BottomLeft.m_Position.Y = fMiddlePosY + pFinalHallway->m_fHeight / 2.0f;
		pFinalHallway->m_BottomLeft.m_Position.Z = 0.0f;

		pFinalHallway->m_BottomRight.m_Position = pFinalHallway->m_BottomLeft.m_Position;
		pFinalHallway->m_BottomRight.m_Position.X += pFinalHallway->m_fWidth;

		pFinalHallway->m_TopRight.m_Position = pFinalHallway->m_BottomRight.m_Position;
		pFinalHallway->m_TopRight.m_Position.Y -= pFinalHallway->m_fHeight;

		pFinalHallway->m_TopLeft.m_Position = pFinalHallway->m_TopRight.m_Position;
		pFinalHallway->m_TopLeft.m_Position.X = pFinalHallway->m_BottomLeft.m_Position.X;

		pFinalHallway->m_CenterNode.m_Position.X = fLeftX + ((fRightX - fLeftX) / 2.0f);
		pFinalHallway->m_CenterNode.m_Position.Y = fMiddlePosY;
		pFinalHallway->m_CenterNode.m_Position.Z = 0.0f;

		/// We store the generated room.
		m_FinalHallways.push_back(pFinalHallway);
	}

	//! Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
	void LG_HallwayGeneration::MakeCornerHallway(LG_Edge* Connection)
	{
		/// The position that will be used to generate straight hallways between the connected rooms.
		LG_Node* pCorner = new LG_Node();

		LG_Edge* pFirstEdge = new LG_Edge();
		LG_Edge* pSecondEdge = new LG_Edge();

		/// We store the minimum positions value in X, and Y axis.
		pCorner->m_Position.X = LG_Math::Min(
			Connection->m_pFirstNode->m_Position.X,
			Connection->m_pSecondNode->m_Position.X);

		pCorner->m_Position.Y = LG_Math::Min(
			Connection->m_pFirstNode->m_Position.Y,
			Connection->m_pSecondNode->m_Position.Y);

		pCorner->m_Position.Z = 0.0f;

		/// This is used to prevent that the corner becomes one of the rooms.
		if (pCorner->m_Position.X == Connection->m_pFirstNode->m_Position.X &&
			pCorner->m_Position.Y == Connection->m_pFirstNode->m_Position.Y)
		{
			pCorner->m_Position.Y = Connection->m_pSecondNode->m_Position.Y;
		}
		else if (pCorner->m_Position.X == Connection->m_pSecondNode->m_Position.X &&
			pCorner->m_Position.Y == Connection->m_pSecondNode->m_Position.Y)
		{
			pCorner->m_Position.Y = Connection->m_pFirstNode->m_Position.Y;
		}

		/// 
		if (pCorner->m_Position.X == Connection->m_pFirstNode->m_Position.X)
		{
			pFirstEdge->Init(pCorner, Connection->m_pFirstNode);
			/// We create a vertical hallway
			MakeVerticalHallway(pFirstEdge);
			pSecondEdge->Init(pCorner, Connection->m_pSecondNode);
			/// We create a horiozontal hallway.
			MakeHorizontalHallway(pSecondEdge);
		}
		else if (pCorner->m_Position.Y == Connection->m_pFirstNode->m_Position.Y)
		{
			/// We create an horizontal hallway
			pFirstEdge->Init(pCorner, Connection->m_pFirstNode);
			MakeHorizontalHallway(pFirstEdge);
			/// 
			pSecondEdge->Init(pCorner, Connection->m_pSecondNode);
			MakeVerticalHallway(pSecondEdge);
		}


		//TODO: Checar  colisiones contra todos los cuartos, y los demás pasillos.
		//		hacer que las funciones de make horizontal y vertical hallway regresen el cuarto que se agregó
		//		Revisar si no colisiona, y si lo hace llamar una función que calcula máximos y minimos.
		//		TODO: crear función que calcule posiciónes maximas o minimas, dependiendo de un bool.

		//for (int32 j = 0; j < m_Rooms.size(); ++j)
		//{
		//	/// See if the iterating rooms collides with the hallway.
		//	if (m_Rooms[j]->CheckCollision(pHallway1) || m_Rooms[j]->CheckCollision(pHallway2))
		//	{
		//		//TODO. calcular rectangulos con maximum positions.
		//	}
		//}

		///// We store the generated room.
		//m_FinalHallways.push_back(pHallway1);
		//m_FinalHallways.push_back(pHallway2);
	}
}