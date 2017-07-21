#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include "LG_Math.h"
#include "LG_Vector3D.h"

namespace LevelGenerator
{
	class LG_UTILITIES_EXPORT LG_Matrix3D
	{
	public:

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
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
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 LG_Matrix3D();
		 ~LG_Matrix3D();
		 LG_Matrix3D(float fX0, float fY0, float fZ0,
			float fX1, float fY1, float fZ1,
			float fX2, float fY2, float fZ2);
		

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 LG_Matrix3D operator+(const LG_Matrix3D& M);
		 LG_Matrix3D operator-(const LG_Matrix3D& M);
		 LG_Matrix3D operator*(const LG_Matrix3D& M);
		 LG_Matrix3D operator/(const LG_Matrix3D& M);

		 LG_Matrix3D operator*(float Value);
		 LG_Matrix3D operator/(float Value);

		 LG_Matrix3D operator*(const LG_Vector3D& V);
		 LG_Matrix3D operator/(const LG_Vector3D& V);

		 LG_Matrix3D operator*=(const LG_Vector3D& V);

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		LG_Matrix3D& operator+=(const LG_Matrix3D& M);
		LG_Matrix3D& operator-=(const LG_Matrix3D& M);
		LG_Matrix3D& operator*=(const LG_Matrix3D& M);
		LG_Matrix3D& operator/=(const LG_Matrix3D& M);

		bool operator==(LG_Matrix3D M);

		
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		static LG_Matrix3D Zero();
		static LG_Matrix3D Identity();
		static LG_Matrix3D RotateX(float fValue);
		static LG_Matrix3D RotateY(float fValue);
		static LG_Matrix3D RotateZ(float fValue);
		static LG_Matrix3D Rotate(float fValue);

		LG_Matrix3D Transpose(const LG_Matrix3D& A);
		LG_Matrix3D Adjunct(LG_Matrix3D M);

		void Inverse(); 
		float Determinant(LG_Matrix3D M, int iCol, int iRow);
		
		
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		LG_Matrix3D Translation(const LG_Vector3D& V);
		LG_Matrix3D Scaling(const LG_Vector3D& V);
		
	};
}

