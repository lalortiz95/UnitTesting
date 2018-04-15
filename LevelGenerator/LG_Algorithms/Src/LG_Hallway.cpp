#include "LG_Hallway.h"


namespace LevelGenerator
{
	//! Default constructor.
	LG_Hallway::LG_Hallway()
	{
		m_pPolygon = new LG_Polygon();
		m_pParentRoom_1 = nullptr;
		m_pParentRoom_2 = nullptr;
		m_pFirstDoor = nullptr;
		m_pSecondDoor = nullptr;
		m_Floors.clear();
		m_Ceilings.clear();
	}

	//! Default destructor.
	LG_Hallway::~LG_Hallway()
	{
		/// Call the destroy function.
		Destroy();
	}

	//! This function create a doors for the hallway.
	void LG_Hallway::CreateDoors(LG_Node* pFD_FP, LG_Node* pFD_SP, LG_Node* pSD_FP, LG_Node* pSD_SP)
	{
		/// Create the first door of the hallway.
		m_pFirstDoor = new LG_Door(pFD_FP, pFD_SP, m_fHeight);
		/// Create the second door of the hallway.
		m_pSecondDoor = new LG_Door(pSD_FP, pSD_SP, m_fHeight);
	}

	//! This function create a ceilings for the hallway.
	void LG_Hallway::CreateCeilings()
	{
		if (m_eHallwayType != CORNER)
		{
			LG_Rect* pNewCeiling = new LG_Rect();
			pNewCeiling->Init(m_pPolygon->m_pNodeVector[0]->m_Position, m_pPolygon->m_pNodeVector[1]->m_Position, m_pPolygon->m_pNodeVector[3]->m_Position, m_pPolygon->m_pNodeVector[2]->m_Position);
			pNewCeiling->m_BottomLeft.m_Position.Z = m_fHeight;
			pNewCeiling->m_BottomRight.m_Position.Z = m_fHeight;
			pNewCeiling->m_TopLeft.m_Position.Z = m_fHeight;
			pNewCeiling->m_TopRight.m_Position.Z = m_fHeight;
			pNewCeiling->m_CenterNode.m_Position.Z = m_fHeight;
			m_Ceilings.push_back(pNewCeiling);
		}
		else
		{
			LG_Rect* pNewCeiling;
			for (int32 i = 0; i < m_Floors.size(); ++i)
			{
				pNewCeiling = new LG_Rect();
				/// 
				pNewCeiling->Init(m_Floors[i]->m_TopLeft.m_Position, 
					m_Floors[i]->m_TopRight.m_Position, 
					m_Floors[i]->m_BottomLeft.m_Position, 
					m_Floors[i]->m_BottomRight.m_Position);

				/// the height is now changed to the height.
				pNewCeiling->m_BottomLeft.m_Position.Z = m_fHeight;
				pNewCeiling->m_BottomRight.m_Position.Z = m_fHeight;
				pNewCeiling->m_TopLeft.m_Position.Z = m_fHeight;
				pNewCeiling->m_TopRight.m_Position.Z = m_fHeight;
				pNewCeiling->m_CenterNode.m_Position.Z = m_fHeight;
				///
				m_Ceilings.push_back(pNewCeiling);

			}
		}
	}

	//! This function create a floors for the hallway.
	void LG_Hallway::CreateFloors()
	{
		if (m_eHallwayType != CORNER)
		{
			LG_Rect* pNewFloor = new LG_Rect();
			pNewFloor->Init(m_pPolygon->m_pNodeVector[0]->m_Position, m_pPolygon->m_pNodeVector[1]->m_Position, m_pPolygon->m_pNodeVector[3]->m_Position, m_pPolygon->m_pNodeVector[2]->m_Position);
			m_Floors.push_back(pNewFloor);
		}
		else
		{
			if (m_eCaseCorner == ROOM1_TOPRIGHT)
			{
				// Top left: node 0 [0], top right: node 1 [5], bottom left: node 4 [1], bottom right: bottom left's Y position, top right's X position.
				/// There will be 3 floors, two rectangles for both hallway directions, one square in the corner to patch the missing gap.
				/// The first floor (vertical) is generated.
				LG_Rect* pNewFloor = new LG_Rect();
				LG_Vector3D topLeft = m_pPolygon->m_pNodeVector[0]->m_Position;
				LG_Vector3D topRight = m_pPolygon->m_pNodeVector[5]->m_Position;
				LG_Vector3D bottomLeft = m_pPolygon->m_pNodeVector[1]->m_Position;
				LG_Vector3D bottomRight = topRight;
				bottomRight.Y = bottomLeft.Y;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// The floor is now stored in the hallway's vector.
				m_Floors.push_back(pNewFloor);

				/// Now the second floor is generated (horizontal)
				// Top left: node 2 [2], Top right: node 4 [1], Bottom left: node 3 [3], bottom right: bottom left's Y pos, and top right's X pos.
				pNewFloor = new LG_Rect();
				topLeft = m_pPolygon->m_pNodeVector[2]->m_Position;
				topRight = m_pPolygon->m_pNodeVector[1]->m_Position;
				bottomLeft = m_pPolygon->m_pNodeVector[3]->m_Position;
				bottomRight = topRight;
				bottomRight.Y = bottomLeft.Y;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);

				/// Now the third and last floor is calculated.
				pNewFloor = new LG_Rect();
				// Top left: node 4 [1], top right: top left's Y pos, and bottom right X position., BottomLeft: bottom right's Y pos and top left's X pos, Bottom Right: node 5 [4]
				/// 
				topRight = m_pPolygon->m_pNodeVector[4]->m_Position;
				topRight.Y = m_pPolygon->m_pNodeVector[1]->m_Position.Y;
				/// 
				bottomLeft = m_pPolygon->m_pNodeVector[4]->m_Position;
				bottomLeft.X = m_pPolygon->m_pNodeVector[1]->m_Position.X;
				pNewFloor->Init(m_pPolygon->m_pNodeVector[1]->m_Position, topRight, bottomLeft, m_pPolygon->m_pNodeVector[4]->m_Position);
				/// 
				m_Floors.push_back(pNewFloor);
			}
			else if (m_eCaseCorner == ROOM1_TOPLEFT)
			{
				// Top left: node 0 [0], top right: node 1 [5], bottom left: node 4 [4], bottom right: bottom left Y and top right X
				/// There will be 3 floors, two rectangles for both hallway directions, one square in the corner to patch the missing gap.
				/// The first floor (vertical) is generated.
				LG_Rect* pNewFloor = new LG_Rect();
				LG_Vector3D topLeft = m_pPolygon->m_pNodeVector[0]->m_Position;
				LG_Vector3D topRight = m_pPolygon->m_pNodeVector[5]->m_Position;
				LG_Vector3D bottomLeft = m_pPolygon->m_pNodeVector[4]->m_Position;
				LG_Vector3D bottomRight = topRight;
				bottomRight.Y = bottomLeft.Y;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// The floor is now stored in the hallway's vector.
				m_Floors.push_back(pNewFloor);

				/// Now the second floor is generated (horizontal)
				// Top left: node 4 [4], Top right: node 2 [3], Bottom left: BR_Y_pos and TL_X_pos, bottom right: node 3 [2].
				pNewFloor = new LG_Rect();
				topLeft = m_pPolygon->m_pNodeVector[4]->m_Position;
				topRight = m_pPolygon->m_pNodeVector[3]->m_Position;
				bottomRight = m_pPolygon->m_pNodeVector[2]->m_Position;
				bottomLeft = bottomRight;
				bottomLeft.X = topLeft.X;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);

				/// Now the third and last floor is calculated.
				pNewFloor = new LG_Rect();
				// Top left: TR_Y_pos and BL_X_pos, top right: node 4 [4], BottomLeft: node 5 [1], Bottom Right BL_Y_pos and TR_X_pos:
				bottomLeft = m_pPolygon->m_pNodeVector[1]->m_Position;
				topRight = m_pPolygon->m_pNodeVector[4]->m_Position;
				/// 
				topLeft = topRight;
				topLeft.X = bottomLeft.X;
				/// 
				bottomRight = bottomLeft;
				bottomRight.X = topRight.X;
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);
			}
			else if (m_eCaseCorner == ROOM1_BOTTOMRIGHT)
			{
				// Top left: node 4 [1], top right:, bottom left: node 0 [0], bottom right: node 1 [5]
				/// There will be 3 floors, two rectangles for both hallway directions, one square in the corner to patch the missing gap.
				/// The first floor (vertical) is generated.
				LG_Rect* pNewFloor = new LG_Rect();
				LG_Vector3D topLeft = m_pPolygon->m_pNodeVector[1]->m_Position;
				LG_Vector3D topRight = topLeft;
				LG_Vector3D bottomLeft = m_pPolygon->m_pNodeVector[0]->m_Position;
				LG_Vector3D bottomRight = m_pPolygon->m_pNodeVector[5]->m_Position;

				topRight.X = bottomRight.X;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// The floor is now stored in the hallway's vector.
				m_Floors.push_back(pNewFloor);

				/// Now the second floor is generated (horizontal)
				// Top left: node 2 [3], Top right: TL_Ypos BL_Xpos, Bottom left: node 3 [2], bottom right: node 4 [1].
				pNewFloor = new LG_Rect();
				topLeft = m_pPolygon->m_pNodeVector[3]->m_Position;
				topRight = topLeft;
				bottomLeft = m_pPolygon->m_pNodeVector[2]->m_Position;
				bottomRight = m_pPolygon->m_pNodeVector[1]->m_Position;
				topRight.X = bottomRight.X;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);

				/// Now the third and last floor is calculated.
				pNewFloor = new LG_Rect();
				// Top left: TR_Y_pos and BL_X_pos, top right: node 5 [4], BottomLeft: node 4 [1], Bottom Right BL_Y_pos and TR_X_pos:
				bottomLeft = m_pPolygon->m_pNodeVector[1]->m_Position;
				topRight = m_pPolygon->m_pNodeVector[4]->m_Position;
				/// 
				topLeft = topRight;
				topLeft.X = bottomLeft.X;
				/// 
				bottomRight = bottomLeft;
				bottomRight.X = topRight.X;
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);
			}
			else if (m_eCaseCorner == ROOM1_BOTTOMLEFT)
			{
				//este caso parece estar bien, uno está mal. on it.
				// Top left: TR_Ypos and BL_Xpos, top right: node 4 [4], bottom left: node 0 [0], bottom right: node 1 [5]
				/// There will be 3 floors, two rectangles for both hallway directions, one square in the corner to patch the missing gap.
				/// The first floor (vertical) is generated.
				LG_Rect* pNewFloor = new LG_Rect();
				LG_Vector3D topLeft;// = m_pPolygon->m_pNodeVector[1]->m_Position;
				LG_Vector3D topRight = m_pPolygon->m_pNodeVector[4]->m_Position;
				LG_Vector3D bottomLeft = m_pPolygon->m_pNodeVector[0]->m_Position;
				LG_Vector3D bottomRight = m_pPolygon->m_pNodeVector[5]->m_Position;

				topLeft = topRight;
				topLeft.X = bottomLeft.X;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// The floor is now stored in the hallway's vector.
				m_Floors.push_back(pNewFloor);

				/// Now the second floor is generated (horizontal)
				// Top left: TR_Ypos and BL_Xpos, Top right: node 2 [2], Bottom left: node 4 [4], bottom right: node 3 [3].
				pNewFloor = new LG_Rect();
				topLeft;// = m_pPolygon->m_pNodeVector[3]->m_Position;
				topRight = m_pPolygon->m_pNodeVector[2]->m_Position;
				bottomLeft = m_pPolygon->m_pNodeVector[4]->m_Position;
				bottomRight = m_pPolygon->m_pNodeVector[3]->m_Position;
				topLeft = topRight;
				topLeft.X = bottomLeft.X;
				/// 
				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);

				/// Now the third and last floor is calculated.
				pNewFloor = new LG_Rect();
				// Top left: node 5 [1], top right: , BottomLeft: , Bottom Right node 4 [4]:
				/// 
				topLeft = m_pPolygon->m_pNodeVector[1]->m_Position;
				/// 
				bottomRight = m_pPolygon->m_pNodeVector[4]->m_Position;
				
				topRight = topLeft;
				topRight.X = bottomRight.X;
				bottomLeft = bottomRight;
				bottomLeft.X = topLeft.X;

				pNewFloor->Init(topLeft, topRight, bottomLeft, bottomRight);
				/// 
				m_Floors.push_back(pNewFloor);
			}
		}
	}

	//! This function create a one wall for the hallway.
	LG_Wall * LG_Hallway::CreateWall(LG_Vector3D BottomLeft, LG_Vector3D BottomRight, bool bIsHorizontal)
	{
		LG_Wall* pNewWall = new LG_Wall();
		LG_Vector3D TopLeft, TopRight;
		TopLeft = BottomLeft;
		TopRight = BottomRight;
		TopLeft.Z = m_fHeight;
		TopRight.Z = m_fHeight;
		pNewWall->Init(TopLeft, TopRight, BottomLeft, BottomRight);
		pNewWall->m_bIsHorizontal = bIsHorizontal;
		return pNewWall;
	}

	//! Delete the memory of the walls.
	void LG_Hallway::DestroyWalls()
	{
		/// Repeat this until the size will be zero.
		while (m_Walls.size() != 0)
		{
			/// Call the destroy function of the last element of the array.
			m_Walls[m_Walls.size() - 1]->Destroy();
			/// Release the memory of the last element.
			delete m_Walls[m_Walls.size() - 1];
			/// Pop the last element.
			m_Walls.pop_back();
		}
		/// Reset the vector.
		m_Walls.clear();
	}

	//! This function delete the floors of the hallway.
	void LG_Hallway::DestroyFloors()
	{
		/// Repeat until the vector of ceilings has empty.
		while (m_Floors.size() != 0)
		{
			/// Call the destroy function of the last element of the floors vector.
			m_Floors[m_Floors.size() - 1]->Destroy();
			/// Delete the memory of the last element.
			delete m_Floors[m_Floors.size() - 1];
			/// pop the last element.
			m_Floors.pop_back();
		}

		/// Clear the vector of floors.
		m_Floors.clear();
	}

	//! This function delete the ceilings of the hallway.
	void LG_Hallway::DestroyCeilings()
	{
		/// Repeat until the vector of ceilings has empty.
		while (m_Ceilings.size() != 0)
		{
			/// Call the destroy function of the last element of the ceilings vector.
			m_Ceilings[m_Ceilings.size() - 1]->Destroy();
			/// Delete the memory of the last element.
			delete m_Ceilings[m_Ceilings.size() - 1];
			/// pop the last element.
			m_Ceilings.pop_back();
		}

		/// Clear the vector of ceilings.
		m_Ceilings.clear();
	}

	//! This function recreate the walls,floors and ceilings of the hallway.
	void LG_Hallway::ReorganizeVariables(CASES_FOR_CORNER eCase)
	{
		/// Delete the walls.
		DestroyWalls();
		/// Delete the ceilings.
		DestroyCeilings();
		/// Delete the floors.
		DestroyFloors();

		m_Walls.push_back(CreateWall(m_pPolygon->m_pNodeVector[0]->m_Position, m_pPolygon->m_pNodeVector[1]->m_Position, false));
		m_Walls.push_back(CreateWall(m_pPolygon->m_pNodeVector[1]->m_Position, m_pPolygon->m_pNodeVector[2]->m_Position, true));
		m_Walls.push_back(CreateWall(m_pPolygon->m_pNodeVector[3]->m_Position, m_pPolygon->m_pNodeVector[4]->m_Position, true));
		m_Walls.push_back(CreateWall(m_pPolygon->m_pNodeVector[4]->m_Position, m_pPolygon->m_pNodeVector[5]->m_Position, false));


		//TODO: Esto solo es para los pasillos que son esquinas. checar con los vertical y horizontal.
		ReorganizeDoors(m_pPolygon->m_pNodeVector[0]->m_Position, m_pPolygon->m_pNodeVector[5]->m_Position, m_pPolygon->m_pNodeVector[2]->m_Position, m_pPolygon->m_pNodeVector[3]->m_Position);

		//if (eCase == ROOM1_TOPRIGHT)
		//{
		//	

		//}

		//else if (eCase == ROOM1_TOPLEFT)
		//{
		//	

		//}

		//else if (eCase == ROOM1_BOTTOMRIGHT)
		//{
		//	
		//}

		//else if (eCase == ROOM1_BOTTOMLEFT)
		//{
		//	
		//}
	}


	//! This function release the memory of the object.
	void LG_Hallway::Destroy()
	{
		/// Erase the memory of the walls.
		DestroyWalls();
		/// Erase the memory of the ceilings.
		DestroyCeilings();
		/// Erase the memory of the floors.
		DestroyFloors();

		/// Check if the second door is not nullptr.
		if (m_pSecondDoor != nullptr)
		{
			/// Call the destroy function of the door.
			m_pSecondDoor->Destroy();
			/// Delete the memory.
			delete m_pSecondDoor;
			/// Set as nullptr.
			m_pSecondDoor = nullptr;
		}

		/// Check if the first door is not nullptr.
		if (m_pFirstDoor != nullptr)
		{
			/// Call the destroy function of the door.
			m_pFirstDoor->Destroy();
			/// Delete the memory.
			delete m_pFirstDoor;
			/// Set as nullptr.
			m_pFirstDoor = nullptr;
		}

		/// Reset the parent's pointers.
		m_pParentRoom_2 = nullptr;
		m_pParentRoom_1 = nullptr;

		/// Check if this pointer has memory.
		if (m_pPolygon != nullptr)
		{
			/// Call the destroy function of this pointer.
			m_pPolygon->Destroy();
			/// Delete the memory of the pointer.
			delete m_pPolygon;
			/// Assign as nullptr.
			m_pPolygon = nullptr;
		}
	}

	//! This function check if the hallway collision with other room.
	bool LG_Hallway::CheckCollisionWithRoom(LG_Room* pOtherRoom)
	{
		if (m_pPolygon->m_pNodeVector.size() != 0)
		{
			if (m_eHallwayType != CORNER)
			{
				///
				LG_Rect TempRect;
				///
				TempRect.m_TopLeft = *m_pPolygon->m_pNodeVector[TOP_LEFT];
				TempRect.m_TopRight = *m_pPolygon->m_pNodeVector[TOP_RIGHT];
				TempRect.m_BottomRight = *m_pPolygon->m_pNodeVector[BOTTOM_RIGHT];
				TempRect.m_BottomLeft = *m_pPolygon->m_pNodeVector[BOTTOM_LEFT];

				return pOtherRoom->m_pFloor->CheckCollision(&TempRect);
			}
			else
			{
				///
				LG_Rect ThisTempHorizontal;
				///
				LG_Rect ThisTempVertical;
				///
				CreateTempRects(ThisTempHorizontal, ThisTempVertical, *this);
				///
				return (pOtherRoom->m_pFloor->CheckCollision(&ThisTempHorizontal) || pOtherRoom->m_pFloor->CheckCollision(&ThisTempVertical));
			}
		}
		return false;
	}

	//! This function check if the hallway collision with other hallway.
	bool LG_Hallway::CheckCollisionWithHallway(LG_Hallway* pOtherHallway)
	{
		if (m_pPolygon->m_pNodeVector.size() != 0 && pOtherHallway->m_pPolygon->m_pNodeVector.size() != 0)
		{
			/// Create a temp rect to check the collision with other polygon.
			LG_Rect ThisPoly;
			/// Create a temp rect to check the collision with this object.
			LG_Rect OtherPoly;
			/// 
			LG_Rect TempHorizontal;
			///
			LG_Rect TempVertical;

			/// If this object is not a corner.
			if (m_eHallwayType != CORNER)
			{
				/// Assign the nodes to the temp rect from this polygon. 
				ThisPoly.m_TopLeft = *m_pPolygon->m_pNodeVector[TOP_LEFT];
				ThisPoly.m_TopRight = *m_pPolygon->m_pNodeVector[TOP_RIGHT];
				ThisPoly.m_BottomRight = *m_pPolygon->m_pNodeVector[BOTTOM_RIGHT];
				ThisPoly.m_BottomLeft = *m_pPolygon->m_pNodeVector[BOTTOM_LEFT];

				/// If the other polygon is not a corner.
				if (pOtherHallway->m_eHallwayType != CORNER)
				{
					/// Assign the nodes to the temp rect from the other polygon.
					OtherPoly.m_TopLeft = *pOtherHallway->m_pPolygon->m_pNodeVector[TOP_LEFT];
					OtherPoly.m_TopRight = *pOtherHallway->m_pPolygon->m_pNodeVector[TOP_RIGHT];
					OtherPoly.m_BottomRight = *pOtherHallway->m_pPolygon->m_pNodeVector[BOTTOM_RIGHT];
					OtherPoly.m_BottomLeft = *pOtherHallway->m_pPolygon->m_pNodeVector[BOTTOM_LEFT];

					/// return if the collision exist or not.
					return OtherPoly.CheckCollision(&ThisPoly);
				}

				/// this object is not a corner and the other polygon is.
				else
				{
					///
					CreateTempRects(TempHorizontal, TempVertical, *pOtherHallway);
					///
					return (ThisPoly.CheckCollision(&TempHorizontal) || ThisPoly.CheckCollision(&TempVertical));
				}
			}

			/// This polygon is a corner.
			else
			{
				/// If the other polygon is not a corner.
				if (pOtherHallway->m_eHallwayType != CORNER)
				{
					/// Assign the nodes to the temp rect from the other polygon.
					OtherPoly.m_TopLeft = *pOtherHallway->m_pPolygon->m_pNodeVector[TOP_LEFT];
					OtherPoly.m_TopRight = *pOtherHallway->m_pPolygon->m_pNodeVector[TOP_RIGHT];
					OtherPoly.m_BottomRight = *pOtherHallway->m_pPolygon->m_pNodeVector[BOTTOM_RIGHT];
					OtherPoly.m_BottomLeft = *pOtherHallway->m_pPolygon->m_pNodeVector[BOTTOM_LEFT];

					///
					CreateTempRects(TempHorizontal, TempVertical, *this);
					///
					return (OtherPoly.CheckCollision(&TempHorizontal) || OtherPoly.CheckCollision(&TempVertical));
				}

				/// both polygons are corners.
				else
				{
					///
					LG_Rect ThisTempHorizontal;
					///
					LG_Rect ThisTempVertical;
					///
					CreateTempRects(ThisTempHorizontal, ThisTempVertical, *this);
					///
					CreateTempRects(TempHorizontal, TempVertical, *pOtherHallway);

					///
					return (ThisTempHorizontal.CheckCollision(&TempHorizontal) || ThisTempHorizontal.CheckCollision(&TempVertical) ||
						ThisTempVertical.CheckCollision(&TempHorizontal) || ThisTempVertical.CheckCollision(&TempVertical));
				}
			}
		}
		return false;
	}

	//! This function generates two temp rects from the hallway to determinate the collision.
	void LG_Hallway::CreateTempRects(LG_Rect & rHorizontal, LG_Rect & rVertical, const LG_Hallway& pHallway)
	{
		///
		if (pHallway.m_eCaseCorner == ROOM1_TOPRIGHT)
		{
			rVertical.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[0];
			rVertical.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[5];
			rVertical.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[4];
			rVertical.m_BottomLeft.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[0]->m_Position.X;
			rVertical.m_BottomLeft.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[4]->m_Position.Y;

			rHorizontal.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[2];
			rHorizontal.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[3];
			rHorizontal.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[4];
			rHorizontal.m_TopRight.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[4]->m_Position.X;
			rHorizontal.m_TopRight.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[2]->m_Position.Y;
		}

		///
		else if (pHallway.m_eCaseCorner == ROOM1_TOPLEFT)
		{
			rVertical.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[0];
			rVertical.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[5];
			rVertical.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[1];
			rVertical.m_BottomRight.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[5]->m_Position.X;
			rVertical.m_BottomRight.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[1]->m_Position.Y;

			rHorizontal.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[3];
			rHorizontal.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[2];
			rHorizontal.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[1];
			rHorizontal.m_TopLeft.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[1]->m_Position.X;
			rHorizontal.m_TopLeft.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[3]->m_Position.Y;
		}

		///
		else if (pHallway.m_eCaseCorner == ROOM1_BOTTOMRIGHT)
		{

			rHorizontal.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[3];
			rHorizontal.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[2];
			rHorizontal.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[4];
			rHorizontal.m_BottomRight.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[4]->m_Position.X;
			rHorizontal.m_BottomRight.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[2]->m_Position.Y;

			rVertical.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[5];
			rVertical.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[0];
			rVertical.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[4];
			rVertical.m_TopLeft.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[0]->m_Position.X;
			rVertical.m_TopLeft.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[4]->m_Position.Y;
		}

		///
		else if (pHallway.m_eCaseCorner == ROOM1_BOTTOMLEFT)
		{
			rVertical.m_BottomLeft = *pHallway.m_pPolygon->m_pNodeVector[0];
			rVertical.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[1];
			rVertical.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[5];
			rVertical.m_TopRight.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[5]->m_Position.X;
			rVertical.m_TopRight.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[1]->m_Position.Y;

			rHorizontal.m_TopLeft = *pHallway.m_pPolygon->m_pNodeVector[1];
			rHorizontal.m_TopRight = *pHallway.m_pPolygon->m_pNodeVector[2];
			rHorizontal.m_BottomRight = *pHallway.m_pPolygon->m_pNodeVector[3];
			rHorizontal.m_BottomLeft.m_Position.X = pHallway.m_pPolygon->m_pNodeVector[1]->m_Position.X;
			rHorizontal.m_BottomLeft.m_Position.Y = pHallway.m_pPolygon->m_pNodeVector[3]->m_Position.Y;
		}
	}

	//!
	void LG_Hallway::ReorganizeDoors(LG_Vector3D FD_FP, LG_Vector3D FD_SP, LG_Vector3D SD_FP, LG_Vector3D SD_SP)
	{
		LG_Vector3D TopRight, TopLeft;
		TopRight = FD_FP;
		TopLeft = FD_SP;
		TopRight.Z = m_fHeight;
		TopLeft.Z = m_fHeight;
		m_pFirstDoor->m_pRectDimension->Init(TopLeft, TopRight, FD_FP, FD_SP);

		TopRight = SD_FP;
		TopLeft = SD_SP;
		TopRight.Z = m_fHeight;
		TopLeft.Z = m_fHeight;
		m_pSecondDoor->m_pRectDimension->Init(TopLeft, TopRight, SD_FP, SD_SP);
	}
}
