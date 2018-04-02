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
		m_pFirstDoor = new LG_Door(pFD_FP, pFD_SP);
		/// Create the second door of the hallway.
		m_pSecondDoor = new LG_Door(pSD_FP, pSD_SP);
	}

	//! This function create a ceilings for the hallway.
	void LG_Hallway::CreateCeilings()
	{
		
	}

	//! This function create a floors for the hallway.
	void LG_Hallway::CreateFloors()
	{
		
	}


	//! This function release the memory of the object.
	void LG_Hallway::Destroy()
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
}
