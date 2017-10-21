#pragma once
#include "LG_UtilitiesPrerequisites.h"

namespace LevelGenerator
{
	///**************************************************************************/
	///*						 Forward declarations.							*/
	///**************************************************************************/
	class LG_Matrix3D;

	/**
	 *	@brief Class to use a Vector in a 3D space.
	 */
	class LG_UTILITIES_EXPORT LG_Vector3D
	{

	public:

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var This variable store the position in X Axis.
		 */
		float X;

		/**
		 *	@var This variable store the position in Y Axis.
		 */
		float Y;

		/**
		 *	@var This variable store the position in Z Axis.
		 */
		float Z;

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 * @brief Constructor default.
		 */
		LG_Vector3D();

		/**
		 *	@brief Constructor with parameters.
		 *	@param float fPosX: Position in X axis.
		 *	@param float fPosY: Position in Y axis.
		 *	@param float fPosY: Position in Z axis.
		 */
		LG_Vector3D(float InX, float InY, float InZ);

		/**
		 * @brief Destructor default.
		 */
		~LG_Vector3D();


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function return the magnitude of the vector given in the parameter.
		 *	@return the magnitude of the vector.
		 */
		float Magnitude();

		/**
		 *	@brief This function return the magnitude of the vector given in the parameter.
		 *	@param const LG_Vector3D& VectorA: The given vector.
		 *	@return the magnitude of two vectors.
		 */
		 static float Magnitude(const LG_Vector3D VectorA);

		/**
		 *	@brief This function realizes the dot product between 2 vectors.
		 *	@param const LG_Vector3D& VectorA:
		 *	@param const LG_Vector3D& VectorB:
		 *	@return The projection from VectorA with VectorB.
		 */
		static float Dot(const LG_Vector3D& VectorA, const LG_Vector3D& VectorB);

		/**
		 *	@brief This function realize the dot product between 2 vectors.
		 *	@param const LG_Vector3D& VectorB: The other vector to work with.
		 *	@return The projection from this with VectorB.
		 */
		float Dot(const LG_Vector3D& VectorB);

		/**
		 *	@brief This function return a perpendicular vector between 2 vectors.
		 *	@param const LG_Vector3D& V: The first vector to cross product with.
		 *	@param const LG_Vector3D& B: The second vector to cross product with.
		 *	@return the vector that is perpendicular.
		 */
		static LG_Vector3D Cross3(const LG_Vector3D& V, const LG_Vector3D& B);


		/**
		 *	@brief This function return a perpendicular vector between 2 vectors.
		 *	@param const LG_Vector3D& V: The vector to cross product with.
		 *	@return the vector that is perpendicular.
		 */
		LG_Vector3D Cross3(const LG_Vector3D& V);

		/**
		 *	@brief This function reduce the Magnitude of the vector given between 0 and 1.
		 *	@param const LG_Vector3D& V: the vector to normalize.
		 *	@return the normalized vector.
		 */
		static LG_Vector3D Normalize(const LG_Vector3D& V);

		/**
		 *	@brief This function reduce the Magnitude of the vector given between 0 and 1.
		 *	@return the normalized vector.
		 */
		LG_Vector3D Normalize();

		/**
1		 *	@brief This function compares if 2 vectors are the same.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@param float fTolerance: This variable is used as a tolerance for considering that 2 vectors are the same.
		 *	@return true if this vector is the same that other vector., if not, false.
		 */
		bool Equals(const LG_Vector3D& OtherVector, float fTolerance) const;

		///************************************************************************/
		///*						Arithmetic Operators.				          */
		///************************************************************************/

		/**
		 *	@brief This is an operator to use + between 2 vectors.
		 *	@param const LG_Vector3D& OtherVector: The vector to Add.
		 *	@return the result of the addition.
		 */
		LG_Vector3D operator+(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This is an operator to use - between 2 vectors.
		 *	@param const LG_Vector3D& OtherVector: The vector to subtract.
		 *	@return the result of the subtraction.
		 */
		LG_Vector3D operator-(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This is an operator to use * between 1 vector and 1 scalar value.
		 *	@param float Value: The value to multiply.
		 *	@return the result of the multiplication.
		 */
		LG_Vector3D operator*(float Value) const;

		/**
		 *	@brief This is an operator to use * between 2 vectors.
		 *	@param const LG_Vector3D& OtherVector: The vector to multiply.
		 *	@return the result of the multiplication.
		 */
		LG_Vector3D operator*(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This is an operator to use * between 2 vectors.
		 *	@param const LG_Matrix3D& M: The matrix to multiply with this vector.
		 *	@return the result of the multiplication.
		 */
		LG_Vector3D operator*(const LG_Matrix3D& M);

		/**
		 *	@brief This is an operator to use / between 1 vector and 1 scalar value.
		 *	@param float Value: The value to divide.
		 *	@return the result of the division.
		 */
		LG_Vector3D operator/(float Value) const;

		/**
		 *	@brief This is an operator to use / between 2 vectors.
		 *	@param const LG_Vector3D& OtherVector: The vector to divide.
		 *	@return the result of the division.
		 */
		LG_Vector3D operator/(const LG_Vector3D& OtherVector) const;


		///************************************************************************/
		///*						Logical Operators.				              */
		///************************************************************************/

		/**
		 *	@brief This operator compares that 2 vectors are the same.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@return true if the vector is the same that this, if not false.
		 */
		bool operator==(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This operator compares that 2 vectors are diferents.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@return true if the vector is diferent that this, if not, false.
		 */
		bool operator!=(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This operator compares that this vector is lesser than other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@return true if this vector is lesser than the other vector, if not, false.
		 */
		bool operator<(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This operator compares that this vector is less greater than a value.
		 *	@param float fValue: The value to compare with.
		 *	@return true if this vector is less greater than the other vector, if not, false.
		 */
		bool operator<(float fValue) const;

		/**
		 *	@brief This operator compares that this vector is greater than other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with.
		 *	@return true if this vector is greater than the other vector, if not, false.
		 */
		bool operator>(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This operator compares that this vector is greater than a value.
		 *	@param float fValue: The vector to compare with.
		 *	@return true if this vector is greater than the value, if not, false.
		 */
		bool operator>(float fValue) const;

		/**
		 *	@brief This operator compares that this vector is lesser or equal than other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@return true if this vector is lesser or equal than the other vector, if not, false.
		 */
		bool operator<=(const LG_Vector3D& OtherVector) const;

		/**
		*	@brief This operator compares that this vector is less greater or equal than a value.
		*	@param float fValue: The value to compare with.
		*	@return true if this vector is less greater or equal than the other vector, if not, false.
		*/
		bool operator<=(float fValue) const;

		/**
		 *	@brief This operator compares that this vector is greater or equal than other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to compare with this.
		 *	@return true if this vector is greater or equal than the other vector, if not, false.
		 */
		bool operator>=(const LG_Vector3D& OtherVector) const;


		/**
		 *	@brief This operator compares that this vector is greater or equal than a value.
		 *	@param float fValue: The vector to compare with.
		 *	@return true if this vector is greater or equal than the value, if not, false.
		 */
		bool operator>=(float fValue) const;

		///************************************************************************/
		///*					Compound Assignment Operators.				      */
		///************************************************************************/

		/**
		 *	@brief This operator assigns the values from other vector with this.
		 *	@param const LG_Vector3D& OtherVector: The vector to add with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator=(const LG_Vector3D& OtherVector);

		/**
		 *	@brief This operator add the values from other vector with this.
		 *	@param const LG_Vector3D& OtherVector: The vector to add with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator+=(const LG_Vector3D& OtherVector);

		/**
		 *	@brief This operator subtract the values from other vector with this.
		 *	@param const LG_Vector3D& OtherVector: The vector to subtract with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator-=(const LG_Vector3D& OtherVector);

		/**
		 *	@brief This operator multiply the values from this vector with a value.
		 *	@param float Value: The value to multiply with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator*=(float Value);


		/**
		 *	@brief This operator multiply the values from this vector with a value.
		 *	@param const LG_Matrix3D& M: The matrix to multiply with this vector. 
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator*=(const LG_Matrix3D& M);

		/**
		 *	@brief This operator divide the values from this vector with a value.
		 *	@param float fValue: The value to divide with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator/=(float fValue);

		/**
		 *	@brief This operator multiply the values from other vector with this.
		 *	@param const LG_Vector3D& OtherVector: The vector to multiply with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator*=(const LG_Vector3D& OtherVector);

		/**
		 *	@brief This operator divide the values from other vector with this.
		 *	@param const LG_Vector3D& OtherVector: The vector to divide with this.
		 *	@return this vector like a reference to actualize it's variables.
		 */
		LG_Vector3D& operator/=(const LG_Vector3D& OtherVector);

		/**
		 *	@brief This operator return the dot product between this vector and other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to apply the dot product with this.
		 *	@return the result of the dot product.
		 */
		float operator|(const LG_Vector3D& OtherVector) const;

		/**
		 *	@brief This operator return the cross product between this vector and other vector.
		 *	@param const LG_Vector3D& OtherVector: The vector to apply the cross product with this.
		 *	@return the result of the cross product.
		 */
		float operator^(const LG_Vector3D& OtherVector) const;

	};
}