#include "LG_Vector3DI.h"
#include "LG_Matrix3D.h"

#include <cmath>

namespace LevelGenerator
{
	//! Default Constructor.
	LG_Vector3DI::LG_Vector3DI()
	{

	}

	//! Parameters Constructor.
	LG_Vector3DI::LG_Vector3DI(int32 InX, int32 InY, int32 InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	//! Default Destructor.
	LG_Vector3DI::~LG_Vector3DI()
	{

	}

	//! This function return the magnitude of a vector.
	int32 LG_Vector3DI::Magnitude()
	{
		return (int32)sqrt(pow(this->X, 2) +
			pow(this->Y, 2) +
			pow(this->Z, 2));
	}
	//! This function return the magnitude of the vector given as a parameter.
	int32 LG_Vector3DI::Magnitude(const LG_Vector3DI& OtherVector)
	{
		return (int32)sqrt(pow(OtherVector.X, 2) +
			pow(OtherVector.Y, 2) +
			pow(OtherVector.Z, 2));
	}

	//! This function calculates the midpoint between two vectors
	LG_Vector3DI LG_Vector3DI::MidPoint(const LG_Vector3DI & VectorB)
	{
		return LG_Vector3DI((X + VectorB.X) / 2, (Y + VectorB.Y) / 2, (Z + VectorB.Z) / 2);
	}

	//! This function calculates the midpoint between two vectors.
	LG_Vector3DI LG_Vector3DI::MidPoint(const LG_Vector3DI & VectorA, const LG_Vector3DI & VectorB)
	{
		return LG_Vector3DI((VectorA.X + VectorB.X) / 2, (VectorA.Y + VectorB.Y) / 2, (VectorA.Z + VectorB.Z) / 2);
	}

	//! This function realize the dot product between 2 vectors.
	int32 LG_Vector3DI::Dot(const LG_Vector3DI& VectorA, const LG_Vector3DI& VectorB)
	{
		return VectorA | VectorB;
	}

	//! This function realize the dot product between 2 vectors.
	int32 LG_Vector3DI::Dot(const LG_Vector3DI & VectorB)
	{
		return *this | VectorB;
	}

	//! This function return a perpendicular vector between 2 vectors.
	LG_Vector3DI LG_Vector3DI::Cross3(const LG_Vector3DI& VectorA, const LG_Vector3DI& VectorB)
	{
		return LG_Vector3DI((VectorA.Y * VectorB.Z - VectorA.Z * VectorB.Y),
			(-1 * (VectorA.X * VectorB.Z - VectorA.Z * VectorB.X)),
			(VectorA.X * VectorB.Y - VectorA.Y * VectorB.X));
	}

	//! This function return a perpendicular vector between 2 vectors.
	LG_Vector3DI LG_Vector3DI::Cross3(const LG_Vector3DI & V)
	{
		return LG_Vector3DI((V.Y * Z - V.Z * Y),
			(-1 * (V.X * Z - V.Z * X)),
			(V.X * Y - V.Y * X));
	}

	//! This function reduce the Magnitude of the vector given between 0 and 1.
	LG_Vector3DI LG_Vector3DI::Normalize(const LG_Vector3DI & V)
	{
		return V / Magnitude(V);
	}

	//! This function reduce the magnitude of the vector given between 0 and 1.
	LG_Vector3DI LG_Vector3DI::Normalize()
	{
		return *this /= Magnitude();
	}

	//! This function compares if 2 vectors are the same.
	bool LG_Vector3DI::Equals(const LG_Vector3DI& OtherVector, int32 Tolerance) const
	{
		return	abs(X - OtherVector.X) < Tolerance &&
			abs(Y - OtherVector.Y) < Tolerance &&
			abs(Z - OtherVector.Z) < Tolerance;
	}

	//! This is an operator to use + between 2 vectors.
	LG_Vector3DI LG_Vector3DI::operator+(const LG_Vector3DI& OtherVector) const
	{
		return LG_Vector3DI(X + OtherVector.X,
			Y + OtherVector.Y,
			Z + OtherVector.Z);
	}

	//! This is an operator to use - between 2 vectors.
	LG_Vector3DI LG_Vector3DI::operator-(const LG_Vector3DI& OtherVector) const
	{
		return LG_Vector3DI(X - OtherVector.X,
			Y - OtherVector.Y,
			Z - OtherVector.Z);
	}

	//! This is an operator to use * between 1 vector and 1 scalar value.
	LG_Vector3DI LG_Vector3DI::operator*(int32 iValue) const
	{
		return LG_Vector3DI(X * iValue,
			Y * iValue,
			Z * iValue);
	}			

	//! This is an operator to use * between 2 vectors.
	LG_Vector3DI LG_Vector3DI::operator*(const LG_Vector3DI& OtherVector) const
	{
		return LG_Vector3DI(X * OtherVector.X,
			Y * OtherVector.Y,
			Z * OtherVector.Z);
	}

	LG_Vector3DI LG_Vector3DI::operator*(const LG_Matrix3D & M)
	{
		return LG_Vector3DI((M.m.X0 * X + M.m.Y0  * X + M.m.Z0 * X),
			(M.m.X1 * Y + M.m.Y1  *Y + M.m.Z1 * Y),
			(M.m.X2 * Z + M.m.Y2  *Z + M.m.Z2 * Z));
	}

	//! This is an operator to use / between 1 vector and 1 scalar value.
	LG_Vector3DI LG_Vector3DI::operator/(int32 Value) const
	{
		const int32 RScale = 1 / Value;
		return LG_Vector3DI(X * RScale,
			Y * RScale,
			Z * RScale);
	}

	//! This is an operator to use / between 2 vectors.
	LG_Vector3DI LG_Vector3DI::operator/(const LG_Vector3DI& OtherVector) const
	{
		return LG_Vector3DI(X / OtherVector.X,
			Y / OtherVector.Y,
			Z / OtherVector.Z);
	}

	//! This operator compares that 2 vectors are the same.
	bool LG_Vector3DI::operator==(const LG_Vector3DI& OtherVector) const
	{
		return	X == OtherVector.X &&
			Y == OtherVector.Y &&
			Z == OtherVector.Z;
	}

	//! This operator compares that 2 vectors are different.
	bool LG_Vector3DI::operator!=(const LG_Vector3DI& OtherVector) const
	{
		return	X != OtherVector.X ||
			Y != OtherVector.Y ||
			Z != OtherVector.Z;
	}

	//! This operator compares that this vector is lesser than other vector.
	bool LG_Vector3DI::operator<(const LG_Vector3DI& OtherVector) const
	{
		return	X < OtherVector.X &&
			Y < OtherVector.Y &&
			Z < OtherVector.Z;
	}

	//! This operator compares that this vector is less greater than a value.
	bool LG_Vector3DI::operator<(int32 fValue) const
	{
		return X < fValue &&
			Y < fValue &&
			Z < fValue;
	}

	//! This operator compares that this vector is greater than other vector.
	bool LG_Vector3DI::operator>(const LG_Vector3DI& OtherVector) const
	{
		return	X > OtherVector.X &&
			Y > OtherVector.Y &&
			Z > OtherVector.Z;
	}

	//! This operator compares that this vector is greater than a value.
	bool LG_Vector3DI::operator>(int32 fValue) const
	{
		return 	X > fValue &&
			Y > fValue &&
			Z > fValue;
	}

	//! This operator compares that this vector is lesser or equal than other vector.
	bool LG_Vector3DI::operator<=(const LG_Vector3DI& OtherVector) const
	{
		return	X <= OtherVector.X &&
			Y <= OtherVector.Y &&
			Z <= OtherVector.Z;
	}

	//! This operator compares that this vector is less greater or equal than a value.
	bool LG_Vector3DI::operator<=(int32 fValue) const
	{
		return	X <= fValue &&
			Y <= fValue &&
			Z <= fValue;
	}

	//! This operator compares that this vector is greater or equal than other vector.
	bool LG_Vector3DI::operator>=(const LG_Vector3DI& OtherVector) const
	{
		return	X >= OtherVector.X &&
			Y >= OtherVector.Y &&
			Z >= OtherVector.Z;
	}

	//! This operator compares that this vector is greater or equal than a value.
	bool LG_Vector3DI::operator>=(int32 fValue) const
	{
		return	X >= fValue &&
			Y >= fValue &&
			Z >= fValue;
	}

	//! This operator assigns the values from other vector with this.
	LG_Vector3DI & LG_Vector3DI::operator=(const LG_Vector3DI & OtherVector)
	{
		X = OtherVector.X;
		Y = OtherVector.Y;
		Z = OtherVector.Z;

		return *this;
	}

	//!	This operator add the values from other vector with this.
	LG_Vector3DI& LG_Vector3DI::operator+=(const LG_Vector3DI& OtherVector)
	{
		X += OtherVector.X;
		Y += OtherVector.Y;
		Z += OtherVector.Z;

		return *this;
	}

	//! This operator subtract the values from other vector with this.
	LG_Vector3DI& LG_Vector3DI::operator-=(const LG_Vector3DI& OtherVector)
	{
		X -= OtherVector.X;
		Y -= OtherVector.Y;
		Z -= OtherVector.Z;

		return *this;
	}

	//! This operator multiply the values from this vector with a value.
	LG_Vector3DI& LG_Vector3DI::operator*=(int32 Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;

		return *this;
	}

	LG_Vector3DI & LG_Vector3DI::operator*=(const LG_Matrix3D & M)
	{
		return *this = *this * M;
	}

	//! This operator divide the values from this vector with a value.
	LG_Vector3DI& LG_Vector3DI::operator/=(int32 Value)
	{
		const int32 RV = 1.f / Value;

		X *= RV;
		Y *= RV;
		Z *= RV;

		return *this;
	}

	//! This operator multiply the values from other vector with this.
	LG_Vector3DI& LG_Vector3DI::operator*=(const LG_Vector3DI& OtherVector)
	{
		X *= OtherVector.X;
		Y *= OtherVector.Y;
		Z *= OtherVector.Z;

		return *this;
	}

	//! This operator divide the values from other vector with this.
	LG_Vector3DI& LG_Vector3DI::operator/=(const LG_Vector3DI& OtherVector)
	{
		X /= OtherVector.X;
		Y /= OtherVector.Y;
		Z /= OtherVector.Z;

		return *this;
	}

	//! This operator return the dot product between this vector and other vector.
	int32 LG_Vector3DI::operator|(const LG_Vector3DI& OtherVector) const
	{
		return	X * OtherVector.X +
			Y * OtherVector.Y +
			Z * OtherVector.Z;
	}

	//! This operator return the cross product between this vector and other vector.
	int32 LG_Vector3DI::operator^(const LG_Vector3DI& OtherVector) const
	{
		return ((Y * OtherVector.Z - Z * OtherVector.Y) -
			(X * OtherVector.Z - Z * OtherVector.X) +
			(X * OtherVector.Y - Y * OtherVector.X));
	}


}