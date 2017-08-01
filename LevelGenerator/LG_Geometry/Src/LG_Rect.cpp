#include "LG_Rect.h"
#include "LG_Math.h"

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Rect::LG_Rect()
	{
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

	//! Function to realease memory and destroy objects.
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

}