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
	class LG_UTILITIES_EXPORT LG_Matrix4D
	{
	public:

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		union
		{
			struct
			{

				float X0, Y0, Z0, W0,
					X1, Y1, Z1, W1,
					X2, Y2, Z2, W2,
					X3, Y3, Z3, W3;
			}m;
			float MatrixLikeArray[16];
			float MatrixLikeMatrix[4][4];
		};
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 LG_Matrix4D();
		 ~LG_Matrix4D();
		 LG_Matrix4D(	float fX0, float fY0, float fZ0, float fW0,
						float fX1, float fY1, float fZ1, float fW1,
						float fX2, float fY2, float fZ2, float fW2,
						float fX3, float fY3, float fZ3, float fW3);


		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 LG_Matrix4D operator+(const LG_Matrix4D& M);
		 LG_Matrix4D operator-(const LG_Matrix4D& M);
		 LG_Matrix4D operator*(const LG_Matrix4D& M);
		 LG_Matrix4D operator/(const LG_Matrix4D& M);
		 LG_Matrix4D operator*(float Value);

		 LG_Vector4D operator*(const LG_Vector4D& V);
		 LG_Vector4D operator/(const LG_Vector4D& V);

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 LG_Matrix4D& operator+=(const LG_Matrix4D& M);
		 LG_Matrix4D& operator-=(const LG_Matrix4D& M);
		 LG_Matrix4D& operator*=(const LG_Matrix4D& M);
		 LG_Matrix4D& operator/=(const LG_Matrix4D& M);

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
		 
		 

		 LG_Matrix4D Transpose();
		 LG_Matrix4D Inverse(const LG_Matrix4D& A); //! Falta la inversa
		 
		 /**
		  *	@brief 
		  */
		 void Identity(void);

		 /**
		  *	@brief 
		  */
		 void Zero(void);

		 /**
		  *	@brief 
		  *	@param float zNear:
		  *	@param float zFar:
		  *	@param float FOV:
		  *	@param AspectRatio:
		  */
		 void PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio);

		 /**
		  *	@brief 
		  *	@param const LG_Vector4D EyePos:
		  *	@param const LG_Vector4D Target:
		  * @param const LG_Vector4D Up:
		  */
		 void LookAtLeftH(const LG_Vector4D EyePos, const LG_Vector4D Target, const LG_Vector4D Up);

		/************************************************************************/
		/*                                                                      */
		/************************************************************************/

		 /**
		  *	@brief 
		  */
		void Translation(const LG_Vector4D& V);

		/**
		 *	@brief 
		 */
		void Scaling(const LG_Vector4D& V);

		/**
		 *	@brief 
		 */
		void Rotate(const LG_Vector4D& V); 

		/**
		 *	@brief 
		 */
		void RotateX(float fvalue);

		/**
		 *	@brief 
		 */
		void RotateY(float fValue);

		/**
		 *	@brief 
		 */
		void RotateZ(float fvalue);

	};
#pragma pop(pack)
}