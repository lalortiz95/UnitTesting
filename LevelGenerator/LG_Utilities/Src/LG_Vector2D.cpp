#include "LG_Vector2D.h"
#include <cmath>

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Vector2D::LG_Vector2D()
	{

	}
	
	//! Constructor with parameters.
	LG_Vector2D::LG_Vector2D(float InX, float InY) : X(InX), Y(InY)
	{

	}
	
	//! Default Destructor.
	LG_Vector2D::~LG_Vector2D()
	{

	}

	//! This function return the magnitud of the vector given in the parameter.
	float LG_Vector2D::Magnitude(const LG_Vector2D & OtherVector)
	{
		return sqrt(pow(OtherVector.X, 2) + pow(OtherVector.Y, 2));
	}

	float LG_Vector2D::Magnitude()
	{
		return sqrt(pow(X, 2) + pow(Y, 2));
	}
	
	//! This function reduce the magnitud of the vector given between 0 and 1.
	LG_Vector2D LG_Vector2D::Normalize(const LG_Vector2D & OtherVector)
	{
		return OtherVector / Magnitude(OtherVector);
	}

	//! This function reduce the magnitud of the vector given between 0 and 1.
	LG_Vector2D LG_Vector2D::Normalize()
	{
		return *this / Magnitude();
	}

	//! This function realize the dot product between 2 vectors.
	float LG_Vector2D::Dot(const LG_Vector2D& VectorA, const LG_Vector2D& VectorB)
	{
		return VectorA | VectorB;
	}

	//! This function realizes the dot product between 2 vectors.
	float LG_Vector2D::Dot(const LG_Vector2D & VectorB)
	{
		return *this | VectorB;
	}

	//! This is an operator to use + between 2 vectors.
	LG_Vector2D LG_Vector2D::operator+(const LG_Vector2D& OtherVector) const
	{
		return LG_Vector2D(X + OtherVector.X, Y + OtherVector.Y);
	}
	
	//! This is an operator to use - between 2 vectors.
	LG_Vector2D LG_Vector2D::operator-(const LG_Vector2D& OtherVector) const
	{
		return LG_Vector2D(X - OtherVector.X, Y - OtherVector.Y);
	}

	//! This is an operator to use * between 1 vector and 1 scalar value.
	LG_Vector2D LG_Vector2D::operator*(float Value) const
	{
		return LG_Vector2D(X * Value, Y * Value);
	}
	
	//! This is an operator to use * between 2 vectors.
	LG_Vector2D LG_Vector2D::operator*(const LG_Vector2D& OtherVector) const
	{
		return LG_Vector2D(X * OtherVector.X, Y * OtherVector.Y);
	}
	
	//! This is an operator to use / between 1 vector and 1 scalar value.
	LG_Vector2D LG_Vector2D::operator/(float Value) const
	{
		const float RScale = 1.f / Value;
		return LG_Vector2D(X * RScale, Y * RScale);
	}

	//! This is an operator to use / between 2 vectors.
	LG_Vector2D LG_Vector2D::operator/(const LG_Vector2D& OtherVector) const
	{
		return LG_Vector2D(X / OtherVector.X, Y / OtherVector.Y);
	}

	//! This operator compares that 2 vectors are the same.
	bool LG_Vector2D::operator==(const LG_Vector2D& OtherVector) const
	{
		return X == OtherVector.X && Y == OtherVector.Y;
	}

	//! This operator compares that 2 vectors are diferents.
	bool LG_Vector2D::operator!=(const LG_Vector2D& OtherVector) const
	{
		return X != OtherVector.X || Y != OtherVector.Y;
	}
	
	//! This operator compares that this vector is lesser than other vector.
	bool LG_Vector2D::operator<(const LG_Vector2D& OtherVector) const
	{
		return X < OtherVector.X && Y < OtherVector.Y;
	}

	//!  This operator compares that a  vector is less greater than a value.
	bool LG_Vector2D::operator<(float fValue) const
	{
		return  X < fValue && Y < fValue;
	}
	
	//! This operator compares that this vector is greater than other vector.
	bool LG_Vector2D::operator>(const LG_Vector2D& OtherVector) const
	{
		return X > OtherVector.X && Y > OtherVector.Y;
	}

	//! This operator compares if a value is greater than other vector.
	bool LG_Vector2D::operator>(float fValue) const
	{
		return X > fValue && Y > fValue;
	}
	
	//! This operator compares that this vector is lesser or equal than other vector.
	bool LG_Vector2D::operator<=(const LG_Vector2D& OtherVector) const
	{
		return X <= OtherVector.X && Y <= OtherVector.Y;
	}

	bool LG_Vector2D::operator<=(float fValue) const
	{
		return X <= fValue && Y <= fValue;
	}

	//! This operator compares that this vector is greater or equal than other vector.
	bool LG_Vector2D::operator>=(const LG_Vector2D& OtherVector) const
	{
		return X >= OtherVector.X && Y >= OtherVector.Y;
	}

	bool LG_Vector2D::operator>=(float fValue) const
	{
		return  X >= fValue && Y >= fValue;
	}
	
	//! This function compares if 2 vectors are the same.
	bool LG_Vector2D::Equals(const LG_Vector2D& OtherVector, float Tolerance) const
	{
		return abs(X - OtherVector.X) < Tolerance && abs(Y - OtherVector.Y) < Tolerance;
	}

	//! This operator add the values from other vector with this.
	LG_Vector2D& LG_Vector2D::operator+=(const LG_Vector2D& OtherVector)
	{
		X += OtherVector.X; Y += OtherVector.Y;
		return *this;
	}
	
	//! This operator subtract the values from other vector with this.
	LG_Vector2D& LG_Vector2D::operator-=(const LG_Vector2D& OtherVector)
	{
		X -= OtherVector.X; Y -= OtherVector.Y;
		return *this;
	}
	
	//! This operator multiply the values from this vector with a value.
	LG_Vector2D& LG_Vector2D::operator*=(float Value)
	{
		X *= Value; Y *= Value;
		return *this;
	}
	
	//! This operator divide the values from this vector with a value.
	LG_Vector2D& LG_Vector2D::operator/=(float Value)
	{
		const float RV = 1.f / Value;
		X *= RV; Y *= RV;
		return *this;
	}
	
	//! This operator multiply the values from other vector with this.
	LG_Vector2D& LG_Vector2D::operator*=(const LG_Vector2D& OtherVector)
	{
		X *= OtherVector.X; Y *= OtherVector.Y;
		return *this;
	}
	
	//! This operator divide the values from other vector with this.
	LG_Vector2D& LG_Vector2D::operator/=(const LG_Vector2D& OtherVector)
	{
		X /= OtherVector.X; Y /= OtherVector.Y;
		return *this;
	}

	//!This operator return the dot product between this vector and other vector.
	float LG_Vector2D::operator|(const LG_Vector2D& OtherVector) const
	{
		return (X * OtherVector.X) + (Y * OtherVector.Y);
	}

	//! This operator return the cross product between this vector and other vector.
	float LG_Vector2D::operator^(const LG_Vector2D& OtherVector) const
	{
		return (X * OtherVector.Y) - (Y * OtherVector.X);
	}
	
}