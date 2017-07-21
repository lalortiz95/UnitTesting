#include "LG_Matrix4D.h"

namespace LevelGenerator
{
	/************************************************************************/
	/* Constructor Default													*/
	/************************************************************************/
	LG_Matrix4D::LG_Matrix4D()
	{
		m.X0 = 0, m.Y0 = 0, m.Z0 = 0, m.W0 = 0;
		m.X1 = 0, m.Y1 = 0, m.Z1 = 0, m.W1 = 0;
		m.X2 = 0, m.Y2 = 0, m.Z2 = 0, m.W2 = 0;
		m.X3 = 0, m.Y3 = 0, m.Z3 = 0, m.W3 = 0;
	}

	/************************************************************************/
	/* Constructor con Parametros											*/
	/************************************************************************/
	LG_Matrix4D::LG_Matrix4D(float fX0, float fY0, float fZ0, float fW0,
		float fX1, float fY1, float fZ1, float fW1,
		float fX2, float fY2, float fZ2, float fW2,
		float fX3, float fY3, float fZ3, float fW3)
	{
		m.X0 = fX0, m.Y0 = fY0, m.Z0 = fZ0, m.W0 = fW0;
		m.X1 = fX1, m.Y1 = fY1, m.Z1 = fZ1, m.W1 = fW1;
		m.X2 = fX2, m.Y2 = fY2, m.Z2 = fZ2, m.W2 = fW2;
		m.X3 = fX3, m.Y3 = fY3, m.Z3 = fZ3, m.W3 = fW3;
	}

	LG_Matrix4D::~LG_Matrix4D()
	{
	}

	/************************************************************************/
	/* Operador Suma														*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::operator+(const LG_Matrix4D& M)
	{
		return LG_Matrix4D(	m.X0 + M.m.X0, m.Y0 + M.m.Y0, m.Z0 + M.m.Z0, m.W0 + M.m.W0,
							m.X1 + M.m.X1, m.Y1 + M.m.Y1, m.Z1 + M.m.Z1, m.W1 + M.m.W1,
							m.X2 + M.m.X2, m.Y2 + M.m.Y2, m.Z2 + M.m.Z2, m.W2 + M.m.W2,
							m.X3 + M.m.X3, m.Y3 + M.m.Y3, m.Z3 + M.m.Z3, m.W3 + M.m.W3);
	}

	/************************************************************************/
	/* Operador Resta														*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::operator-(const LG_Matrix4D& M)
	{
		return LG_Matrix4D(m.X0 - M.m.X0, m.Y0 - M.m.Y0, m.Z0 - M.m.Z0, m.W0 - M.m.W0,
			m.X1 - M.m.X1, m.Y1 - M.m.Y1, m.Z1 - M.m.Z1, m.W1 - M.m.W1,
			m.X2 - M.m.X2, m.Y2 - M.m.Y2, m.Z2 - M.m.Z2, m.W2 - M.m.W2,
			m.X3 - M.m.X3, m.Y3 - M.m.Y3, m.Z3 - M.m.Z3, m.W3 - M.m.W3);
	}

	/************************************************************************/
	/* Operador Multiplicación												*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::operator*(const LG_Matrix4D & M)
	{
		return LG_Matrix4D(m.X0 * M.m.X0, m.Y0 * M.m.X1, m.Z0 * M.m.X2, m.W0 * M.m.X3,
			m.X1 * M.m.Y0, m.Y1 * M.m.Y1, m.Z1 * M.m.Y2, m.W1 * M.m.Y3,
			m.X2 * M.m.Z0, m.Y2 * M.m.Z1, m.Z2 * M.m.Z2, m.W2 * M.m.Z3,
			m.X3 * M.m.W0, m.Y3 * M.m.W1, m.Z3 * M.m.W2, m.W3 * M.m.W3);
	}

	/************************************************************************/
	/* Operador Division													*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::operator/(const LG_Matrix4D & M)
	{
		return LG_Matrix4D(m.X0 / M.m.X0, m.Y0 / M.m.X1, m.Z0 / M.m.X2, m.W0 / M.m.X3,
			m.X1 / M.m.Y0, m.Y1 / M.m.Y1, m.Z1 / M.m.Y2, m.W1 / M.m.Y3,
			m.X2 / M.m.Z0, m.Y2 / M.m.Z1, m.Z2 / M.m.Z2, m.W2 / M.m.Z3,
			m.X3 / M.m.W0, m.Y3 / M.m.W1, m.Z3 / M.m.W2, m.W3 / M.m.W3);
	}

	/************************************************************************/
	/* Operador Multiplicación por un Escalar								*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::operator*(float Value)
	{
		return LG_Matrix4D(m.X0 * Value, m.Y0 * Value, m.Z0 * Value, m.W0 * Value,
			m.X1 * Value, m.Y1 * Value, m.Z1 * Value, m.W1 * Value,
			m.X2 * Value, m.Y2 * Value, m.Z2 * Value, m.W2 * Value,
			m.X3 * Value, m.Y3 * Value, m.Z3 * Value, m.W3 * Value);
	}

	//! Operador para multiplicar la matriz por un vector.
	LG_Vector4D LG_Matrix4D::operator*(const LG_Vector4D& V)
	{
		return LG_Vector4D((m.X0 * V.X + m.Y0 * V.X + m.Z0 * V.X + m.W0 * V.W),
			(m.X1 * V.Y + m.Y1 * V.Y + m.Z1 * V.Y + m.W1 * V.W),
			(m.X2 * V.Z + m.Y2 * V.Z + m.Z2 * V.Z + m.W2 * V.W),
			(m.X3 * V.Z + m.Y3 * V.Z + m.Z3 * V.Z + m.W3 * V.W));
	}

	//! Operador para dividir una matriz por un vector.
	LG_Vector4D LG_Matrix4D::operator/(const LG_Vector4D& V)
	{
		return LG_Vector4D((m.X0 / V.X + m.Y0 / V.X + m.Z0 / V.X + m.W0 / V.W),
			(m.X1 / V.Y + m.Y1 / V.Y + m.Z1 / V.Y + m.W1 / V.W),
			(m.X2 / V.Z + m.Y2 / V.Z + m.Z2 / V.Z + m.W2 / V.W),
			(m.X3 / V.Z + m.Y3 / V.Z + m.Z3 / V.Z + m.W3 / V.W));
	}
	/************************************************************************/
	/* Operador Mas igual de matiz											*/
	/************************************************************************/
	LG_Matrix4D& LG_Matrix4D::operator+=(const LG_Matrix4D & M)
	{
		m.X0 += M.m.X0; m.Y0 += M.m.Y0; m.Z0 += M.m.Z0; m.W0 += M.m.W0;
		m.X1 += M.m.X1; m.Y1 += M.m.Y1; m.Z1 += M.m.Z1; m.W1 += M.m.W1;
		m.X2 += M.m.X2; m.Y2 += M.m.Y2; m.Z2 += M.m.Z2; m.W2 += M.m.W2;
		m.X3 += M.m.X3; m.Y3 += M.m.Y3; m.Z3 += M.m.Z3; m.W3 += M.m.W3;
		return *this;
	}
	/************************************************************************/
	/* Operador menos igual de matriz										*/
	/************************************************************************/
	LG_Matrix4D& LG_Matrix4D::operator-=(const LG_Matrix4D & M)
	{
		m.X0 -= M.m.X0; m.Y0 -= M.m.Y0; m.Z0 -= M.m.Z0; m.W0 -= M.m.W0;
		m.X1 -= M.m.X1; m.Y1 -= M.m.Y1; m.Z1 -= M.m.Z1; m.W1 -= M.m.W1;
		m.X2 -= M.m.X2; m.Y2 -= M.m.Y2; m.Z2 -= M.m.Z2; m.W2 -= M.m.W2;
		m.X3 -= M.m.X3; m.Y3 -= M.m.Y3; m.Z3 -= M.m.Z3; m.W3 -= M.m.W3;
		return *this;
	}
	/************************************************************************/
	/* Operador por igual de matriz											*/
	/************************************************************************/
	LG_Matrix4D& LG_Matrix4D::operator*=(const LG_Matrix4D& M)
	{
		m.X0 *= M.m.X0; m.Y0 *= M.m.Y0; m.Z0 *= M.m.Z0; m.W0 *= M.m.W0;
		m.X1 *= M.m.X1; m.Y1 *= M.m.Y1; m.Z1 *= M.m.Z1; m.W1 *= M.m.W1;
		m.X2 *= M.m.X2; m.Y2 *= M.m.Y2; m.Z2 *= M.m.Z2; m.W2 *= M.m.W2;
		m.X3 *= M.m.X3; m.Y3 *= M.m.Y3; m.Z3 *= M.m.Z3; m.W3 *= M.m.W3;
		return *this;
	}
	/************************************************************************/
	/* Operador entre igual de matriz                                       */
	/************************************************************************/
	LG_Matrix4D& LG_Matrix4D::operator/=(const LG_Matrix4D & M)
	{
		m.X0 /= M.m.X0; m.Y0 /= M.m.Y0; m.Z0 /= M.m.Z0; m.W0 /= M.m.W0;
		m.X1 /= M.m.X1; m.Y1 /= M.m.Y1; m.Z1 /= M.m.Z1; m.W1 /= M.m.W1;
		m.X2 /= M.m.X2; m.Y2 /= M.m.Y2; m.Z2 /= M.m.Z2; m.W2 /= M.m.W2;
		m.X3 /= M.m.X3; m.Y3 /= M.m.Y3; m.Z3 /= M.m.Z3; m.W3 /= M.m.W3;
		return *this;
	}
	/************************************************************************/
	/* Matriz Inicializada en 0                                             */
	/************************************************************************/
	void LG_Matrix4D::Zero(void)
	{
		for (int i = 0; i < 16; i++)
			this->LikeArray[i] = 0;
	}
	/************************************************************************/
	/* Matriz identidad														*/
	/************************************************************************/
	void LG_Matrix4D::Identity(void)
	{
		this->Zero();
		this->m.X0 = 1;
		this->m.Y1 = 1;
		this->m.Z2 = 1;
		this->m.W3 = 1;
	}
	/************************************************************************/
	/* Transpuesta de una matriz											*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::Transpose()
	{
		LG_Matrix4D MatTemp;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				MatTemp.LikeMatrix[j][i] = this->LikeMatrix[i][j];

		return MatTemp;
	}
	/************************************************************************/
	/*  Inversa de una matriz												*/
	/************************************************************************/
	LG_Matrix4D LG_Matrix4D::Inverse(const LG_Matrix4D & A)
	{
		//TODO: Implementar la inversa.
		return LG_Matrix4D();
	}

	void LG_Matrix4D::PerspectiveFOVLH(float zNear, float zFar, float FOV, float AspectRatio)
	{
		float yScale = 1.0f / LG_Math::Tan(FOV * 0.5f);
		float xScale = yScale / AspectRatio;

		this->m.X0 = xScale, this->m.Y0 = 0, this->m.Z0 = 0, this->m.W0 = 0;
		this->m.X1 = 0, this->m.Y1 = yScale, this->m.Z1 = 0, this->m.W1 = 0;
		this->m.X2 = 0, this->m.Y2 = 0, this->m.Z2 = zFar*zNear / (zFar - zNear), this->m.W2 = 1;
		this->m.X3 = 0, this->m.Y3 = 0, this->m.Z3 = -zNear*zFar / (zFar - zNear), this->m.W3 = 0;


	}

	void LG_Matrix4D::LookAtLeftH(const LG_Vector4D EyePos, const LG_Vector4D Target, const LG_Vector4D Up)
	{
		LG_Vector4D xDir, yDir, zDir;

		zDir = Target - EyePos;
		zDir = zDir.Normalize(zDir);

		xDir = xDir.Cross(Up, zDir);
		xDir = xDir.Normalize(xDir);

		yDir = zDir.Cross(zDir, xDir);
		yDir = yDir.Normalize(yDir);

		this->m.X0 = xDir.X, this->m.Y0 = yDir.X, this->m.Z0 = zDir.X, this->m.W0 = 0;
		this->m.X1 = xDir.Y, this->m.Y1 = yDir.Y, this->m.Z1 = zDir.Y, this->m.W1 = 0;
		this->m.X2 = xDir.Z, this->m.Y2 = yDir.Z, this->m.Z2 = zDir.Z, this->m.W2 = 0;
		this->m.X3 = -xDir.Dot(EyePos), this->m.Y3 = -yDir.Dot(EyePos), this->m.Z3 = -zDir.Dot(EyePos), this->m.W3 = 1;

	}

	/************************************************************************/
	/* Matriz de translacion												*/
	/************************************************************************/
	void LG_Matrix4D::Translation(const LG_Vector4D & V)
	{
		this->m.X0 = 1,   this->m.Y0 = 0,	this->m.Z0 = 0,   this->m.W0 = 0;
		this->m.X1 = 0,   this->m.Y1 = 1,	this->m.Z1 = 0,	  this->m.W1 = 0;
		this->m.X2 = 0,	  this->m.Y2 = 0,	this->m.Z2 = 1,	  this->m.W2 = 0;
		this->m.X3 = V.X, this->m.Y3 = V.Y, this->m.Z3 = V.Z, this->m.W3 = V.W;
	}
	/************************************************************************/
	/* Matriz de escalacion													*/
	/************************************************************************/
	void LG_Matrix4D::Scaling(const LG_Vector4D & V)
	{
		this->m.X0 = V.X, this->m.Y0 = 0,	this->m.Z0 = 0,		this->m.W0 = 0;
		this->m.X1 = 0,	  this->m.Y1 = V.Y, this->m.Z1 = 0,		this->m.W1 = 0;
		this->m.X2 = 0,	  this->m.Y2 = 0,	this->m.Z2 = V.Z,	this->m.W2 = 0;
		this->m.X3 = 0,   this->m.Y3 = 0,	this->m.Z3 = 0,		this->m.W3 = V.W;

	}
	/************************************************************************/
	/* Matriz de rotacion													*/
	/************************************************************************/
	void LG_Matrix4D::Rotate(const LG_Vector4D & V)
	{
		RotateX(V.X);
		RotateY(V.Y);
		RotateZ(V.Z);
	}

	//! Funcion para rotar en X.
	void LG_Matrix4D::RotateX(float fValue)
	{
		this->m.X0 = 1, this->m.Y0 = 0,						this->m.Z0 = 0,						this->m.W0 = 0;
		this->m.X1 = 0, this->m.Y1 =  LG_Math::Cos(fValue), this->m.Z1 = LG_Math::Sin(fValue),	this->m.W1 = 0;
		this->m.X2 = 0, this->m.Y2 = -LG_Math::Sin(fValue), this->m.Z2 = LG_Math::Cos(fValue),	this->m.W2 = 0;
		this->m.X3 = 0, this->m.Y3 = 0,                     this->m.Z3 = 0,						this->m.W3 = 1;
	}

	//! Funcion para rotar en Y.
	void LG_Matrix4D::RotateY(float fValue)
	{
		this->m.X0 = LG_Math::Cos(fValue),	this->m.Y0 = 0, this->m.Z0 = -LG_Math::Sin(fValue), this->m.W0 = 0;
		this->m.X1 = 0,						this->m.Y1 = 1, this->m.Z1 = 0,						this->m.W1 = 0;
		this->m.X2 = LG_Math::Sin(fValue),	this->m.Y2 = 0, this->m.Z2 = LG_Math::Cos(fValue),	this->m.W2 = 0;
		this->m.X3 = 0,						this->m.Y3 = 0, this->m.Z3 = 0,						this->m.W3 = 1;
	}

	//! Funcion para rotar en Z.
	void LG_Matrix4D::RotateZ(float fValue)
	{
		this->m.X0 =  LG_Math::Cos(fValue), this->m.Y0 = LG_Math::Sin(fValue),	this->m.Z0 = 0, this->m.W0 = 0;
		this->m.X1 = -LG_Math::Sin(fValue),	this->m.Y1 = LG_Math::Cos(fValue),	this->m.Z1 = 0, this->m.W1 = 0;
		this->m.X2 = 0,						this->m.Y2 = 0,						this->m.Z2 = 1, this->m.W2 = 0;
		this->m.X3 = 0,						this->m.Y3 = 0,						this->m.Z3 = 0, this->m.W3 = 1;
	}

}