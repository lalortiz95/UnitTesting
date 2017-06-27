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
		/* Declaraci�n de operadores aritm�ticos                                 												*/
		/************************************************************************************************************************/
		CVector2DI operator+(const CVector2DI& V) const;		//Suma
		CVector2DI operator-(const CVector2DI& V) const;		//Resta
		CVector2DI operator*(int Scale) const;				//Multiplicaci�n (escalar)
		CVector2DI operator*(const CVector2DI& V) const;		//Multiplicaci�n (vector)
		CVector2DI operator/(int Scale) const;							//Divisi�n (escalar)
		CVector2DI operator/(const CVector2DI& V) const;					//Divisi�n (vector)



		/************************************************************************************************************************/
		/* Declaraci�n de operadores l�gicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector2DI& V) const;						//Igual a
		bool operator!=(const CVector2DI& V) const;						//Diferente a
		bool operator<(const CVector2DI& Other) const;					//Menor que
		bool operator>(const CVector2DI& Other) const;					//Mayor que
		bool operator<=(const CVector2DI& Other) const;					//Menor o igual a
		bool operator>=(const CVector2DI& Other) const;					//Mayor o igual a
		bool Equals(const CVector2DI& V, int Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaraci�n de operadores de asignaci�n compuesta                    												*/
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
