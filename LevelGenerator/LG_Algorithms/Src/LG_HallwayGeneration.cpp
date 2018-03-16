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
	void LG_HallwayGeneration::Init(float fCorridorWidth, Vector<LG_Rect*>* Rooms)
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
		//TODO: liberar memoria.
		m_fHallwayWidth = 0;
	}

	//! This function is the only one you need to generate Hallways.
	void LG_HallwayGeneration::Run(Vector<LG_Rect*>* pRooms, float fCorridorWidth)
	{
		Init(fCorridorWidth, pRooms);

		///
		LG_Vector3D MidPoint(0, 0, 0);
		///
		LG_Vector2D Max_Pos;
		///
		LG_Vector2D Min_Pos;

		/// 
		std::shared_ptr<LG_Polygon> spConerHallway = std::make_shared<LG_Polygon>();
		/// 
		std::shared_ptr<LG_Polygon> spSecondCornerHallway = std::make_shared<LG_Polygon>();
		/// 
		std::shared_ptr<LG_Polygon> spCorner2 = std::make_shared<LG_Polygon>();

		/// We iterate all the rooms and it's connections.
		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			for (int32 j = 0; j < (*m_pRooms)[i]->m_RoomsConnections.size(); ++j)
			{
				if (!(*m_pRooms)[i]->m_RoomsConnections[j]->m_bIsChecked)
				{
					/// The mid point between both iterating rooms is calculated.
					MidPoint = (*m_pRooms)[i]->m_CenterNode.m_Position.MidPoint((*m_pRooms)[i]->m_RoomsConnections[j]->m_CenterNode.m_Position);

					/// Assign the max value in the X Axis between both room's left nodes.
					Max_Pos.X = LG_Math::Max((*m_pRooms)[i]->m_BottomLeft.m_Position.X, (*m_pRooms)[i]->m_RoomsConnections[j]->m_BottomLeft.m_Position.X);
					/// Assign the max value in the Y Axis between both room's right nodes.
					Max_Pos.Y = LG_Math::Max((*m_pRooms)[i]->m_TopRight.m_Position.Y, (*m_pRooms)[i]->m_RoomsConnections[j]->m_TopRight.m_Position.Y);

					/// Assign the min value in the X Axis between both room's bottom nodes.
					Min_Pos.X = LG_Math::Min((*m_pRooms)[i]->m_BottomRight.m_Position.X, (*m_pRooms)[i]->m_RoomsConnections[j]->m_BottomRight.m_Position.X);
					/// Assign the min value in the Y Axis between both room's up nodes.
					Min_Pos.Y = LG_Math::Min((*m_pRooms)[i]->m_BottomRight.m_Position.Y, (*m_pRooms)[i]->m_RoomsConnections[j]->m_BottomRight.m_Position.Y);

					/// We now check if the mid point is inside of the room's boundaries.
					if (MidPoint.X > Max_Pos.X && MidPoint.X < Min_Pos.X)
					{
						if (MidPoint.X - m_fHallwayWidth / 2 > Max_Pos.X)
						{
							if (MidPoint.X + m_fHallwayWidth / 2 < Min_Pos.X)
							{
								/// Generate a vertical hallway.
								GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
								continue;
							}
							else
							{
								float fDifference = (MidPoint.X + m_fHallwayWidth / 2) - Min_Pos.X;
								if (((MidPoint.X - m_fHallwayWidth / 2) - fDifference) > Max_Pos.X)
								{
									MidPoint.X -= fDifference;
									/// Generate a vertical hallway.
									GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
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
								GenerateVerticalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
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
								GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
								continue;
							}
							else
							{
								float fDifference = (MidPoint.Y + m_fHallwayWidth / 2) - Min_Pos.Y;
								if (((MidPoint.Y - m_fHallwayWidth / 2) - fDifference) > Max_Pos.Y)
								{
									MidPoint.Y -= fDifference;
									/// Generate a vertical hallway.
									GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
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
								GenerateHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j], MidPoint);
								continue;
							}
						}
					}

					/// When it couldn't fit in any case, we generate a L shaped hallway.
					spConerHallway = GenerateCornerHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
					m_FinalHallways.push_back(spConerHallway);

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
				if (!m_FinalHallways[iActual]->m_bIsCorner) continue;

				/// We iterate against all the other hallways.
				for (int32 iIterating = 0; iIterating < m_FinalHallways.size(); ++iIterating)
				{
					/// We make sure that we're not checking collision between the same hallways.
					if (m_FinalHallways[iActual] != m_FinalHallways[iIterating])
					{
						/// We now check collision between both hallways.
						if (m_FinalHallways[iActual]->CheckCollision(m_FinalHallways[iIterating]))
						{
							LG_Rect* TempRoom1 = m_FinalHallways[iActual]->m_pParentRoom_2;
							LG_Rect* TempRoom2 = m_FinalHallways[iActual]->m_pParentRoom_1;
							m_FinalHallways.erase(m_FinalHallways.begin() + iActual);
							m_FinalHallways.push_back(GenerateCornerHallway(TempRoom1, TempRoom2));
							bCheckCollisionWithHallways = true;
							break;
						}
					}
				}
				if (bCheckCollisionWithHallways) break;
			}
		}

		/// First the hallways are iterated.
		for (int32 iActual = 0; iActual < m_FinalHallways.size(); ++iActual)
		{
			/// There's only need to check the corner hallways.
			if (!m_FinalHallways[iActual]->m_bIsCorner) continue;

			ReorganizeCornerHallway(m_FinalHallways[iActual], spSecondCornerHallway);
		}


	}

	//! Creates a vertical hallway between two rooms.
	void LG_HallwayGeneration::GenerateVerticalHallway(LG_Rect * pRoom1, LG_Rect * pRoom2, LG_Vector3D MidPoint)
	{
		/// Boolean used to know which room is on top of which one.
		bool bRoom1IsOnTop;

		/// Here we fill each one of the polygon's nodes. That will represent the position of the hallway's corners.
		std::shared_ptr<LG_Polygon> spNewHall = std::make_shared<LG_Polygon>();
		/// We make them shared pointers to avoid memory leaks.
		/// The bottom left node is the first one thats calculated.
		std::shared_ptr<LG_Node> spBLNode = std::make_shared<LG_Node>();
		/// The bottom right node is the second one thats calculated.
		std::shared_ptr<LG_Node> spBRNode = std::make_shared<LG_Node>();
		/// The top left node is the third one thats calculated.
		std::shared_ptr<LG_Node> spTLNode = std::make_shared<LG_Node>();
		/// The top right node is the fourth one to be calculated.
		std::shared_ptr<LG_Node> spTRNode = std::make_shared<LG_Node>();

		/// 
		spNewHall->m_bIsCorner = false;

		/// We start assigning the center node of the lowest room, as we need to fill our bottom left node.
		spBLNode->m_Position.Y = LG_Math::Max(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y);
		/// The position in the X axis is the midpoint minus half the hallway width.
		spBLNode->m_Position.X = MidPoint.X - (m_fHallwayWidth / 2);
		/// It has the same Z position as the mid point.
		spBLNode->m_Position.Z = MidPoint.Z;

		/// We see which room is on top of which room.
		bRoom1IsOnTop = !(pRoom1->m_CenterNode.m_Position.Y == spBLNode->m_Position.Y);

		/// Next we go for the top left node.
		spTLNode->m_Position = spBLNode->m_Position;
		/// 
		spTLNode->m_Position.Y = LG_Math::Min(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y);

		/// We see which room is on top of which one in order to know what room we subtract (or add) the height from.
		if (bRoom1IsOnTop)
		{
			spBLNode->m_Position.Y -= (pRoom2->m_fHeight / 2);
			spTLNode->m_Position.Y += (pRoom1->m_fHeight / 2);
		}
		else
		{
			spBLNode->m_Position.Y -= (pRoom1->m_fHeight / 2);
			spTLNode->m_Position.Y += (pRoom2->m_fHeight / 2);
		}



		/// Now we add the bottom right node's position. Starting off from the bottom left, and we just change the value of the X axis.
		spBRNode->m_Position = spBLNode->m_Position;
		/// 
		spBRNode->m_Position.X += m_fHallwayWidth;

		/// 
		spTRNode->m_Position = spTLNode->m_Position;
		/// 
		spTRNode->m_Position.X += m_fHallwayWidth;

		/// 
		spNewHall->InsertNodeToVector(spTLNode);
		/// 
		spNewHall->InsertNodeToVector(spTRNode);
		/// 
		spNewHall->InsertNodeToVector(spBRNode);
		/// Now that the node has it's position set, we add it to the polygon.
		spNewHall->InsertNodeToVector(spBLNode);

		/// 
		spNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		spNewHall->m_pParentRoom_2 = pRoom2;

		/// 
		m_FinalHallways.push_back(spNewHall);
	}

	//! Creates a horizontal hallway between two rooms.
	void LG_HallwayGeneration::GenerateHorizontalHallway(LG_Rect * pRoom1, LG_Rect * pRoom2, LG_Vector3D MidPoint)
	{
		/// Boolean used to know which room is at the left or right side of the other.
		bool bRoom1IsLeft;

		/// Here we fill each one of the polygon's nodes. That will represent the position of the hallway's corners.
		std::shared_ptr<LG_Polygon> spNewHall = std::make_shared<LG_Polygon>();
		/// We make them shared pointers to avoid memory leaks.
		/// The bottom left node is the first one thats calculated.
		std::shared_ptr<LG_Node> spBLNode = std::make_shared<LG_Node>();
		/// The bottom right node is the second one thats calculated.
		std::shared_ptr<LG_Node> spBRNode = std::make_shared<LG_Node>();
		/// The top left node is the third one thats calculated.
		std::shared_ptr<LG_Node> spTLNode = std::make_shared<LG_Node>();
		/// The top right node is the fourth one to be calculated.
		std::shared_ptr<LG_Node> spTRNode = std::make_shared<LG_Node>();

		/// 
		spNewHall->m_bIsCorner = false;

		/// We start assigning the center node of the lowest room, as we need to fill our bottom left node.
		spBLNode->m_Position.X = LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);
		/// The position in the Y axis is the midpoint minus half the hallway width.
		spBLNode->m_Position.Y = MidPoint.Y + (m_fHallwayWidth / 2);
		/// It has the same Z position as the mid point.
		spBLNode->m_Position.Z = MidPoint.Z;

		/// We see which room is on left of which room.
		bRoom1IsLeft = (pRoom1->m_CenterNode.m_Position.X == spBLNode->m_Position.X);

		/// Next we go for the top left node.
		spBRNode->m_Position = spBLNode->m_Position;
		/// 
		spBRNode->m_Position.X = LG_Math::Max(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);

		/// We see which room is on top of which one in order to know what room we subtract (or add) the height from.
		if (bRoom1IsLeft)
		{
			spBLNode->m_Position.X += (pRoom1->m_fWidth / 2);
			spBRNode->m_Position.X -= (pRoom2->m_fWidth / 2);
		}
		else
		{
			spBLNode->m_Position.X += (pRoom2->m_fWidth / 2);
			spBRNode->m_Position.X -= (pRoom1->m_fWidth / 2);
		}


		/// Now we add the bottom right node's position. Starting off from the bottom left, and we just change the value of the X axis.
		spTLNode->m_Position = spBLNode->m_Position;
		/// 
		spTLNode->m_Position.Y -= m_fHallwayWidth;

		/// 
		spTRNode->m_Position = spBRNode->m_Position;
		/// 
		spTRNode->m_Position.Y -= m_fHallwayWidth;

		/// 
		spNewHall->InsertNodeToVector(spTLNode);
		/// 
		spNewHall->InsertNodeToVector(spTRNode);
		/// 
		spNewHall->InsertNodeToVector(spBRNode);
		/// Now that the node has it's position set, we add it to the polygon.
		spNewHall->InsertNodeToVector(spBLNode);

		/// 
		spNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		spNewHall->m_pParentRoom_2 = pRoom2;

		/// 
		m_FinalHallways.push_back(spNewHall);
	}

	//! Creates a L shaped hallway between two rooms.
	std::shared_ptr<LG_Polygon> LG_HallwayGeneration::GenerateCornerHallway(LG_Rect * pRoom1, LG_Rect * pRoom2)
	{
		/// Here we fill each one of the polygon's nodes. That will represent the position of the hallway's corners.
		std::shared_ptr<LG_Polygon> spNewHall = std::make_shared<LG_Polygon>();
		/// We make them shared pointers to avoid memory leaks.
		/// The nodes that will be used to fill the polygon
		std::shared_ptr<LG_Node> spNode0 = std::make_shared<LG_Node>();
		std::shared_ptr<LG_Node> spNode1 = std::make_shared<LG_Node>();
		std::shared_ptr<LG_Node> spNode2 = std::make_shared<LG_Node>();
		std::shared_ptr<LG_Node> spNode3 = std::make_shared<LG_Node>();
		std::shared_ptr<LG_Node> spNode4 = std::make_shared<LG_Node>();
		std::shared_ptr<LG_Node> spNode5 = std::make_shared<LG_Node>();

		/// We see if the room 1 is on top or bottom of the room 2.
		bool bRoom1IsOnTop = (pRoom1->m_CenterNode.m_Position.Y == LG_Math::Min(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y));
		bool bRoom2IsLeft = (pRoom2->m_CenterNode.m_Position.X == LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X));

		/// We set the hallway flag that indicates it's a corner and not a straight hallway.
		spNewHall->m_bIsCorner = true;

		/// First we calculate the nodes that start from room 1.
		spNode0->m_Position = pRoom1->m_CenterNode.m_Position;
		/// We now subtract or add half the room's height.
		if (bRoom1IsOnTop)
		{
			/// If the room 1 is on top, we add so that the hall starts underneath room 1.
			spNode0->m_Position.Y += (pRoom1->m_fHeight / 2);
		}
		else
		{
			/// If the room 1 is on top, we subtract so that the hall starts on top of room 1.
			spNode0->m_Position.Y -= (pRoom1->m_fHeight / 2);
		}
		/// We subtract half the hallway width to place the node correctly.
		spNode0->m_Position.X -= (m_fHallwayWidth / 2);

		/// We now calculate the node that will be next to the one we just calculated, being both nodes that represent the door of room 1.
		spNode1->m_Position = spNode0->m_Position;
		/// We move it so that it's got the hallway's width.
		spNode1->m_Position.X += m_fHallwayWidth;

		/// We now calculate the 2 nodes that will be stuck to room2. 
		spNode2->m_Position = pRoom2->m_CenterNode.m_Position;
		/// 
		spNode2->m_Position.Y -= (m_fHallwayWidth / 2);
		/// 
		if (bRoom2IsLeft)
		{
			/// 
			spNode2->m_Position.X += (pRoom2->m_fWidth / 2);
		}
		else
		{
			/// 
			spNode2->m_Position.X -= (pRoom2->m_fWidth / 2);
		}

		/// 
		spNode3->m_Position = spNode2->m_Position;
		///
		spNode3->m_Position.Y += m_fHallwayWidth;

		/// The node 0 is the pRoom1's first door node. The door is placed either on the top or the bottom side of the room. 
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
		float fDistancen0n2 = n0n2.Magnitude();
		float fDistancen0n3 = n0n3.Magnitude();

		/// n1n3 will represent the X axis from the outer node, while n1n2 will have the inner value in X axis.
		if (fDistancen1n2 < fDistancen1n3)
		{
			if (bRoom2IsLeft)
			{
				/// Inner corner node. 
				spNode4->m_Position = spNode0->m_Position;
				/// 
				spNode4->m_Position.Y = spNode2->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode1->m_Position;
				/// 
				spNode5->m_Position.Y = spNode3->m_Position.Y;

				/// 
				spNewHall->InsertNodeToVector(spNode0);
				/// 
				spNewHall->InsertNodeToVector(spNode4);
				/// 
				spNewHall->InsertNodeToVector(spNode2);
				/// 
				spNewHall->InsertNodeToVector(spNode3);
				/// 
				spNewHall->InsertNodeToVector(spNode5);
				/// 
				spNewHall->InsertNodeToVector(spNode1);
				/// 
				spNewHall->m_eCase = ROOM1_TOPRIGHT;
			}
			else
			{
				/// Inner corner node. 
				spNode4->m_Position = spNode1->m_Position;
				/// 
				spNode4->m_Position.Y = spNode2->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode0->m_Position;
				/// 
				spNode5->m_Position.Y = spNode3->m_Position.Y;

				/// 
				spNewHall->InsertNodeToVector(spNode0);
				/// 
				spNewHall->InsertNodeToVector(spNode5);
				/// 
				spNewHall->InsertNodeToVector(spNode3);
				/// 
				spNewHall->InsertNodeToVector(spNode2);
				/// 
				spNewHall->InsertNodeToVector(spNode4);
				/// 
				spNewHall->InsertNodeToVector(spNode1);
				/// 
				spNewHall->m_eCase = ROOM1_TOPLEFT;
			}
		}

		else
		{
			if (bRoom2IsLeft)
			{
				/// Inner corner node. 
				spNode4->m_Position = spNode0->m_Position;
				/// 
				spNode4->m_Position.Y = spNode3->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode1->m_Position;
				/// 
				spNode5->m_Position.Y = spNode2->m_Position.Y;

				/// 
				spNewHall->InsertNodeToVector(spNode0);
				/// 
				spNewHall->InsertNodeToVector(spNode4);
				/// 
				spNewHall->InsertNodeToVector(spNode3);
				/// 
				spNewHall->InsertNodeToVector(spNode2);
				/// 
				spNewHall->InsertNodeToVector(spNode5);
				/// 
				spNewHall->InsertNodeToVector(spNode1);
				///
				spNewHall->m_eCase = ROOM1_BOTTOMRIGHT;
			}
			else
			{
				/// Inner corner node. 
				spNode4->m_Position = spNode1->m_Position;
				/// 
				spNode4->m_Position.Y = spNode3->m_Position.Y;

				/// Outer corner node.
				spNode5->m_Position = spNode0->m_Position;
				/// 
				spNode5->m_Position.Y = spNode2->m_Position.Y;

				/// 
				spNewHall->InsertNodeToVector(spNode0);
				/// 
				spNewHall->InsertNodeToVector(spNode5);
				/// 
				spNewHall->InsertNodeToVector(spNode2);
				/// 
				spNewHall->InsertNodeToVector(spNode3);
				/// 
				spNewHall->InsertNodeToVector(spNode4);
				/// 
				spNewHall->InsertNodeToVector(spNode1);
				///
				spNewHall->m_eCase = ROOM1_BOTTOMLEFT;
			}
		}

		/// 
		spNewHall->m_pParentRoom_1 = pRoom1;
		/// 
		spNewHall->m_pParentRoom_2 = pRoom2;


		return spNewHall;
		//		m_FinalHallways.push_back(spNewHall);
	}

	float LG_HallwayGeneration::GetLongestDistance(LG_Polygon hallwayToMove)
	{
		LG_Vector3D HorizontalMagnitude;
		LG_Vector3D VerticalMagnitude;
		switch (hallwayToMove.m_eCase)
		{
		case ROOM1_TOPRIGHT:

			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove.m_pNodeVector[0]->m_Position - hallwayToMove.m_pParentRoom_1->m_BottomLeft.m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove.m_pNodeVector[2]->m_Position - hallwayToMove.m_pParentRoom_2->m_TopRight.m_Position;

			/// Compares both magnitudes and return the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_TOPLEFT:

			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove.m_pParentRoom_1->m_BottomRight.m_Position - hallwayToMove.m_pNodeVector[5]->m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove.m_pNodeVector[3]->m_Position - hallwayToMove.m_pParentRoom_2->m_TopLeft.m_Position;

			/// Compares both magnitudes and returns the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_BOTTOMLEFT:

			/// Create a vertical vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove.m_pParentRoom_1->m_TopRight.m_Position - hallwayToMove.m_pNodeVector[5]->m_Position;
			/// Create a horizontal vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove.m_pParentRoom_2->m_BottomLeft.m_Position - hallwayToMove.m_pNodeVector[3]->m_Position;

			/// Compares both magnitudes and returns the biggest one.
			if (HorizontalMagnitude.Magnitude() >= VerticalMagnitude.Magnitude())
				return HorizontalMagnitude.Magnitude();

			else
				return VerticalMagnitude.Magnitude();

			break;

		case ROOM1_BOTTOMRIGHT:
			/// Create a horizontal vector to determinate the magnitude.
			HorizontalMagnitude = hallwayToMove.m_pNodeVector[0]->m_Position - hallwayToMove.m_pParentRoom_1->m_TopLeft.m_Position;
			/// Create a vertical vector to determinate the magnitude.
			VerticalMagnitude = hallwayToMove.m_pParentRoom_2->m_BottomRight.m_Position - hallwayToMove.m_pNodeVector[2]->m_Position;

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

	bool LG_HallwayGeneration::MoveCorner(std::shared_ptr<LG_Polygon> CornerToMove, LG_Rect* CollisionRoom)
	{
		bool bFlagX = false;
		bool bFlagY = false;
		/// Depending oon the hall's case we see how to move it so that it doesn't collide.
		switch (CornerToMove->m_eCase)
		{
		case ROOM1_TOPRIGHT:
			//TODO: mover el nodo 0 del pasillo hacia el bottom left del cuarto 1. Y mover el nodo 2 del pasillo al top right del cuarto 2.

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollision(*CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pNodeVector[0]->m_Position.X >= CornerToMove->m_pParentRoom_1->m_BottomLeft.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pNodeVector[0]->m_Position.X;
					--CornerToMove->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pNodeVector[1]->m_Position.X;
					--CornerToMove->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pNodeVector[2]->m_Position.Y >= CornerToMove->m_pParentRoom_2->m_TopRight.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pNodeVector[2]->m_Position.Y;
					--CornerToMove->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pNodeVector[1]->m_Position.Y;
					--CornerToMove->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
					return false;
			}

			return true;
			break;

		case ROOM1_TOPLEFT:
			// TODO: mover el nodo 1 del pasillo hacia el bottom right del cuarto 1. Y el nodo 2 del pasillo hacia el top left dle cuarto 2.

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollision(*CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pNodeVector[5]->m_Position.X <= CornerToMove->m_pParentRoom_1->m_BottomRight.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pNodeVector[0]->m_Position.X;
					++CornerToMove->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pNodeVector[1]->m_Position.X;
					++CornerToMove->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pNodeVector[3]->m_Position.Y >= CornerToMove->m_pParentRoom_2->m_TopLeft.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pNodeVector[2]->m_Position.Y;
					--CornerToMove->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pNodeVector[1]->m_Position.Y;
					--CornerToMove->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
					return false;
			}

			return true;
			break;

		case ROOM1_BOTTOMRIGHT:
			// TODO: mover el nodo 0 del pasillo hacia el top left del cuarto 1. Y el nodo 3 hacia el bottom right del cuarto 2

			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollision(*CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pNodeVector[0]->m_Position.X >= CornerToMove->m_pParentRoom_1->m_TopLeft.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					--CornerToMove->m_pNodeVector[0]->m_Position.X;
					--CornerToMove->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					--CornerToMove->m_pNodeVector[1]->m_Position.X;
					--CornerToMove->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pNodeVector[2]->m_Position.Y <= CornerToMove->m_pParentRoom_2->m_BottomRight.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pNodeVector[2]->m_Position.Y;
					++CornerToMove->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pNodeVector[1]->m_Position.Y;
					++CornerToMove->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
					return false;
			}

			return true;
			break;

		case ROOM1_BOTTOMLEFT:
			// TODO: mover el nodo 1 del pasillo hacia el top right del cuarto 1. Y el nodo 3 hacía el bottom left del cuarto 2.
			/// Check if the corner is collision with the room.
			while (CornerToMove->CheckCollision(*CollisionRoom))
			{
				/// Move the position of the hallway.

				/// Check if 
				if (CornerToMove->m_pNodeVector[5]->m_Position.X <= CornerToMove->m_pParentRoom_1->m_TopRight.m_Position.X)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pNodeVector[0]->m_Position.X;
					++CornerToMove->m_pNodeVector[5]->m_Position.X;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pNodeVector[1]->m_Position.X;
					++CornerToMove->m_pNodeVector[4]->m_Position.X;
				}
				else
				{
					bFlagX = true;
				}

				/// Check if 
				if (CornerToMove->m_pNodeVector[3]->m_Position.Y <= CornerToMove->m_pParentRoom_2->m_BottomLeft.m_Position.Y)
				{
					/// We move the nodes that represent  the door of room 1.
					++CornerToMove->m_pNodeVector[2]->m_Position.Y;
					++CornerToMove->m_pNodeVector[3]->m_Position.Y;

					/// We move the inner and outer nodes. 
					++CornerToMove->m_pNodeVector[1]->m_Position.Y;
					++CornerToMove->m_pNodeVector[4]->m_Position.Y;
				}
				else
				{
					bFlagY = true;
				}

				if (bFlagX && bFlagY)
					return false;
			}

			return true;
			break;

		default:
			break;
		}
	}
	void LG_HallwayGeneration::ReorganizeCornerHallway(std::shared_ptr<LG_Polygon> CornerToReorganize, std::shared_ptr<LG_Polygon> SecondCorner)
	{

		for (int32 k = 0; k < m_pRooms->size(); ++k)
		{
			/// We make sure that it doesn't check collision with none of it's parent rooms.
			if (CornerToReorganize->m_pParentRoom_2 != (*m_pRooms)[k] && CornerToReorganize->m_pParentRoom_1 != (*m_pRooms)[k])
			{
				/// 
				if (CornerToReorganize->CheckCollision(*(*m_pRooms)[k]))
				{
					LG_Rect* TempRoom1 = CornerToReorganize->m_pParentRoom_2;
					LG_Rect* TempRoom2 = CornerToReorganize->m_pParentRoom_1;
					SecondCorner = GenerateCornerHallway(TempRoom1, TempRoom2);

					/// We see between which rooms is better to generate the hallway. Based on the distance between the rooms and the hallway.
					/// The more distance we have, the more we can move the hallways so that they don't collide with other objects.
					float fDistance1 = GetLongestDistance(*CornerToReorganize);
					float fDistance2 = GetLongestDistance(*SecondCorner);

					/// the first hallway we calculated is best for moving it and avoiding collisions.
					if (fDistance1 >= fDistance2)
					{
						// TODO: recorrer el pasillo lo más que se pueda para la dirección que le toque.
						//dependiendo del caso del pasillo, igual y generar una función que se encargue de eso, qué pedo?
						if (MoveCorner(CornerToReorganize, (*m_pRooms)[k]))
						{
							//TODO: Insertar la esquina como que ya se armo. Checar logica pero break.
							break;
						}

						else
						{
							///
							if (MoveCorner(SecondCorner, (*m_pRooms)[k]))
							{
								//TODO: Insertar la esquina como que ya se armo. Checar logica pero break.
								CornerToReorganize = SecondCorner;
								break;
							}
							else
							{
								//TODO: Ninguna esquina funciono que pedo ???
							}
						}

					}
					/// The second hall we generated is best to implement.
					else
					{
						///
						if (MoveCorner(SecondCorner, (*m_pRooms)[k]))
						{
							//TODO: Insertar la esquina como que ya se armo. Checar logica pero break.
							CornerToReorganize = SecondCorner;
							break;
						}
						else
						{
							if (MoveCorner(CornerToReorganize, (*m_pRooms)[k]))
							{
								// TODO: Insertar la esquina como que ya se armo.Checar logica pero break.

								break;
							}

							else
							{
								//TODO: Ninguna esquina funciono que pedo ???
							}
						}
					}
					break;
				}
			}
		}
	}
}