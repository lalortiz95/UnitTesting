#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include <cmath>

namespace LevelGenerator
{
	/**
	 *	@brief Class to use a Vector in a 2D space.
	 */
	class LG_UTILITIES_EXPORT LG_Vector2D
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
		LG_Vector2D();

		/**
		 *	@brief Constructor with parameters.
		 *	@param float fPosX: Position in X axis.
		 *	@param float fPosY: Position in Y axis.
		 */
		LG_Vector2D(float InX, float InY);

		/**
		 * @brief Destructor default.
		 */
		~LG_Vector2D();


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function return the magnitud of the vector given in the parameter.
		 *	@param LG_Vector2D& Vector: The vector.
		 *	@return the magnitud of the vector.
		 */
		float Magnitud(const LG_Vector2D& Vector);

		/**
		 *	@brief This function reduce the magnitud of the vector given between 0 and 1.
		 *	@param LG_Vector2D& Vector: The vector.
		 *	@return The normalized vector.
		 */
		LG_Vector2D Normalize(const LG_Vector2D& V);

		/**
		 *	@brief This function reduce the magnitud of the vector given between 0 and 1.
		 *	@param LG_Vector2D& VectorA: 
		 *	@param LG_Vector2D& VectorB:
		 *	@return The proyection from VectorA and VectorB.
		 */
		float DotProduct(const LG_Vector2D& VectorA, const LG_Vector2D& VectorB);

		/************************************************************************************************************************/
		/* Declaración de operadores aritméticos                                 												*/
		/************************************************************************************************************************/
		LG_Vector2D operator+(const LG_Vector2D& V) const;		//Suma
		LG_Vector2D operator-(const LG_Vector2D& V) const;		//Resta
		LG_Vector2D operator*(float Scale) const;				//Multiplicación (escalar)
		LG_Vector2D operator*(const LG_Vector2D& V) const;		//Multiplicación (vector)
		LG_Vector2D operator/(float Scale) const;							//División (escalar)
		LG_Vector2D operator/(const LG_Vector2D& V) const;					//División (vector)



		/************************************************************************************************************************/
		/* Declaración de operadores lógicos                                     												*/
		/************************************************************************************************************************/
		bool operator==(const LG_Vector2D& V) const;						//Igual a
		bool operator!=(const LG_Vector2D& V) const;						//Diferente a
		bool operator<(const LG_Vector2D& Other) const;					//Menor que
		bool operator>(const LG_Vector2D& Other) const;					//Mayor que
		bool operator<=(const LG_Vector2D& Other) const;					//Menor o igual a
		bool operator>=(const LG_Vector2D& Other) const;					//Mayor o igual a
		bool Equals(const LG_Vector2D& V, float Tolerance) const;			//Compara si son "iguales" manejando una toleracia

		/************************************************************************************************************************/
		/* Declaración de operadores de asignación compuesta                    												*/
		/************************************************************************************************************************/
		LG_Vector2D& operator+=(const LG_Vector2D& V);
		LG_Vector2D& operator-=(const LG_Vector2D& V);
		LG_Vector2D& operator*=(float Scale);
		LG_Vector2D& operator/=(float Scale);
		LG_Vector2D& operator*=(const LG_Vector2D& V);
		LG_Vector2D& operator/=(const LG_Vector2D& V);


		float operator|(const LG_Vector2D& V) const;			//Dot Product
		float operator^(const LG_Vector2D& V) const;			//Cross Product


	


	};
}

