#include "LG_HallwayGeneration.h"

#include <LG_Math.h>
#include <LG_Vector2D.h>

namespace LevelGenerator
{
	//! Default constructor
	LG_HallwayGeneration::LG_HallwayGeneration()
	{
		m_pRooms = nullptr;
		m_fHallwayWidth = 0.0f;
		m_FinalHallways.clear();
	}

	//! Default destructor
	LG_HallwayGeneration::~LG_HallwayGeneration()
	{
		Destroy();
	}

	//! Initializes the member variables of the class.
	void LG_HallwayGeneration::Init(float fCorridorWidth, Vector<LG_Room*>* Rooms)
	{
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
		/// Repeat until the vector of Hallways has empty.
		while (m_FinalHallways.size() != 0)
		{
			/// Call the destroy function of the last element of the Hallway vector.
			m_FinalHallways[m_FinalHallways.size() - 1]->Destroy();
			/// Delete the memory of the last element.
			delete m_FinalHallways[m_FinalHallways.size() - 1];
			/// pop the last element.
			m_FinalHallways.pop_back();
		}
		/// Clear the vector of hallways.
		m_FinalHallways.clear();
		/// Reset the value of this variable.
		m_fHallwayWidth = 0.0f;
		/// Set as nullptr.
		m_pRooms = nullptr;
	}

	//! This function is the only one you need to generate Hallways.
	void LG_HallwayGeneration::Run(Vector<LG_Room*>* pRooms, float fCorridorWidth, float fHeight)
	{
		Init(fCorridorWidth, pRooms);

		///
		LG_Vector3D MidPoint(0, 0, 0);
		///
		LG_Vector2D Max_Pos;
		///
		LG_Vector2D Min_Pos;

		/// 
		LG_Hallway* pCorner = nullptr;

		/// We iterate all the rooms and it's connections to make a hallway for every connection between them.
		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			for (int32 j = 0; j < (*m_pRooms)[i]->m_RoomsConnections.size(); ++j)
			{
				if (!(*m_pRooms)[i]->m_RoomsConnections[j]->m_bIsChecked)
				{
					/// The mid point between both iterating rooms is calculated.
					MidPoint = (*m_pRooms)[i]->m_pFloor->m_CenterNode.m_Position.MidPoint((*m_pRooms)[i]->m_RoomsConnections[j]->m_pFloor->m_CenterNode.m_Position);

					/// Assign the max value in the X Axis between both room's left nodes.
					Max_Pos.X = LG_Math::Max((*m_pRooms)[i]->m_pFloor->m_BottomLeft.m_Position.X, (*m_pRooms)[i]->m_RoomsConnections[j]->m_pFloor->m_BottomLeft.m_Position.X);
					/// Assign the max value in the Y Axis between both room's right nodes.
					Max_Pos.Y = LG_Math::Max((*m_pRooms)[i]->m_pFloor->m_TopRight.m_Position.Y, (*m_pRooms)[i]->m_RoomsConnections[j]->m_pFloor->m_TopRight.m_Position.Y);

					/// Assign the min value in the X Axis between both room's bottom nodes.
					Min_Pos.X = LG_Math::Min((*m_pRooms)[i]->m_pFloor->m_BottomRight.m_Position.X, (*m_pRooms)[i]->m_RoomsConnections[j]->m_pFloor->m_BottomRight.m_Position.X);
					/// Assign the min value in the Y Axis between both room's up nodes.
					Min_Pos.Y = LG_Math::Min((*m_pRooms)[i]->m_pFloor->m_BottomRight.m_Position.Y, (*m_pRooms)[i]->m_RoomsConnections[j]->m_pFloor->m_BottomRight.m_Position.Y);

					/// We now check if the mid point is inside of the room's boundaries.
					if (MidPoint.X > Max_Pos.X && MidPoint.X < Min_Pos.X)
					{
						if (MidPoint.X - m_fHallwayWidth / 2 > Max_Pos.X)
						{
							if (MidPoint.X + m_fHallwayWidth / 2 < Min_Pos.X)
							{
								/// Generate a vertical hallway.
								GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
								continue;
							}
							else
							{
								float fDifference = (MidPoint.X + m_fHallwayWidth / 2) - Min_Pos.X;
								if (((MidPoint.X - m_fHallwayWidth / 2) - fDifference) > Max_Pos.X)
								{
									MidPoint.X -= fDifference;
									/// Generate a vertical hallway.
									GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
									continue;
								}
							}
						}
						else
						{
							float fDifference = Max_Pos.X - (MidPoint.X - m_fHallwayWidth / 2);
							if (((MidPoint.X + m_fHallwayWidth / 2) + fDifference) < Min_Pos.X)
							{
								MidPoint.X += fDifference;
								/// Generate a vertical hallway.
								GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
								continue;
							}
						}
					}
					else if (MidPoint.Y > Max_Pos.Y && MidPoint.Y < Min_Pos.Y)
					{
						if (MidPoint.Y - m_fHallwayWidth / 2 > Max_Pos.Y)
						{
							if (MidPoint.Y + m_fHallwayWidth / 2 < Min_Pos.Y)
							{
								/// Generate a vertical hallway.
								GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
								continue;
							}
							else
							{
								float fDifference = (MidPoint.Y + m_fHallwayWidth / 2) - Min_Pos.Y;
								if (((MidPoint.Y - m_fHallwayWidth / 2) - fDifference) > Max_Pos.Y)
								{
									MidPoint.Y -= fDifference;
									/// Generate a vertical hallway.
									GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
									continue;
								}
							}
						}
						else
						{
							float fDifference = Max_Pos.Y - (MidPoint.Y - m_fHallwayWidth / 2);
							if (((MidPoint.Y + m_fHallwayWidth / 2) + fDifference) < Min_Pos.Y)
							{
								MidPoint.Y += fDifference;
								/// Generate a vertical hallway.
								GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint, fHeight);
								continue;
							}
						}
					}

					/// When it couldn't fit in any case, we generate a L shaped hallway.
					m_FinalHallways.push_back(GenerateCornerHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], fHeight));

				}/// Closing If the connection have not been checked.
			}/// Second for
			(*m_pRooms)[i]->m_bIsChecked = true;
		}/// First for.

		bool bCheckCollisionWithHallways = true;

		//TODO: Una en un chingo vale verga se queda en el while sin salir... que pedo correjir..
		//TODO: Tambien con una separacion muy grande ocurre el mismo problema... que pedo correjir.
		/// We will now check collision between the generated corner hallways, and the rooms. So that no hallway overlaps with nothing.
		while (bCheckCollisionWithHallways)
		{
			bCheckCollisionWithHallways = false;
			/// First the hallways are iterated.
			for (int32 iActual = 0; iActual < m_FinalHallways.size(); ++iActual)
			{
				/// There's only need to check the corner hallways.
				if (m_FinalHallways[iActual]->m_eHallwayType != CORNER) continue;

				/// We iterate against all the other hallways.
				for (int32 iIterating = 0; iIterating < m_FinalHallways.size(); ++iIterating)
				{
					/// We make sure that we're not checking collision between the same hallways.
					if (m_FinalHallways[iActual] != m_FinalHallways[iIterating])
					{
						/// We now check collision between both hallways.
						if (m_FinalHallways[iActual]->CheckCollisionWithHallway(m_FinalHallways[iIterating]))
						{
							LG_Room* TempRoom1 = m_FinalHallways[iActual]->m_pParentRoom_2;
							LG_Room* TempRoom2 = m_FinalHallways[iActual]->m_pParentRoom_1;
							m_FinalHallways[iActual]->Destroy();
							delete m_FinalHallways[iActual];
							m_FinalHallways.erase(m_FinalHallways.begin() + iActual);
							m_FinalHallways.push_back(GenerateCornerHallway(TempRoom1, TempRoom2, fHeight));
							bCheckCollisionWithHallways = true;
							break;
						}
					}
				}
				if (bCheckCollisionWithHallways) break;
			}
		}


		/// Once we have all the doors created, we insert them to the rooms.
		/// First the hallways are iterated.
		for (int32 iActual = 0; iActual < m_FinalHallways.size(); ++iActual)
		{
			/// There's only need to check the corner hallways.
			if (m_FinalHallways[iActual]->m_eHallwayType == VERTICAL)
			{

				if ((m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y)
					|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_TopLeft.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y))
				{
					m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
					m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
				}
				else
				{
					m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
					m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
				}
			}

			else if (m_FinalHallways[iActual]->m_eHallwayType == HORIZONTAL)
			{
				if ((m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X)
					|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X))
				{
					m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
					m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
				}
				else
				{
					m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
					m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
				}
			}

			else
			{
				/// Assign the second corner values
				pCorner = ReorganizeCornerHallway(m_FinalHallways[iActual], fHeight);
				/// If the second corner have memory add to the vector and erase the actual hallway from the vector.
				if (pCorner != nullptr)
				{
					m_FinalHallways.erase(m_FinalHallways.begin() + iActual);
					m_FinalHallways.insert(m_FinalHallways.begin() + iActual, pCorner);

					if ((m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_TopRight.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y))
					{
						m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
						m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
					}
					else
					{
						m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
						m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
					}
				}
				/// 
				else
				{
					if ((m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.X == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.X)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_TopRight.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y)
						|| (m_FinalHallways[iActual]->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.Y == m_FinalHallways[iActual]->m_pFirstDoor->m_pFirstPosition->m_Position.Y))
					{
						m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
						m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
					}
					else
					{
						m_FinalHallways[iActual]->m_pParentRoom_1->m_Doors.push_back(m_FinalHallways[iActual]->m_pSecondDoor);
						m_FinalHallways[iActual]->m_pParentRoom_2->m_Doors.push_back(m_FinalHallways[iActual]->m_pFirstDoor);
					}
				}
			}
		}

	}

	//! Creates a vertical hallway between two rooms.
	void LG_HallwayGeneration::GenerateVerticalHallway(LG_Room * pRoom1, LG_Room * pRoom2, LG_Vector3D MidPoint, float fHeight)
	{
		/// Boolean used to know which room is on top of which one.
		bool bRoom1IsOnTop;

		/// Here we fill each one of the polygon's nodes. That will represent the position of the hallway's corners.
		LG_Hallway* pNewHall = new LG_Hallway();

		///
		pNewHall->m_fHeight = fHeight;
		/// We make them shared pointers to avoid memory leaks.

		/// The bottom left node is the first one thats calculated.
		LG_Node* pBLNode = new LG_Node();
		/// The bottom right node is the second one thats calculated.
		LG_Node* pBRNode = new LG_Node();
		/// The top left node is the third one thats calculated.
		LG_Node* pTLNode = new LG_Node();
		/// The top right node is the fourth one to be calculated.
		LG_Node* pTRNode = new LG_Node();

		/// 
		pNewHall->m_eHallwayType = VERTICAL;

		/// We start assigning the center node of the lowest room, as we need to fill our bottom left node.
		pBLNode->m_Position.Y = LG_Math::Max(pRoom1->m_pFloor->m_CenterNode.m_Position.Y, pRoom2->m_pFloor->m_CenterNode.m_Position.Y);
		/// The position in the X axis is the midpoint minus half the hallway width.
		pBLNode->m_Position.X = MidPoint.X - (m_fHallwayWidth / 2);
		/// It has the same Z position as the mid point.
		pBLNode->m_Position.Z = MidPoint.Z;

		/// We see which room is on top of which room.
		bRoom1IsOnTop = !(pRoom1->m_pFloor->m_CenterNode.m_Position.Y == pBLNode->m_Position.Y);

		/// Next we go for the top left node.
		pTLNode->m_Position = pBLNode->m_Position;
		/// 
		pTLNode->m_Position.Y = LG_Math::Min(pRoom1->m_pFloor->m_CenterNode.m_Position.Y, pRoom2->m_pFloor->m_CenterNode.m_Position.Y);

		/// We see which room is on top of which one in order to know what room we subtract (or add) the height from.
		if (bRoom1IsOnTop)
		{
			pBLNode->m_Position.Y -= (pRoom2->m_pFloor->m_fHeight / 2);
			pTLNode->m_Position.Y += (pRoom1->m_pFloor->m_fHeight / 2);
		}
		else
		{
			pBLNode->m_Position.Y -= (pRoom1->m_pFloor->m_fHeight / 2);
			pTLNode->m_Position.Y += (pRoom2->m_pFloor->m_fHeight / 2);
		}



		/// Now we add the bottom right node's position. Starting off from the bottom left, and we just change the value of the X axis.
		pBRNode->m_Position = pBLNode->m_Position;
		/// 
		pBRNode->m_Position.X += m_fHallwayWidth;

		/// 
		pTRNode->m_Position = pTLNode->m_Position;
		/// 
		pTRNode->m_Position.X += m_fHallwayWidth;

		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pTLNode);
		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pTRNode);
		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pBRNode);
		/// Now that the node has it's position set, we add it to the polygon.
		pNewHall->m_pPolygon->InsertNodeToVector(pBLNode);
		///
		pNewHall->CreateDoors(pTLNode, pTRNode, pBLNode, pBRNode);

		/// Here create the rectangles that represent the hallway's walls.
		pNewHall->m_Walls.push_back(pNewHall->CreateWall(pTLNode->m_Position, pBLNode->m_Position, false));
		///
		pNewHall->m_Walls.push_back(pNewHall->CreateWall(pTRNode->m_Position, pBRNode->m_Position, false));

		/// 
		pNewHall->CreateFloors();
		/// 
		pNewHall->CreateCeilings();

		/// 
		pNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		pNewHall->m_pParentRoom_2 = pRoom2;

		/// 
		m_FinalHallways.push_back(pNewHall);
	}

	//! Creates a horizontal hallway between two rooms.
	void LG_HallwayGeneration::GenerateHorizontalHallway(LG_Room * pRoom1, LG_Room * pRoom2, LG_Vector3D MidPoint, float fHeight)
	{
		/// Boolean used to know which room is at the left or right side of the other.
		bool bRoom1IsLeft;

		/// Here we fill each one of the polygon's nodes. That will represent the position of the hallway's corners.
		LG_Hallway* pNewHall = new LG_Hallway();

		///
		pNewHall->m_fHeight = fHeight;
		/// We make them shared pointers to avoid memory leaks.
		/// The bottom left node is the first one thats calculated.
		LG_Node* pBLNode = new LG_Node();
		/// The bottom right node is the second one thats calculated.
		LG_Node* pBRNode = new LG_Node();
		/// The top left node is the third one thats calculated.
		LG_Node* pTLNode = new LG_Node();
		/// The top right node is the fourth one to be calculated.
		LG_Node* pTRNode = new LG_Node();

		/// 
		pNewHall->m_eHallwayType = HORIZONTAL;

		/// We start assigning the center node of the lowest room, as we need to fill our bottom left node.
		pBLNode->m_Position.X = LG_Math::Min(pRoom1->m_pFloor->m_CenterNode.m_Position.X, pRoom2->m_pFloor->m_CenterNode.m_Position.X);
		/// The position in the Y axis is the midpoint minus half the hallway width.
		pBLNode->m_Position.Y = MidPoint.Y + (m_fHallwayWidth / 2);
		/// It has the same Z position as the mid point.
		pBLNode->m_Position.Z = MidPoint.Z;

		/// We see which room is on left of which room.
		bRoom1IsLeft = (pRoom1->m_pFloor->m_CenterNode.m_Position.X == pBLNode->m_Position.X);

		/// Next we go for the top left node.
		pBRNode->m_Position = pBLNode->m_Position;
		/// 
		pBRNode->m_Position.X = LG_Math::Max(pRoom1->m_pFloor->m_CenterNode.m_Position.X, pRoom2->m_pFloor->m_CenterNode.m_Position.X);

		/// We see which room is on top of which one in order to know what room we subtract (or add) the height from.
		if (bRoom1IsLeft)
		{
			pBLNode->m_Position.X += (pRoom1->m_pFloor->m_fWidth / 2);
			pBRNode->m_Position.X -= (pRoom2->m_pFloor->m_fWidth / 2);
		}
		else
		{
			pBLNode->m_Position.X += (pRoom2->m_pFloor->m_fWidth / 2);
			pBRNode->m_Position.X -= (pRoom1->m_pFloor->m_fWidth / 2);
		}


		/// Now we add the bottom right node's position. Starting off from the bottom left, and we just change the value of the X axis.
		pTLNode->m_Position = pBLNode->m_Position;
		/// 
		pTLNode->m_Position.Y -= m_fHallwayWidth;

		/// 
		pTRNode->m_Position = pBRNode->m_Position;
		/// 
		pTRNode->m_Position.Y -= m_fHallwayWidth;

		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pTLNode);
		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pTRNode);
		/// 
		pNewHall->m_pPolygon->InsertNodeToVector(pBRNode);
		/// Now that the node has it's position set, we add it to the polygon.
		pNewHall->m_pPolygon->InsertNodeToVector(pBLNode);

		/// Create the doors of the hallway.
		pNewHall->CreateDoors(pTLNode, pBLNode, pTRNode, pBRNode);

		/// Here create the rectangles that represent the hallway's walls.
		pNewHall->m_Walls.push_back(pNewHall->CreateWall(pTLNode->m_Position, pTRNode->m_Position, true));
		///
		pNewHall->m_Walls.push_back(pNewHall->CreateWall(pBLNode->m_Position, pBRNode->m_Position, true));

		/// 
		pNewHall->CreateFloors();
		/// 
		pNewHall->CreateCeilings();

		/// 
		pNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		pNewHall->m_pParentRoom_2 = pRoom2;

		/// 
		m_FinalHallways.push_back(pNewHall);
	}

	//! Creates a L shaped hallway between two rooms.
	LG_Hallway* LG_HallwayGeneration::GenerateCornerHallway(LG_Room * pRoom1, LG_Room * pRoom2, float fHeight)
	{
		///we allocate memory to what will become the next corner hallway.
		LG_Hallway* pNewHall = new LG_Hallway();
		/// initialize it's height.
		pNewHall->m_fHeight = fHeight;
		/// We make them shared pointers to avoid memory leaks.
		/// The nodes that will be used to fill the polygon
		LG_Node* spNode0 = new LG_Node();
		LG_Node* spNode1 = new LG_Node();
		LG_Node* spNode2 = new LG_Node();
		LG_Node* spNode3 = new LG_Node();
		LG_Node* spNode4 = new LG_Node();
		LG_Node* spNode5 = new LG_Node();

		/// We see if the room 1 is on top or bottom of the room 2.
		bool bRoom1IsOnTop = (pRoom1->m_pFloor->m_CenterNode.m_Position.Y == LG_Math::Min(pRoom1->m_pFloor->m_CenterNode.m_Position.Y, pRoom2->m_pFloor->m_CenterNode.m_Position.Y));
		bool bRoom2IsLeft = (pRoom2->m_pFloor->m_CenterNode.m_Position.X == LG_Math::Min(pRoom1->m_pFloor->m_CenterNode.m_Position.X, pRoom2->m_pFloor->m_CenterNode.m_Position.X));

		/// We set the hallway flag that indicates it's a corner and not a straight hallway.
		pNewHall->m_eHallwayType = CORNER;

		/// First we calculate the nodes that start from room 1.
		spNode0->m_Position = pRoom1->m_pFloor->m_CenterNode.m_Position;
		/// We now subtract or add half the room's height.
		if (bRoom1IsOnTop)
		{
			/// If the room 1 is on top, we add so that the hall starts underneath room 1.
			spNode0->m_Position.Y += (pRoom1->m_pFloor->m_fHeight / 2);
		}
		else
		{
			/// If the room 1 is on top, we subtract so that the hall starts on top of room 1.
			spNode0->m_Position.Y -= (pRoom1->m_pFloor->m_fHeight / 2);
		}
		/// We subtract half the hallway width to place the node correctly.
		spNode0->m_Position.X -= (m_fHallwayWidth / 2);

		/// We now calculate the node that will be next to the one we just calculated, being both nodes that represent the door of room 1.
		spNode1->m_Position = spNode0->m_Position;
		/// We move it so that it's got the hallway's width.
		spNode1->m_Position.X += m_fHallwayWidth;

		/// We now calculate the 2 nodes that will be stuck to room2. 
		spNode2->m_Position = pRoom2->m_pFloor->m_CenterNode.m_Position;
		/// 
		spNode2->m_Position.Y -= (m_fHallwayWidth / 2);
		/// 
		if (bRoom2IsLeft)
		{
			/// 
			spNode2->m_Position.X += (pRoom2->m_pFloor->m_fWidth / 2);
		}
		else
		{
			/// 
			spNode2->m_Position.X -= (pRoom2->m_pFloor->m_fWidth / 2);
		}

		/// 
		spNode3->m_Position = spNode2->m_Position;
		///
		spNode3->m_Position.Y += m_fHallwayWidth;

		/// The node 0 is the pRoom1's first door node. The door is placed either on the top or the bottom wall of the room. 
		/// Node 1 is the one at the right of the node 0. Making the door for L shaped hallway. 
		LG_Vector3D n1n2 = spNode1->m_Position - spNode2->m_Position;
		/// Node 2 is the top node of the door from one wall of the side walls of the room.
		LG_Vector3D n1n3 = spNode1->m_Position - spNode3->m_Position;
		/// Node number 3 makes the second node of the door that's being shared by node2.
		LG_Vector3D n0n2 = spNode0->m_Position - spNode2->m_Position;
		LG_Vector3D n0n3 = spNode0->m_Position - spNode3->m_Position;

		/// We store the magnitudes from each connection.
		float fDistancen1n2 = n1n2.Magnitude();
		float fDistancen1n3 = n1n3.Magnitude();

		/// n1n3 will represent the X axis from the outer node, while n1n2 will have the inner value in X axis.
		if (fDistancen1n2 < fDistancen1n3)
		{
			if (bRoom2IsLeft)
			{
				/// 
				pNewHall->m_eCaseCorner = ROOM1_TOPRIGHT;
				/// Inner corner node. 
				spNode4->m_Position = spNode0->m_Position;
				/// 
				spNode4->m_Position.Y = spNode2->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode1->m_Position;
				/// 
				spNode5->m_Position.Y = spNode3->m_Position.Y;

				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode0);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode4);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode2);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode3);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode5);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode1);

				pNewHall->CreateDoors(spNode0, spNode1, spNode2, spNode3);
				/// 
				pNewHall->CreateFloors();
				/// 
				pNewHall->CreateCeilings();

				/// Here create the rectangles that represent the hallway's walls.
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode0->m_Position, spNode4->m_Position, false));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode4->m_Position, spNode2->m_Position, true));
				/// 
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode3->m_Position, spNode5->m_Position, true));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode5->m_Position, spNode1->m_Position, false));
			}
			else
			{
				/// the case of the corner, room1 top left, room 2 bottom right.
				pNewHall->m_eCaseCorner = ROOM1_TOPLEFT;
				
				/// Inner corner node. 
				spNode4->m_Position = spNode1->m_Position;
				/// 
				spNode4->m_Position.Y = spNode2->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode0->m_Position;
				/// 
				spNode5->m_Position.Y = spNode3->m_Position.Y;

				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode0);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode5);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode3);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode2);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode4);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode1);
				///
				pNewHall->CreateDoors(spNode0, spNode1, spNode2, spNode3);
				/// 
				pNewHall->CreateFloors();
				/// 
				pNewHall->CreateCeilings();

				/// Here create the rectangles that represent the hallway's walls.
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode0->m_Position, spNode5->m_Position, false));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode5->m_Position, spNode3->m_Position, true));
				/// 
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode2->m_Position, spNode4->m_Position, true));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode4->m_Position, spNode1->m_Position, false));
			}
		}

		else
		{
			if (bRoom2IsLeft)
			{
				///
				pNewHall->m_eCaseCorner = ROOM1_BOTTOMRIGHT;
				/// Inner corner node. 
				spNode4->m_Position = spNode0->m_Position;
				/// 
				spNode4->m_Position.Y = spNode3->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode1->m_Position;
				/// 
				spNode5->m_Position.Y = spNode2->m_Position.Y;

				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode0);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode4);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode3);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode2);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode5);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode1);
				///
				pNewHall->CreateDoors(spNode0, spNode1, spNode2, spNode3);
				/// 
				pNewHall->CreateFloors();
				/// 
				pNewHall->CreateCeilings();

				/// Here create the rectangles that represent the hallway's walls.
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode0->m_Position, spNode4->m_Position, false));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode4->m_Position, spNode3->m_Position, true));
				/// 
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode2->m_Position, spNode5->m_Position, true));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode5->m_Position, spNode1->m_Position, false));
			}
			else
			{
				///
				pNewHall->m_eCaseCorner = ROOM1_BOTTOMLEFT;
				/// Inner corner node. 
				spNode4->m_Position = spNode1->m_Position;
				/// 
				spNode4->m_Position.Y = spNode3->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode0->m_Position;
				/// 
				spNode5->m_Position.Y = spNode2->m_Position.Y;

				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode0);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode5);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode2);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode3);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode4);
				/// 
				pNewHall->m_pPolygon->InsertNodeToVector(spNode1);
				///
				pNewHall->CreateDoors(spNode0, spNode1, spNode2, spNode3);
				/// 
				pNewHall->CreateFloors();
				/// 
				pNewHall->CreateCeilings();

				/// Here create the rectangles that represent the hallway's walls.
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode0->m_Position, spNode5->m_Position, false));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode5->m_Position, spNode2->m_Position, true));
				/// 
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode3->m_Position, spNode4->m_Position, true));
				///
				pNewHall->m_Walls.push_back(pNewHall->CreateWall(spNode4->m_Position, spNode1->m_Position, false));
			}
		}

		/// 
		pNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		pNewHall->m_pParentRoom_2 = pRoom2;

		///
		return pNewHall;
	}

	float LG_HallwayGeneration::GetLongestDistance(LG_Hallway* hallwayToMove)
	{
		LG_Vector3D HorizontalMagnitude;
		LG_Vector3D VerticalMagnitude;
		switch (hallwayToMove->m_eCaseCorner)
		{
		case ROOM1_TOPRIGHT:

			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove->m_pPolygon->m_pNodeVector[0]->m_Position - hallwayToMove->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove->m_pPolygon->m_pNodeVector[2]->m_Position - hallwayToMove->m_pParentRoom_2->m_pFloor->m_TopRight.m_Position;

			/// Compares both magnitudes and return the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_TOPLEFT:

			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position - hallwayToMove->m_pPolygon->m_pNodeVector[5]->m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove->m_pPolygon->m_pNodeVector[3]->m_Position - hallwayToMove->m_pParentRoom_2->m_pFloor->m_TopLeft.m_Position;

			/// Compares both magnitudes and returns the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_BOTTOMLEFT:

			/// Create a vertical vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove->m_pParentRoom_1->m_pFloor->m_TopRight.m_Position - hallwayToMove->m_pPolygon->m_pNodeVector[5]->m_Position;
			/// Create a horizontal vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove->m_pParentRoom_2->m_pFloor->m_BottomLeft.m_Position - hallwayToMove->m_pPolygon->m_pNodeVector[3]->m_Position;

			/// Compares both magnitudes and returns the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_BOTTOMRIGHT:
			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove->m_pPolygon->m_pNodeVector[0]->m_Position - hallwayToMove->m_pParentRoom_1->m_pFloor->m_TopLeft.m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove->m_pParentRoom_2->m_pFloor->m_BottomRight.m_Position - hallwayToMove->m_pPolygon->m_pNodeVector[2]->m_Position;

			/// Compares both magnitudes and returns the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		default:
			break;
		}
		return 0.0f;
	}

	bool LG_HallwayGeneration::MoveCorner(LG_Hallway* CornerToMove, LG_Room* CollisionRoom)
	{
		bool bFlagX = false;
		bool bFlagY = false;
		/// Depending on the hall's case we see how to move it so that it doesn't collide.
		switch (CornerToMove->m_eCaseCorner)
		{
		case ROOM1_TOPRIGHT:
			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollisionWithRoom(CollisionRoom))
			{
				/// Move the position of the hallway. node 0 from the hall to the bottom left node of room 1. And node 2 from the hallway is moved towards top right node from room 2.
				//TODO: aquí checar que no se encime con sus parents.
				/// Check that when moving it stays inside of the parent room boundaries.
				if (CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X >= CornerToMove->m_pParentRoom_1->m_pFloor->m_BottomLeft.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X;
					--CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.X;
					--CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y >= CornerToMove->m_pParentRoom_2->m_pFloor->m_TopRight.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y;
					--CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.Y;
					--CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
				{
					CornerToMove->ReorganizeVariables(ROOM1_TOPRIGHT);
					return false;
				}
			}
			CornerToMove->ReorganizeVariables(ROOM1_TOPRIGHT);
			return true;
			break;

		case ROOM1_TOPLEFT:

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollisionWithRoom(CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X <= CornerToMove->m_pParentRoom_1->m_pFloor->m_BottomRight.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X;
					++CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.X;
					++CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y >= CornerToMove->m_pParentRoom_2->m_pFloor->m_TopLeft.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y;
					--CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.Y;
					--CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
				{
					CornerToMove->ReorganizeVariables(ROOM1_TOPLEFT);
					return false;
				}
			}

			CornerToMove->ReorganizeVariables(ROOM1_TOPLEFT);
			return true;
			break;

		case ROOM1_BOTTOMRIGHT:

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollisionWithRoom(CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X >= CornerToMove->m_pParentRoom_1->m_pFloor->m_TopLeft.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X;
					--CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.X;
					--CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y <= CornerToMove->m_pParentRoom_2->m_pFloor->m_BottomRight.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y;
					++CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.Y;
					++CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
				{
					CornerToMove->ReorganizeVariables(ROOM1_BOTTOMRIGHT);
					return false;
				}
			}
			CornerToMove->ReorganizeVariables(ROOM1_BOTTOMRIGHT);
			return true;
			break;

		case ROOM1_BOTTOMLEFT:

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollisionWithRoom(CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X <= CornerToMove->m_pParentRoom_1->m_pFloor->m_TopRight.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pPolygon->m_pNodeVector[0]->m_Position.X;
					++CornerToMove->m_pPolygon->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.X;
					++CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y <= CornerToMove->m_pParentRoom_2->m_pFloor->m_BottomLeft.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pPolygon->m_pNodeVector[2]->m_Position.Y;
					++CornerToMove->m_pPolygon->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pPolygon->m_pNodeVector[1]->m_Position.Y;
					++CornerToMove->m_pPolygon->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
				{
					CornerToMove->ReorganizeVariables(ROOM1_BOTTOMLEFT);
					return false;
				}
			}

			CornerToMove->ReorganizeVariables(ROOM1_BOTTOMLEFT);
			return true;
			break;

		default:
			return false;
			break;
		}
	}

	//!
	LG_Hallway* LG_HallwayGeneration::ReorganizeCornerHallway(LG_Hallway* CornerToReorganize, float fHeight)
	{

		for (int32 k = 0; k < m_pRooms->size(); ++k)
		{
			/// We make sure that it doesn't check collision with none of it's parent rooms.
			if (CornerToReorganize->m_pParentRoom_2 != (*m_pRooms)[k] && CornerToReorganize->m_pParentRoom_1 != (*m_pRooms)[k])
			{
				/// We check collision with the iterating room.
				if (CornerToReorganize->CheckCollisionWithRoom((*m_pRooms)[k]))
				{
					LG_Room* TempRoom1 = CornerToReorganize->m_pParentRoom_2;
					LG_Room* TempRoom2 = CornerToReorganize->m_pParentRoom_1;
					LG_Hallway* pSecondCorner = GenerateCornerHallway(TempRoom1, TempRoom2, fHeight);

					/// We see between which rooms is better to generate the hallway. Based on the distance between the rooms and the hallway.
					/// The more distance we have, the more we can move the hallways so that they don't collide with other objects.
					float fDistance1 = GetLongestDistance(CornerToReorganize);
					float fDistance2 = GetLongestDistance(pSecondCorner);

					/// the first hallway we calculated is best for moving it and avoiding collisions.
					if (fDistance1 >= fDistance2)
					{

						if (MoveCorner(CornerToReorganize, (*m_pRooms)[k]))
						{
							
							/// Call the destroy function of the second corner.
							pSecondCorner->Destroy();
							/// Erase the allocated memory for this hallway.
							delete pSecondCorner;
							/// Set as nullptr.
							pSecondCorner = nullptr;
							/// Finish this iteration.
							return pSecondCorner;
						}

						else
						{
							///
							if (MoveCorner(pSecondCorner, (*m_pRooms)[k]))
							{
							
								/// Call the destroy function of the CornerToReorganize.
								CornerToReorganize->Destroy();
								/// Erase the allocated memory for this hallway.
								delete CornerToReorganize;
								/// Set as nullptr.
								CornerToReorganize = nullptr;
								/// 
								return pSecondCorner;
							}
							else
							{
								//TODO: Ninguna esquina funciono que pedo ???
								int i = 0;
								i = 5;
							}
						}

					}
					/// The second hall we generated is best to implement.
					else
					{
						///
						if (MoveCorner(pSecondCorner, (*m_pRooms)[k]))
						{

							/// Call the destroy function of the CornerToReorganize.
							CornerToReorganize->Destroy();
							/// Erase the allocated memory for this hallway.
							delete CornerToReorganize;
							/// Set as nullptr.
							CornerToReorganize = nullptr;
							/// Finish this iteration.
							return pSecondCorner;
						}
						else
						{
							if (MoveCorner(CornerToReorganize, (*m_pRooms)[k]))
							{

								/// Call the destroy function of the second corner.
								pSecondCorner->Destroy();
								/// Erase the allocated memory for this hallway.
								delete pSecondCorner;
								/// Set as nullptr.
								pSecondCorner = nullptr;
								/// 
								return pSecondCorner;
							}

							else
							{
								//TODO: Ninguna esquina funciono que pedo ???
								int i = 0;
								i = 5;
							}
						}
					}
					break;
				}
			}
		}
		return nullptr;
	}
}