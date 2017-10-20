#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Node.h"
#include <LG_Matrix3D.h>

namespace LevelGenerator
{
	/**
	*	@brief This class is a rectangle.
	*/
	class LG_GEOMETRY_EXPORT LG_Rect
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Rect();

		/**
		 *	@brief Parameter Constructor.
		 */
		LG_Rect(LG_Vector3D Position, float fWidth, float fHeight);

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Rect();

		///**************************************************************************/
		///*						  Member Constants.								*/
		///**************************************************************************/

		/**
		 *	@var This variable stores the width of the rect.
		 */
		float m_fWidth;

		/**
		 *	@var This variable stores the height of the rect.
		 */
		float m_fHeight;

		/**
		 *	@var The center position of the rectangle.
		 */
		LG_Vector3D m_Position;

		/**
		 *	@var This matrix is used to check collisions easily.
		 */
		LG_Matrix3D m_RotationMatrix;

		/**
		 *	@var The top node on the left of the tile.
		 */
		LG_Node m_TopLeft;

		/**
		 *	@var The top node on the right of the tile.
		 */
		LG_Node m_TopRight;

		/**
		 *	@var The bottom node on the right of the tile.
		 */
		LG_Node m_BottomRight;

		/**
		 *	@var The bottom node on the left of the tile.
		 */
		LG_Node m_BottomLeft;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Function to initialize the variables.
		 *	@param LG_Vector3D StartPosition: The position of the left node.
		 *	@param LG_Vector3D EndPosition: The position of the right node.
		 *	@param float fRange: the range.
		 */
		void Init(LG_Vector3D StartPosition,LG_Vector3D EndPosition, float fRange);

		/**
		 *	@brief Function to initialize the variables.
		 *	@param LG_Vector3D Position: The center position of the rectangle.
		 *	@param float fWidth: the rectangle's width.
		 *	@param float fHeight: the rectangle's height
		 */
		void Init(LG_Vector3D Position, float fWidth, float fHeight);

		/**
		 *	@brief Function to realease memory and destroy objects.
		 */
		void Destroy();

		/**
		 *	@brief This functions checks if the given node is colliding with the rect.
		 *	@param LG_Node ActualNode: The node to check with this.
		 *	@param LG_Node StartPosition: The start position.
		 *	@return true if it's inside otherwise false.
		 */
		bool CheckCollision(LG_Node ActualNode,LG_Node StartPoistion);
	};
}

