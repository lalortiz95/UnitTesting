#pragma once
#include "LG_UtilitiesPrerequisites.h"

namespace LevelGenerator
{
	/**
	 *	@brief Class to use a Vector in a 2D space with integer.
	 */
	class LG_UTILITIES_EXPORT LG_Vector2DI
	{
	
		public:

			///**************************************************************************/
			///*						  Member Variables.								*/
			///**************************************************************************/

			/**
			 *	@brief This variable store the position in X Axis.
			 */
			int32 X;

			/**
			 *	@brief This variable store the position in Y Axis.
			 */
			int32 Y;

			///************************************************************************/
			///*                            Constructor & Destructor.                 */
			///************************************************************************/

			/**
			 * @brief Constructor default.
			 */
			LG_Vector2DI();

			/**
			 *	@brief Constructor with parameters.
			 *	@param int fPosX: Position in X axis.
			 *	@param int fPosY: Position in Y axis.
			 */
			LG_Vector2DI(int32 InX, int32 InY);

			/**
			 * @brief Destructor default.
			 */
			~LG_Vector2DI();


			///************************************************************************/
			///*						   Class Functions.							  */
			///************************************************************************/

			/**
			 *	@brief This function return the magnitud of the vector given in the parameter.
			 *	@param const LG_Vector2DI& OtherVector: The vector.
			 *	@return the magnitud of the vector.
			 */
			int Magnitud(const LG_Vector2DI& OtherVector);

			/**
			 *	@brief This function realize the dot product between 2 vectors.
			 *	@param const LG_Vector2DI& VectorA:
			 *	@param const LG_Vector2DI& VectorB:
			 *	@return The projection from VectorA with VectorB.
			 */
			int Dot(const LG_Vector2DI& VectorA, const LG_Vector2DI& VectorB);

			/**
			 *	@brief This function reduce the magnitud of the vector given between 0 and 1.
			 *	@param const LG_Vector2DI& OtherVector: The vector.
			 *	@return The normalized vector.
			 */
			LG_Vector2DI Normalize(const LG_Vector2DI& OtherVector);

			///************************************************************************/
			///*						Arithmetic Operators.				          */
			///************************************************************************/

			/**
			 *	@brief This is an operator to use + between 2 vectors.
			 *	@param const LG_Vector2DI& OtherVector: The vector to Add.
			 *	@return the result of the addition.
			 */
			LG_Vector2DI operator+(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This is an operator to use - between 2 vectors.
			 *	@param const LG_Vector2DI& OtherVector: The vector to subtract.
			 *	@return the result of the subtraction.
			 */
			LG_Vector2DI operator-(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This is an operator to use * between 1 vector and 1 scalar value.
			 *	@param int32 Value: The value to multiply.
			 *	@return the result of the multiplication.
			 */
			LG_Vector2DI operator*(int32 Value) const;

			/**
			 *	@brief This is an operator to use * between 2 vectors.
			 *	@param const LG_Vector2DI& OtherVector: The vector to multiply.
			 *	@return the result of the multiplication.
			 */
			LG_Vector2DI operator*(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This is an operator to use / between 1 vector and 1 scalar value.
			 *	@param int32 Value: The value to divide.
			 *	@return the result of the division.
			 */
			LG_Vector2DI operator/(int32 Value) const;

			/**
			 *	@brief This is an operator to use / between 2 vectors.
			 *	@param const LG_Vector2DI& OtherVector: The vector to divide.
			 *	@return the result of the division.
			 */
			LG_Vector2DI operator/(const LG_Vector2DI& OtherVector) const;


			///************************************************************************/
			///*						Logical Operators.				              */
			///************************************************************************/

			/**
			 *	@brief This operator compares that 2 vectors are the same.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if the vector is the same that this, if not false.
			 */
			bool operator==(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator compares that 2 vectors are diferents
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if the vector is diferent that this, if not, false.
			 */
			bool operator!=(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator compares that this vector is lesser than other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if this vector is lesser than the other vector, if not, false.
			 */
			bool operator<(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator compares that this vector is greater than other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if this vector is greater than the other vector, if not, false.
			 */
			bool operator>(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator compares that this vector is lesser or equal than other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if this vector is lesser or equal than the other vector, if not, false.
			 */
			bool operator<=(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator compares that this vector is greater or equal than other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@return true if this vector is greater or equal than the other vector, if not, false.
			 */
			bool operator>=(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This function compares if 2 vectors are the same.
			 *	@param const LG_Vector2DI& OtherVector: The vector to compare with this.
			 *	@param int32 fTolerance: This variable is used as a tolerance for considering that 2 vectors are the same.
			 *	@return true if this vector is the same that other vector., if not, false.
			 */
			bool Equals(const LG_Vector2DI& OtherVector, int32 Tolerance) const;


			///************************************************************************/
			///*					Compound Assignment Operators.				      */
			///************************************************************************/

			/**
			 *	@brief This operator add the values from other vector with this.
			 *	@param const LG_Vector2DI& OtherVector: The vector to add with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator+=(const LG_Vector2DI& OtherVector);

			/**
			 *	@brief This operator subtract the values from other vector with this.
			 *	@param const LG_Vector2DI& OtherVector: The vector to subtract with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator-=(const LG_Vector2DI& OtherVector);

			/**
			 *	@brief This operator multiply the values from this vector with a value.
			 *	@param int32 Value: The value to multiply with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator*=(int32 Value);

			/**
			 *	@brief This operator divide the values from this vector with a value.
			 *	@param int Value: The value to divide with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator/=(int Value);

			/**
			 *	@brief This operator multiply the values from other vector with this.
			 *	@param const LG_Vector2DI& OtherVector: The vector to multiply with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator*=(const LG_Vector2DI& OtherVector);

			/**
			 *	@brief This operator divide the values from other vector with this.
			 *	@param const LG_Vector2DI& OtherVector: The vector to divide with this.
			 *	@return this vector like a reference to actualize it's variables.
			 */
			LG_Vector2DI& operator/=(const LG_Vector2DI& OtherVector);

			/**
			 *	@brief This operator return the dot product between this vector and other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to apply the dot product with this.
			 *	@return the result of the dot product.
			 */
			int operator|(const LG_Vector2DI& OtherVector) const;

			/**
			 *	@brief This operator return the cross product between this vector and other vector.
			 *	@param const LG_Vector2DI& OtherVector: The vector to apply the cross product with this.
			 *	@return the result of the cross product.
			 */
			int operator^(const LG_Vector2DI& OtherVector) const;
	};
}
