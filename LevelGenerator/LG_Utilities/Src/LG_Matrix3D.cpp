#include "LG_Matrix3D.h"



namespace LevelGenerator
{
	/************************************************************************/
	/* Constructor Default													*/
	/************************************************************************/
	LG_Matrix3D::LG_Matrix3D()
	{

	}

	/************************************************************************/
	/* Constructor con Parametros											*/
	/************************************************************************/
	LG_Matrix3D::LG_Matrix3D(float fX0, float fY0, float fZ0,
		float fX1, float fY1, float fZ1,
		float fX2, float fY2, float fZ2)
	{
		m.X0 = fX0, m.Y0 = fY0, m.Z0 = fZ0;
		m.X1 = fX1, m.Y1 = fY1, m.Z1 = fZ1;
		m.X2 = fX2, m.Y2 = fY2, m.Z2 = fZ2;
	}

	LG_Matrix3D::~LG_Matrix3D()
	{
	}

	/************************************************************************/
	/* Operador Suma														*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator+(const LG_Matrix3D& M)
	{
		return LG_Matrix3D(m.X0 + M.m.X0, m.Y0 + M.m.Y0, m.Z0 + M.m.Z0,
			m.X1 + M.m.X1, m.Y1 + M.m.Y1, m.Z1 + M.m.Z1,
			m.X2 + M.m.X2, m.Y2 + M.m.Y2, m.Z2 + M.m.Z2);
	}

	/************************************************************************/
	/* Operador Resta														*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator-(const LG_Matrix3D& M)
	{
		return LG_Matrix3D(m.X0 - M.m.X0, m.Y0 - M.m.Y0, m.Z0 - M.m.Z0,
			m.X1 - M.m.X1, m.Y1 - M.m.Y1, m.Z1 - M.m.Z1,
			m.X2 - M.m.X2, m.Y2 - M.m.Y2, m.Z2 - M.m.Z2);
	}

	/************************************************************************/
	/* Operador Multiplicación												*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator*(const LG_Matrix3D & M)
	{
		int i, j, k;
		///inicializamos en 0 la matriz.
		LG_Matrix3D R = Zero();

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				for (k = 0; k < 3; k++)
				{
					R.LikeMatrix[i][j] += LikeMatrix[j][k] * M.LikeMatrix[k][i];
				}
			}
		}

		return R;
	}

	/************************************************************************/
	/* Operador Division													*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator/(const LG_Matrix3D & M)
	{
		return LG_Matrix3D(m.X0 / M.m.X0, m.Y0 / M.m.X1, m.Z0 / M.m.X2,
			m.X1 / M.m.Y0, m.Y1 / M.m.Y1, m.Z1 / M.m.Y2,
			m.X2 / M.m.Z0, m.Y2 / M.m.Z1, m.Z2 / M.m.Z2);
	}

	/************************************************************************/
	/* Operador Multiplicación por un Escalar								*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator*(float fValue)
	{
		return LG_Matrix3D(m.X0 * fValue, m.Y0 * fValue, m.Z0 * fValue,
			m.X1 * fValue, m.Y1 * fValue, m.Z1 * fValue,
			m.X2 * fValue, m.Y2 * fValue, m.Z2 * fValue);
	}
	LG_Matrix3D LG_Matrix3D::operator/(float fValue)
	{
		if (fValue != 0)
		{
			return LG_Matrix3D(m.X0 / fValue, m.Y0 / fValue, m.Z0 / fValue,
				m.X1 / fValue, m.Y1 / fValue, m.Z1 / fValue,
				m.X2 / fValue, m.Y2 / fValue, m.Z2 / fValue);
		}
		return Identity();
	}
	/************************************************************************/
	/* Multiplicacion de Matriz por Vector                                  */
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::operator*(const LG_Vector3D & V)
	{
		LG_Matrix3D R = Zero();

		R.m.X0 = m.X0 * V.X + m.X0 * V.Y + m.X0 * V.Z;
		R.m.Y0 =  m.Y0 * V.X +  m.Y0 * V.Y +  m.Y0 * V.Z;
		R.m.Z0 = m.Z0 * V.X + m.Z0 * V.Y + m.Z0 * V.Z;
							    
		R.m.X1 = m.X1 * V.X + m.X1 * V.Y + m.X1 * V.Z;
		R.m.Y1 = m.Y1 * V.X + m.Y1 * V.Y + m.Y1 * V.Z;
		R.m.Z1 = m.Z1 * V.X + m.Z1 * V.Y + m.Z1 * V.Z;
							    
		R.m.X2 = m.X2 * V.X + m.X2 * V.Y + m.X2 * V.Z;
		R.m.Y2 = m.Y2 * V.X + m.Y2 * V.Y + m.Y2 * V.Z;
		R.m.Z2 = m.Z2 * V.X + m.Z2 * V.Y + m.Z2 * V.Z;

		return R;
	}

	LG_Matrix3D LG_Matrix3D::operator/(const LG_Vector3D & V)
	{
		//TODO Hacer funcion 
		return Identity();
	}

	LG_Matrix3D LG_Matrix3D::operator*=(const LG_Vector3D & V)
	{
		return *this = *this * V;
	}
	/************************************************************************/
	/* Operador Mas igual de matiz											*/
	/************************************************************************/
	LG_Matrix3D& LG_Matrix3D::operator+=(const LG_Matrix3D & M)
	{
		return *this = *this + M;
	}
	/************************************************************************/
	/* Operador menos igual de matriz										*/
	/************************************************************************/
	LG_Matrix3D& LG_Matrix3D::operator-=(const LG_Matrix3D & M)
	{
		return *this = *this - M;
	}
	/************************************************************************/
	/* Operador por igual de matriz											*/
	/************************************************************************/
	LG_Matrix3D& LG_Matrix3D::operator*=(const LG_Matrix3D& M)
	{
		return *this = *this * M;
	}
	/************************************************************************/
	/* Operador entre igual de matriz                                       */
	/************************************************************************/
	LG_Matrix3D& LG_Matrix3D::operator/=(const LG_Matrix3D & M)
	{
		return *this = *this / M;
	}

	bool LG_Matrix3D::operator==(LG_Matrix3D M)
	{
		///contador que nos indica si coincidieron todas las casillas.
		int count = 0;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (LikeMatrix[i][j] == M.LikeMatrix[i][j])
				{
					count++;
				}
			}
		}

		return (count == 9);
	}
	/************************************************************************/
	/* Matriz Inicializada en 0                                             */
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::Zero()
	{
		LG_Matrix3D mZero;
		for (int i = 0; i < 9; i++)
			mZero.LikeArray[i] = 0;
		return mZero;
	}
	/************************************************************************/
	/* Matriz identidad														*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::Identity()
	{
		LG_Matrix3D identity;
		identity = Zero();
		identity.m.X0 = 1;
		identity.m.Y1 = 1;
		identity.m.Z2 = 1;
		return identity;
	}
	/************************************************************************/
	/* Transpuesta de una matriz											*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::Transpose(const LG_Matrix3D & A)
	{
		LG_Matrix3D MatTemp;
		MatTemp = Zero();
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				MatTemp.LikeMatrix[j][i] = A.LikeMatrix[i][j];
		return MatTemp;
	}

	LG_Matrix3D LG_Matrix3D::RotateX(float fValue)
	{
		LG_Matrix3D M;
		M = Identity();
		M.m.Y1 = LG_Math::Cos(fValue);
		M.m.Z1 = -LG_Math::Sin(fValue);
		M.m.Y2 = LG_Math::Sin(fValue);
		M.m.Z2 = LG_Math::Cos(fValue);
		return M;
	}

	LG_Matrix3D LG_Matrix3D::RotateY(float fValue)
	{
		LG_Matrix3D M;
		M = Identity();
		M.m.X0 = LG_Math::Cos(fValue);
		M.m.Z0 = LG_Math::Sin(fValue);
		M.m.X2 = -LG_Math::Sin(fValue);
		M.m.Z2 = LG_Math::Cos(fValue);
		return M;
	}

	LG_Matrix3D LG_Matrix3D::RotateZ(float fValue)
	{
		LG_Matrix3D M;
		M = Identity();
		M.m.X0 = LG_Math::Cos(fValue);
		M.m.Y0 = -LG_Math::Sin(fValue);
		M.m.X1 = LG_Math::Sin(fValue);
		M.m.Y1 = LG_Math::Cos(fValue);
		return M;
	}


	LG_Matrix3D LG_Matrix3D::Rotate(float fValue)
	{
		return (RotateX(fValue) * RotateY(fValue) * RotateZ(fValue));
	}

	/************************************************************************/
	/* Matriz de translacion												*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::Translation(const LG_Vector3D & V)
	{
		return LG_Matrix3D(1, 0, 0,
			0, 1, 0,
			V.X, V.Y, V.Z);
	}
	/************************************************************************/
	/* Matriz de escalacion													*/
	/************************************************************************/
	LG_Matrix3D LG_Matrix3D::Scaling(const LG_Vector3D & V)
	{
		return LG_Matrix3D(V.X, 0, 0,
			0, V.Y, 0,
			0, 0, V.Z);
	}
	
	void LG_Matrix3D::Inverse()
	{
		float determinante = 0;
		LG_Matrix3D TransposedMatrix;
		LG_Matrix3D AdjunctedMatrix;

		/// Calculate the determinante.
		determinante =
			(LikeMatrix[0][0] * LikeMatrix[1][1] * LikeMatrix[2][2]) +
			(LikeMatrix[0][2] * LikeMatrix[1][0] * LikeMatrix[2][1]) +
			(LikeMatrix[2][0] * LikeMatrix[0][1] * LikeMatrix[1][2]) -
			(LikeMatrix[2][0] * LikeMatrix[1][1] * LikeMatrix[0][2]) -
			(LikeMatrix[0][0] * LikeMatrix[1][2] * LikeMatrix[2][1]) -
			(LikeMatrix[2][2] * LikeMatrix[0][1] * LikeMatrix[1][0]);

		/// Check if we can draw the inverse.
		if (determinante != 0)
		{

			/// Calculated the transpose.
			TransposedMatrix = Transpose(*this);
			///We calculated the enclosed matrix once it was transposed.
			AdjunctedMatrix = Adjunct(TransposedMatrix);

			*this = AdjunctedMatrix / determinante;
		}
	}

	//! 
	LG_Matrix3D LG_Matrix3D::Adjunct(LG_Matrix3D M)
	{
		LG_Matrix3D adjunct;
		/// Initialize the matrix adjunct like 0.
		adjunct = Zero();

		///We calculate each place of the adjunct.
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				adjunct.LikeMatrix[i][j] = Determinant(M, i, j);

		///return the adjunct matrix.
		return adjunct;
	}

	//! 
	float LG_Matrix3D::Determinant(LG_Matrix3D M, int iCol, int iRow)
	{

		float fValues[4];
		///contador para llenar fValues
		int iCount = 0;
		///
		float fDeterminant = 0;

		///guardamos los valores que no están en la columna ni en la fila dada.	
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
			{
				if (i != iCol && j != iRow)
				{
					fValues[iCount] = M.LikeMatrix[i][j];
					iCount++;
				}
			}

		///Calculamos la adjunta del lugar dado.
		float fElevated = LG_Math::Pow(-1, ((iCol + 1) + (iRow + 1)));
		return fElevated * (fValues[0] * fValues[3] - fValues[1] * fValues[2]);
	}


}