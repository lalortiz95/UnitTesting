#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include <cmath>

namespace LevelGenerator
{
	class LG_UTILITIES_EXPORT LG_Vector3D
	{
	public:

		float X;
		float Y;
		float Z;

		/************************************************************************************************************************/
		/* Constructores   y Destructores                                                     									*/
		/************************************************************************************************************************/
		LG_Vector3D();
		LG_Vector3D(float InX, float InY, float InZ);

		~LG_Vector3D();

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		LG_Vector3D operator+(const LG_Vector3D& V) const;		//Suma
		LG_Vector3D operator-(const LG_Vector3D& V) const;		//Resta
		LG_Vector3D operator*(float Scale) const;				//Multiplicación (escalar)
		LG_Vector3D operator*(const LG_Vector3D& V) const;		//Multiplicación (vector)
		LG_Vector3D operator/(float Scale) const;							//División (escalar)
		LG_Vector3D operator/(const LG_Vector3D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const LG_Vector3D& V) const;						//Igual a
		bool operator!=(const LG_Vector3D& V) const;						//Diferente a
		bool operator<(const LG_Vector3D& Other) const;					//Menor que
		bool operator>(const LG_Vector3D& Other) const;					//Mayor que
		bool operator<=(const LG_Vector3D& Other) const;					//Menor o igual a
		bool operator>=(const LG_Vector3D& Other) const;					//Mayor o igual a
		bool Equals(const LG_Vector3D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		LG_Vector3D operator+=(const LG_Vector3D& V);
		LG_Vector3D operator-=(const LG_Vector3D& V);
		LG_Vector3D operator*=(float Scale);
		LG_Vector3D operator/=(float Scale);
		LG_Vector3D operator*=(const LG_Vector3D& V);
		LG_Vector3D operator/=(const LG_Vector3D& V);

		float operator|(const LG_Vector3D& V) const;			//Dot Product
		float operator^(const LG_Vector3D& V) const;			//Cross Product

		float Magnitud(const LG_Vector3D& V);
		LG_Vector3D Normalize(const LG_Vector3D& V);
		float DotProduct(const LG_Vector3D& A, const LG_Vector3D& B);
		LG_Vector3D Cross3(const LG_Vector3D& V, const LG_Vector3D& B);

	};
}