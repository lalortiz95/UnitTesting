#pragma once
#include <cmath>

namespace LevelGenerator
{
#define DELTA 0.00001f
	class  CVector4D
	{
	public:

		float X;
		float Y;
		float Z;
		float W;

		/************************************************************************************************************************/
		/* Constructores   y Destructores                                                     									*/
		/************************************************************************************************************************/
		CVector4D();
		CVector4D(float InX, float InY, float InZ, float InW);

		~CVector4D();

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		CVector4D operator+(const CVector4D& V) const;		//Suma
		CVector4D operator-(const CVector4D& V) const;		//Resta
		CVector4D operator*(float Scale) const;				//Multiplicación (escalar)
		CVector4D operator*(const CVector4D& V) const;		//Multiplicación (vector)
		CVector4D operator/(float Scale) const;							//División (escalar)
		CVector4D operator/(const CVector4D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector4D& V) const;						//Igual a
		bool operator!=(const CVector4D& V) const;						//Diferente a
		bool operator<(const CVector4D& Other) const;					//Menor que
		bool operator>(const CVector4D& Other) const;					//Mayor que
		bool operator<=(const CVector4D& Other) const;					//Menor o igual a
		bool operator>=(const CVector4D& Other) const;					//Mayor o igual a
		bool Equals(const CVector4D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		CVector4D operator+=(const CVector4D& V);
		CVector4D operator-=(const CVector4D& V);
		CVector4D operator*=(float Scale);
		CVector4D operator/=(float Scale);
		CVector4D operator*=(const CVector4D& V);
		CVector4D operator/=(const CVector4D& V);

		float operator|(const CVector4D& V) const;			//Dot Product
		float operator^(const CVector4D& V) const;			//Cross Product

		float Magnitud(const CVector4D& V);
		CVector4D Normalize(const CVector4D& V);
		float Dot(const CVector4D& B);
		CVector4D Cross(const CVector4D& V, const CVector4D& B);

	};
}


