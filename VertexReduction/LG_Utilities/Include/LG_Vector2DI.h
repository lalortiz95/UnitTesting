#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include <cmath>

namespace LevelGenerator
{
	class LG_UTILITIES_EXPORT LG_Vector2DI
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
		LG_Vector2DI();
		//! Parameter Constructor.
		LG_Vector2DI(int iX, int iY);
		//! Default Destructor.
		~LG_Vector2DI();

		/************************************************************************************************************************/
		/* Declaraci�n de operadores aritm�ticos                                 												*/
		/************************************************************************************************************************/
		LG_Vector2DI operator+(const LG_Vector2DI& V) const;		//Suma
		LG_Vector2DI operator-(const LG_Vector2DI& V) const;		//Resta
		LG_Vector2DI operator*(int Scale) const;				//Multiplicaci�n (escalar)
		LG_Vector2DI operator*(const LG_Vector2DI& V) const;		//Multiplicaci�n (vector)
		LG_Vector2DI operator/(int Scale) const;							//Divisi�n (escalar)
		LG_Vector2DI operator/(const LG_Vector2DI& V) const;					//Divisi�n (vector)



		/************************************************************************************************************************/
		/* Declaraci�n de operadores l�gicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const LG_Vector2DI& V) const;						//Igual a
		bool operator!=(const LG_Vector2DI& V) const;						//Diferente a
		bool operator<(const LG_Vector2DI& Other) const;					//Menor que
		bool operator>(const LG_Vector2DI& Other) const;					//Mayor que
		bool operator<=(const LG_Vector2DI& Other) const;					//Menor o igual a
		bool operator>=(const LG_Vector2DI& Other) const;					//Mayor o igual a
		bool Equals(const LG_Vector2DI& V, int Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaraci�n de operadores de asignaci�n compuesta                    												*/
		/************************************************************************************************************************/
		LG_Vector2DI operator+=(const LG_Vector2DI& V);
		LG_Vector2DI operator-=(const LG_Vector2DI& V);
		LG_Vector2DI operator*=(int Scale);
		LG_Vector2DI operator/=(int Scale);
		LG_Vector2DI operator*=(const LG_Vector2DI& V);
		LG_Vector2DI operator/=(const LG_Vector2DI& V);

		int operator|(const LG_Vector2DI& V) const;			//Dot Product
		int operator^(const LG_Vector2DI& V) const;			//Cross Product

		int Magnitud(const LG_Vector2DI& V);
		LG_Vector2DI Normalize(const LG_Vector2DI& V);
		int DotProduct(const LG_Vector2DI& A, const LG_Vector2DI& B);


	};
}
