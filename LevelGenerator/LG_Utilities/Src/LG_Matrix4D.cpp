#include "LG_Matrix4D.h"
#include "LG_Matrix3D.h"

namespace LevelGenerator
{
	//const LG_Matrix4D::ZERO = LG_Matrix4D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	LG_Matrix4D::LG_Matrix4D()
	{
	}

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

	LG_Matrix4D LG_Matrix4D::operator+(const LG_Matrix4D& M)
	{
		return LG_Matrix4D(m.X0 + M.m.X0, m.Y0 + M.m.Y0, m.Z0 + M.m.Z0, m.W0 + M.m.W0,
			m.X1 + M.m.X1, m.Y1 + M.m.Y1, m.Z1 + M.m.Z1, m.W1 + M.m.W1,
			m.X2 + M.m.X2, m.Y2 + M.m.Y2, m.Z2 + M.m.Z2, m.W2 + M.m.W2,
			m.X3 + M.m.X3, m.Y3 + M.m.Y3, m.Z3 + M.m.Z3, m.W3 + M.m.W3);
	}

	LG_Matrix4D LG_Matrix4D::operator-(const LG_Matrix4D& M)
	{
		return LG_Matrix4D(m.X0 - M.m.X0, m.Y0 - M.m.Y0, m.Z0 - M.m.Z0, m.W0 - M.m.W0,
			m.X1 - M.m.X1, m.Y1 - M.m.Y1, m.Z1 - M.m.Z1, m.W1 - M.m.W1,
			m.X2 - M.m.X2, m.Y2 - M.m.Y2, m.Z2 - M.m.Z2, m.W2 - M.m.W2,
			m.X3 - M.m.X3, m.Y3 - M.m.Y3, m.Z3 - M.m.Z3, m.W3 - M.m.W3);
	}

	LG_Matrix4D LG_Matrix4D::operator*(const LG_Matrix4D & M)
	{
		///enteros que se usan para los for.
		int32 i, j, k;
		///inicializamos en 0 la matriz.
		LG_Matrix4D R = Zero();

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				for (k = 0; k < 4; k++)
				{
					R.LikeMatrix[i][j] += LikeMatrix[j][k] * M.LikeMatrix[k][i];
				}
			}
		}

		return R;
	}

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

	LG_Matrix4D LG_Matrix4D::operator/(float fValue)
	{
		LG_Matrix4D R = Zero();

		if (fValue != 0)
		{
			for (int32 i = 0; i < 4; ++i)
			{
				for (int32 j = 0; j < 4; ++j)
				{
					R.LikeMatrix[i][j] = LikeMatrix[i][j] / fValue;
				}
			}
		}

		return R;
	}

	LG_Matrix4D& LG_Matrix4D::operator+=(const LG_Matrix4D & M)
	{
		return *this = *this + M;
	}

	LG_Matrix4D& LG_Matrix4D::operator-=(const LG_Matrix4D & M)
	{
		return *this = *this - M;
	}

	LG_Matrix4D& LG_Matrix4D::operator*=(const LG_Matrix4D& M)
	{
		return *this = *this * M;
	}

	LG_Matrix4D LG_Matrix4D::Zero(void)
	{
		LG_Matrix4D mZero;
		mZero.m.X0 = 0;
		mZero.m.X1 = 0;
		mZero.m.X2 = 0;
		mZero.m.X3 = 0;

		mZero.m.Y0 = 0;
		mZero.m.Y1 = 0;
		mZero.m.Y2 = 0;
		mZero.m.Y3 = 0;

		mZero.m.Z0 = 0;
		mZero.m.Z1 = 0;
		mZero.m.Z2 = 0;
		mZero.m.Z3 = 0;

		mZero.m.W0 = 0;
		mZero.m.W1 = 0;
		mZero.m.W2 = 0;
		mZero.m.W3 = 0;

		return mZero;
	}

	LG_Matrix4D LG_Matrix4D::Identity(void)
	{
		LG_Matrix4D identity;
		identity = Zero();
		identity.m.X0 = 1;
		identity.m.Y1 = 1;
		identity.m.Z2 = 1;
		identity.m.W3 = 1;
		return identity;
	}

	LG_Matrix4D LG_Matrix4D::Transpose()
	{
		LG_Matrix4D MatTemp;
		for (int32 i = 0; i < 4; ++i)
			for (int32 j = 0; j < 4; ++j)
				MatTemp.LikeMatrix[j][i] = this->LikeMatrix[i][j];

		return MatTemp;
	}

	void LG_Matrix4D::Inverse()
	{
		float determinante = 0;
		LG_Matrix4D TransposedMatrix;
		LG_Matrix4D AdjunctedMatrix;

		//TODO: al quitar una columna o una hilera, quedan 4 matrices 3D a las que les
		//Sacamos su determinante.
		/// Calculamos la determinante.
		determinante =
			(LikeMatrix[0][0] * LikeMatrix[1][1] * LikeMatrix[2][2]) + (LikeMatrix[0][2] * LikeMatrix[1][0] * LikeMatrix[2][1]) +
			(LikeMatrix[2][0] * LikeMatrix[0][1] * LikeMatrix[1][2]) - (LikeMatrix[2][0] * LikeMatrix[1][1] * LikeMatrix[0][2]) -
			(LikeMatrix[0][0] * LikeMatrix[1][2] * LikeMatrix[2][1]) - (LikeMatrix[2][2] * LikeMatrix[0][1] * LikeMatrix[1][0]);

		/// Revisamos que se pueda sacar su inversa.
		if (determinante != 0)
		{
			///Es posible
			/// Calculamos la transpuesta.
			TransposedMatrix = Transpose();
			///Calculamos la adjunta de la matriz una vez que ya fue transpuessta.
			AdjunctedMatrix = GetAdjunct(TransposedMatrix);

			*this = AdjunctedMatrix / determinante;
		}
	}

	//! Calculates the inverse of the matrix.
	void LG_Matrix4D::GaussJordan(LG_Vector4D& Position)
	{
		/////
		//float x, y;
		///// counters used in the fors.
		//int32 i, ii, j;
		//float fdividendo;
		///// iterates through the matrix.
		//for (i = 0; i < 4; i++)
		//{
		//	for (ii = 0; ii < 4; ii++)
		//	{
		//		/// see that it's not in the same row and column
		//		if (ii != i)
		//		{
		//			/// values to calculate the output.
		//			x = -LikeMatrix[i][i];
		//			y = LikeMatrix[ii][i];
		//			for (j = 0; j < 4 + 1; j++)
		//			{
		//				fdividendo = y * x + LikeMatrix[i][j];
		//				if (fdividendo > 0)
		//				{
		//					/// fills the matrix.
		//					LikeMatrix[ii][j] = LikeMatrix[ii][j] / fdividendo;
		//				}
		//			}
		//		}
		//	}
		//}

		float fAux, fPivote;
		for (int32 i = 0; i < 3; ++i)
		{
			if (LikeMatrix[i][i] != 0)
			{
				///
				fPivote = 1 / LikeMatrix[i][i];

				for (int32 j = 0; j < 4; ++j)
				{
					/// 
					//if (fPivote != 0.0)
					//{
					/// 
					LikeMatrix[i][j] = fPivote * LikeMatrix[i][j];
				}
				for (int32 j = 0; j < 3; ++j)
				{
					///tomamos todas las columnas que no sean la que se itera en i.
					if (j != i)
					{
						/// guardamos en un auxiliar el valor el la iteración.
						fAux = -LikeMatrix[j][i];

						for (int32 k = 0; k < 4; ++k)
						{
							///aquí no entendí que pedo.
							LikeMatrix[j][k] = LikeMatrix[j][k] + (fAux * LikeMatrix[i][k]);
							if (LikeMatrix[j][k] - LG_Math::DELTA <= 0 &&
								LikeMatrix[j][k] + LG_Math::DELTA >= 0)
							{
								LikeMatrix[j][k] = 0;
							}
						}
					}
				}
			}
		}

		///guardamos el resultado final.
		Position.X = LikeMatrix[0][3];
		Position.Y = LikeMatrix[1][3];
		Position.Z = LikeMatrix[2][3];
		Position.W = 0.0f;
	}

	LG_Matrix4D LG_Matrix4D::GetAdjunct(LG_Matrix4D M)
	{
		LG_Matrix4D Adjunct;
		/// Inicializamos en 0 la matriz adjunta.
		Adjunct = Zero();

		///Calculamos cada lugar de la adjunta.
		for (int32 i = 0; i < 4; ++i)
			for (int32 j = 0; j < 4; ++j)
				Adjunct.LikeMatrix[i][j] = GetDeterminant(M, i, j);

		///La regresamos.
		return Adjunct;
	}

	float LG_Matrix4D::GetDeterminant(LG_Matrix4D M, int32 col, int32 row)
	{
		///Los valores que hay en la matriz cuando se ignoran la col y la row dada.
		LG_Matrix3D determinantMatrix;
		float fValues[16];
		///contador para llenar fValues
		int32 iCount = 0;

		///guardamos los valores que no están en la columna ni en la fila dada.	
		for (int32 i = 0; i < 4; ++i)
			for (int32 j = 0; j < 4; ++j)
			{
				if (i != col && j != row)
				{
					//TODO: meter esto a una matriz 3x3, y calcular el determinante
					// de dicha matriz. Con las determinantes que se obtengan de la
					// matriz 3x3, obtener la determinante de esta matriz 4x4.
					fValues[iCount] = M.LikeMatrix[i][j];
					iCount++;
				}
			}

		///Calculamos la adjunta del lugar dado.
		float fElevated = LG_Math::Pow(-1.0f, (((float)col + 1.0f) + ((float)row + 1.0f)));
		//TODO: corregir esto.
		return fElevated * (fValues[0] * fValues[3] - fValues[1] * fValues[2]);
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

	void LG_Matrix4D::Translation(const LG_Vector4D & V)
	{
		this->m.X0 = 1, this->m.Y0 = 0, this->m.Z0 = 0, this->m.W0 = 0;
		this->m.X1 = 0, this->m.Y1 = 1, this->m.Z1 = 0, this->m.W1 = 0;
		this->m.X2 = 0, this->m.Y2 = 0, this->m.Z2 = 1, this->m.W2 = 0;
		this->m.X3 = V.X, this->m.Y3 = V.Y, this->m.Z3 = V.Z, this->m.W3 = V.W;
	}

	void LG_Matrix4D::Scaling(const LG_Vector4D & V)
	{
		this->m.X0 = V.X, this->m.Y0 = 0, this->m.Z0 = 0, this->m.W0 = 0;
		this->m.X1 = 0, this->m.Y1 = V.Y, this->m.Z1 = 0, this->m.W1 = 0;
		this->m.X2 = 0, this->m.Y2 = 0, this->m.Z2 = V.Z, this->m.W2 = 0;
		this->m.X3 = 0, this->m.Y3 = 0, this->m.Z3 = 0, this->m.W3 = V.W;

	}

	LG_Matrix4D LG_Matrix4D::Rotate(const LG_Vector4D & V)
	{
		LG_Matrix4D FinalRotation;
		FinalRotation = RotateX(V.X) * RotateY(V.Y) * RotateZ(V.Z);

		return FinalRotation;
	}

	//!
	LG_Matrix4D LG_Matrix4D::RotateX(float fValue)
	{
		/// The final rotation.
		LG_Matrix4D FR;

		FR.m.X0 = 1, FR.m.Y0 = 0, FR.m.Z0 = 0, FR.m.W0 = 0;
		FR.m.X1 = 0, FR.m.Y1 = LG_Math::Cos(fValue), FR.m.Z1 = LG_Math::Sin(fValue), FR.m.W1 = 0;
		FR.m.X2 = 0, FR.m.Y2 = -LG_Math::Sin(fValue), FR.m.Z2 = LG_Math::Cos(fValue), FR.m.W2 = 0;
		FR.m.X3 = 0, FR.m.Y3 = 0, FR.m.Z3 = 0, FR.m.W3 = 1;

		return FR;
	}

	//!
	LG_Matrix4D LG_Matrix4D::RotateY(float fValue)
	{
		/// The final rotation.
		LG_Matrix4D FR;

		FR.m.X0 = LG_Math::Cos(fValue), FR.m.Y0 = 0, FR.m.Z0 = -LG_Math::Sin(fValue), FR.m.W0 = 0;
		FR.m.X1 = 0, FR.m.Y1 = 1, FR.m.Z1 = 0, FR.m.W1 = 0;
		FR.m.X2 = LG_Math::Sin(fValue), FR.m.Y2 = 0, FR.m.Z2 = LG_Math::Cos(fValue), FR.m.W2 = 0;
		FR.m.X3 = 0, FR.m.Y3 = 0, FR.m.Z3 = 0, FR.m.W3 = 1;

		return FR;
	}

	//! 
	LG_Matrix4D LG_Matrix4D::RotateZ(float fValue)
	{
		/// The final rotation.
		LG_Matrix4D FR;

		FR.m.X0 = LG_Math::Cos(fValue), FR.m.Y0 = LG_Math::Sin(fValue), FR.m.Z0 = 0, FR.m.W0 = 0;
		FR.m.X1 = -LG_Math::Sin(fValue), FR.m.Y1 = LG_Math::Cos(fValue), FR.m.Z1 = 0, FR.m.W1 = 0;
		FR.m.X2 = 0, FR.m.Y2 = 0, FR.m.Z2 = 1, FR.m.W2 = 0;
		FR.m.X3 = 0, FR.m.Y3 = 0, FR.m.Z3 = 0, FR.m.W3 = 1;

		return FR;
	}

}