#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include "LG_Math.h"
#include "LG_Vector3D.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class is a 3 dimensional matrix.
	 */
	class LG_UTILITIES_EXPORT LG_Matrix3D
	{
	public:

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		union
		{
			struct
			{
				float X0, Y0, Z0,
					X1, Y1, Z1,
					X2, Y2, Z2;
			}m;

			float LikeArray[9];
			float LikeMatrix[3][3];
		};

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Matrix3D();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Matrix3D();

		/**
		 *	@brief Constructor based on parameters.
		 */
		LG_Matrix3D(float fX0, float fY0, float fZ0,
			float fX1, float fY1, float fZ1,
			float fX2, float fY2, float fZ2);

		///************************************************************************/
		///*						Arithmetic Operators.				           */
		///************************************************************************/

	   /**
		*	@brief This is an operator that uses + between 2 matrices.
		*	@param const LG_Matrix3D& M: The matrix to add.
		*	@return the result of the addition.
		*/
		LG_Matrix3D operator+(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator that uses - between 2 matrices.
		 *	@param const LG_Matrix3D& M: The matrix to substract.
		 *	@return the result of the substraction.
		 */
		LG_Matrix3D operator-(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator that uses * between 2 matrices.
		 *	@param const LG_Matrix3D& M: The matrix to multiply.
		 *	@return the result of the multiplication.
		 */
		LG_Matrix3D operator*(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator that uses * between a matrix and a float.
		 *	@param float value: The value to multiply the matrix.
		 *	@return the result of the multiplication.
		 */
		LG_Matrix3D operator*(float Value);

		/**
		 *	@brief This is an operator that uses / between a matrix and a float.
		 *	@param float value: The value to divide the matrix by.
		 *	@return the result of the division.
		 */
		LG_Matrix3D operator/(float Value);

		/**
		 *	@brief This is an operator that uses * between a matrix and a 3D vector.
		 *	@param const LG_Vector3D V: The vector that will multiply the matrix.
		 *	@return the result of the multiplication.
		 */
		LG_Matrix3D operator*(const LG_Vector3D& V);

		/**
		 *	@brief This is an operator that uses *= between a matrix and a 3D vector.
		 *	@param const LG_Vector3D V: The vector that will multiply the matrix.
		 *	@return the result of the multiplication.
		 */
		LG_Matrix3D operator*=(const LG_Vector3D& V);

		/**
		 *	@brief This is an operator that uses += between 2 matrices.
		 *	@param const LG_Matrix3D M: The matrix that will be added.
		 *	@return the result of the addition.
		 */
		LG_Matrix3D& operator+=(const LG_Matrix3D& M);
		
		/**
		 *	@brief This is an operator that uses -= between 2 matrices.
		 *	@param const LG_Matrix3D M: The matrix that will be substracted.
		 *	@return the result of the substraction.
		 */
		LG_Matrix3D& operator-=(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator that uses *= between 2 matrices.
		 *	@param const LG_Matrix3D M: The matrix that will be multiplied.
		 *	@return the result of the multiplication.
		 */
		LG_Matrix3D& operator*=(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator that uses == between 2 matrices.
		 *	@param LG_Matrix3D M: The matrix that will be compared.
		 *	@return true if both matrices are the same.
		 */
		bool operator==(LG_Matrix3D M);

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/
		
		/**
		 *	@brief Used to equalize a matrix to 0.
		 *	@return A new matrix with all it's components assigned to 0.
		 */
		static LG_Matrix3D Zero();

		/**
		 *	@brief Used to equalize a matrix to it's identity.
		 *	@return A new identity matrix.
		 */
		static LG_Matrix3D Identity();

		/**
		 *	@brief Rotates a matrix on the X axis.
		 *	@param float fValue: The angle to rotate the matrix.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix3D RotateX(float fValue);

		/**
		 *	@brief Rotates a matrix on the Y axis.
		 *	@param float fValue: The angle to rotate the matrix.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix3D RotateY(float fValue);

		/**
		 *	@brief Rotates a matrix on the Z axis.
		 *	@param float fValue: The angle to rotate the matrix.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix3D RotateZ(float fValue);

		/**
		 *	@brief Rotates a matrix on all of the axis.
		 *	@param float fValue: The angle to rotate each axis of the matrix.
		 *	@return The rotated matrix.
		 */
		static LG_Matrix3D Rotate(float fValue);

		/**
		 *	@brief Transposes a matrix.
		 *	@param const LG_Matrix3D A: The matrix to be transposed.
		 *	@return The transposed matrix.
		 */
		LG_Matrix3D Transpose(const LG_Matrix3D& A);

		/**
		 *	@brief Calculates the adjunct of a given matrix.
		 *	@param LG_Matrix3D M: The matrix to be adjuncted.
		 *	@return The adjuncted matrix.
		 */
		LG_Matrix3D Adjunct(LG_Matrix3D M);

		/**
		 *	@brief Calculates the inverse of the matrix.
		 */
		void Inverse(); 

		/**
		 *	@brief Calculates the determinant of a given matrix.
		 *	@param LG_Matrix3D M: The matrix used for the determinant.
		 *	@param int iCol: The column that will be ignored.
		 *	@param int iRow: The row that will be ignored.
		 *	@return The value for the place given of the matrix.
		 */
		float Determinant(LG_Matrix3D M, int iCol, int iRow);
		
		/**
		 *	@brief Translades a matrix in a 3D space.
		 *	@param const LG_Vector3D V: The position where we want to move the matrix.
		 *	@return The translated matrix.
		 */
		LG_Matrix3D Translation(const LG_Vector3D& V);

		/**
		 *	@brief Scales a matrix.
		 *	@param LG_Vector3D V: The scale that we want for the matrix.
		 *	@return The sclaed matrix.
		 */
		LG_Matrix3D Scaling(const LG_Vector3D& V);	
	};
}

