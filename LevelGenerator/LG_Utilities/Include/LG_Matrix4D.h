#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include "LG_Math.h"
#include "LG_Vector4D.h"

namespace LevelGenerator
{
	class LG_Vector4D;
	class LG_Vector3D;

#pragma push(pack)
#pragma pack(16)

	/**
	*	@brief This class is a 3 dimensional matrix.
	*/
	class LG_UTILITIES_EXPORT LG_Matrix4D
	{
	public:

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/
		union
		{
			struct
			{

				float X0, Y0, Z0, W0,
					X1, Y1, Z1, W1,
					X2, Y2, Z2, W2,
					X3, Y3, Z3, W3;
			}m;
			float LikeArray[16];
			float LikeMatrix[4][4];
		};

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		 LG_Matrix4D();

		/**
		 *	@brief Default destructor.
		 */
		 ~LG_Matrix4D();

		/**
		 *	@brief Constructor with parameters.
		 */
		 LG_Matrix4D(	float fX0, float fY0, float fZ0, float fW0,
						float fX1, float fY1, float fZ1, float fW1,
						float fX2, float fY2, float fZ2, float fW2,
						float fX3, float fY3, float fZ3, float fW3);

		 ///************************************************************************/
		 ///*						Arithmetic Operators.				           */
		 ///************************************************************************/

		/**
		 *	@brief This is an operator that uses + between 2 matrices.
		 *	@param const LG_Matrix4D& M: The matrix to add.
		 *	@return the result of the addition.
		 */
		 LG_Matrix4D operator+(const LG_Matrix4D& M);

		/**
		 *	@brief This is an operator that uses - between 2 matrices.
		 *	@param const LG_Matrix4D& M: The matrix to substract.
		 *	@return the result of the substraction.
		 */
		 LG_Matrix4D operator-(const LG_Matrix4D& M);

		/**
		 *	@brief This is an operator that uses * between 2 matrices.
		 *	@param const LG_Matrix4D& M: The matrix to multiply.
		 *	@return the result of the multiplication.
		 */
		 LG_Matrix4D operator*(const LG_Matrix4D& M);

		/**
		 *	@brief This is an operator that uses * between a matrix and a float.
		 *	@param float value: The value to multiply the matrix.
		 *	@return the result of the multiplication.
		 */
		 LG_Matrix4D operator*(float Value);

		/**
		 *	@brief This is an operator that uses * between a matrix and a 4D vector.
		 *	@param const LG_Vector4D V: The vector that will multiply the matrix.
		 *	@return the result of the multiplication.
		 */
		 LG_Vector4D operator*(const LG_Vector4D& V);

		/**
		 *	@brief This is an operator that uses / between a matrix and a float.
		 *	@param float fValue: The value to divide the matrix.
		 *	@return the result of the division.
		 */
		 LG_Matrix4D operator/(float fValue);

		/**
		 *	@brief This is an operator that uses += between 2 matrices.
		 *	@param const LG_Matrix4D M: The matrix that will be added.
		 *	@return the result of the addition.
		 */
		 LG_Matrix4D& operator+=(const LG_Matrix4D& M);

		/**
		 *	@brief This is an operator that uses -= between 2 matrices.
		 *	@param const LG_Matrix4D M: The matrix that will be substracted.
		 *	@return the result of the substraction.
		 */
		 LG_Matrix4D& operator-=(const LG_Matrix4D& M);

		/**
		 *	@brief This is an operator that uses *= between 2 matrices.
		 *	@param const LG_Matrix4D M: The matrix that will be multiplied.
		 *	@return the result of the multiplication.
		 */
		 LG_Matrix4D& operator*=(const LG_Matrix4D& M);

		/**
		 *	@brief Transposes a matrix.
		 *	@return The transposed matrix.
		 */
		 LG_Matrix4D Transpose();

		/**
		 *	@brief Used to equalize a matrix to it's identity.
		 *	@return A new identity matrix.
		 */
		 static LG_Matrix4D Identity(void);

		 /**
		 *	@brief Used to equalize a matrix to 0.
		 *	@return A new matrix with all it's components assigned to 0.
		 */
		 static LG_Matrix4D Zero(void);

		 /**
		  *	@brief Calculates the perspective field of view.
		  *	@param float zNear: the near plane.
		  *	@param float zFar: far plane.
		  *	@param float FOV: the opening angle.
		  *	@param AspectRatio: the width minus the height.
		  */
		 void PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio);

		 /**
		  *	@brief Calculates the inverse of the matrix.
		  */
		 void Inverse();

		/**
		 *	@brief Gets the adjunct of a given matrix.
		 *	@param LG_Matrix4D M: The matrix to calculate the adjunct.
		 */
		 static LG_Matrix4D GetAdjunct(LG_Matrix4D M);

		/**
		 *	@brief Gets the determinant of a given matrix on a given position.
		 *	@param LG_Matrix4D M: The matrix to get the determinant from.
		 *	@param int32 col: the column where the determinant is.
		 *	@param int32 row: the row where the determinant is.
		 */
		 static float GetDeterminant(LG_Matrix4D M, int32 col, int32 row);

		 /**
		  *	@brief Looks at a given target on the desired position.
		  *	@param const LG_Vector4D EyePos: Where the eye will be placed.
		  *	@param const LG_Vector4D Target: Where the eye will be looking at.
		  * @param const LG_Vector4D Up: which axis is going to be upwards.
		  */
		 void LookAtLeftH(const LG_Vector4D EyePos, const LG_Vector4D Target, const LG_Vector4D Up);

		/**
		 *	@brief Translates a matrix to a given position.
		 *	@param const LG_Vector4D V: The position that we want to translate to.
		 */
		void Translation(const LG_Vector4D& V);

		/**
		 *	@brief Scales the matrix to a given scale.
		 *	@param const LG_Vector4D V: the scale that the matrix will have.
		 */
		void Scaling(const LG_Vector4D& V);

		/**
		 *	@brief Rotates the matrix in the axis given
		 *	@param const LG_Vector4D V: how many angles it will rotate in every axis.
		 *	@return The rotated matrix.
		 */
		LG_Matrix4D Rotate(const LG_Vector4D& V);

		/**
		 *	@brief Rotates the matrix in the X axis.
		 *	@param float fValue: how many angles it will rotate.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix4D RotateX(float fValue);

		/**
		 *	@brief Rotates the matrix in the Y axis.
		 *	@param float fValue: how many angles it will rotate.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix4D RotateY(float fValue);

		/**
		 *	@brief Rotates the matrix in the Z axis.
		 *	@param float fValue: how many angles it will rotate.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix4D RotateZ(float fvalue);
	};
#pragma pop(pack)
}