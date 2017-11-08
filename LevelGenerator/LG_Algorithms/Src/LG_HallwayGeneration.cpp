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
	void LG_HallwayGeneration::Init(float fCorridorWidth, Vector<LG_Rect*>* Rooms)
	{
		//TODO: Este ancho debe depender del minimo del cuarto mas chico de la coneccion.
		m_fHallwayWidth = fCorridorWidth;
		m_pRooms = Rooms;


	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_HallwayGeneration::Destroy()
	{
		//TODO: liberar memoria.
		m_fHallwayWidth = 0;
	}

	//! This function is the only one you need to generate Hallways.
	void LG_HallwayGeneration::Run(Vector<LG_Rect*>* pRooms, float fCorridorWidth)
	{
		Init(fCorridorWidth, pRooms);

		LG_Vector3D AngleVect;
		float fAngle;
		/// The created hallway.
		LG_Rect* pHallway;

		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			//TODO: sacar el ángulo entre las conexiones, ver que caso generar a partir de eso.
			for (int32 j = 0; j < (*m_pRooms)[i]->m_RoomsConnections.size(); ++j)
			{
				/// Makes a vector between the room and it's connections.
				AngleVect = (*m_pRooms)[i]->m_RoomsConnections[j]->m_CenterNode.m_Position - (*m_pRooms)[i]->m_CenterNode.m_Position;
				AngleVect.Normalize();
				/// Get the angle it's got.
				fAngle = LG_Math::Acos(AngleVect.X);

				/// See in which boundaries is the connection, in order to know what kind of hallway to create.
				if (fAngle < _20_DEGREES && fAngle > -_20_DEGREES || fAngle > _160_DEGREES && fAngle < -_160_DEGREES)
				{
					/// If the angle of the connection is inside of this limits, we consider it a horizontal hallway.
					pHallway = MakeHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], false);
					/// Add the hallway in the final vector.
					m_FinalHallways.push_back(pHallway);
				}
				else if (fAngle > _70_DEGREES && fAngle < _110_DEGREES || fAngle < -_70_DEGREES && fAngle > -_110_DEGREES)
				{
					/// If the angle of the connection is inside of this limits, we consider it a vertical hallway.
					pHallway = MakeVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], false);
					/// Add the hallway in the final vector.
					m_FinalHallways.push_back(pHallway);
				}
				else
				{
					/// Any other angle will be represented with a corner hallway.
					MakeCornerHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
				}
			}
		}

		///// Iterates through all of the connections, to make each one of them a hallway.
		//for (int32 i = 0; i < Connections.size(); ++i)
		//{
		//	/// Makes a vector between both nodes of the connection.
		//	AngleVect = Connections[i]->m_pFirstNode->m_Position - Connections[i]->m_pSecondNode->m_Position;
		//	AngleVect.Normalize();
		//	/// Get the angle it's got.
		//	fAngle = LG_Math::Acos(AngleVect.X);

		//	/// Stores in the member variables which rooms are the ones from the connection's nodes
		//	GetConnectionsRooms(Connections[i]);

		//	/// See in which boundaries is the connection, in order to know what kind of hallway to create.
		//	if (fAngle < _20_DEGREES && fAngle > -_20_DEGREES || fAngle > _160_DEGREES && fAngle < -_160_DEGREES)
		//	{
		//		/// If the angle of the connection is inside of this limits, we consider it a horizontal hallway.
		//		pHallway = MakeHorizontalHallway(Connections[i], false);
		//		/// Add the hallway in the final vector.
		//		m_FinalHallways.push_back(pHallway);
		//	}
		//	else if (fAngle > _70_DEGREES && fAngle < _110_DEGREES || fAngle < -_70_DEGREES && fAngle > -_110_DEGREES)
		//	{
		//		/// If the angle of the connection is inside of this limits, we consider it a vertical hallway.
		//		pHallway = MakeVerticalHallway(Connections[i], false);
		//		/// Add the hallway in the final vector.
		//		m_FinalHallways.push_back(pHallway);
		//	}
		//	else
		//	{
		//		/// Any other angle will be represented with a corner hallway.
		//		MakeCornerHallway(Connections[i]);
		//	}
		//}
	}

	//! Creates a vertical hallway between two rooms.
	LG_Rect* LG_HallwayGeneration::MakeVerticalHallway(LG_Rect* Room1, LG_Rect* Room2, bool bIsCorner)
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

		float fTempTopPosY = 0.0f;
		float fTempBottomPosY = 0.0f;

		/// Initialize thee final hallway.
		pFinalHallway = new LG_Rect();

		/// We find the maximum and minimum and maximum positions in the Y axis of the hallway.
		fBottomPosY = LG_Math::Max(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y);
		fTopPosY = LG_Math::Min(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y);

		fTempTopPosY = fTopPosY;
		fTempBottomPosY = fBottomPosY;

		if (!bIsCorner)
		{
			/// Sees if we need to substract or add to the bottom or top position.
			if (Room1->m_CenterNode.m_Position.Y == fTempBottomPosY)
			{
				fBottomPosY -= Room1->m_fHeight / 2;
			}
			else if (Room1->m_CenterNode.m_Position.Y == fTempTopPosY)
			{
				fTopPosY += Room1->m_fHeight / 2;
			}


			if (Room2->m_CenterNode.m_Position.Y == fTempBottomPosY)
			{
				fBottomPosY -= Room2->m_fHeight / 2;
			}
			else if (Room2->m_CenterNode.m_Position.Y == fTempTopPosY)
			{
				fTopPosY += Room2->m_fHeight / 2;
			}
		}

		/// We store the width and height of the hallway. The height depends on the distance between the rooms.
		pFinalHallway->m_fWidth = m_fHallwayWidth;
		pFinalHallway->m_fHeight = fBottomPosY - fTopPosY;

		/// We find the difference in distance on the X axis between both rooms. 
		fDistanceBetweenRooms =
			LG_Math::Max(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X) -
			LG_Math::Min(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X);

		/// If it isn't a straight line we divide the middle position, and then it will be added to the room that's 
		/// nearest to the origin in the X axis. Becoming the middle position between both rooms.
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the X axis, We just add it to the lowest position
		/// to get the middle point in the X axis where we will generate the hallway.
		fMiddlePosX = LG_Math::Min(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X) + fDistanceBetweenRooms;

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

		return pFinalHallway;
	}

	

	//! Creates a horizontal hallway between two rooms.
	//LG_Rect* LG_HallwayGeneration::MakeHorizontalHallway(LG_Edge* Connection, bool bIsCorner)
	LG_Rect* LG_HallwayGeneration::MakeHorizontalHallway(LG_Rect* Room1, LG_Rect* Room2, bool bIsCorner)
	{
		/// Where we store the generated room.
		LG_Rect* pFinalHallway = nullptr;
		/// The middle position in the X axis between both rooms.
		float fMiddlePosY = 0.0f;
		/// the distance between both rooms in the Y axis.
		float fDistanceBetweenRooms = 0.0f;
		/// 
		float fRightPosX = 0.0f;
		/// 
		float fLeftPosX = 0.0f;

		float fTempRightPosX = 0.0f;
		float fTempLeftPosX = 0.0f;

		/// 
		pFinalHallway = new LG_Rect();
		/// 
		fRightPosX = LG_Math::Max(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X);
		fLeftPosX = LG_Math::Min(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X);


		fTempLeftPosX = fLeftPosX;
		fTempRightPosX = fRightPosX;

		if (!bIsCorner)
		{
			/// Sees if we need to substract or add to the bottom or top position.
			if (Room1->m_CenterNode.m_Position.X == fTempRightPosX)
			{
				fRightPosX -= Room1->m_fWidth / 2;
			}
			else if (Room1->m_CenterNode.m_Position.X == fTempLeftPosX)
			{
				fLeftPosX += Room1->m_fWidth / 2;
			}

			if (Room2->m_CenterNode.m_Position.X == fTempRightPosX)
			{
				fRightPosX -= Room2->m_fWidth / 2;
			}
			else if (Room2->m_CenterNode.m_Position.X == fTempLeftPosX)
			{
				fLeftPosX += Room2->m_fWidth / 2;
			}

		}

		/// Assign the final hallway width and height.
		pFinalHallway->m_fWidth = fRightPosX - fLeftPosX;
		pFinalHallway->m_fHeight = m_fHallwayWidth;
		/// 
		fDistanceBetweenRooms =
			LG_Math::Max(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y) -
			LG_Math::Min(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y);
		/// 
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the Y axis, We just add it to the lowest position
		/// to get the middle point in the Y axis where we will generate the hallway.
		fMiddlePosY = LG_Math::Min(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y) + fDistanceBetweenRooms;

		pFinalHallway->m_BottomLeft.m_Position.X = fLeftPosX;
		pFinalHallway->m_BottomLeft.m_Position.Y = fMiddlePosY + pFinalHallway->m_fHeight / 2.0f;
		pFinalHallway->m_BottomLeft.m_Position.Z = 0.0f;

		pFinalHallway->m_BottomRight.m_Position = pFinalHallway->m_BottomLeft.m_Position;
		pFinalHallway->m_BottomRight.m_Position.X += pFinalHallway->m_fWidth;

		pFinalHallway->m_TopRight.m_Position = pFinalHallway->m_BottomRight.m_Position;
		pFinalHallway->m_TopRight.m_Position.Y -= pFinalHallway->m_fHeight;

		pFinalHallway->m_TopLeft.m_Position = pFinalHallway->m_TopRight.m_Position;
		pFinalHallway->m_TopLeft.m_Position.X = pFinalHallway->m_BottomLeft.m_Position.X;

		pFinalHallway->m_CenterNode.m_Position.X = fLeftPosX + (pFinalHallway->m_fWidth / 2.0f);
		pFinalHallway->m_CenterNode.m_Position.Y = fMiddlePosY;
		pFinalHallway->m_CenterNode.m_Position.Z = 0.0f;

		return pFinalHallway;
	}

	//! Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
	void LG_HallwayGeneration::MakeCornerHallway(LG_Rect* Room1, LG_Rect* Room2)
	{
		/// the vertical and horizontal hallways, they're used to check collision with rooms or other hallways.
		LG_Rect* pVerticalHallway = nullptr, *pHorizontalHallway = nullptr;

		CalculateCornerPosition(false, pVerticalHallway, pHorizontalHallway, Room1, Room2);

		for (int32 j = 0; j < m_pRooms->size(); ++j)
		{
			/// See if the iterating rooms collides with the hallway.
			if ((*m_pRooms)[j] != Room1 && (*m_pRooms)[j] != Room2)
			{
				if ((*m_pRooms)[j]->CheckCollision(pVerticalHallway) || (*m_pRooms)[j]->CheckCollision(pHorizontalHallway))
				{
					/// Calculates hallways with the maximum positions.
					CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, Room1, Room2);
					break;
				}
				else
				{
					/// After knowing that it doesn't collide with a room, we make sure that it doesn't collide with another hallway.
					for (int32 k = 0; k < m_FinalHallways.size(); ++k)
					{
						if (m_FinalHallways[k]->CheckCollision(pVerticalHallway) || m_FinalHallways[k]->CheckCollision(pHorizontalHallway))
						{
							/// Calculates hallways with the maximum positions.
							CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, Room1, Room2);
							break;
						}
					}
				}
			}
		}

		/// We store the generated hallways.
		m_FinalHallways.push_back(pVerticalHallway);
		m_FinalHallways.push_back(pHorizontalHallway);
	}

	//! Returns the two rooms that have the iterating connection.
	//void LG_HallwayGeneration::GetConnectionsRooms(LG_Edge* Connection)
	//{
	//	int32 iCount = 0;
	//	/// Used to see if we are assigning the first, or the second room.
	//	bool bFirstRoomAssigned = false;
	//	/// We will associate the connection's ID's with the ones of the rooms.
	//	for (int32 i = 0; i < m_pRooms->size(); ++i)
	//	{
	//		if (
	//			(((*m_pRooms)[i]->m_CenterNode.m_Position == Connection->m_pFirstNode->m_Position) && !bFirstRoomAssigned) ||
	//			(((*m_pRooms)[i]->m_CenterNode.m_Position == Connection->m_pSecondNode->m_Position) && !bFirstRoomAssigned))
	//		{
	//			/// Assign the first room.
	//			m_pRoom1 = (*m_pRooms)[i];
	//			/// Makes sure that it doesn't get in this block of code again.
	//			bFirstRoomAssigned = true;

	//			++iCount;
	//		}
	//		else if (
	//			((*m_pRooms)[i]->m_CenterNode.m_Position == Connection->m_pFirstNode->m_Position) ||
	//			((*m_pRooms)[i]->m_CenterNode.m_Position == Connection->m_pSecondNode->m_Position))
	//		{
	//			/// Assign the second room.
	//			m_pRoom2 = (*m_pRooms)[i];

	//			++iCount;
	//		}
	//	}
	//}

	//! Calculates a position for a corner between two connected rooms.
	void LG_HallwayGeneration::CalculateCornerPosition(bool bIsMaximum, LG_Rect*& VerticalHall, LG_Rect*& HorizontalHall, LG_Rect* Room1, LG_Rect* Room2)
	{
		/// The position that will be used to generate straight hallways between the connected rooms.
		LG_Node* pCorner = new LG_Node();
		LG_Rect* pHallwayCorner = new LG_Rect();

		if (bIsMaximum)
		{
			/// We store the minimum positions value in X, and Y axis.
			pCorner->m_Position.X = LG_Math::Max(
				Room1->m_CenterNode.m_Position.X,
				Room2->m_CenterNode.m_Position.X);

			pCorner->m_Position.Y = LG_Math::Max(
				Room1->m_CenterNode.m_Position.Y,
				Room2->m_CenterNode.m_Position.Y);

			/// This is used to prevent that the corner becomes one of the rooms.
			if (pCorner->m_Position.X == Room1->m_CenterNode.m_Position.X &&
				pCorner->m_Position.Y == Room1->m_CenterNode.m_Position.Y)
			{
				pCorner->m_Position.X = Room2->m_CenterNode.m_Position.X;
			}
			else if (pCorner->m_Position.X == Room2->m_CenterNode.m_Position.X &&
				pCorner->m_Position.Y == Room2->m_CenterNode.m_Position.Y)
			{
				pCorner->m_Position.X = Room1->m_CenterNode.m_Position.X;
			}
		}
		else
		{
			/// We store the minimum positions value in X, and Y axis.
			pCorner->m_Position.X = LG_Math::Min(
				Room1->m_CenterNode.m_Position.X,
				Room2->m_CenterNode.m_Position.X);

			pCorner->m_Position.Y = LG_Math::Min(
				Room1->m_CenterNode.m_Position.Y,
				Room2->m_CenterNode.m_Position.Y);

			/// This is used to prevent that the corner becomes one of the rooms.
			if (pCorner->m_Position.X == Room1->m_CenterNode.m_Position.X &&
				pCorner->m_Position.Y == Room1->m_CenterNode.m_Position.Y)
			{
				pCorner->m_Position.Y = Room2->m_CenterNode.m_Position.Y;
			}
			else if (pCorner->m_Position.X == Room2->m_CenterNode.m_Position.X &&
				pCorner->m_Position.Y == Room2->m_CenterNode.m_Position.Y)
			{
				pCorner->m_Position.Y = Room1->m_CenterNode.m_Position.Y;
			}
		}

		pCorner->m_Position.Z = 0.0f;
		pHallwayCorner->Init(*pCorner, m_fHallwayWidth, m_fHallwayWidth);
		/// 
		if (pCorner->m_Position.X == Room1->m_CenterNode.m_Position.X)
		{
			VerticalHall = MakeVerticalHallway(pHallwayCorner,Room1, false);
			HorizontalHall = MakeHorizontalHallway(pHallwayCorner,Room2, false);
		}
		else if (pCorner->m_Position.Y == Room1->m_CenterNode.m_Position.Y)
		{
			HorizontalHall = MakeHorizontalHallway(pHallwayCorner, Room1, false);
			VerticalHall = MakeVerticalHallway(pHallwayCorner, Room2, false);
		}
		else
		{
			LG_Node* Debug = nullptr;
			Debug = pCorner;
		}
	}
}