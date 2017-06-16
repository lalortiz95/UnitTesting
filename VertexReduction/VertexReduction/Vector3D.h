#pragma once
#include <cmath>

	class  CVector3D
	{
	public:

		float X;
		float Y;
		float Z;

		/************************************************************************************************************************/
		/* Constructores   y Destructores                                                     									*/
		/************************************************************************************************************************/
		CVector3D();
		CVector3D(float InX, float InY, float InZ);

		~CVector3D();

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		CVector3D operator+(const CVector3D& V) const;		//Suma
		CVector3D operator-(const CVector3D& V) const;		//Resta
		CVector3D operator*(float Scale) const;				//Multiplicación (escalar)
		CVector3D operator*(const CVector3D& V) const;		//Multiplicación (vector)
		CVector3D operator/(float Scale) const;							//División (escalar)
		CVector3D operator/(const CVector3D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector3D& V) const;						//Igual a
		bool operator!=(const CVector3D& V) const;						//Diferente a
		bool operator<(const CVector3D& Other) const;					//Menor que
		bool operator>(const CVector3D& Other) const;					//Mayor que
		bool operator<=(const CVector3D& Other) const;					//Menor o igual a
		bool operator>=(const CVector3D& Other) const;					//Mayor o igual a
		bool Equals(const CVector3D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

	    /************************************************************************************************************************/
	    /* Declaración de operadores de asignación compuesta                    												*/
	    /************************************************************************************************************************/
		CVector3D operator+=(const CVector3D& V);
		CVector3D operator-=(const CVector3D& V);
		CVector3D operator*=(float Scale);
		CVector3D operator/=(float Scale);
		CVector3D operator*=(const CVector3D& V);
		CVector3D operator/=(const CVector3D& V);

		float operator|(const CVector3D& V) const;			//Dot Product
		float operator^(const CVector3D& V) const;			//Cross Product

		float Magnitud(const CVector3D& V);
		CVector3D Normalize(const CVector3D& V);
		float DotProduct(const CVector3D& A, const CVector3D& B);
		CVector3D Cross3(const CVector3D& V, const CVector3D& B);

	};
