#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include <cmath>

namespace LevelGenerator
{
#define DELTA 0.00001f
	class LG_UTILITIES_EXPORT LG_Vector4D
	{
	public:

		float X;
		float Y;
		float Z;
		float W;

		/************************************************************************************************************************/
		/* Constructores   y Destructores                                                     									*/
		/************************************************************************************************************************/
		LG_Vector4D();
		LG_Vector4D(float InX, float InY, float InZ, float InW);

		~LG_Vector4D();

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		LG_Vector4D operator+(const LG_Vector4D& V) const;		//Suma
		LG_Vector4D operator-(const LG_Vector4D& V) const;		//Resta
		LG_Vector4D operator*(float Scale) const;				//Multiplicación (escalar)
		LG_Vector4D operator*(const LG_Vector4D& V) const;		//Multiplicación (vector)
		LG_Vector4D operator/(float Scale) const;							//División (escalar)
		LG_Vector4D operator/(const LG_Vector4D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const LG_Vector4D& V) const;						//Igual a
		bool operator!=(const LG_Vector4D& V) const;						//Diferente a
		bool operator<(const LG_Vector4D& Other) const;					//Menor que
		bool operator>(const LG_Vector4D& Other) const;					//Mayor que
		bool operator<=(const LG_Vector4D& Other) const;					//Menor o igual a
		bool operator>=(const LG_Vector4D& Other) const;					//Mayor o igual a
		bool Equals(const LG_Vector4D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		LG_Vector4D operator+=(const LG_Vector4D& V);
		LG_Vector4D operator-=(const LG_Vector4D& V);
		LG_Vector4D operator*=(float Scale);
		LG_Vector4D operator/=(float Scale);
		LG_Vector4D operator*=(const LG_Vector4D& V);
		LG_Vector4D operator/=(const LG_Vector4D& V);

		float operator|(const LG_Vector4D& V) const;			//Dot Product
		float operator^(const LG_Vector4D& V) const;			//Cross Product

		float Magnitud(const LG_Vector4D& V);
		LG_Vector4D Normalize(const LG_Vector4D& V);
		float Dot(const LG_Vector4D& B);
		LG_Vector4D Cross(const LG_Vector4D& V, const LG_Vector4D& B);

	};
}


