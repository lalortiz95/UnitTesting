#pragma once
#include <cmath>

namespace LevelGenerator
{
	class CVector2D
	{
	public:

		float X;
		float Y;

		/************************************************************************************************************************/
		/* Constructores   y Destructores                                                     									*/
		/************************************************************************************************************************/
		CVector2D();
		CVector2D(float InX, float InY);

		~CVector2D();

		/************************************************************************************************************************/
		/* Declaraci�n de operadores aritm�ticos                                 												*/
		/************************************************************************************************************************/
		CVector2D operator+(const CVector2D& V) const;		//Suma
		CVector2D operator-(const CVector2D& V) const;		//Resta
		CVector2D operator*(float Scale) const;				//Multiplicaci�n (escalar)
		CVector2D operator*(const CVector2D& V) const;		//Multiplicaci�n (vector)
		CVector2D operator/(float Scale) const;							//Divisi�n (escalar)
		CVector2D operator/(const CVector2D& V) const;					//Divisi�n (vector)



		/************************************************************************************************************************/
		/* Declaraci�n de operadores l�gicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector2D& V) const;						//Igual a
		bool operator!=(const CVector2D& V) const;						//Diferente a
		bool operator<(const CVector2D& Other) const;					//Menor que
		bool operator>(const CVector2D& Other) const;					//Mayor que
		bool operator<=(const CVector2D& Other) const;					//Menor o igual a
		bool operator>=(const CVector2D& Other) const;					//Mayor o igual a
		bool Equals(const CVector2D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaraci�n de operadores de asignaci�n compuesta                    												*/
		/************************************************************************************************************************/
		CVector2D& operator+=(const CVector2D& V);
		CVector2D& operator-=(const CVector2D& V);
		CVector2D& operator*=(float Scale);
		CVector2D& operator/=(float Scale);
		CVector2D& operator*=(const CVector2D& V);
		CVector2D& operator/=(const CVector2D& V);

		float operator|(const CVector2D& V) const;			//Dot Product
		float operator^(const CVector2D& V) const;			//Cross Product

		float Magnitud(const CVector2D& V);
		CVector2D Normalize(const CVector2D& V);
		float DotProduct(const CVector2D& A, const CVector2D& B);


	};
}

