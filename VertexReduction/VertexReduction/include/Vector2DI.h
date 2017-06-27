#pragma once
#include <cmath>

namespace LevelGenerator
{
	class CVector2DI
	{
	public:

		/************************************************************************/
		/*                          Member Variables.							*/
		/************************************************************************/

		//! X Position.
		int X;
		//! Y Position.
		int Y;

		/************************************************************************/
		/*                   Constructors & Destructors.						*/
		/************************************************************************/

		//! Default Constructor.
		CVector2DI();
		//! Parameter Constructor.
		CVector2DI(int iX, int iY);
		//! Default Destructor.
		~CVector2DI();

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		CVector2DI operator+(const CVector2DI& V) const;		//Suma
		CVector2DI operator-(const CVector2DI& V) const;		//Resta
		CVector2DI operator*(int Scale) const;				//Multiplicación (escalar)
		CVector2DI operator*(const CVector2DI& V) const;		//Multiplicación (vector)
		CVector2DI operator/(int Scale) const;							//División (escalar)
		CVector2DI operator/(const CVector2DI& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector2DI& V) const;						//Igual a
		bool operator!=(const CVector2DI& V) const;						//Diferente a
		bool operator<(const CVector2DI& Other) const;					//Menor que
		bool operator>(const CVector2DI& Other) const;					//Mayor que
		bool operator<=(const CVector2DI& Other) const;					//Menor o igual a
		bool operator>=(const CVector2DI& Other) const;					//Mayor o igual a
		bool Equals(const CVector2DI& V, int Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		CVector2DI operator+=(const CVector2DI& V);
		CVector2DI operator-=(const CVector2DI& V);
		CVector2DI operator*=(int Scale);
		CVector2DI operator/=(int Scale);
		CVector2DI operator*=(const CVector2DI& V);
		CVector2DI operator/=(const CVector2DI& V);

		int operator|(const CVector2DI& V) const;			//Dot Product
		int operator^(const CVector2DI& V) const;			//Cross Product

		int Magnitud(const CVector2DI& V);
		CVector2DI Normalize(const CVector2DI& V);
		int DotProduct(const CVector2DI& A, const CVector2DI& B);


	};
}
