#include "LG_Rect.h"
#include "LG_Math.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Rect::LG_Rect()
	{
		m_CenterNode = LG_Vector3D(0, 0, 0);
		m_Direction = LG_Vector3D(0, 0, 0);
		m_fHeight = 0.0f;
		m_fWidth = 0.0f;
		m_RotationMatrix.Zero();
	}

	LG_Rect::LG_Rect(LG_Node CenterNode, float fWidth, float fHeight)
	{
		m_Direction = LG_Vector3D(0, 0, 0);
		Init(CenterNode, fWidth, fHeight);
	}

	//! Default destructor.
	LG_Rect::~LG_Rect()
	{
		/// Call the destroy function.
		Destroy();
	}

	//! Function to initialize the variables.
	void LG_Rect::Init(LG_Vector3D StartPosition, LG_Vector3D EndPosition, float fRange)
	{

		/// A new vector from the given points, sent to the origin.
		LG_Vector3D PositionNode = (EndPosition - StartPosition) - (StartPosition - StartPosition);

		/// We now normalize the vector.
		PositionNode.Normalize();
		/// Initialize the width and height
		m_fWidth = PositionNode.Magnitude();
		m_fHeight = fRange;

		///The angle between the given vector and the x axis.
		float fAngle;
		fAngle = LG_Math::Atan(PositionNode.Y / PositionNode.X);

		/// We rotate this matrix in the Z Axis with the given angle.
		m_RotationMatrix = LG_Matrix3D::RotateZ(fAngle);
		/// WE apply the inverse of the matrix, so that it's rotated to the origin.
		m_RotationMatrix.Inverse();
		/// Now it's time to rotate our vector.
		PositionNode *= m_RotationMatrix;

		/// Calculate the position to ever vertex of the rectangle.
		m_TopRight.m_Position = PositionNode;
		m_TopRight.m_Position.Y += (m_fHeight / 2);

		m_TopLeft.m_Position = m_TopRight.m_Position;
		m_TopLeft.m_Position.X -= m_fWidth;

		m_BottomRight.m_Position = m_TopRight.m_Position;
		m_BottomRight.m_Position.Y -= m_fHeight;

		m_BottomLeft.m_Position = m_TopLeft.m_Position;
		m_BottomLeft.m_Position.Y -= m_fHeight;
	}

	//! 
	void LG_Rect::Init(LG_Node CenterNode, float fWidth, float fHeight)
	{
		/// assign value to the variable
		m_CenterNode = CenterNode;
		m_fHeight = fHeight;
		m_fWidth = fWidth;

		/// We initialize all the nodes positions.
		m_TopLeft.m_Position.X = m_CenterNode.m_Position.X - (fWidth / 2);
		m_TopLeft.m_Position.Y = m_CenterNode.m_Position.Y - (fHeight / 2);

		m_BottomLeft.m_Position.X = m_TopLeft.m_Position.X;
		m_BottomLeft.m_Position.Y = m_TopLeft.m_Position.Y + fHeight;

		m_TopRight.m_Position.X = m_TopLeft.m_Position.X + m_fWidth;
		m_TopRight.m_Position.Y = m_TopLeft.m_Position.Y;

		m_BottomRight.m_Position.X = m_TopRight.m_Position.X;
		m_BottomRight.m_Position.Y = m_BottomLeft.m_Position.Y;
	}

	//! Function to release memory and destroy objects.
	void LG_Rect::Destroy()
	{
		
	}

	//! This functions checks if the given node is colliding with the rect.
	bool LG_Rect::CheckCollision(LG_Node ActualNode, LG_Node StartPosition)
	{
		/// We multiply this node times the rotation matrix, to send it to the origin.

		LG_Vector3D RotatedNode;
		RotatedNode = (ActualNode.m_Position - StartPosition.m_Position) - (StartPosition.m_Position - StartPosition.m_Position);
		RotatedNode.Normalize();
		RotatedNode *= m_RotationMatrix;

		/// We check if the node is inside of the rectangle, after both have been rotated
		/// and sent to the origin.
		return (RotatedNode.X >= m_TopLeft.m_Position.X &&
			RotatedNode.X <= m_BottomRight.m_Position.X &&
			RotatedNode.Y <= m_TopLeft.m_Position.Y &&
			RotatedNode.Y >= m_BottomRight.m_Position.Y);
	}

	bool LG_Rect::CheckCollision(LG_Rect * pRect, float fRange)
	{
		LG_Vector3D tTopLeft = pRect->m_TopLeft.m_Position;
		tTopLeft.X -= fRange;
		tTopLeft.Y -= fRange;

		LG_Vector3D tTopRight = pRect->m_TopRight.m_Position;
		tTopRight.X += fRange;
		tTopRight.Y -= fRange;

		LG_Vector3D tBottomLeft = pRect->m_BottomLeft.m_Position;
		tBottomLeft.X -= fRange;
		tBottomLeft.Y += fRange;

		LG_Vector3D tBottomRight = pRect->m_BottomRight.m_Position;
		tBottomRight.X += fRange;
		tBottomRight.Y += fRange;

		/// First we check if the top left node of this rect is inside of the given rect.
		if (((m_TopLeft.m_Position.X >= tTopLeft.X  &&
			m_TopLeft.m_Position.Y >= tTopLeft.Y) &&
			(m_TopLeft.m_Position.X <= tBottomRight.X  &&
				m_TopLeft.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}
		/// check the top left node of the parameter rect.
		if (((tTopLeft.X >= m_TopLeft.m_Position.X  &&
			tTopLeft.Y >= m_TopLeft.m_Position.Y) &&
			(tTopLeft.X <= m_BottomRight.m_Position.X  &&
				tTopLeft.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}

		/// Check the top right of the rect.
		if (((m_TopRight.m_Position.X >= tTopLeft.X  &&
			m_TopRight.m_Position.Y >= tTopLeft.Y) &&
			(m_TopRight.m_Position.X <= tBottomRight.X  &&
				m_TopRight.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}

		/// Check the top right of the parameter rect.
		if (((tTopRight.X >= m_TopLeft.m_Position.X  &&
			tTopRight.Y >= m_TopLeft.m_Position.Y) &&
			(tTopRight.X <= m_BottomRight.m_Position.X  &&
				tTopRight.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}




		/// Check the bottom left of the rect.
		if (((m_BottomLeft.m_Position.X >= tTopLeft.X  &&
			m_BottomLeft.m_Position.Y >= tTopLeft.Y) &&
			(m_BottomLeft.m_Position.X <= tBottomRight.X  &&
				m_BottomLeft.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}
		/// Check the bottom left of the parameter rect.
		if (((tBottomLeft.X >= m_TopLeft.m_Position.X  &&
			tBottomLeft.Y >= m_TopLeft.m_Position.Y) &&
			(tBottomLeft.X <= m_BottomRight.m_Position.X  &&
				tBottomLeft.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}

		/// Check the bottom right of the rect.
		if (((m_BottomRight.m_Position.X >= tTopLeft.X  &&
			m_BottomRight.m_Position.Y >= tTopLeft.Y) &&
			(m_BottomRight.m_Position.X <= tBottomRight.X  &&
				m_BottomRight.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}

		/// Check the bottom right of the rect.
		if (((tBottomRight.X >= m_TopLeft.m_Position.X  &&
			tBottomRight.Y >= m_TopLeft.m_Position.Y) &&
			(tBottomRight.X <= m_BottomRight.m_Position.X  &&
				tBottomRight.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}



		if ((m_TopLeft.m_Position.X >= tTopLeft.X  &&
			m_TopRight.m_Position.X <= tBottomRight.X) &&
			(m_TopLeft.m_Position.Y <= tTopLeft.Y && m_BottomRight.m_Position.Y >= tBottomRight.Y))

		{
			return true;
		}


		if ((tTopLeft.X >= m_TopLeft.m_Position.X  &&
			tTopRight.X <= m_BottomRight.m_Position.X) &&
			(tTopLeft.Y <= m_TopLeft.m_Position.Y && tBottomRight.Y >= m_BottomRight.m_Position.Y))

		{
			return true;
		}

		return false;
	}

	void LG_Rect::RestructureNodes()
	{
		/// We initialize all the nodes positions.
		m_TopLeft.m_Position.X = m_CenterNode.m_Position.X - (m_fWidth / 2);
		m_TopLeft.m_Position.Y = m_CenterNode.m_Position.Y - (m_fHeight / 2);

		m_BottomLeft.m_Position.X = m_TopLeft.m_Position.X;
		m_BottomLeft.m_Position.Y = m_TopLeft.m_Position.Y + m_fHeight;

		m_TopRight.m_Position.X = m_TopLeft.m_Position.X + m_fWidth;
		m_TopRight.m_Position.Y = m_TopLeft.m_Position.Y;

		m_BottomRight.m_Position.X = m_TopRight.m_Position.X;
		m_BottomRight.m_Position.Y = m_BottomLeft.m_Position.Y;
	}

	//TODO: Falta checar por tamaños del rect...
	bool LG_Rect::CheckCollision(LG_Rect * pRect)
	{
		LG_Vector3D tTopLeft = pRect->m_TopLeft.m_Position;
		LG_Vector3D tTopRight = pRect->m_TopRight.m_Position;
		LG_Vector3D tBottomLeft = pRect->m_BottomLeft.m_Position;
		LG_Vector3D tBottomRight = pRect->m_BottomRight.m_Position;

		/// First we check if the top left node of this rect is inside of the given rect.
		if (((m_TopLeft.m_Position.X >= tTopLeft.X  &&
			m_TopLeft.m_Position.Y >= tTopLeft.Y) &&
			(m_TopLeft.m_Position.X <= tBottomRight.X  &&
				m_TopLeft.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}
		/// check the top left node of the parameter rect.
		if (((tTopLeft.X >= m_TopLeft.m_Position.X  &&
			tTopLeft.Y >= m_TopLeft.m_Position.Y) &&
			(tTopLeft.X <= m_BottomRight.m_Position.X  &&
				tTopLeft.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}

		/// Check the top right of the rect.
		if (((m_TopRight.m_Position.X >= tTopLeft.X  &&
			m_TopRight.m_Position.Y >= tTopLeft.Y) &&
			(m_TopRight.m_Position.X <= tBottomRight.X  &&
				m_TopRight.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}

		/// Check the top right of the parameter rect.
		if (((tTopRight.X >= m_TopLeft.m_Position.X  &&
			tTopRight.Y >= m_TopLeft.m_Position.Y) &&
			(tTopRight.X <= m_BottomRight.m_Position.X  &&
				tTopRight.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}




		/// Check the bottom left of the rect.
		if (((m_BottomLeft.m_Position.X >= tTopLeft.X  &&
			m_BottomLeft.m_Position.Y >= tTopLeft.Y) &&
			(m_BottomLeft.m_Position.X <= tBottomRight.X  &&
				m_BottomLeft.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}
		/// Check the bottom left of the parameter rect.
		if (((tBottomLeft.X >= m_TopLeft.m_Position.X  &&
			tBottomLeft.Y >= m_TopLeft.m_Position.Y) &&
			(tBottomLeft.X <= m_BottomRight.m_Position.X  &&
				tBottomLeft.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}

		/// Check the bottom right of the rect.
		if (((m_BottomRight.m_Position.X >= tTopLeft.X  &&
			m_BottomRight.m_Position.Y >= tTopLeft.Y) &&
			(m_BottomRight.m_Position.X <= tBottomRight.X  &&
				m_BottomRight.m_Position.Y <= tBottomRight.Y)))
		{
			return true;
		}

		/// Check the bottom right of the rect.
		if (((tBottomRight.X >= m_TopLeft.m_Position.X  &&
			tBottomRight.Y >= m_TopLeft.m_Position.Y) &&
			(tBottomRight.X <= m_BottomRight.m_Position.X  &&
				tBottomRight.Y <= m_BottomRight.m_Position.Y)))
		{
			return true;
		}



		if ((m_TopLeft.m_Position.X >= tTopLeft.X  &&
			m_TopRight.m_Position.X <= tBottomRight.X) &&
			(m_TopLeft.m_Position.Y <= tTopLeft.Y && m_BottomRight.m_Position.Y >= tBottomRight.Y))

		{
			return true;
		}


		if ((tTopLeft.X >= m_TopLeft.m_Position.X  &&
			tTopRight.X <= m_BottomRight.m_Position.X) &&
			(tTopLeft.Y <= m_TopLeft.m_Position.Y && tBottomRight.Y >= m_BottomRight.m_Position.Y))

		{
			return true;
		}

		return false;
	}
}