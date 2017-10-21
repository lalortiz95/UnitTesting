#pragma once
#include <LG_Vector2D.h>
#include <LG_Vector2DI.h>
#include <LG_Vector3D.h>
#include <LG_Vector4D.h>
#include <LG_Matrix3D.h>
#include <LG_Matrix4D.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;

///************************************************************************/
///*                     Utilities_Wrapping_UnitTest                      */
///************************************************************************/

/// Check that the size of our variables is what it's supposed to be.

//! Wrapping Char test.
TEST(Wrapping_Var, Char_8_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(int8) == 1);
}

//! Wrapping Short test.
TEST(Wrapping_Var, Short_16_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(int16) == 2);
}

//! Wrapping Int test.
TEST(Wrapping_Var, Int_32_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(int32) == 4);
}

//! Wrapping Long test.
TEST(Wrapping_Var, Long_64_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(int64) == 8);
}

//! Wrapping Double test.
TEST(Wrapping_Var, Double_128_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(int128) == 16);
}

//! Wrapping Unsigned Char test.
TEST(Wrapping_Var, Unsigned_Char_8_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(uint8) == 1);
}

//! Wrapping Unsigned Short test.
TEST(Wrapping_Var, Unsigned_Short_16_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(uint16) == 2);
}

//! Wrapping Unsigned Int test.
TEST(Wrapping_Var, Unsigned_Int_32_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(uint32) == 4);
}

//! Wrapping Unsigned Long test.
TEST(Wrapping_Var, Unsigned_Long_64_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(uint64) == 8);
}

//! Wrapping Unsigned Double test.
TEST(Wrapping_Var, Unsigned_Double_128_Bits)
{
	/// check that this variable measures the number of desired bits.
	EXPECT_TRUE(sizeof(uint128) == 16);
}

///************************************************************************/
///*                     Utilities_Math_UnitTest                          */
///************************************************************************/

//! Pi Constant Value Test.
TEST(Math_Constant, PI_)
{
	/// If constant pi is equal to atn(1.0f) * 4.0f return true, otherwise return false. 
	EXPECT_TRUE(LG_Math::PI == std::atan(1.0f) * 4.0f);
}

//! Pi half Constant Value Test.
TEST(Math_Constant, PI_Half)
{
	/// If constant PIHalf is equal to Pi/2 return true, otherwise return false. 
	EXPECT_TRUE(LG_Math::PI_HALF == LG_Math::PI / 2.0f);
}

//! Pi2 Constant Value Test.
TEST(Math_Constant, 2_PI)
{
	/// If constant euler is equal to Pi*2 return true, otherwise return false. 
	EXPECT_TRUE(LG_Math::PI2 == LG_Math::PI * 2.0f);
}

//! Euler Constant Value Test.
TEST(Math_Constant, Euler)
{
	/// If constant euler is equal to 2.71828182845904523536f return true, otherwise return false. 
	EXPECT_TRUE(LG_Math::EULERS == 2.71828182845904523536f);
}

//! Infinite num Constant Value Test.
TEST(Math_Constant, Infinite_Num)
{
	/// If infinite num is equal to numeric_limits<float>::infinity() return true, otherwise return false.
	EXPECT_TRUE(LG_Math::INFINITE_NUM == std::numeric_limits<float>::infinity());
}

//! Delta Constant Value Test.
TEST(Math_Constant, Delta)
{
	/// If delta is equal to a 0.00001f return true, otherwise false.
	EXPECT_TRUE(LG_Math::DELTA == 0.00001f);
}

//! Epsilon Constant Value Test.
TEST(Math_Constant, Epsilon)
{
	/// If epsilon is equal to a numeric_limits<float>::epsilon() return true, otherwise false.
	EXPECT_TRUE(LG_Math::EPSILON == std::numeric_limits<float>::epsilon());
}

//! Max Float Presition Constant Value Test.
TEST(Math_Constant, Max_Float_Presition)
{
	/// If max float presition is equal to a 0.00000001f return true, otherwise false.
	EXPECT_TRUE(LG_Math::MAX_FLOAT_PRESITION == 0.00000001f);
}

//! SquareRoot Function Test.
TEST(Math_Function, SquareRoot)
{
	LG_Math math;
	/// If the square root of 25 is 5 return true, otherwise false.
	EXPECT_TRUE(math.Sqrt(25) == 5);
}

//! Inverse SquareRoot Function Test.
TEST(Math_Function, Inverse_SquereRoot)
{
	LG_Math math;
	/// If the inverse square root of 25 is 1/5 return true, otherwise false.
	EXPECT_TRUE(math.InvSqrt(25) == 1.0f / 5);
}

//! Exponential Function Test.
TEST(Math_Function, Exponential)
{
	LG_Math math;
	/// If the Exponential of 5 is 148.4131262f return true, otherwise false.
	EXPECT_TRUE(math.Exp(5) == 148.413162f);
}

//! Power Function Test.
TEST(Math_Function, Power_)
{
	LG_Math math;
	/// If 3 pow to 3 is 27 return true, otherwise false.
	EXPECT_TRUE(math.Pow(3, 3) == 27);
}

//! NaturalLogarithm Function Test.
TEST(Math_Function, NaturalLogarithm)
{
	LG_Math math;
	/// If loge 25 is 3.21887589 return true, otherwise false.
	EXPECT_TRUE(math.Loge(25) == 3.21887589f);
}

//! Truncation Function Test.
TEST(Math_Function, Truncation_)
{
	LG_Math math;
	/// If we truncate pi we expect a 3 since its value is 3.1415..., otherwise false.
	EXPECT_TRUE(math.Trunc(LG_Math::PI) == 3);
}

//! Float Truncation Function Test.
TEST(Math_Function, Float_Truncation)
{
	LG_Math math;
	/// If we truncate pi we expect a 3.0f since its value is 3.1415..., otherwise false.
	EXPECT_TRUE(math.TruncFloat(LG_Math::PI) == 3.0f);
}

//! Floor Function Test.
TEST(Math_Function, Floor_)
{
	LG_Math math;
	/// If we aplicate floor to pi we expect a 3 since its value is 3.1415..., otherwise false.
	EXPECT_TRUE(math.Floor(LG_Math::PI) == 3);
}

//! Round Function Test.
TEST(Math_Function, Round_)
{
	LG_Math math;
	/// If we aplicate round to pi we expect a 3 since its value is 3.1415..., otherwise false.
	EXPECT_TRUE(math.Round(LG_Math::PI) == 3);
}

//! Ceil Function Test.
TEST(Math_Function, Ceil_)
{
	LG_Math math;
	/// If we aplicate ceil to pi we expect a 4 since its value is 3.1415..., otherwise false.
	EXPECT_TRUE(math.Ceil(LG_Math::PI) == 4);
}

//! Sine Function Test.
TEST(Math_Function, Sine)
{
	LG_Math math;
	/// If the sine of pi half(90°) is equal to 1 return true, otherwise false.
	EXPECT_TRUE(math.Sin(LG_Math::PI_HALF) == 1);
}

//! Cosine Function Test.
TEST(Math_Function, Cosine)
{
	LG_Math math;
	/// If the cosine of PI2(360°) is equal to 1 return true, otherwise false.
	EXPECT_TRUE(math.Cos(LG_Math::PI2) == 1);
}

//! Tangent Function Test.
TEST(Math_Function, Tangent)
{
	LG_Math math;
	EXPECT_TRUE(math.Tan(LG_Math::PI) <= LG_Math::DELTA && math.Tan(LG_Math::PI) >= -LG_Math::DELTA);
}

//! Maximum between 2 numbers Function Test.
TEST(Math_Function, Maximum_2Numbers)
{
	LG_Math math;
	/// If we insert 5 and a 2 in this function we expect the result to be 5 since it is greater than 2.
	EXPECT_TRUE(math.Max(5, 2) == 5);
}

//! Minimum between 2 numbers Function Test.
TEST(Math_Function, Minimum_2Numbers)
{
	LG_Math math;
	/// If we insert 5 and a 2 in this function we expect the result to be 2 since it is less than 5.
	EXPECT_TRUE(math.Min(5, 2) == 2);
}

//! Maximum between 3 numbers Function Test.
TEST(Math_Function, Maximum_3Numbers)
{
	LG_Math math;
	/// If we insert 5,2 and 9 in this function we expect the result to be 9 since it is greater than 2 and 5.
	EXPECT_TRUE(math.Max3(5, 2, 9) == 9);
}

//! Minimum between 3 numbers Function Test.
TEST(Math_Function, Minimum_3Numbers)
{
	LG_Math math;
	/// If we insert 5,2 and 1 in this function we expect the result to be 1 since it is less than 5 and 2.
	EXPECT_TRUE(math.Min3(5, 2, 1) == 1);
}

//TODO: Falta, LogX, Asin, ACos, Atan, Abs, Clamp, Lerp, Slerp

///************************************************************************/
///*                     Utilities_Vector2D_UnitTest                      */
///************************************************************************/

//! Magnitude Function Test.
TEST(Vector2D_Function, Magnitude_)
{
	/// The Vector that we want to obtain its magnitude.
	LG_Vector2D Test_2D(0, 5);
	/// If the magnitud of the vector is equal to 5 return true, otherwise false. 
	EXPECT_TRUE(Test_2D.Magnitude() == 5);
}

//! DotProduct Function Test.
TEST(Vector2D_Function, DotProduct_)
{
	/// The first vector for the dot product.
	LG_Vector2D VectorA(-6, 8);
	/// The second vector for the dot product.
	LG_Vector2D VectorB(5, 12);
	/// IF fesult is equal to 66 return true, otherwise false.
	EXPECT_TRUE(VectorA.Dot(VectorB) == 66);
}

//! Normalize Function Test.
TEST(Vector2D_Function, Normalize_)
{
	/// The Vector that we want to normalize.
	LG_Vector2D Test_2D(0, 1);
	/// If the magnitude of the normalized vector its between 1 and 0 return true, otherwise false. 
	EXPECT_TRUE(Test_2D.Normalize() <= 1 && Test_2D.Normalize() >= 0);
}

//! Equals Function Test.
TEST(Vector2D_Function, Equals_)
{
	/// The vector that we want to compare if its equal to the parameter vector.
	LG_Vector2D Test_2D(0, 1);
	/// If the vector test is equal to the parameter vector return true, otherwise false.
	EXPECT_TRUE(Test_2D.Equals(LG_Vector2D(0, 1), LG_Math::DELTA));
}

//! Static Magnitude Function Test.
TEST(Vector2D_Function, StaticMagnitude)
{
	/// If the magnitud of the vector is equal to 5 return true, otherwise false. 
	EXPECT_TRUE(LG_Vector2D::Magnitude(LG_Vector2D(0, 5)) == 5);
}

//! Static DotProduct Function Test.
TEST(Vector2D_Function, StaticDotProduct)
{
	/// IF result is equal to 66 return true, otherwise false.
	EXPECT_TRUE(LG_Vector2D::Dot(LG_Vector2D(-6, 8), LG_Vector2D(5, 12)) == 66);
}

//! Static Normalize Function Test.
TEST(Vector2D_Function, StaticNormalize)
{
	/// If the magnitude of the normalized vector its between 1 and 0 return true, otherwise false. 
	EXPECT_TRUE(LG_Vector2D::Normalize(LG_Vector2D(0, 1)) <= 1 && LG_Vector2D::Normalize(LG_Vector2D(0, 1)) >= 0);
}

//! Operator + between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_Plus_Vector)
{
	/// The result vector between the first vector plus the second vector.
	LG_Vector2D VectorResult = LG_Vector2D(7.1f, 2.2f) + LG_Vector2D(3.6f, 4.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2D(10.7f, 6.7f));
}

//! Operator - between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_Minus_Vector)
{
	/// The result vector between the first vector minus the second vector.
	LG_Vector2D VectorResult = LG_Vector2D(2.6f, 2.2f) - LG_Vector2D(4.6f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(-2.0f, 0.7f), LG_Math::DELTA));
}

//! Operator * between 1 Vector and 1 number Test.
TEST(Vector2D_Operator, Vector_Times_Float)
{
	/// The result vector between the first vector times the float value.
	LG_Vector2D VectorResult = LG_Vector2D(3.5f, 6.7f) * 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(10.5f, 20.1f), LG_Math::DELTA));
}

//! Operator * between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_Times_Vector)
{
	/// The result vector between the first vector times the second vector.
	LG_Vector2D VectorResult = LG_Vector2D(3.5f, 6.7f) * LG_Vector2D(2.2f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(7.7f, 10.05f), LG_Math::DELTA));
}

//! Operator / between 1 Vector and 1 number Test.
TEST(Vector2D_Operator, Vector_DividedBy_Float)
{
	/// The result vector between the first vector divided by the float value.
	LG_Vector2D VectorResult = LG_Vector2D(3.5f, 6.7f) / 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(1.16666f, 2.23333f), LG_Math::DELTA));
}

//! Operator / between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_DividedBy_Vector)
{
	/// The result vector between the first vector divided by the second vector.
	LG_Vector2D VectorResult = LG_Vector2D(3.5f, 6.7f) / LG_Vector2D(2.2f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(1.59090f, 4.46666f), LG_Math::DELTA));
}

//! Operator == between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_Equal_Vector)
{
	/// IF the first vector is the same that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000000f, 6.70000000f) == LG_Vector2D(3.50000000f, 6.70000000f));
}

//! Operator != between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_Different_Vector)
{
	/// IF the first vector is diferent that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000500f, 6.70000000f) != LG_Vector2D(3.50000000f, 6.70000001f));
}

//! Operator < between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_LeesThan_Vector)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000100f, 6.70000100f) < LG_Vector2D(3.50010000f, 6.70100000f));
}

//! Operator < between 1 Vector and 1 Value Test.
TEST(Vector2D_Operator, Vector_LessThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000100f, 6.70000100f) < 7.00023015f);
}

//! Operator > between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_GreaterThan_Vector)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2D(3.50000100f, 6.70000100f) > LG_Vector2D(3.50010000f, 6.70100000f));
}

//! Operator > between 1 Vector and 1 Value Test.
TEST(Vector2D_Operator, Vector_GreaterThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2D(3.50000100f, 6.70000100f) > 7.00023015f);
}

//! Operator <= between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_LessOrEqualThan_Vector)
{
	/// IF the first vector is less or equal that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000100f, 6.70100000f) <= LG_Vector2D(3.50010000f, 6.70100000f));
}

//! Operator <= between 1 Vector and 1 Value Test.
TEST(Vector2D_Operator, Vector_LessOrEqualThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2D(3.50000100f, 7.00023015f) <= 7.00023015f);
}

//! Operator >= between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_GreaterOrEqualThan_Vector)
{
	/// IF the first vector is greater or equal that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2D(3.50000100f, 6.70100000f) >= LG_Vector2D(3.50010000f, 6.70100000f));
}

//! Operator >= between 1 Vector and 1 Value Test.
TEST(Vector2D_Operator, Vector_GreaterOrEqualThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2D(3.50000100f, 7.00023015f) >= 7.00023015f);
}

//! Operator += between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_PlusEqual_Vector)
{
	/// The result vector.
	LG_Vector2D VectorResult(7.1f, 2.2f);
	/// The result vector between the first vector plus the second vector.
	VectorResult += LG_Vector2D(3.6f, 4.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2D(10.7f, 6.7f));
}

//! Operator -= between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_MinusEqual_Vector)
{
	/// The result vector.
	LG_Vector2D VectorResult(2.6f, 2.2f);
	/// The result vector between the first vector minus the second vector.
	VectorResult -= LG_Vector2D(4.6f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(-2.0f, 0.7f), LG_Math::DELTA));
}

//! Operator *= between 1 Vector and 1 number Test.
TEST(Vector2D_Operator, Vector_TimesEqual_Float)
{
	/// The result vector.
	LG_Vector2D VectorResult(3.50000000f, 6.70000000f);
	/// The result vector between the first vector times the float value.
	VectorResult *= 3.00000000f;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(10.5f, 20.1f), LG_Math::DELTA));
}

//! Operator *= between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_TimesEqual_Vector)
{
	/// The result vector.
	LG_Vector2D VectorResult(3.5f, 6.7f);
	/// The result vector between the first vector times the second vector.
	VectorResult *= LG_Vector2D(2.2f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(7.7f, 10.05f), LG_Math::DELTA));
}

//! Operator /= between 1 Vector and 1 number Test.
TEST(Vector2D_Operator, Vector_DivideEqualBy_Float)
{
	/// The result vector.
	LG_Vector2D VectorResult(3.5f, 6.7f);
	/// The result vector between the first vector divided by the float value.
	VectorResult /= 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(1.16666f, 2.23333f), LG_Math::DELTA));
}

//! Operator /= between 2 Vectors Test.
TEST(Vector2D_Operator, Vector_DivideEqualBy_Vector)
{
	/// The result vector.
	LG_Vector2D VectorResult(3.5f, 6.7f);
	/// The result vector between the first vector divided by the second vector.
	VectorResult /= LG_Vector2D(2.2f, 1.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector2D(1.59090f, 4.46666f), LG_Math::DELTA));
}

///************************************************************************/
///*                     Utilities_Vector2DI_UnitTest                      */
///************************************************************************/

//! Magnitude Function Test.
TEST(Vector2DI_Function, Magnitude_)
{
	/// The Vector that we want to obtain its magnitude.
	LG_Vector2DI Test_2D(0, 5);
	/// If the magnitud of the vector is equal to 5 return true, otherwise false. 
	EXPECT_TRUE(Test_2D.Magnitude() == 5);
}

//! DotProduct Function Test.
TEST(Vector2DI_Function, DotProduct_)
{
	/// The first vector for the dot product.
	LG_Vector2DI VectorA(-6, 8);
	/// The second vector for the dot product.
	LG_Vector2DI VectorB(5, 12);
	/// IF fesult is equal to 66 return true, otherwise false.
	EXPECT_TRUE(VectorA.Dot(VectorB) == 66);
}

//! Normalize Function Test.
TEST(Vector2DI_Function, Normalize_)
{
	/// The Vector that we want to normalize.
	LG_Vector2DI Test_2D(0, 1);
	/// If the magnitude of the normalized vector its between 1 and 0 return true, otherwise false. 
	EXPECT_TRUE(Test_2D.Normalize() <= 1 && Test_2D.Normalize() >= 0);
}

//! Static Magnitude Function Test.
TEST(Vector2DI_Function, StaticMagnitude)
{
	/// If the magnitud of the vector is equal to 5 return true, otherwise false. 
	EXPECT_TRUE(LG_Vector2DI::Magnitude(LG_Vector2DI(0, 5)) == 5);
}

//! Static DotProduct Function Test.
TEST(Vector2DI_Function, StaticDotProduct)
{
	/// IF result is equal to 66 return true, otherwise false.
	EXPECT_TRUE(LG_Vector2DI::Dot(LG_Vector2DI(-6, 8), LG_Vector2DI(5, 12)) == 66);
}

//! Static Normalize Function Test.
TEST(Vector2DI_Function, StaticNormalize)
{
	/// If the magnitude of the normalized vector its between 1 and 0 return true, otherwise false. 
	EXPECT_TRUE(LG_Vector2DI::Normalize(LG_Vector2DI(0, 1)) <= 1 && LG_Vector2DI::Normalize(LG_Vector2DI(0, 1)) >= 0);
}

//! Operator + between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_Plus_Vector)
{
	/// The result vector between the first vector plus the second vector.
	LG_Vector2DI VectorResult = LG_Vector2DI(7, 2) + LG_Vector2DI(3, 4);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(10, 6));
}

//! Operator - between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_Minus_Vector)
{
	/// The result vector between the first vector minus the second vector.
	LG_Vector2DI VectorResult = LG_Vector2DI(2, 2) - LG_Vector2DI(4, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(-2, 1));
}

//! Operator * between 1 Vector and 1 number Test.
TEST(Vector2DI_Operator, Vector_Times_Float)
{
	/// The result vector between the first vector times the float value.
	LG_Vector2DI VectorResult = LG_Vector2DI(3, 6) * 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(9, 18));
}

//! Operator * between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_Times_Vector)
{
	/// The result vector between the first vector times the second vector.
	LG_Vector2DI VectorResult = LG_Vector2DI(3, 6) * LG_Vector2DI(2, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(6, 6));
}

//! Operator / between 1 Vector and 1 number Test.
TEST(Vector2DI_Operator, Vector_DividedBy_Float)
{
	/// The result vector between the first vector divided by the float value.
	LG_Vector2DI VectorResult = LG_Vector2DI(3, 6) / 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(1, 2));
}

//! Operator / between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_DividedBy_Vector)
{
	/// The result vector between the first vector divided by the second vector.
	LG_Vector2DI VectorResult = LG_Vector2DI(3, 6) / LG_Vector2DI(3, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(1, 6));
}

//! Operator == between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_Equal_Vector)
{
	/// IF the first vector is the same that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(3, 6) == LG_Vector2DI(3, 6));
}

//! Operator != between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_Different_Vector)
{
	/// IF the first vector is diferent that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(3, 5) != LG_Vector2DI(3, 6));
}

//! Operator < between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_LeesThan_Vector)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(2, 6) < LG_Vector2DI(3, 7));
}

//! Operator < between 1 Vector and 1 Value Test.
TEST(Vector2DI_Operator, Vector_LessThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(3, 6) < 7);
}

//! Operator > between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_GreaterThan_Vector)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2DI(3, 6) > LG_Vector2DI(4, 6));
}

//! Operator > between 1 Vector and 1 Value Test.
TEST(Vector2DI_Operator, Vector_GreaterThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2DI(3, 7) > 7);
}

//! Operator <= between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_LessOrEqualThan_Vector)
{
	/// IF the first vector is less or equal that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(2, 6) <= LG_Vector2DI(3, 6));
}

//! Operator <= between 1 Vector and 1 Value Test.
TEST(Vector2DI_Operator, Vector_LessOrEqualThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector2DI(3, 7) <= 7);
}

//! Operator >= between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_GreaterOrEqualThan_Vector)
{
	/// IF the first vector is greater or equal that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2DI(3, 6) >= LG_Vector2DI(4, 6));
}

//! Operator >= between 1 Vector and 1 Value Test.
TEST(Vector2DI_Operator, Vector_GreaterOrEqualThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector2DI(3, 7) >= 7);
}

//! Operator += between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_PlusEqual_Vector)
{
	/// The result vector.
	LG_Vector2DI VectorResult(7, 2);
	/// The result vector between the first vector plus the second vector.
	VectorResult += LG_Vector2DI(3, 4);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(10, 6));
}

//! Operator -= between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_MinusEqual_Vector)
{
	/// The result vector.
	LG_Vector2DI VectorResult(2, 2);
	/// The result vector between the first vector minus the second vector.
	VectorResult -= LG_Vector2DI(4, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(-2, 1));
}

//! Operator *= between 1 Vector and 1 number Test.
TEST(Vector2DI_Operator, Vector_TimesEqual_Float)
{
	/// The result vector.
	LG_Vector2DI VectorResult(3, 6);
	/// The result vector between the first vector times the float value.
	VectorResult *= 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(9, 18));
}

//! Operator *= between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_TimesEqual_Vector)
{
	/// The result vector.
	LG_Vector2DI VectorResult(3, 6);
	/// The result vector between the first vector times the second vector.
	VectorResult *= LG_Vector2DI(2, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(6, 6));
}

//! Operator /= between 1 Vector and 1 number Test.
TEST(Vector2DI_Operator, Vector_DivideEqualBy_Float)
{
	/// The result vector.
	LG_Vector2DI VectorResult(3, 6);
	/// The result vector between the first vector divided by the float value.
	VectorResult /= 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(1, 2));
}

//! Operator /= between 2 Vectors Test.
TEST(Vector2DI_Operator, Vector_DivideEqualBy_Vector)
{
	/// The result vector.
	LG_Vector2DI VectorResult(3, 6);
	/// The result vector between the first vector divided by the second vector.
	VectorResult /= LG_Vector2DI(3, 1);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector2DI(1, 6));
}

///************************************************************************/
///*                     Utilities_Vector3D_UnitTest                      */
///************************************************************************/

TEST(Utilities_Vector3D, Magnitude_Function)
{
	LG_Vector3D V(0.f, 5.f, 0.f);
	EXPECT_TRUE(V.Magnitude() == 5.0f);
}

TEST(Utilities_Vector3D, StaticMagnitude_Function)
{
	LG_Vector3D V(0.f, 5.f, 0.f);
	float fMAg = LG_Vector3D::Magnitude(V);
	EXPECT_TRUE(fMAg == 5.0f);
}

TEST(Utilities_Vector3D, DotProduct_Function)
{
	LG_Vector3D V1(1.f, 2.f, 3.f);
	LG_Vector3D V2(6.f, 7.f, 8.f);
	EXPECT_TRUE(V1.Dot(V2) == 44.f);
}

TEST(Utilities_Vector3D, StaitcDotProduct_Function)
{
	LG_Vector3D V1(1.f, 2.f, 3.f);
	LG_Vector3D V2(6.f, 7.f, 8.f);
	EXPECT_TRUE(LG_Vector3D::Dot(V1, V2) == 44.f);
}

TEST(Utilities_Vector3D, CrossProduct_Function)
{
	LG_Vector3D V1(2.f, 1.f, -1.f);
	LG_Vector3D V2(-3.f, 4.f, 1.f);
	EXPECT_TRUE(V1.Cross3(V2) == LG_Vector3D(-5.f, -1.f, -11.f));
}

TEST(Utilities_Vector3D, StaticCrossProduct_Function)
{
	LG_Vector3D V1(2.f, 1.f, -1.f);
	LG_Vector3D V2(-3.f, 4.f, 1.f);
	EXPECT_TRUE(LG_Vector3D::Cross3(V1, V2) == LG_Vector3D(5.f, 1.f, 11.f));
}

TEST(Utilities_Vector3D, Normalize_Function)
{
	LG_Vector3D V(3.f, 1.f, 2.f);
	EXPECT_TRUE(V.Normalize() == LG_Vector3D(0.801783681, 0.267261237, 0.534522474));
}

TEST(Utilities_Vector3D, StaticNormalize_Function)
{
	LG_Vector3D V(3.f, 1.f, 2.f);
	EXPECT_TRUE(LG_Vector3D::Normalize(V) == LG_Vector3D(0.801783681, 0.267261237, 0.534522474));
}

TEST(Utilities_Vector3D, Equals_Function)
{
	LG_Vector3D V1(3.f, 1.f, 2.f);
	LG_Vector3D V2(3.f, 1.f, 2.f);
	EXPECT_TRUE(V1.Equals(V2, LG_Math::DELTA));
}

//! Operator + between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_Plus_Vector)
{
	/// The result vector between the first vector plus the second vector.
	LG_Vector3D VectorResult = LG_Vector3D(7.1f, 2.2f, 1.0f) + LG_Vector3D(3.6f, 4.5f, 2.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector3D(10.7f, 6.7f, 3.5f));
}

//! Operator - between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_Minus_Vector)
{
	/// The result vector between the first vector minus the second vector.
	LG_Vector3D VectorResult = LG_Vector3D(2.6f, 2.2f, 1.0f) - LG_Vector3D(4.6f, 1.5f, 2.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(-2.0f, 0.7f, -1.5f), LG_Math::DELTA));
}

//! Operator * between 1 Vector and 1 number Test.
TEST(Vector3D_Operator, Vector_Times_Float)
{
	/// The result vector between the first vector times the float value.
	LG_Vector3D VectorResult = LG_Vector3D(3.5f, 6.7f, 2.0f) * 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(10.5f, 20.1f, 6.0f), LG_Math::DELTA));
}

//! Operator * between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_Times_Vector)
{
	/// The result vector between the first vector times the second vector.
	LG_Vector3D VectorResult = LG_Vector3D(3.5f, 6.7f, 5.0f) * LG_Vector3D(2.2f, 1.5f, 5.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(7.7f, 10.05f, 25.0f), LG_Math::DELTA));
}

//! Operator / between 1 Vector and 1 number Test.
TEST(Vector3D_Operator, Vector_DividedBy_Float)
{
	/// The result vector between the first vector divided by the float value.
	LG_Vector3D VectorResult = LG_Vector3D(3.5f, 6.7f, 3.0f) / 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(1.16666f, 2.23333f, 1.0f), LG_Math::DELTA));
}

//! Operator / between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_DividedBy_Vector)
{
	/// The result vector between the first vector divided by the second vector.
	LG_Vector3D VectorResult = LG_Vector3D(3.5f, 6.7f, 25.0f) / LG_Vector3D(2.2f, 1.5f, 5.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(1.59090f, 4.46666f, 5.0f), LG_Math::DELTA));
}

//! Operator == between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_Equal_Vector)
{
	/// IF the first vector is the same that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000000f, 6.70000000f, 6.70000000f) == LG_Vector3D(3.50000000f, 6.70000000f, 6.70000000f));
}

//! Operator != between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_Different_Vector)
{
	/// IF the first vector is diferent that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000500f, 6.70000000f, 6.70000000f) != LG_Vector3D(3.50000000f, 6.70000001f, 6.70000000f));
}

//! Operator < between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_LeesThan_Vector)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000100f, 6.70000100f, 6.70000100f) < LG_Vector3D(3.50010000f, 6.70100000f, 6.70100000f));
}

//! Operator < between 1 Vector and 1 Value Test.
TEST(Vector3D_Operator, Vector_LessThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000100f, 6.70000100f, 6.70000000f) < 7.00023015f);
}

//! Operator > between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_GreaterThan_Vector)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector3D(3.50000100f, 6.70000100f, 6.70000100f) > LG_Vector3D(3.50010000f, 6.70100000f, 6.70100000f));
}

//! Operator > between 1 Vector and 1 Value Test.
TEST(Vector3D_Operator, Vector_GreaterThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector3D(3.50000100f, 6.70000100f, 6.70000000f) > 7.00023015f);
}

//! Operator <= between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_LessOrEqualThan_Vector)
{
	/// IF the first vector is less or equal that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000100f, 6.70100000f, 5.01000000f) <= LG_Vector3D(3.50010000f, 6.70100000f, 5.10000000f));
}

//! Operator <= between 1 Vector and 1 Value Test.
TEST(Vector3D_Operator, Vector_LessOrEqualThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector3D(3.50000100f, 7.00023015f, 5.00000000f) <= 7.00023015f);
}

//! Operator >= between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_GreaterOrEqualThan_Vector)
{
	/// IF the first vector is greater or equal that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector3D(3.50000100f, 6.70100000f, 5.01000000f) >= LG_Vector3D(3.50010000f, 6.70100000f, 5.00000100f));
}

//! Operator >= between 1 Vector and 1 Value Test.
TEST(Vector3D_Operator, Vector_GreaterOrEqualThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector3D(3.50000100f, 7.00023015f, 5.00000000f) >= 7.00023015f);
}

//! Operator += between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_PlusEqual_Vector)
{
	/// The result vector.
	LG_Vector3D VectorResult(7.1f, 2.2f, 5.0f);
	/// The result vector between the first vector plus the second vector.
	VectorResult += LG_Vector3D(3.6f, 4.5f, 5.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector3D(10.7f, 6.7f, 10.0f));
}

//! Operator -= between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_MinusEqual_Vector)
{
	/// The result vector.
	LG_Vector3D VectorResult(2.6f, 2.2f, 5.0f);
	/// The result vector between the first vector minus the second vector.
	VectorResult -= LG_Vector3D(4.6f, 1.5f, 5.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(-2.0f, 0.7f, 0.0f), LG_Math::DELTA));
}

//! Operator *= between 1 Vector and 1 number Test.
TEST(Vector3D_Operator, Vector_TimesEqual_Float)
{
	/// The result vector.
	LG_Vector3D VectorResult(3.50000000f, 6.70000000f, 2.00000000f);
	/// The result vector between the first vector times the float value.
	VectorResult *= 3.00000000f;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(10.5f, 20.1f, 6.0f), LG_Math::DELTA));
}

//! Operator *= between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_TimesEqual_Vector)
{
	/// The result vector.
	LG_Vector3D VectorResult(3.5f, 6.7f, 2.0f);
	/// The result vector between the first vector times the second vector.
	VectorResult *= LG_Vector3D(2.2f, 1.5f, 3.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(7.7f, 10.05f, 6.0f), LG_Math::DELTA));
}

//! Operator /= between 1 Vector and 1 number Test.
TEST(Vector3D_Operator, Vector_DivideEqualBy_Float)
{
	/// The result vector.
	LG_Vector3D VectorResult(3.5f, 6.7f, 6.0f);
	/// The result vector between the first vector divided by the float value.
	VectorResult /= 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(1.16666f, 2.23333f, 2.0f), LG_Math::DELTA));
}

//! Operator /= between 2 Vectors Test.
TEST(Vector3D_Operator, Vector_DivideEqualBy_Vector)
{
	/// The result vector.
	LG_Vector3D VectorResult(3.5f, 6.7f, 6.0f);
	/// The result vector between the first vector divided by the second vector.
	VectorResult /= LG_Vector3D(2.2f, 1.5f, 2.0f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector3D(1.59090f, 4.46666f, 3.0f), LG_Math::DELTA));
}

///************************************************************************/
///*                     Utilities_Vector4D_UnitTest                      */
///************************************************************************/


TEST(Utilities_Vector4D, Magnitude_Function)
{
	LG_Vector4D V(0.f, 5.f, 0.f, 0.f);
	EXPECT_TRUE(V.Magnitude() == 5.0f);
}

TEST(Utilities_Vector4D, StaticMagnitude_Function)
{
	LG_Vector4D V(0.f, 5.f, 0.f, 0.f);
	float fMAg = LG_Vector4D::Magnitude(V);
	EXPECT_TRUE(fMAg == 5.0f);
}

TEST(Utilities_Vector4D, DotProduct_Function)
{
	LG_Vector4D V1(1.f, 2.f, 3.f, 0.f);
	LG_Vector4D V2(6.f, 7.f, 8.f, 0.f);
	EXPECT_TRUE(V1.Dot(V2) == 44.f);
}

TEST(Utilities_Vector4D, StaitcDotProduct_Function)
{
	LG_Vector4D V1(1.f, 2.f, 3.f, 0.f);
	LG_Vector4D V2(6.f, 7.f, 8.f, 0.f);
	EXPECT_TRUE(LG_Vector4D::Dot(V1, V2) == 44.f);
}

TEST(Utilities_Vector4D, CrossProduct_Function)
{
	LG_Vector4D V1(2.f, 1.f, -1.f, 10.f);
	LG_Vector4D V2(-3.f, 4.f, 1.f, 2.f);
	EXPECT_TRUE(V1.Cross(V2) == LG_Vector4D(5.f, 1.f, 11.f, 0.f));
}

TEST(Utilities_Vector4D, StaticCrossProduct_Function)
{
	LG_Vector4D V1(2.f, 1.f, -1.f, 0.f);
	LG_Vector4D V2(-3.f, 4.f, 1.f, 0.f);
	EXPECT_TRUE(LG_Vector4D::Cross(V1, V2) == LG_Vector4D(5.f, 1.f, 11.f, 0.f));
}

TEST(Utilities_Vector4D, Normalize_Function)
{
	LG_Vector4D V(3.f, 1.f, 2.f, 0.f);
	V.Normalize();
	EXPECT_TRUE(V == LG_Vector4D(0.801783681, 0.267261237, 0.534522474, 0.f));
}

TEST(Utilities_Vector4D, StaticNormalize_Function)
{
	LG_Vector4D V(3.f, 1.f, 2.f, 0.f);
	EXPECT_TRUE(LG_Vector4D::Normalize(V) == LG_Vector4D(0.801783681, 0.267261237, 0.534522474, 0.f));
}

TEST(Utilities_Vector4D, Equals_Function)
{
	LG_Vector4D V1(3.f, 1.f, 2.f, 3.f);
	LG_Vector4D V2(3.f, 1.f, 2.f, 3.f);
	EXPECT_TRUE(V1.Equals(V2, LG_Math::DELTA));
}

//! Operator + between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_Plus_Vector)
{
	/// The result vector between the first vector plus the second vector.
	LG_Vector4D VectorResult = LG_Vector4D(7.1f, 2.2f, 1.0f, 2.3f) + LG_Vector4D(3.6f, 4.5f, 2.5f, 5.5f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector4D(10.7f, 6.7f, 3.5f, 7.8f));
}

//! Operator - between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_Minus_Vector)
{
	/// The result vector between the first vector minus the second vector.
	LG_Vector4D VectorResult = LG_Vector4D(2.6f, 2.2f, 1.0f, 5.f) - LG_Vector4D(4.6f, 1.5f, 2.5f, 4.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(-2.0f, 0.7f, -1.5f, 1.f), LG_Math::DELTA));
}

//! Operator * between 1 Vector and 1 number Test.
TEST(Vector4D_Operator, Vector_Times_Float)
{
	/// The result vector between the first vector times the float value.
	LG_Vector4D VectorResult = LG_Vector4D(3.5f, 6.7f, 2.0f, 6.f) * 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(10.5f, 20.1f, 6.0f, 18.f), LG_Math::DELTA));
}

//! Operator * between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_Times_Vector)
{
	/// The result vector between the first vector times the second vector.
	LG_Vector4D VectorResult = LG_Vector4D(3.5f, 6.7f, 5.0f, 4.f) * LG_Vector4D(2.2f, 1.5f, 5.0f, 7.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(7.7f, 10.05f, 25.0f, 28.f), LG_Math::DELTA));
}

//! operator / between 1 vector and 1 number test.
TEST(Vector4D_Operator, Vector_DividedBy_Float)
{
	/// the result vector between the first vector divided by the float value.
	LG_Vector4D VectorRes = LG_Vector4D(3.5f, 6.7f, 3.0f, 6.f) / 3;
	/// if the result vector is the same that the other vector.
	EXPECT_TRUE(VectorRes.Equals(LG_Vector4D(1.16666f, 2.23333f, 1.0f, 2.f), LG_Math::DELTA));
}

//! Operator / between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_DividedBy_Vector)
{
	/// The result vector between the first vector divided by the second vector.
	LG_Vector4D VectorResult = LG_Vector4D(3.5f, 6.7f, 25.0f, 36.f) / LG_Vector4D(2.2f, 1.5f, 5.0f, 6.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(1.59090f, 4.46666f, 5.0f, 6.f), LG_Math::DELTA));
}

//! Operator == between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_Equal_Vector)
{
	/// IF the first vector is the same that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000000f, 6.70000000f, 6.70000000f, 5.5f) == LG_Vector4D(3.50000000f, 6.70000000f, 6.70000000f, 5.5f));
}

//! Operator != between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_Different_Vector)
{
	/// IF the first vector is different that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000500f, 6.70000000f, 6.70000000f, 5.5f) != LG_Vector4D(3.50000000f, 6.70000001f, 6.70000000f, 8.f));
}

//! Operator < between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_LeesThan_Vector)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000100f, 6.70000100f, 6.70000100f, 5.3f) < LG_Vector4D(3.50010000f, 6.70100000f, 6.70100000f, 5.4f));
}

//! Operator < between 1 Vector and 1 Value Test.
TEST(Vector4D_Operator, Vector_LessThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000100f, 6.70000100f, 6.70000000f, 5.5f) < 7.00023015f);
}

//! Operator > between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_GreaterThan_Vector)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector4D(3.50000100f, 6.70000100f, 6.70000100f, 5.5f) > LG_Vector4D(3.50010000f, 6.70100000f, 6.70100000f, 5.56));
}

//! Operator > between 1 Vector and 1 Value Test.
TEST(Vector4D_Operator, Vector_GreaterThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector4D(3.50000100f, 6.70000100f, 6.70000000f, 5.5f) > 7.00023015f);
}

//! Operator <= between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_LessOrEqualThan_Vector)
{
	/// IF the first vector is less or equal that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000100f, 6.70100000f, 5.01000000f, 5.5f) <= LG_Vector4D(3.50010000f, 6.70100000f, 5.10000000f, 5.5f));
}

//! Operator <= between 1 Vector and 1 Value Test.
TEST(Vector4D_Operator, Vector_LessOrEqualThan_Float)
{
	/// IF the first vector is less that the second vector return true, otherwise return false.
	EXPECT_TRUE(LG_Vector4D(3.50000100f, 7.00023015f, 5.00000000f, 7.00023015f) <= 7.00023015f);
}

//! Operator >= between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_GreaterOrEqualThan_Vector)
{
	/// IF the first vector is greater or equal that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector4D(3.50000100f, 6.70100000f, 5.01000000f, 5.5f) >= LG_Vector4D(3.50010000f, 6.70100000f, 5.00000100f, 5.5f));
}

//! Operator >= between 1 Vector and 1 Value Test.
TEST(Vector4D_Operator, Vector_GreaterOrEqualThan_Float)
{
	/// IF the first vector is greater that the second vector return false, otherwise return true.
	EXPECT_FALSE(LG_Vector4D(3.50000100f, 7.00023015f, 5.00000000f, 7.0f) >= 7.00023015f);
}

//! Operator += between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_PlusEqual_Vector)
{
	/// The result vector.
	LG_Vector4D VectorResult(7.1f, 2.2f, 5.0f, 20.f);
	/// The result vector between the first vector plus the second vector.
	VectorResult += LG_Vector4D(3.6f, 4.5f, 5.0f, 10.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult == LG_Vector4D(10.7f, 6.7f, 10.0f, 30.f));
}

//! Operator -= between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_MinusEqual_Vector)
{
	/// The result vector.
	LG_Vector4D VectorResult(2.6f, 2.2f, 5.0f, 20.0f);
	/// The result vector between the first vector minus the second vector.
	VectorResult -= LG_Vector4D(4.6f, 1.5f, 5.0f, 10.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(-2.0f, 0.7f, 0.0f, 10.f), LG_Math::DELTA));
}

//! Operator *= between 1 Vector and 1 number Test.
TEST(Vector4D_Operator, Vector_TimesEqual_Float)
{
	/// The result vector.
	LG_Vector4D VectorResult(3.50000000f, 6.70000000f, 2.00000000f, 10.f);
	/// The result vector between the first vector times the float value.
	VectorResult *= 3.00000000f;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(10.5f, 20.1f, 6.0f, 30.f), LG_Math::DELTA));
}

//! Operator *= between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_TimesEqual_Vector)
{
	/// The result vector.
	LG_Vector4D VectorResult(3.5f, 6.7f, 2.0f, 5.f);
	/// The result vector between the first vector times the second vector.
	VectorResult *= LG_Vector4D(2.2f, 1.5f, 3.0f, 5.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(7.7f, 10.05f, 6.0f, 25.f), LG_Math::DELTA));
}

//! Operator /= between 1 Vector and 1 number Test.
TEST(Vector4D_Operator, Vector_DivideEqualBy_Float)
{
	/// The result vector.
	LG_Vector4D VectorResult(3.5f, 6.7f, 6.0f, 36.f);
	/// The result vector between the first vector divided by the float value.
	VectorResult /= 3;
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(1.16666f, 2.23333f, 2.0f, 12.f), LG_Math::DELTA));
}

//! Operator /= between 2 Vectors Test.
TEST(Vector4D_Operator, Vector_DivideEqualBy_Vector)
{
	/// The result vector.
	LG_Vector4D VectorResult(3.5f, 6.7f, 6.0f, 10.f);
	/// The result vector between the first vector divided by the second vector.
	VectorResult /= LG_Vector4D(2.2f, 1.5f, 2.0f, 10.f);
	/// If the result vector is the same that the OtherVector.
	EXPECT_TRUE(VectorResult.Equals(LG_Vector4D(1.59090f, 4.46666f, 3.0f, 1.f), LG_Math::DELTA));
}

///************************************************************************/
///*                     Utilities_Matrices_UnitTest                      */
///************************************************************************/

TEST(Utilities_Matrix3D, Zero_Function)
{
	///Zero function test.
	LG_Matrix3D M = LG_Matrix3D::Zero();

	/// Iterate through the matrix.
	for (int32 i = 0; i < 9; ++i)
	{
		/// See that the matrix has only got values of 0.
		EXPECT_TRUE(M.LikeArray[i] == 0);
	}
}

TEST(Utilities_Matrix3D, Identity_Function)
{
	/// Identity method test.
	LG_Matrix3D M = LG_Matrix3D::Identity();
	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 3; ++j)
		{
			/// Check the identity values.
			if (i == j)
			{
				EXPECT_TRUE(M.LikeMatrix[i][j] == 1);
			}
			else
			{
				///Check every other value.
				EXPECT_TRUE(M.LikeMatrix[i][j] == 0);
			}
		}
	}
}

TEST(Utilities_Matrix3D, Inverse_Function)
{
	/// Inverse method test. The Adjunct, Transpose and Determinant functions are inside of Inverse
	/// The fact of it working correctly, means that those are correct.
	LG_Matrix3D M =
	{
		1.0f, -1.0f, 2.0f,
		-2.0f, 0.0f, 4.0f,
		0.0f, -2.0f, 7.0f
	};

	LG_Matrix3D InverseM = M;
	InverseM.Inverse();
	EXPECT_TRUE(M * InverseM == LG_Matrix3D::Identity());
}

/// Test init zero of the matrix 4D
TEST(Utilities_Matrix4D, Zero_Function)
{
	///Zero function test.
	LG_Matrix4D M4 = LG_Matrix4D::Zero();

	/// Iterate through the matrix.
	for (int32 i = 0; i < 16; ++i)
	{
		/// See that the matrix has only got values of 0.
		EXPECT_TRUE(M4.LikeArray[i] == 0);
	}
}


/// Test the identity of the matrix 4D
TEST(Utilities_Matrix4D, Identity_Function)
{
	/// Identity method test.
	LG_Matrix4D M4 = LG_Matrix4D::Identity();
	for (int32 i = 0; i < 4; ++i)
	{
		for (int32 j = 0; j < 4; ++j)
		{
			///Check the identity values.
			if (i == j)
			{
				EXPECT_TRUE(M4.LikeMatrix[i][j] == 1);
			}
			else
			{
				///Check every other value.
				EXPECT_TRUE(M4.LikeMatrix[i][j] == 0);
			}
		}
	}
	system("Pause");
}
