
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
	class LG_UTILITIES_EXPORT LG_Vector3DI
	{

	public:

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		*	@var This variable store the position in X Axis.
		*/
		int32 X;

		/**
		*	@var This variable store the position in Y Axis.
		*/
		int32 Y;

		/**
		*	@var This variable store the position in Z Axis.
		*/
		int32 Z;

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		* @brief Constructor default.
		*/
		LG_Vector3DI();

		/**
		*	@brief Constructor with parameters.
		*	@param int32 iPosX: Position in X axis.
		*	@param int32 iPosY: Position in Y axis.
		*	@param int32 iPosY: Position in Z axis.
		*/
		LG_Vector3DI(int32 InX, int32 InY, int32 InZ);

		/**
		* @brief Destructor default.
		*/
		~LG_Vector3DI();


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		*	@brief This function return the magnitude of a vector.
		*	@return the magnitude of the vector.
		*/
		int32 Magnitude();

		/**
		*	@brief This function return the magnitude of the vector given as a parameter.
		*	@param const LG_Vector3DI& VectorA: The given vector.
		*	@return the magnitude of two vectors.
		*/
		static int32 Magnitude(const LG_Vector3DI& VectorA);

		/*
		* @brief This function calculates the midpoint between two vectors.
		* @param const LG_Vector3DI& VectorB: The second vector used to get the middle position.
		* @return The position that in the middle of both vectors.
		*/
		LG_Vector3DI MidPoint(const LG_Vector3DI& VectorB);

		/*
		* @brief This function calculates the midpoint between two vectors.
		* @param const LG_Vector3DI& VectorA: The first vector used to get the middle position.
		* @param const LG_Vector3DI& VectorB: The second vector used to get the middle position.
		* @return The position that in the middle of both vectors.
		*/
		static LG_Vector3DI MidPoint(const LG_Vector3DI& VectorA, const LG_Vector3DI& VectorB);

		/**
		*	@brief This function realizes the dot product between 2 vectors.
		*	@param const LG_Vector3DI& VectorA:
		*	@param const LG_Vector3DI& VectorB:
		*	@return The projection from VectorA with VectorB.
		*/
		static int32 Dot(const LG_Vector3DI& VectorA, const LG_Vector3DI& VectorB);

		/**
		*	@brief This function realize the dot product between 2 vectors.
		*	@param const LG_Vector3DI& VectorB: The other vector to work with.
		*	@return The projection from this with VectorB.
		*/
		int32 Dot(const LG_Vector3DI& VectorB);

		/**
		*	@brief This function return a perpendicular vector between 2 vectors.
		*	@param const LG_Vector3DI& V: The first vector to cross product with.
		*	@param const LG_Vector3DI& B: The second vector to cross product with.
		*	@return the vector that is perpendicular.
		*/
		static LG_Vector3DI Cross3(const LG_Vector3DI& V, const LG_Vector3DI& B);


		/**
		*	@brief This function return a perpendicular vector between 2 vectors.
		*	@param const LG_Vector3DI& V: The vector to cross product with.
		*	@return the vector that is perpendicular.
		*/
		LG_Vector3DI Cross3(const LG_Vector3DI& V);

		/**
		*	@brief This function reduce the Magnitude of the vector given between 0 and 1.
		*	@param const LG_Vector3DI& V: the vector to normalize.
		*	@return the normalized vector.
		*/
		static LG_Vector3DI Normalize(const LG_Vector3DI& V);

		/**
		*	@brief This function reduce the Magnitude of the vector given between 0 and 1.
		*	@return the normalized vector.
		*/
		LG_Vector3DI Normalize();

		/**
		*   @brief This function compares if 2 vectors are the same.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@param int32 iTolerance: This variable is used as a tolerance for considering that 2 vectors are the same.
		*	@return true if this vector is the same that other vector., if not, false.
		*/
		bool Equals(const LG_Vector3DI& OtherVector, int32 iTolerance) const;

		///************************************************************************/
		///*						Arithmetic Operators.				          */
		///************************************************************************/

		/**
		*	@brief This is an operator to use + between 2 vectors.
		*	@param const LG_Vector3DI& OtherVector: The vector to Add.
		*	@return the result of the addition.
		*/
		LG_Vector3DI operator+(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This is an operator to use - between 2 vectors.
		*	@param const LG_Vector3DI& OtherVector: The vector to subtract.
		*	@return the result of the subtraction.
		*/
		LG_Vector3DI operator-(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This is an operator to use * between 1 vector and 1 scalar value.
		*	@param int32 Value: The value to multiply.
		*	@return the result of the multiplication.
		*/
		LG_Vector3DI operator*(int32 Value) const;

		/**
		*	@brief This is an operator to use * between 2 vectors.
		*	@param const LG_Vector3DI& OtherVector: The vector to multiply.
		*	@return the result of the multiplication.
		*/
		LG_Vector3DI operator*(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This is an operator to use * between 2 vectors.
		*	@param const LG_Matrix3D& M: The matrix to multiply with this vector.
		*	@return the result of the multiplication.
		*/
		LG_Vector3DI operator*(const LG_Matrix3D& M);

		/**
		*	@brief This is an operator to use / between 1 vector and 1 scalar value.
		*	@param int32 Value: The value to divide.
		*	@return the result of the division.
		*/
		LG_Vector3DI operator/(int32 Value) const;

		/**
		*	@brief This is an operator to use / between 2 vectors.
		*	@param const LG_Vector3DI& OtherVector: The vector to divide.
		*	@return the result of the division.
		*/
		LG_Vector3DI operator/(const LG_Vector3DI& OtherVector) const;


		///************************************************************************/
		///*						Logical Operators.				              */
		///************************************************************************/

		/**
		*	@brief This operator compares that 2 vectors are the same.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@return true if the vector is the same that this, if not false.
		*/
		bool operator==(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator compares that 2 vectors are diferents.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@return true if the vector is diferent that this, if not, false.
		*/
		bool operator!=(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator compares that this vector is lesser than other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@return true if this vector is lesser than the other vector, if not, false.
		*/
		bool operator<(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator compares that this vector is less greater than a value.
		*	@param int32 fValue: The value to compare with.
		*	@return true if this vector is less greater than the other vector, if not, false.
		*/
		bool operator<(int32 fValue) const;

		/**
		*	@brief This operator compares that this vector is greater than other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with.
		*	@return true if this vector is greater than the other vector, if not, false.
		*/
		bool operator>(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator compares that this vector is greater than a value.
		*	@param int32 fValue: The vector to compare with.
		*	@return true if this vector is greater than the value, if not, false.
		*/
		bool operator>(int32 fValue) const;

		/**
		*	@brief This operator compares that this vector is lesser or equal than other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@return true if this vector is lesser or equal than the other vector, if not, false.
		*/
		bool operator<=(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator compares that this vector is less greater or equal than a value.
		*	@param int32 fValue: The value to compare with.
		*	@return true if this vector is less greater or equal than the other vector, if not, false.
		*/
		bool operator<=(int32 fValue) const;

		/**
		*	@brief This operator compares that this vector is greater or equal than other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to compare with this.
		*	@return true if this vector is greater or equal than the other vector, if not, false.
		*/
		bool operator>=(const LG_Vector3DI& OtherVector) const;


		/**
		*	@brief This operator compares that this vector is greater or equal than a value.
		*	@param int32 fValue: The vector to compare with.
		*	@return true if this vector is greater or equal than the value, if not, false.
		*/
		bool operator>=(int32 fValue) const;

		///************************************************************************/
		///*					Compound Assignment Operators.				      */
		///************************************************************************/

		/**
		*	@brief This operator assigns the values from other vector with this.
		*	@param const LG_Vector3DI& OtherVector: The vector to add with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator=(const LG_Vector3DI& OtherVector);

		/**
		*	@brief This operator add the values from other vector with this.
		*	@param const LG_Vector3DI& OtherVector: The vector to add with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator+=(const LG_Vector3DI& OtherVector);

		/**
		*	@brief This operator subtract the values from other vector with this.
		*	@param const LG_Vector3DI& OtherVector: The vector to subtract with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator-=(const LG_Vector3DI& OtherVector);

		/**
		*	@brief This operator multiply the values from this vector with a value.
		*	@param int32 Value: The value to multiply with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator*=(int32 Value);


		/**
		*	@brief This operator multiply the values from this vector with a value.
		*	@param const LG_Matrix3D& M: The matrix to multiply with this vector.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator*=(const LG_Matrix3D& M);

		/**
		*	@brief This operator divide the values from this vector with a value.
		*	@param int32 fValue: The value to divide with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator/=(int32 fValue);

		/**
		*	@brief This operator multiply the values from other vector with this.
		*	@param const LG_Vector3DI& OtherVector: The vector to multiply with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator*=(const LG_Vector3DI& OtherVector);

		/**
		*	@brief This operator divide the values from other vector with this.
		*	@param const LG_Vector3DI& OtherVector: The vector to divide with this.
		*	@return this vector like a reference to actualize it's variables.
		*/
		LG_Vector3DI& operator/=(const LG_Vector3DI& OtherVector);

		/**
		*	@brief This operator return the dot product between this vector and other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to apply the dot product with this.
		*	@return the result of the dot product.
		*/
		int32 operator|(const LG_Vector3DI& OtherVector) const;

		/**
		*	@brief This operator return the cross product between this vector and other vector.
		*	@param const LG_Vector3DI& OtherVector: The vector to apply the cross product with this.
		*	@return the result of the cross product.
		*/
		int32 operator^(const LG_Vector3DI& OtherVector) const;

	};
}