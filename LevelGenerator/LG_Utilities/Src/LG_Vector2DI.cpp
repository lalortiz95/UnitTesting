#include "LG_Vector2DI.h"
#include <cmath>

namespace LevelGenerator
{

	//! Default Constructor.
	LG_Vector2DI::LG_Vector2DI()
	{

	}

	//! Constructor with parameters.
	LG_Vector2DI::LG_Vector2DI(int32 InX, int32 InY) : X(InX), Y(InY)
	{

	}

	//! Default Destructor.
	LG_Vector2DI::~LG_Vector2DI()
	{

	}

	//! This function return the magnitud of the vector given in the parameter.
	int32 LG_Vector2DI::Magnitude(const LG_Vector2DI & OtherVector)
	{
		return (int32)sqrt(pow(OtherVector.X, 2) + pow(OtherVector.Y, 2));
	}

	//! This function return the magnitude of a vector.
	int32 LG_Vector2DI::Magnitude()
	{
		return (int32)sqrt(pow(X, 2) + pow(Y, 2));
	}

	//! This function realize the dot product between 2 vectors.
	int32 LG_Vector2DI::Dot(const LG_Vector2DI& VectorA, const LG_Vector2DI& VectorB)
	{
		return VectorA | VectorB;
	}

	//! This function realize the dot product between 2 vectors.
	int32 LG_Vector2DI::Dot(const LG_Vector2DI & VectorB)
	{
		return *this | VectorB;
	}

	//! This function reduce the magnitud of the vector given between 0 and 1.
	LG_Vector2DI LG_Vector2DI::Normalize(const LG_Vector2DI & OtherVector)
	{
		return OtherVector / Magnitude(OtherVector);
	}

	//! This function reduces the magnitude a vector to something between 0 and 1.
	LG_Vector2DI LG_Vector2DI::Normalize()
	{
		return *this / Magnitude();
	}

	//! This is an operator to use + between 2 vectors.
	LG_Vector2DI LG_Vector2DI::operator+(const LG_Vector2DI& OtherVector) const
	{
		return LG_Vector2DI(X + OtherVector.X, Y + OtherVector.Y);
	}

	//! This is an operator to use - between 2 vectors.
	LG_Vector2DI LG_Vector2DI::operator-(const LG_Vector2DI& OtherVector) const
	{
		return LG_Vector2DI(X - OtherVector.X, Y - OtherVector.Y);
	}

	//! This is an operator to use * between 1 vector and 1 scalar value.
	LG_Vector2DI LG_Vector2DI::operator*(int32 Value) const
	{
		return LG_Vector2DI(X * Value, Y * Value);
	}

	//! This is an operator to use * between 2 vectors.
	LG_Vector2DI LG_Vector2DI::operator*(const LG_Vector2DI& OtherVector) const
	{
		return LG_Vector2DI(X * OtherVector.X, Y * OtherVector.Y);
	}

	//! This is an operator to use / between 1 vector and 1 scalar value.
	LG_Vector2DI LG_Vector2DI::operator/(int32 Value) const
	{
		const float RScale = 1.0f / Value;
		return LG_Vector2DI(X * RScale, Y * RScale);
	}

	//! This is an operator to use / between 2 vectors.
	LG_Vector2DI LG_Vector2DI::operator/(const LG_Vector2DI& OtherVector) const
	{
		return LG_Vector2DI(X / OtherVector.X, Y / OtherVector.Y);
	}

	//! This operator compares that 2 vectors are the same.
	bool LG_Vector2DI::operator==(const LG_Vector2DI& OtherVector) const
	{
		return X == OtherVector.X && Y == OtherVector.Y;
	}

	//! This operator compares that a vector and a value are the same.
	bool LG_Vector2DI::operator==(int32 iValue) const
	{
		return X == iValue && Y == iValue;
	}

	//! This operator compares that 2 vectors are diferents.
	bool LG_Vector2DI::operator!=(const LG_Vector2DI& OtherVector) const
	{
		return X != OtherVector.X || Y != OtherVector.Y;
	}

	bool LG_Vector2DI::operator!=(int32 iValue) const
	{
		return X != iValue || Y != iValue;
	}

	//! This operator compares that this vector is lesser than other vector.
	bool LG_Vector2DI::operator<(const LG_Vector2DI& OtherVector) const
	{
		return X < OtherVector.X && Y < OtherVector.Y;
	}

	//! This operator compares that a value is less greater than a vector.
	bool LG_Vector2DI::operator<(int32 iValue) const
	{
		return X < iValue && Y < iValue;
	}

	//! This operator compares that this vector is greater than other vector.
	bool LG_Vector2DI::operator>(const LG_Vector2DI& OtherVector) const
	{
		return X > OtherVector.X && Y > OtherVector.Y;
	}

	//! This operator compares that a value is greater than a vector.
	bool LG_Vector2DI::operator>(int32 iValue) const
	{
		return X > iValue && Y > iValue;
	}

	//! This operator compares that this vector is lesser or equal than other vector.
	bool LG_Vector2DI::operator<=(const LG_Vector2DI& OtherVector) const
	{
		return X <= OtherVector.X && Y <= OtherVector.Y;
	}

	//! This operator compares that a value is less greater or equal to a vector.
	bool LG_Vector2DI::operator<=(int32 iValue) const
	{
		return X <= iValue && Y <= iValue;
	}

	//! This operator compares that this vector is greater or equal than other vector.
	bool LG_Vector2DI::operator>=(const LG_Vector2DI& OtherVector) const
	{
		return X >= OtherVector.X && Y >= OtherVector.Y;
	}

	bool LG_Vector2DI::operator>=(int32 iValue) const
	{
		return X >= iValue && Y >= iValue;
	}

	//! This operator add the values from other vector with this.
	LG_Vector2DI& LG_Vector2DI::operator+=(const LG_Vector2DI& OtherVector)
	{
		X += OtherVector.X; Y += OtherVector.Y;
		return *this;
	}

	//! This operator subtract the values from other vector with this.
	LG_Vector2DI& LG_Vector2DI::operator-=(const LG_Vector2DI& OtherVector)
	{
		X -= OtherVector.X; Y -= OtherVector.Y;
		return *this;
	}

	//! This operator multiply the values from this vector with a value.
	LG_Vector2DI& LG_Vector2DI::operator*=(int32 Value)
	{
		X *= Value; Y *= Value;
		return *this;
	}

	//! This operator divide the values from this vector with a value.
	LG_Vector2DI& LG_Vector2DI::operator/=(int32 Value)
	{
		const float RV = 1.0f / Value;
		X *= RV; Y *= RV;
		return *this;
	}

	//! This operator multiply the values from other vector with this.
	LG_Vector2DI& LG_Vector2DI::operator*=(const LG_Vector2DI& OtherVector)
	{
		X *= OtherVector.X; Y *= OtherVector.Y;
		return *this;
	}

	//! This operator divide the values from other vector with this.
	LG_Vector2DI& LG_Vector2DI::operator/=(const LG_Vector2DI& OtherVector)
	{
		X /= OtherVector.X; Y /= OtherVector.Y;
		return *this;
	}

	//!This operator return the dot product between this vector and other vector.
	int32 LG_Vector2DI::operator|(const LG_Vector2DI& OtherVector) const
	{
		return (X * OtherVector.X) + (Y * OtherVector.Y);
	}

	//! This operator return the cross product between this vector and other vector.
	int32 LG_Vector2DI::operator^(const LG_Vector2DI& OtherVector) const
	{
		return (X * OtherVector.Y) - (Y * OtherVector.X);
	}
}