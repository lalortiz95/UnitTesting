#include "LG_Vector3D.h"
#include <cmath>

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Vector3D::LG_Vector3D()
	{

	}
	
	//! Parameters Constructor.
	LG_Vector3D::LG_Vector3D(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ)
	{

	}
	
	//! Default Destructor.
	LG_Vector3D::~LG_Vector3D()
	{

	}

	//! This function return the magnitud of the vector given in the parameter.
	float LG_Vector3D::Magnitud(const LG_Vector3D & OtherVector)
	{
		return sqrt(pow(OtherVector.X, 2) + 
					pow(OtherVector.Y, 2) + 
					pow(OtherVector.Z, 2));
	}

	//! This function realize the dot product between 2 vectors.
	float LG_Vector3D::Dot(const LG_Vector3D& VectorA, const LG_Vector3D& VectorB)
	{
		return VectorA | VectorB;
	}

	//! This function return a perpendicular vector between 2 vectors.
	LG_Vector3D LG_Vector3D::Cross3(const LG_Vector3D& VectorA, const LG_Vector3D& VectorB)
	{
		return LG_Vector3D(	(VectorA.Y * VectorB.Z - VectorA.Z * VectorB.Y),
							(-1 * (VectorA.X * VectorB.Z - VectorA.Z * VectorB.X)),
							(VectorA.X * VectorB.Y - VectorA.Y * VectorB.X));
	}

	//! This function reduce the magnitud of the vector given between 0 and 1.
	LG_Vector3D LG_Vector3D::Normalize(const LG_Vector3D & OtherVector)
	{
		return OtherVector / Magnitud(OtherVector);
	}

	//! This function compares if 2 vectors are the same.
	bool LG_Vector3D::Equals(const LG_Vector3D& OtherVector, float Tolerance) const
	{
		return	abs(X - OtherVector.X) < Tolerance &&
				abs(Y - OtherVector.Y) < Tolerance && 
				abs(Z - OtherVector.Z) < Tolerance;
	}

	//! This is an operator to use + between 2 vectors.
	LG_Vector3D LG_Vector3D::operator+(const LG_Vector3D& OtherVector) const
	{
		return LG_Vector3D(	X + OtherVector.X, 
							Y + OtherVector.Y, 
							Z + OtherVector.Z);
	}
	
	//! This is an operator to use - between 2 vectors.
	LG_Vector3D LG_Vector3D::operator-(const LG_Vector3D& OtherVector) const
	{
		return LG_Vector3D(	X - OtherVector.X,
							Y - OtherVector.Y, 
							Z - OtherVector.Z);
	}
	
	//! This is an operator to use * between 1 vector and 1 scalar value.
	LG_Vector3D LG_Vector3D::operator*(float Value) const
	{
		return LG_Vector3D(	X * Value, 
							Y * Value, 
							Z * Value);
	}
	
	//! This is an operator to use * between 2 vectors.
	LG_Vector3D LG_Vector3D::operator*(const LG_Vector3D& OtherVector) const
	{
		return LG_Vector3D(	X * OtherVector.X, 
							Y * OtherVector.Y, 
							Z * OtherVector.Z);
	}
	
	//! This is an operator to use / between 1 vector and 1 scalar value.
	LG_Vector3D LG_Vector3D::operator/(float Value) const
	{
		const float RScale = 1.f / Value;
		return LG_Vector3D(	X * RScale, 
							Y * RScale, 
							Z * RScale);
	}
	
	//! This is an operator to use / between 2 vectors.
	LG_Vector3D LG_Vector3D::operator/(const LG_Vector3D& OtherVector) const
	{
		return LG_Vector3D(	X / OtherVector.X, 
							Y / OtherVector.Y,
							Z / OtherVector.Z);
	}

	//! This operator compares that 2 vectors are the same.
	bool LG_Vector3D::operator==(const LG_Vector3D& OtherVector) const
	{
		return	X == OtherVector.X && 
				Y == OtherVector.Y && 
				Z == OtherVector.Z;
	}
	
	//! This operator compares that 2 vectors are diferents.
	bool LG_Vector3D::operator!=(const LG_Vector3D& OtherVector) const
	{
		return	X != OtherVector.X ||
				Y != OtherVector.Y ||
				Z != OtherVector.Z;
	}
	
	//! This operator compares that this vector is lesser than other vector.
	bool LG_Vector3D::operator<(const LG_Vector3D& OtherVector) const
	{
		return	X < OtherVector.X && 
				Y < OtherVector.Y && 
				Z < OtherVector.Z;
	}
	
	//! This operator compares that this vector is greater than other vector.
	bool LG_Vector3D::operator>(const LG_Vector3D& OtherVector) const
	{
		return	X > OtherVector.X && 
				Y > OtherVector.Y &&
				Z > OtherVector.Z;
	}
	
	//! This operator compares that this vector is lesser or equal than other vector.
	bool LG_Vector3D::operator<=(const LG_Vector3D& OtherVector) const
	{
		return	X <= OtherVector.X && 
				Y <= OtherVector.Y && 
				Z <= OtherVector.Z;
	}
	
	//! This operator compares that this vector is greater or equal than other vector.
	bool LG_Vector3D::operator>=(const LG_Vector3D& OtherVector) const
	{
		return	X >= OtherVector.X && 
				Y >= OtherVector.Y && 
				Z >= OtherVector.Z;
	}
	
	//! This operator assigns the values from other vector with this.
	LG_Vector3D & LG_Vector3D::operator=(const LG_Vector3D & OtherVector)
	{
		X = OtherVector.X;
		Y = OtherVector.Y;
		Z = OtherVector.Z;

		return *this;
	}

	//!	This operator add the values from other vector with this.
	LG_Vector3D& LG_Vector3D::operator+=(const LG_Vector3D& OtherVector)
	{
		X += OtherVector.X; 
		Y += OtherVector.Y; 
		Z += OtherVector.Z;

		return *this;
	}
	
	//! This operator subtract the values from other vector with this.
	LG_Vector3D& LG_Vector3D::operator-=(const LG_Vector3D& OtherVector)
	{
		X -= OtherVector.X; 
		Y -= OtherVector.Y; 
		Z -= OtherVector.Z;

		return *this;
	}
	
	//! This operator multiply the values from this vector with a value.
	LG_Vector3D& LG_Vector3D::operator*=(float Value)
	{
		X *= Value; 
		Y *= Value;
		Z *= Value;

		return *this;
	}
	
	//! This operator divide the values from this vector with a value.
	LG_Vector3D& LG_Vector3D::operator/=(float Value)
	{
		const float RV = 1.f / Value;

		X *= RV;
		Y *= RV;
		Z *= RV;

		return *this;
	}
	
	//! This operator multiply the values from other vector with this.
	LG_Vector3D& LG_Vector3D::operator*=(const LG_Vector3D& OtherVector)
	{
		X *= OtherVector.X; 
		Y *= OtherVector.Y; 
		Z *= OtherVector.Z;

		return *this;
	}
	
	//! This operator divide the values from other vector with this.
	LG_Vector3D& LG_Vector3D::operator/=(const LG_Vector3D& OtherVector)
	{
		X /= OtherVector.X;
		Y /= OtherVector.Y;
		Z /= OtherVector.Z;

		return *this;
	}
	
	//! This operator return the dot product between this vector and other vector.
	float LG_Vector3D::operator|(const LG_Vector3D& OtherVector) const
	{
		return	X * OtherVector.X + 
				Y * OtherVector.Y +
				Z * OtherVector.Z;
	}

	//! This operator return the cross product between this vector and other vector.
	float LG_Vector3D::operator^(const LG_Vector3D& OtherVector) const
	{
		return ((Y * OtherVector.Z - Z * OtherVector.Y) - 
				(X * OtherVector.Z - Z * OtherVector.X) +
				(X * OtherVector.Y - Y * OtherVector.X));
	}

	
}