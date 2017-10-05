#include "LG_Vector4D.h"
#include <cmath>

#define DELTA 0.00001f

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Vector4D::LG_Vector4D()
	{

	}

	//! Parameters Constructor.
	LG_Vector4D::LG_Vector4D(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW)
	{

	}

	//! Default Destructor.
	LG_Vector4D::~LG_Vector4D()
	{

	}

	//! This function return the magnitud of the vector given in the parameter.
	float LG_Vector4D::Magnitude(const LG_Vector4D & OtherVector)
	{
		return sqrt(pow(OtherVector.X, 2) +
					pow(OtherVector.Y, 2) + 
					pow(OtherVector.Z, 2) + 
					pow(OtherVector.W, 2));
	}

	float LG_Vector4D::Magnitude()
	{
		return sqrt(pow(X, 2) +
			pow(Y, 2) +
			pow(Z, 2) +
			pow(W, 2));
	}

	//! This function realize the dot product between 2 vectors.
	float LG_Vector4D::Dot(const LG_Vector4D & VectorA, const LG_Vector4D & VectorB)
	{
		float escalar = (VectorA.X * VectorB.X) +
			(VectorA.Y * VectorB.Y) +
			(VectorA.Z * VectorB.Z) +
			(VectorA.W * VectorB.W);

		if (escalar <= DELTA && escalar >= 0 - DELTA)
		{
			escalar = 0;
		}

		return escalar;
	}

	//! This function realize the dot product between 2 vectors.
	float LG_Vector4D::Dot(const LG_Vector4D& OtherVector)
	{
		float escalar = (X * OtherVector.X) + 
						(Y * OtherVector.Y) + 
						(Z * OtherVector.Z) + 
						(W * OtherVector.W);

		if (escalar <= DELTA && escalar >= 0 - DELTA)
		{
			escalar = 0;
		}

		return escalar;
	}

	//! This function return a perpendicular vector between 2 vectors.
	LG_Vector4D LG_Vector4D::Cross(const LG_Vector4D & VectorA, const LG_Vector4D & VectorB)
	{
		return LG_Vector4D((VectorA.Y * VectorB.Z - VectorA.Z * VectorB.Y),
						   (VectorA.Z * VectorB.X - VectorA.X * VectorB.Z),
						   (VectorA.X * VectorB.Y - VectorA.Y * VectorB.X),
							0);
	}

	//! This function return a perpendicular vector between 2 vectors.
	LG_Vector4D LG_Vector4D::Cross(const LG_Vector4D & V)
	{
		return LG_Vector4D((Y * V.Z - Z * V.Y),
			(Z * V.X - X * V.Z),
			(X * V.Y - Y * V.X),
			0);
	}

	//! This function reduce the magnitud of the vector given between 0 and 1.
	LG_Vector4D LG_Vector4D::Normalize(const LG_Vector4D & OtherVector)
	{
		return OtherVector / Magnitude(OtherVector);
	}

	void LG_Vector4D::Normalize()
	{
		*this /= Magnitude();
	}

	//! This function compares if 2 vectors are the same.
	bool LG_Vector4D::Equals(const LG_Vector4D& OtherVector, float fTolerance) const
	{
		return	abs(X - OtherVector.X) < fTolerance &&
			abs(Y - OtherVector.Y) < fTolerance &&
			abs(Z - OtherVector.Z) < fTolerance &&
			abs(W - OtherVector.W) < fTolerance;
	}

	//! This is an operator to use + between 2 vectors.
	LG_Vector4D LG_Vector4D::operator+(const LG_Vector4D& OtherVector) const
	{
		return LG_Vector4D(	X + OtherVector.X, 
							Y + OtherVector.Y,
							Z + OtherVector.Z,
							W + OtherVector.W);
	}
	
	//! This is an operator to use - between 2 vectors.
	LG_Vector4D LG_Vector4D::operator-(const LG_Vector4D& OtherVector) const
	{
		return LG_Vector4D(	X - OtherVector.X, 
							Y - OtherVector.Y, 
							Z - OtherVector.Z, 
							W - OtherVector.W);
	}
	
	//! This is an operator to use * between 1 vector and 1 scalar value.
	LG_Vector4D LG_Vector4D::operator*(float Value) const
	{
		return LG_Vector4D(	X * Value, 
							Y * Value, 
							Z * Value, 
							W * Value);
	}

	//! This is an operator to use * between 2 vectors.
	LG_Vector4D LG_Vector4D::operator*(const LG_Vector4D& OtherVector) const
	{
		return LG_Vector4D(	X * OtherVector.X, 
							Y * OtherVector.Y, 
							Z * OtherVector.Z, 
							W * OtherVector.W);
	}
	
	//! This is an operator to use / between 1 vector and 1 scalar value.
	LG_Vector4D LG_Vector4D::operator/(float Value) const
	{
		const float RValue = 1.f / Value;
		return LG_Vector4D(	X * RValue, 
							Y * RValue, 
							Z * RValue,		
							W * RValue);
	}
	
	//! This is an operator to use / between 2 vectors.
	LG_Vector4D LG_Vector4D::operator/(const LG_Vector4D& OtherVector) const
	{
		return LG_Vector4D(	X / OtherVector.X, 
							Y / OtherVector.Y, 
							Z / OtherVector.Z,	
							W / OtherVector.W);
	}

	//! This operator compares that 2 vectors are the same.
	bool LG_Vector4D::operator==(const LG_Vector4D& OtherVector) const
	{
		return	X == OtherVector.X &&
				Y == OtherVector.Y &&
				Z == OtherVector.Z &&
				W == OtherVector.W;
	}

	//! This operator compares that 2 vectors are diferents
	bool LG_Vector4D::operator!=(const LG_Vector4D& OtherVector) const
	{
		return	X != OtherVector.X || 
				Y != OtherVector.Y || 
				Z != OtherVector.Z || 
				W != OtherVector.W;
	}

	//! This operator compares that this vector is lesser than other vector.
	bool LG_Vector4D::operator<(const LG_Vector4D& OtherVector) const
	{
		return	X < OtherVector.X && 
				Y < OtherVector.Y && 
				Z < OtherVector.Z && 
				W < OtherVector.W;
	}

	bool LG_Vector4D::operator<(float fValue) const
	{
		return 	X < fValue &&
			Y < fValue &&
			Z < fValue &&
			W < fValue;
	}
	
	//! his operator compares that this vector is greater than other vector.
	bool LG_Vector4D::operator>(const LG_Vector4D& OtherVector) const
	{
		return	X > OtherVector.X && 
				Y > OtherVector.Y && 
				Z > OtherVector.Z && 
				W > OtherVector.W;
	}

	bool LG_Vector4D::operator>(float fValue) const
	{
		return	X > fValue &&
			Y > fValue &&
			Z > fValue &&
			W > fValue;
	}
	
	//! This operator compares that this vector is lesser or equal than other vector.
	bool LG_Vector4D::operator<=(const LG_Vector4D& OtherVector) const
	{
		return	X <= OtherVector.X && 
				Y <= OtherVector.Y && 
				Z <= OtherVector.Z && 
				W <= OtherVector.W;
	}

	bool LG_Vector4D::operator<=(float fValue) const
	{
		return 	X <= fValue &&
			Y <= fValue &&
			Z <= fValue &&
			W <= fValue;
	}
	
	//! This operator compares that this vector is greater or equal than other vector.
	bool LG_Vector4D::operator>=(const LG_Vector4D& OtherVector) const
	{
		return	X >= OtherVector.X && 
				Y >= OtherVector.Y &&
				Z >= OtherVector.Z && 
				W >= OtherVector.W;
	}

	bool LG_Vector4D::operator>=(float fValue) const
	{
		return	X >= fValue &&
			Y >= fValue &&
			Z >= fValue &&
			W >= fValue;
	}
	
	//! This operator add the values from other vector with this.
	LG_Vector4D& LG_Vector4D::operator+=(const LG_Vector4D& OtherVector)
	{
		X += OtherVector.X; 
		Y += OtherVector.Y; 
		Z += OtherVector.Z; 
		W += OtherVector.W;

		return *this;
	}
	
	//! This operator subtract the values from other vector with this.
	LG_Vector4D& LG_Vector4D::operator-=(const LG_Vector4D& OtherVector)
	{
		X -= OtherVector.X; 
		Y -= OtherVector.Y; 
		Z -= OtherVector.Z; 
		W -= OtherVector.W;

		return *this;
	}
	
	//! This operator multiply the values from this vector with a value.
	LG_Vector4D& LG_Vector4D::operator*=(float Value)
	{
		X *= Value; 
		Y *= Value; 
		Z *= Value; 
		W *= Value;

		return *this;
	}
	
	//! This operator divide the values from this vector with a value.
	LG_Vector4D& LG_Vector4D::operator/=(float Value)
	{
		const float RV = 1.f / Value;

		X *= RV;
		Y *= RV; 
		Z *= RV; 
		W *= RV;

		return *this;
	}
	
	//! This operator multiply the values from other vector with this.
	LG_Vector4D& LG_Vector4D::operator*=(const LG_Vector4D& OtherVector)
	{
		X *= OtherVector.X; 
		Y *= OtherVector.Y; 
		Z *= OtherVector.Z; 
		W *= OtherVector.W;

		return *this;
	}
	
	//! This operator divide the values from other vector with this.
	LG_Vector4D& LG_Vector4D::operator/=(const LG_Vector4D& OtherVector)
	{
		X /= OtherVector.X; 
		Y /= OtherVector.Y; 
		Z /= OtherVector.Z;
		W /= OtherVector.W;

		return *this;
	}

	//! his operator return the dot product between this vector and other vector.
	float LG_Vector4D::operator|(const LG_Vector4D& OtherVector) const
	{
		return	X * OtherVector.X + 
				Y * OtherVector.Y + 
				Z * OtherVector.Z + 
				W * OtherVector.W;
	}

	//! This operator return the cross product between this vector and other vector.
	float LG_Vector4D::operator^(const LG_Vector4D& V) const
	{
		//TODO: Implementar el operador.
		return 0.0f;
	}
}
