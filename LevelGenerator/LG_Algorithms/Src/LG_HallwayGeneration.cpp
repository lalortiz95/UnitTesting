#include "LG_HallwayGeneration.h"

#include <LG_Math.h>
#include <LG_Rect.h>

namespace LevelGenerator
{
	const float LG_HallwayGeneration::_20_DEGREES = LG_Math::PI / 9;
	const float LG_HallwayGeneration::_70_DEGREES = (LG_Math::PI * 7) / 18;
	const float LG_HallwayGeneration::_110_DEGREES = (LG_Math::PI * 11) / 18;
	const float LG_HallwayGeneration::_160_DEGREES = (LG_Math::PI * 8) / 9;
	const float  LG_HallwayGeneration::_200_DEGREES = (LG_Math::PI * 10) / 9;
	const float  LG_HallwayGeneration::_250_DEGREES = (LG_Math::PI * 25) / 18;
	const float  LG_HallwayGeneration::_290_DEGREES = (LG_Math::PI * 29) / 18;
	const float  LG_HallwayGeneration::_340_DEGREES = (LG_Math::PI * 34) / 18;


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

		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			(*m_pRooms)[i]->m_bIsChecked = false;
		}
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_HallwayGeneration::Destroy()
	{
		/// We generate an annonymus temporary vector and rezise our final hallway. The memory then is released by STL.
		Vector<LG_Rect*>().swap(m_FinalHallways);

		//TODO: liberar memoria.
		//(Vector<LG_Rect*>*)(m_pRooms)->swap(*m_pRooms);
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

		/// Makes hallways with the connections from every room.
		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			/// Iterates through every room's connections.
			for (int32 j = 0; j < (*m_pRooms)[i]->m_RoomsConnections.size(); ++j)
			{
				if (!(*m_pRooms)[i]->m_RoomsConnections[j]->m_bIsChecked)
				{
					/// Makes a vector between the room and it's connections.
					AngleVect = (*m_pRooms)[i]->m_RoomsConnections[j]->m_CenterNode.m_Position - (*m_pRooms)[i]->m_CenterNode.m_Position;
					AngleVect.Normalize();
					/// Get the angle it's got.
					fAngle = LG_Math::Acos(AngleVect.X);

					/// See in which boundaries is the connection, in order to know what kind of hallway to create.
					if (fAngle < _20_DEGREES || fAngle > _160_DEGREES)
					{
						/// If the angle of the connection is inside of this limits, we consider it a horizontal hallway.
						//MakeHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
						pHallway = MakeHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
						m_FinalHallways.push_back(pHallway);
					}
					else if (fAngle > _70_DEGREES && fAngle < _110_DEGREES)
					{
						/// If the angle of the connection is inside of this limits, we consider it a vertical hallway.
						//MakeVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
						pHallway = MakeVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
						m_FinalHallways.push_back(pHallway);
					}
					else
					{
						/// Any other angle will be represented with a corner hallway.
						MakeCornerHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
					}

				}
			}
			(*m_pRooms)[i]->m_bIsChecked = true;
		}
	}

	//! Creates a vertical hallway between two rooms.
	LG_Rect* LG_HallwayGeneration::MakeVerticalHallway(LG_Rect* Room1, LG_Rect* Room2)
	{
		/// Where we store the generated room.
		LG_Rect* pFinalHallway = nullptr;
		/// The middle position in the X axis between both rooms.
		float fMiddlePosX = 0.0f;
		/// the distance between both rooms in the X axis.
		float fDistanceBetweenRooms = 0.0f;
		/// The position of the room that's got a higher value in the Y axis
		float fTopPosY = 0.0f;
		/// The position of the room that's got a lower value in the Y axis.
		float fBottomPosY = 0.0f;
		/// The position of the room's that's got a lower value in the X axis.
		float fLeftPosX;
		/// The position of the room's that's got a lower value in the X axis.
		float fRightPosX;

		float fTempTopPosY = 0.0f;
		float fTempBottomPosY = 0.0f;

		/// Initialize thee final hallway.
		pFinalHallway = new LG_Rect();

		/// We find the maximum and minimum and maximum positions in the Y axis of the hallway.
		fBottomPosY = LG_Math::Max(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y);
		fTopPosY = LG_Math::Min(Room1->m_CenterNode.m_Position.Y, Room2->m_CenterNode.m_Position.Y);

		/// We find the maximum and minimum and maximum positions in the X axis of the hallway.
		fRightPosX = LG_Math::Max(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X);
		fLeftPosX = LG_Math::Min(Room1->m_CenterNode.m_Position.X, Room2->m_CenterNode.m_Position.X);

		fTempTopPosY = fTopPosY;
		fTempBottomPosY = fBottomPosY;

		/// Sees if we need to subtract or add to the bottom or top position.
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

		/// We store the hallway that has just been generated in the final hallways vector.
		//m_FinalHallways.push_back(pFinalHallway);

		return pFinalHallway;
	}



	//! Creates a horizontal hallway between two rooms.
	LG_Rect* LG_HallwayGeneration::MakeHorizontalHallway(LG_Rect* Room1, LG_Rect* Room2)
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

		/// Sees if we need to subtract or add to the bottom or top position.
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

		//TODO: make sure that the hall fits though both rooms.
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

		/// We store the hallway that has just been generated in the final hallways vector.
		//m_FinalHallways.push_back(pFinalHallway);

		return pFinalHallway;
	}

	//! Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
	void LG_HallwayGeneration::MakeCornerHallway(LG_Rect* pRoom1, LG_Rect* pRoom2)
	{
		/// the vertical and horizontal hallways, they're being used to check collision with rooms or other hallways.
		LG_Rect* pVerticalHallway = nullptr, *pHorizontalHallway = nullptr;

		/// See if a vertical or horizontal room can be placed between both rooms. This happens when they're too close to each other.
		if (SetRoomsCases(pRoom1, pRoom2))
		{
			/// We verify that a straight hallway fits through bought rooms.
			if (CheckForStraightHallway(pRoom1, pRoom2))
			{
				//TODO Esto se puede simplificar.
				return;
			}
		}

		CalculateCornerPosition(false, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);

		for (int32 j = 0; j < m_pRooms->size(); ++j)
		{
			/// See if the iterating rooms collides with the hallway.
			if ((*m_pRooms)[j] != pRoom1 && (*m_pRooms)[j] != pRoom2)
			{
				if (pVerticalHallway->CheckCollision((*m_pRooms)[j]) || pHorizontalHallway->CheckCollision((*m_pRooms)[j]))
				{
					/// Calculates hallways with the maximum positions.
					CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);
					break;
				}
				else
				{
					/// After knowing that it doesn't collide with a room, we make sure that it doesn't collide with another hallway.
					for (int32 k = 0; k < m_FinalHallways.size(); ++k)
					{
						if (pVerticalHallway != m_FinalHallways[k] && pHorizontalHallway != m_FinalHallways[k])
						{
							if (pVerticalHallway->CheckCollision(m_FinalHallways[k]) || pHorizontalHallway->CheckCollision(m_FinalHallways[k]))
							{
								/// Calculates hallways with the maximum positions.
								CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);
								break;
							}
						}
					}
				}
			}
		}

		/// We store the generated hallways.
		m_FinalHallways.push_back(pVerticalHallway);
		m_FinalHallways.push_back(pHorizontalHallway);
	}

	//! Calculates each room's cases.
	bool LG_HallwayGeneration::SetRoomsCases(LG_Rect * pRoom1, LG_Rect * pRoom2)
	{
		/// Indicates that the first room is to the left of the second one.
		if (pRoom1->m_TopLeft.m_Position.X < pRoom2->m_TopLeft.m_Position.X)
		{
			if ((pRoom1->m_TopRight.m_Position.Y > pRoom2->m_BottomLeft.m_Position.Y  && 
				pRoom1->m_TopRight.m_Position.X < pRoom2->m_BottomLeft.m_Position.X) ||
				(pRoom1->m_BottomRight.m_Position.Y < pRoom2->m_TopLeft.m_Position.Y &&
				pRoom1->m_BottomRight.m_Position.X < pRoom2->m_TopLeft.m_Position.X))
			{
				return false;
			}

			/// We see whether the room is at the top, or bottom.
			if (pRoom1->m_TopRight.m_Position.Y <= pRoom2->m_TopLeft.m_Position.Y)
			{
				/// TOP
				pRoom1->m_iRoomCase = TOP_LEFT;
				pRoom2->m_iRoomCase = BOTTOM_RIGHT;
				return true;
			}
			else
			{
				/// BOTTOM
				pRoom1->m_iRoomCase = BOTTOM_LEFT;
				pRoom2->m_iRoomCase = TOP_RIGHT;
				return true;
			}
		}
		/// We check if the top left node is in between of the top right and left nodes of the second room.
		else if (pRoom1->m_TopLeft.m_Position.X >= pRoom2->m_TopLeft.m_Position.X)
		{

			if ((pRoom1->m_BottomLeft.m_Position.Y < pRoom2->m_TopRight.m_Position.Y  &&
				pRoom1->m_BottomLeft.m_Position.X > pRoom2->m_TopRight.m_Position.X) ||
				(pRoom1->m_TopLeft.m_Position.Y > pRoom2->m_BottomRight.m_Position.Y &&
					pRoom1->m_TopLeft.m_Position.X > pRoom2->m_BottomRight.m_Position.X))
			{
				return false;
			}

			/// We see whether the room is at the top, or bottom.
			if (pRoom1->m_TopLeft.m_Position.Y < pRoom2->m_TopLeft.m_Position.Y)
			{
				/// TOP
				pRoom1->m_iRoomCase = TOP_RIGHT;
				pRoom2->m_iRoomCase = BOTTOM_LEFT;
				return true;
			}
			else
			{
				/// BOTTOM
				pRoom1->m_iRoomCase = BOTTOM_RIGHT;
				pRoom2->m_iRoomCase = TOP_LEFT;
				return true;
			}
		}
		return false;
	}

	//! Check if we can do an horizontal or vertical hallway depending on the room's case.
	bool LG_HallwayGeneration::CheckForStraightHallway(LG_Rect * pRoom1, LG_Rect * pRoom2)
	{

		/// The first room's case is TOP_LEFT, and the second one's is BOTTOMRIGHT.
		if (pRoom1->m_iRoomCase == TOP_LEFT)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_BottomRight.m_Position.Y >= pRoom2->m_TopLeft.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom1->m_BottomRight.m_Position.Y - pRoom2->m_TopLeft.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					
					m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
			/// Meaning room 1 is on top of room 2.
			else 
			{
				/// We see if the hallway fits.
				if (pRoom1->m_BottomRight.m_Position.X - pRoom2->m_TopLeft.m_Position.X >= m_fHallwayWidth)
				{
					/// Now a new vertical hallway is created.
					m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// The first room's case is TOP_RIGHT, and the second one's is BOTTOMLEFT.
		else if (pRoom1->m_iRoomCase == TOP_RIGHT)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_BottomLeft.m_Position.Y >= pRoom2->m_TopRight.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom1->m_BottomLeft.m_Position.Y - pRoom2->m_TopRight.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
			/// Meaning room 1 is on top of room 2.
			else 
			{
				/// We see if the hallway fits.
				if (pRoom2->m_TopRight.m_Position.X - pRoom1->m_BottomLeft.m_Position.X >= m_fHallwayWidth)
				{
					/// Now a new vertical hallway is created.
					m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// CHECK this one
		else if (pRoom1->m_iRoomCase == BOTTOM_LEFT)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_TopRight.m_Position.Y <= pRoom2->m_BottomLeft.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom2->m_BottomLeft.m_Position.Y - pRoom1->m_TopRight.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
			/// Meaning room 2 is on top of room 1.
			else 
			{
				/// We see if the hallway fits.
				if (pRoom1->m_TopRight.m_Position.X - pRoom2->m_BottomLeft.m_Position.X >= m_fHallwayWidth)
				{
					/// Now a new vertical hallway is created.
					m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// 
		else if (pRoom1->m_iRoomCase == BOTTOM_RIGHT)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_TopLeft.m_Position.Y <= pRoom2->m_BottomRight.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom2->m_BottomRight.m_Position.Y - pRoom1->m_TopLeft.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
			/// Meaning room 2 is on top of room 1.
			else 
			{
				/// We see if the hallway fits.
				if (pRoom2->m_BottomRight.m_Position.X - pRoom1->m_TopLeft.m_Position.X >= m_fHallwayWidth)
				{
					/// Now a new vertical hallway is created.
					m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		return false;
	}

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
				pCorner->m_Position.X = Room2->m_CenterNode.m_Position.X;
			}
			else if (pCorner->m_Position.X == Room2->m_CenterNode.m_Position.X &&
				pCorner->m_Position.Y == Room2->m_CenterNode.m_Position.Y)
			{
				pCorner->m_Position.X = Room1->m_CenterNode.m_Position.X;
			}
		}

		pCorner->m_Position.Z = 0.0f;
		pHallwayCorner->Init(*pCorner, m_fHallwayWidth, m_fHallwayWidth);
		/// 
		if (pCorner->m_Position.X == Room1->m_CenterNode.m_Position.X)
		{
			VerticalHall = MakeVerticalHallway(pHallwayCorner, Room1);
			HorizontalHall = MakeHorizontalHallway(pHallwayCorner, Room2);
		}
		else if (pCorner->m_Position.Y == Room1->m_CenterNode.m_Position.Y)
		{
			HorizontalHall = MakeHorizontalHallway(pHallwayCorner, Room1);
			VerticalHall = MakeVerticalHallway(pHallwayCorner, Room2);
		}
	}

	//! 
	void LG_HallwayGeneration::GenerateHallwayPollygon(LG_Rect * Room1)
	{
		/// The final polygon that represents the hallway. For this case is a simple square.
		LG_Polygon* Hallway = nullptr;
		/// the edge that will be filled in order to generate the final hallway.
		LG_Edge* EdgeToAdd = nullptr;

		/// Assign memory to the edge that forms the polygon.
		EdgeToAdd = new LG_Edge();
		///Initialize the first vector of the polygon.
		EdgeToAdd->Init(&Room1->m_TopLeft, &Room1->m_TopRight);
		/// 
		Hallway->InsertEdgeToVector(EdgeToAdd);

		/// Assign memory to the edge that forms the polygon.
		EdgeToAdd = new LG_Edge();
		/// 
		EdgeToAdd->Init(&Room1->m_TopRight, &Room1->m_BottomRight);
		/// 
		Hallway->InsertEdgeToVector(EdgeToAdd);

		/// Assign memory to the edge that forms the polygon.
		EdgeToAdd = new LG_Edge();
		/// 
		EdgeToAdd->Init(&Room1->m_BottomRight, &Room1->m_BottomLeft);
		/// 
		Hallway->InsertEdgeToVector(EdgeToAdd);

		/// Assign memory to the edge that forms the polygon.
		EdgeToAdd = new LG_Edge();
		/// 
		EdgeToAdd->Init(&Room1->m_BottomLeft, &Room1->m_TopLeft);
		/// 
		Hallway->InsertEdgeToVector(EdgeToAdd);

		/// Add the finished hallway.
		//m_FinalHallways.push_back(Hallway);
	}

}