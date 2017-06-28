#pragma once
#include "PrerequisitesLevelGenerator.h"
#include <cmath>

namespace LevelGenerator
{
	/**
	 *	@brief Class to use a Vector in a 2D space.
	 */
	class LG_EXPORT CVector2D
	{
	public:

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable store the position in X Axis.
		 */
		float X;

		/**
		 *	@brief This variable store the position in Y Axis.
		 */
		float Y;

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 * @brief Constructor default.
		 */
		CVector2D();

		/**
		 *	@brief Constructor with parameters.
		 *	@param float fPosX: Position in X axis.
		 *	@param float fPosY: Position in Y axis.
		 */
		CVector2D(float InX, float InY);

		/**
		 * @brief Destructor default.
		 */
		~CVector2D();


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function return the magnitud of the vector given in the parameter.
		 *	@param CVector2D& Vector: The vector.
		 *	@return the magnitud of the vector.
		 */
		float Magnitud(const CVector2D& Vector);

		/**
		 *	@brief This function reduce the magnitud of the vector given between 0 and 1.
		 *	@param CVector2D& Vector: The vector.
		 *	@return The normalized vector.
		 */
		CVector2D Normalize(const CVector2D& V);

		/**
		 *	@brief This function reduce the magnitud of the vector given between 0 and 1.
		 *	@param CVector2D& VectorA: 
		 *	@param CVector2D& VectorB:
		 *	@return The proyection from VectorA and VectorB.
		 */
		float DotProduct(const CVector2D& VectorA, const CVector2D& VectorB);

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		CVector2D operator+(const CVector2D& V) const;		//Suma
		CVector2D operator-(const CVector2D& V) const;		//Resta
		CVector2D operator*(float Scale) const;				//Multiplicación (escalar)
		CVector2D operator*(const CVector2D& V) const;		//Multiplicación (vector)
		CVector2D operator/(float Scale) const;							//División (escalar)
		CVector2D operator/(const CVector2D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const CVector2D& V) const;						//Igual a
		bool operator!=(const CVector2D& V) const;						//Diferente a
		bool operator<(const CVector2D& Other) const;					//Menor que
		bool operator>(const CVector2D& Other) const;					//Mayor que
		bool operator<=(const CVector2D& Other) const;					//Menor o igual a
		bool operator>=(const CVector2D& Other) const;					//Mayor o igual a
		bool Equals(const CVector2D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		CVector2D& operator+=(const CVector2D& V);
		CVector2D& operator-=(const CVector2D& V);
		CVector2D& operator*=(float Scale);
		CVector2D& operator/=(float Scale);
		CVector2D& operator*=(const CVector2D& V);
		CVector2D& operator/=(const CVector2D& V);


		float operator|(const CVector2D& V) const;			//Dot Product
		float operator^(const CVector2D& V) const;			//Cross Product


	


	};
}

