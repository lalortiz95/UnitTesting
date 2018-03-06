#include "LG_Polygon.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Polygon::LG_Polygon()
	{
		m_bIsCorner = false;
	}

	//! Default Destructor.
	LG_Polygon::~LG_Polygon()
	{
		Destroy();
	}

	//! 
	void LG_Polygon::Destroy()
	{
		m_bIsCorner = false;
	}

	//! This function add a edge to the vector of edges.
	void LG_Polygon::InsertNodeToVector(std::shared_ptr<LG_Node> pNewNode)
	{
		m_pNodeVector.push_back(pNewNode);
	}

	//! 
	bool LG_Polygon::CheckCollision(LG_Rect OtherRect)
	{
		if (m_pNodeVector.size() != 0)
		{
			if (!m_bIsCorner)
			{
				///
				LG_Rect TempRect;
				///
				TempRect.m_TopLeft = *m_pNodeVector[TOP_LEFT];
				TempRect.m_TopRight = *m_pNodeVector[TOP_RIGHT];
				TempRect.m_BottomRight = *m_pNodeVector[BOTTOM_RIGHT];
				TempRect.m_BottomLeft = *m_pNodeVector[BOTTOM_LEFT];

				return OtherRect.CheckCollision(&TempRect);
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
				return (OtherRect.CheckCollision(&ThisTempHorizontal) || OtherRect.CheckCollision(&ThisTempVertical));
			}
		}
		return false;
	}

	//! 
	bool LG_Polygon::CheckCollision(std::shared_ptr<LG_Polygon> pOtherPolygon)
	{
		if (m_pNodeVector.size() != 0 && pOtherPolygon->m_pNodeVector.size() != 0)
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
			if (!m_bIsCorner)
			{
				/// Assign the nodes to the temp rect from this polygon. 
				ThisPoly.m_TopLeft = *m_pNodeVector[TOP_LEFT];
				ThisPoly.m_TopRight = *m_pNodeVector[TOP_RIGHT];
				ThisPoly.m_BottomRight = *m_pNodeVector[BOTTOM_RIGHT];
				ThisPoly.m_BottomLeft = *m_pNodeVector[BOTTOM_LEFT];

				/// If the other polygon is not a corner.
				if (!pOtherPolygon->m_bIsCorner)
				{
					/// Assign the nodes to the temp rect from the other polygon.
					OtherPoly.m_TopLeft = *pOtherPolygon->m_pNodeVector[TOP_LEFT];
					OtherPoly.m_TopRight = *pOtherPolygon->m_pNodeVector[TOP_RIGHT];
					OtherPoly.m_BottomRight = *pOtherPolygon->m_pNodeVector[BOTTOM_RIGHT];
					OtherPoly.m_BottomLeft = *pOtherPolygon->m_pNodeVector[BOTTOM_LEFT];

					/// return if the collision exist or not.
					return OtherPoly.CheckCollision(&ThisPoly);
				}

				/// this object is not a corner and the other polygon is.
				else
				{
					///
					CreateTempRects(TempHorizontal, TempVertical, *pOtherPolygon);
					///
					return (ThisPoly.CheckCollision(&TempHorizontal) || ThisPoly.CheckCollision(&TempVertical));
				}
			}

			/// This polygon is a corner.
			else
			{
				/// If the other polygon is not a corner.
				if (!pOtherPolygon->m_bIsCorner)
				{
					/// Assign the nodes to the temp rect from the other polygon.
					OtherPoly.m_TopLeft = *pOtherPolygon->m_pNodeVector[TOP_LEFT];
					OtherPoly.m_TopRight = *pOtherPolygon->m_pNodeVector[TOP_RIGHT];
					OtherPoly.m_BottomRight = *pOtherPolygon->m_pNodeVector[BOTTOM_RIGHT];
					OtherPoly.m_BottomLeft = *pOtherPolygon->m_pNodeVector[BOTTOM_LEFT];

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
					CreateTempRects(TempHorizontal, TempVertical, *pOtherPolygon);

					///
					return (ThisTempHorizontal.CheckCollision(&TempHorizontal) || ThisTempHorizontal.CheckCollision(&TempVertical) ||
						ThisTempVertical.CheckCollision(&TempHorizontal) || ThisTempVertical.CheckCollision(&TempVertical));
				}
			}
		}
		return false;
	}

	//! This function generates two temp rects from the polygon to determinate the collision.
	void LG_Polygon::CreateTempRects(LG_Rect & rHorizontal, LG_Rect & rVertical, LG_Polygon pPolygon)
	{
		///
		if (pPolygon.m_eCase == ROOM1_TOPRIGHT)
		{
			rVertical.m_TopLeft = *pPolygon.m_pNodeVector[0];
			rVertical.m_TopRight = *pPolygon.m_pNodeVector[5];
			rVertical.m_BottomRight = *pPolygon.m_pNodeVector[4];
			rVertical.m_BottomLeft.m_Position.X = pPolygon.m_pNodeVector[0]->m_Position.X;
			rVertical.m_BottomLeft.m_Position.Y = pPolygon.m_pNodeVector[4]->m_Position.Y;

			rHorizontal.m_TopLeft = *pPolygon.m_pNodeVector[2];
			rHorizontal.m_BottomLeft = *pPolygon.m_pNodeVector[3];
			rHorizontal.m_BottomRight = *pPolygon.m_pNodeVector[4];
			rHorizontal.m_TopRight.m_Position.X = pPolygon.m_pNodeVector[4]->m_Position.X;
			rHorizontal.m_TopRight.m_Position.Y = pPolygon.m_pNodeVector[2]->m_Position.Y;
		}

		///
		else if (pPolygon.m_eCase == ROOM1_TOPLEFT)
		{
			rVertical.m_TopLeft = *pPolygon.m_pNodeVector[0];
			rVertical.m_TopRight = *pPolygon.m_pNodeVector[5];
			rVertical.m_BottomLeft = *pPolygon.m_pNodeVector[1];
			rVertical.m_BottomRight.m_Position.X = pPolygon.m_pNodeVector[5]->m_Position.X;
			rVertical.m_BottomRight.m_Position.Y = pPolygon.m_pNodeVector[1]->m_Position.Y;

			rHorizontal.m_TopRight = *pPolygon.m_pNodeVector[3];
			rHorizontal.m_BottomRight = *pPolygon.m_pNodeVector[2];
			rHorizontal.m_BottomLeft = *pPolygon.m_pNodeVector[1];
			rHorizontal.m_TopLeft.m_Position.X = pPolygon.m_pNodeVector[1]->m_Position.X;
			rHorizontal.m_TopLeft.m_Position.Y = pPolygon.m_pNodeVector[3]->m_Position.Y;
		}

		///
		else if (pPolygon.m_eCase == ROOM1_BOTTOMRIGHT)
		{

			rHorizontal.m_TopLeft = *pPolygon.m_pNodeVector[3];
			rHorizontal.m_BottomLeft = *pPolygon.m_pNodeVector[2];
			rHorizontal.m_TopRight = *pPolygon.m_pNodeVector[4];
			rHorizontal.m_BottomRight.m_Position.X = pPolygon.m_pNodeVector[4]->m_Position.X;
			rHorizontal.m_BottomRight.m_Position.Y = pPolygon.m_pNodeVector[2]->m_Position.Y;

			rVertical.m_BottomRight = *pPolygon.m_pNodeVector[5];
			rVertical.m_BottomLeft = *pPolygon.m_pNodeVector[0];
			rVertical.m_TopRight = *pPolygon.m_pNodeVector[4];
			rVertical.m_TopLeft.m_Position.X = pPolygon.m_pNodeVector[0]->m_Position.X;
			rVertical.m_TopLeft.m_Position.Y = pPolygon.m_pNodeVector[4]->m_Position.Y;
		}

		///
		else if (pPolygon.m_eCase == ROOM1_BOTTOMLEFT)
		{
			rVertical.m_BottomLeft = *pPolygon.m_pNodeVector[0];
			rVertical.m_TopLeft = *pPolygon.m_pNodeVector[1];
			rVertical.m_BottomRight = *pPolygon.m_pNodeVector[5];
			rVertical.m_TopRight.m_Position.X = pPolygon.m_pNodeVector[5]->m_Position.X;
			rVertical.m_TopRight.m_Position.Y = pPolygon.m_pNodeVector[1]->m_Position.Y;

			rHorizontal.m_TopLeft = *pPolygon.m_pNodeVector[1];
			rHorizontal.m_TopRight = *pPolygon.m_pNodeVector[2];
			rHorizontal.m_BottomRight = *pPolygon.m_pNodeVector[3];
			rHorizontal.m_BottomLeft.m_Position.X = pPolygon.m_pNodeVector[1]->m_Position.X;
			rHorizontal.m_BottomLeft.m_Position.Y = pPolygon.m_pNodeVector[3]->m_Position.Y;
		}
	}
}
