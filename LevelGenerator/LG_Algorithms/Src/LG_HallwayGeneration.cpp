#include "LG_HallwayGeneration.h"

#include <LG_Math.h>
#include <LG_Rect.h>

namespace LevelGenerator
{
	const float LG_HallwayGeneration::_20_DEGREES = LG_Math::PI / 9;
	const float LG_HallwayGeneration::_70_DEGREES = (LG_Math::PI * 7) / 18;
	const float LG_HallwayGeneration::_110_DEGREES = (LG_Math::PI * 11) / 18;
	const float LG_HallwayGeneration::_160_DEGREES = (LG_Math::PI * 8) / 9;
	const float LG_HallwayGeneration::_200_DEGREES = (LG_Math::PI * 10) / 9;
	const float LG_HallwayGeneration::_250_DEGREES = (LG_Math::PI * 25) / 18;
	const float LG_HallwayGeneration::_290_DEGREES = (LG_Math::PI * 29) / 18;
	const float LG_HallwayGeneration::_340_DEGREES = (LG_Math::PI * 34) / 18;

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

		LG_Vector3D AngleVect;
		float fAngle;
		/// The created hallway.
		LG_Polygon* pHallway;
		///
		LG_Vector3D MidPoint(0, 0, 0);

		///
		LG_Vector2D Max_Pos;
		///
		LG_Vector2D Min_Pos;


		/// We iterate all the rooms and it's connections.
		for (int32 i = 0; i < m_pRooms->size(); ++i)
		{
			for (int32 j = 0; j < (*m_pRooms)[i]->m_RoomsConnections.size(); ++j)
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
			
				GenerateCornerHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
			}
		}

		/*	/// Makes hallways with the connections from every room.
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
							pHallway = MakeHorizontalHallway((*m_pRooms)[i], (*m_pRooms)[i]->m_RoomsConnections[j]);
							m_FinalHallways.push_back(pHallway);
						}
						else if (fAngle > _70_DEGREES && fAngle < _110_DEGREES)
						{
							/// If the angle of the connection is inside of this limits, we consider it a vertical hallway.
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
			}*/
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
		/// Now that the node has it's position set, we add it to the polygon.
		spNewHall->InsertNodeToVector(spBLNode);
		/// 
		spNewHall->InsertNodeToVector(spBRNode);
		/// 
		spNewHall->InsertNodeToVector(spTRNode);
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
		/// Now that the node has it's position set, we add it to the polygon.
		spNewHall->InsertNodeToVector(spBLNode);
		/// 
		spNewHall->InsertNodeToVector(spBRNode);
		/// 
		spNewHall->InsertNodeToVector(spTRNode);
		/// 
		m_FinalHallways.push_back(spNewHall);
	}

	//! Creates a L shaped hallway between two rooms.
	void LG_HallwayGeneration::GenerateCornerHallway(LG_Rect * pRoom1, LG_Rect * pRoom2)
	{

	}

	//! Creates a vertical hallway between two rooms.
	LG_Polygon* LG_HallwayGeneration::MakeVerticalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2)
	{
		/// Where we store the generated room.
		LG_Polygon* pFinalHallway = new LG_Polygon();
		///
		float fMiddlePosX = 0.0f;
		/// the distance between both rooms in the X axis.
		float fDistanceBetweenRooms = 0.0f;
		/// The position of the room that's got a higher value in the Y axis
		float fTopPosY = 0.0f;
		/// The position of the room that's got a lower value in the Y axis.
		float fBottomPosY = 0.0f;
		/// The position of the room's that's got a lower value in the X axis.
		float fLeftPosX = 0.0f;
		/// The position of the room's that's got a lower value in the X axis.
		float fRightPosX = 0.0f;
		///
		float fTempTopPosY = 0.0f;
		///
		float fTempBottomPosY = 0.0f;

		///
		SetRoomsCases(pRoom1, pRoom2);

		/*/// We find the maximum and minimum and maximum positions in the Y axis of the hallway.
		fBottomPosY = LG_Math::Max(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y);
		fTopPosY = LG_Math::Min(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y);

		/// We find the maximum and minimum and maximum positions in the X axis of the hallway.
		fRightPosX = LG_Math::Max(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);
		fLeftPosX = LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);

		///
		fTempTopPosY = fTopPosY;
		///
		fTempBottomPosY = fBottomPosY;

		/// Sees if we need to subtract or add to the bottom or top position.
		if (pRoom1->m_CenterNode.m_Position.Y == fTempBottomPosY)
		{
			fBottomPosY -= pRoom1->m_fHeight / 2;
		}
		else if (pRoom1->m_CenterNode.m_Position.Y == fTempTopPosY)
		{
			fTopPosY += pRoom1->m_fHeight / 2;
		}

		if (pRoom2->m_CenterNode.m_Position.Y == fTempBottomPosY)
		{
			fBottomPosY -= pRoom2->m_fHeight / 2;
		}
		else if (pRoom2->m_CenterNode.m_Position.Y == fTempTopPosY)
		{
			fTopPosY += pRoom2->m_fHeight / 2;
		}

		/// We store the width and height of the hallway. The height depends on the distance between the rooms.
		pFinalHallway->m_fWidth = m_fHallwayWidth;
		pFinalHallway->m_fHeight = fBottomPosY - fTopPosY;

		/// We find the difference in distance on the X axis between both rooms.
		fDistanceBetweenRooms =
			LG_Math::Max(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X) -
			LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);

		/// If it isn't a straight line we divide the middle position, and then it will be added to the room that's
		/// nearest to the origin in the X axis. Becoming the middle position between both rooms.
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the X axis, We just add it to the lowest position
		/// to get the middle point in the X axis where we will generate the hallway.
		fMiddlePosX = LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X) + fDistanceBetweenRooms;

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
		pFinalHallway->m_CenterNode.m_Position.Z = 0.0f;*/

		/// We store the hallway that has just been generated in the final hallways vector.
		return pFinalHallway;
	}

	//! Creates a horizontal hallway between two rooms.
	LG_Polygon* LG_HallwayGeneration::MakeHorizontalHallway(LG_Rect* pRoom1, LG_Rect* pRoom2)
	{
		/// Where we store the generated room.
		LG_Polygon* pFinalHallway = new LG_Polygon();
		/// The middle position in the X axis between both rooms.
		float fMiddlePosY = 0.0f;
		/// the distance between both rooms in the Y axis.
		float fDistanceBetweenRooms = 0.0f;
		/// 
		float fRightPosX = 0.0f;
		/// 
		float fLeftPosX = 0.0f;
		/// 
		float fTempRightPosX = 0.0f;
		///
		float fTempLeftPosX = 0.0f;


		///
		SetRoomsCases(pRoom1, pRoom2);

		// TODO: Hacer en funcion
		if (LEFT == pRoom1->m_iRoomCase)
		{
			/// LLama la funcion que checa cual de las dos posibilidades tiene hacia la izquierda.
			//TODO: Nota tomar encuenta que esto puede verse afectado por el angulo.
			if (pRoom1->m_BottomRight.m_Position.Y >= pRoom2->m_TopLeft.m_Position.Y)
			{
				if (pRoom1->m_BottomRight.m_Position.Y - pRoom2->m_TopLeft.m_Position.Y >= m_fHallwayWidth)
				{
					fDistanceBetweenRooms = pRoom2->m_TopLeft.m_Position.X - pRoom1->m_BottomRight.m_Position.X;

					LG_Node* pBL = new LG_Node();
					pBL->m_Position = pRoom1->m_BottomRight.m_Position;

					LG_Node* pBR = new LG_Node();
					pBR = pBL;
					pBR->m_Position.X += fDistanceBetweenRooms;

					LG_Node* pTR = new LG_Node();
					pTR = pBR;
					pTR->m_Position.Y -= m_fHallwayWidth;

					LG_Node* pTL = new LG_Node();
					pTL = pTR;
					pTL->m_Position.X -= fDistanceBetweenRooms;

					//pFinalHallway->InsertNodeToVector(pBL);
					//pFinalHallway->InsertNodeToVector(pBR);
					//pFinalHallway->InsertNodeToVector(pTR);
					//pFinalHallway->InsertNodeToVector(pTL);
				}

				else
				{
					//TODO: Hacer un corner.
				}
			}

			else if (pRoom1->m_TopRight.m_Position.Y <= pRoom2->m_BottomLeft.m_Position.Y)
			{

				if (pRoom2->m_BottomLeft.m_Position.Y - pRoom1->m_TopRight.m_Position.Y >= m_fHallwayWidth)
				{

					fDistanceBetweenRooms = pRoom2->m_TopLeft.m_Position.X - pRoom1->m_BottomRight.m_Position.X;

					LG_Node* pBL = new LG_Node();
					pBL->m_Position = pRoom1->m_BottomRight.m_Position;

					LG_Node* pBR = new LG_Node();
					pBR = pBL;
					pBR->m_Position.X += fDistanceBetweenRooms;

					LG_Node* pTR = new LG_Node();
					pTR = pBR;
					pTR->m_Position.Y -= m_fHallwayWidth;

					LG_Node* pTL = new LG_Node();
					pTL = pTR;
					pTL->m_Position.X -= fDistanceBetweenRooms;

					//pFinalHallway->InsertNodeToVector(pBL);
					//pFinalHallway->InsertNodeToVector(pBR);
					//pFinalHallway->InsertNodeToVector(pTR);
					//pFinalHallway->InsertNodeToVector(pTL);

				}

				else
				{
					//TODO: Hacer un corner.
				}
			}
		}

		else if (RIGHT == pRoom1->m_iRoomCase)
		{

		}

		/*/// Since we are calculating the hallway's positions from the Room's center nodes, we will now subtract, or add half of the room's width.
		/// This will make the hallways spawn from the border of the room (the wall) and not  from the center node.

		/// It's time to figure out Which room is at the left and which one is at the right of each other.
		fRightPosX = LG_Math::Max(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);
		fLeftPosX = LG_Math::Min(pRoom1->m_CenterNode.m_Position.X, pRoom2->m_CenterNode.m_Position.X);

		/// We store the value in a temporal variable so that we keep the original value.
		fTempLeftPosX = fLeftPosX;
		fTempRightPosX = fRightPosX;

		/// Sees if we need to subtract or add to the bottom or top position.
		if (pRoom1->m_CenterNode.m_Position.X == fTempRightPosX)
		{
			fRightPosX -= pRoom1->m_fWidth / 2;
		}
		else if (pRoom1->m_CenterNode.m_Position.X == fTempLeftPosX)
		{
			fLeftPosX += pRoom1->m_fWidth / 2;
		}

		if (pRoom2->m_CenterNode.m_Position.X == fTempRightPosX)
		{
			fRightPosX -= pRoom2->m_fWidth / 2;
		}
		else if (pRoom2->m_CenterNode.m_Position.X == fTempLeftPosX)
		{
			fLeftPosX += pRoom2->m_fWidth / 2;
		}

		/// Assign the final hallway width and height.
		pFinalHallway->m_fWidth = fRightPosX - fLeftPosX;
		pFinalHallway->m_fHeight = m_fHallwayWidth;
		/// Now the distance between rooms is calculated.
		fDistanceBetweenRooms =
			LG_Math::Max(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y) -
			LG_Math::Min(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y);
		/// We get half of the room's distance, to get a mid point between both rooms, where we'll calculate our hallways.
		if (fDistanceBetweenRooms != 0.0f)
		{
			fDistanceBetweenRooms /= 2.0f;
		}

		/// We have the difference between both room's positions in the Y axis, We just add it to the lowest position
		/// to get the middle point in the Y axis where we will generate the hallway.
		fMiddlePosY = LG_Math::Min(pRoom1->m_CenterNode.m_Position.Y, pRoom2->m_CenterNode.m_Position.Y) + fDistanceBetweenRooms;

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
		pFinalHallway->m_CenterNode.m_Position.Z = 0.0f;*/

		return pFinalHallway;
	}

	////! Creates a corner hallway between two rooms. Meaning that the connection was too much of a diagonal.
	//void LG_HallwayGeneration::MakeCornerHallway(LG_Rect* pRoom1, LG_Rect* pRoom2)
	//{
	//	/// the vertical and horizontal hallways, they're being used to check collision with rooms or other hallways.
	//	LG_Polygon* pVerticalHallway = nullptr, *pHorizontalHallway = nullptr;

	//	/// See if a vertical or horizontal room can be placed between both rooms. This happens when they're too close to each other.
	//	// Se hace esto porque ahora se caculculan los casos de todos los cuartos fuera del scope de esta función, case not set significa que no puede ser un pasillo recto.
	//	//if (pRoom1->m_iRoomCase != CASE_NOT_SET && pRoom2->m_iRoomCase != CASE_NOT_SET)
	//	if (SetRoomsCornerCases(pRoom1, pRoom2))
	//	{
	//		/// We verify that a straight hallway fits through bought rooms.
	//		if (CheckForStraightHallway(pRoom1, pRoom2))
	//		{
	//			/// We exit the function since continuing would make a corner hallway where there's already a straight hall.
	//			return;
	//		}
	//	}

	//	//CalculateCornerPosition(false, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);

	//	for (int32 j = 0; j < m_pRooms->size(); ++j)
	//	{
	//		/// See if the iterating rooms collides with the hallway.
	//		if ((*m_pRooms)[j] != pRoom1 && (*m_pRooms)[j] != pRoom2)
	//		{
	//			if (pVerticalHallway->CheckCollision((*m_pRooms)[j]) || pHorizontalHallway->CheckCollision((*m_pRooms)[j]))
	//			{
	//				/// Calculates hallways with the maximum positions.
	//				//CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);
	//				break;
	//			}
	//			else
	//			{
	//				/// After knowing that it doesn't collide with a room, we make sure that it doesn't collide with another hallway.
	//				for (int32 k = 0; k < m_FinalHallways.size(); ++k)
	//				{
	//					//if (pVerticalHallway != m_FinalHallways[k] && pHorizontalHallway != m_FinalHallways[k])
	//					//{
	//					//	if (pVerticalHallway->CheckCollision(m_FinalHallways[k]) || pHorizontalHallway->CheckCollision(m_FinalHallways[k]))
	//					//	{
	//					//		/// Calculates hallways with the maximum positions.
	//					//		CalculateCornerPosition(true, pVerticalHallway, pHorizontalHallway, pRoom1, pRoom2);
	//					//		break;
	//					//	}
	//					//}
	//				}
	//			}
	//		}
	//	}

	//	/// We store the generated hallways.
	//	//m_FinalHallways.push_back(pVerticalHallway);
	//	//m_FinalHallways.push_back(pHorizontalHallway);
	//}

	//! Calculates each room's cases.
	void LG_HallwayGeneration::SetRoomsCases(LG_Rect * pRoom1, LG_Rect * pRoom2)
	{
		if (pRoom1->m_CenterNode.m_Position.X < pRoom2->m_CenterNode.m_Position.X)
		{
			pRoom1->m_iRoomCase = LEFT;
			pRoom2->m_iRoomCase = RIGHT;

		}
		else if (pRoom1->m_CenterNode.m_Position.X > pRoom2->m_CenterNode.m_Position.X)
		{
			pRoom2->m_iRoomCase = LEFT;
			pRoom1->m_iRoomCase = RIGHT;

		}
		else if (pRoom1->m_CenterNode.m_Position.Y < pRoom2->m_CenterNode.m_Position.Y)
		{
			pRoom1->m_iRoomCase = UP;
			pRoom2->m_iRoomCase = DOWN;

		}
		else if (pRoom1->m_CenterNode.m_Position.Y > pRoom2->m_CenterNode.m_Position.Y)
		{
			pRoom2->m_iRoomCase = UP;
			pRoom1->m_iRoomCase = DOWN;

		}
	}

	//! Calculates each room's cases.
	bool LG_HallwayGeneration::SetRoomsCornerCases(LG_Rect * pRoom1, LG_Rect * pRoom2)
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
		if (TOP_LEFT == pRoom1->m_iRoomCase)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_BottomRight.m_Position.Y >= pRoom2->m_TopLeft.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom1->m_BottomRight.m_Position.Y - pRoom2->m_TopLeft.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.

					//m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
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
					//m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// The first room's case is TOP_RIGHT, and the second one's is BOTTOMLEFT.
		else if (TOP_RIGHT == pRoom1->m_iRoomCase)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_BottomLeft.m_Position.Y >= pRoom2->m_TopRight.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom1->m_BottomLeft.m_Position.Y - pRoom2->m_TopRight.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					//m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
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
					//m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// CHECK this one
		else if (BOTTOM_LEFT == pRoom1->m_iRoomCase)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_TopRight.m_Position.Y <= pRoom2->m_BottomLeft.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom2->m_BottomLeft.m_Position.Y - pRoom1->m_TopRight.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					//m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
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
					//m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
					return true;
				}
				return false;
			}
		}

		/// 
		else if (BOTTOM_RIGHT == pRoom1->m_iRoomCase)
		{
			/// If the first room is next to the second, instead of on top. We see if a straight hall can fit through those rooms.
			if (pRoom1->m_TopLeft.m_Position.Y <= pRoom2->m_BottomRight.m_Position.Y)
			{
				/// We see if the hallway fits.
				if (pRoom2->m_BottomRight.m_Position.Y - pRoom1->m_TopLeft.m_Position.Y >= m_fHallwayWidth)
				{
					/// Now a new horizontal hallway is created.
					//m_FinalHallways.push_back(MakeHorizontalHallway(pRoom1, pRoom2));
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
					//m_FinalHallways.push_back(MakeVerticalHallway(pRoom1, pRoom2));
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
			//VerticalHall = MakeVerticalHallway(pHallwayCorner, Room1);
			//HorizontalHall = MakeHorizontalHallway(pHallwayCorner, Room2);
		}
		else if (pCorner->m_Position.Y == Room1->m_CenterNode.m_Position.Y)
		{
			//HorizontalHall = MakeHorizontalHallway(pHallwayCorner, Room1);
			//VerticalHall = MakeVerticalHallway(pHallwayCorner, Room2);
		}
	}
}