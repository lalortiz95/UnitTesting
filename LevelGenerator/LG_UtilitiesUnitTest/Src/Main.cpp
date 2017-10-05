#pragma once
#include <LG_Vector2D.h>
#include <LG_Vector2DI.h>
#include <LG_Vector3D.h>
#include <LG_Vector4D.h>
#include <LG_Matrix3D.h>
#include <LG_Matrix4D.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;

TEST(UtilitiesUnitTest, Matrices)
{
	LG_Matrix3D M =
	{
		1.0f, -1.0f, 2.0f,
		-2.0f, 0.0f, 4.0f,
		0.0f, -2.0f, 7.0f
	};
	LG_Matrix3D InverseM = M;
	InverseM.Inverse();
	LG_Matrix3D X = M * InverseM;

	EXPECT_TRUE(M * InverseM == LG_Matrix3D::Identity());

	/// Check that the size of our variables is what it's supposed to be.
	EXPECT_TRUE(sizeof(int8) == 1);
	EXPECT_TRUE(sizeof(int16) == 2);
	EXPECT_TRUE(sizeof(int32) == 4);
	EXPECT_TRUE(sizeof(int64) == 8);
	EXPECT_TRUE(sizeof(int128) == 16);

	EXPECT_TRUE(sizeof(uint8) == 1);
	EXPECT_TRUE(sizeof(uint16) == 2);
	EXPECT_TRUE(sizeof(uint32) == 4);
	EXPECT_TRUE(sizeof(uint64) == 8);
	EXPECT_TRUE(sizeof(uint128) == 16);

	//TODO: hacer el unit test del gauss jordan
	LG_Vector4D Result;
	LG_Matrix4D GaussJ =
	{ 3, 2,-3,-13,
	  4,-3, 6, 7,
	  1, 0,-1,-5,
	  0, 0, 0, 0 };

	GaussJ.GaussJordan(Result);

	GaussJ =
	{ 3, 6,-3,-13,
		4,-3, 6, 7,
		-2, 5,-3,4,
		0, 0, 0, 0 };

	GaussJ.GaussJordan(Result);

	system("pause");
}

TEST(MathUnitTest, Functions)
{
	LG_Math math;

	EXPECT_TRUE(math.Sqrt(25) == 5);
	EXPECT_TRUE(math.InvSqrt(25) == 1.0f / 5);
	EXPECT_TRUE(math.Exp(5) == 148.413162f);
	EXPECT_TRUE(math.Pow(3, 3) == 27);
	EXPECT_TRUE(math.Loge(25) == 3.21887589f);
	//EXPECT_TRUE(math.LogX(25, 5) == 5);
	EXPECT_TRUE(math.Trunc(LG_Math::PI) == 3);
	EXPECT_TRUE(math.TruncFloat(LG_Math::PI) == 3.0f);
	EXPECT_TRUE(math.Floor(LG_Math::PI) == 3);
	EXPECT_TRUE(math.Round(LG_Math::PI) == 3);
	EXPECT_TRUE(math.Ceil(LG_Math::PI) == 4);

	EXPECT_TRUE(math.Sin(LG_Math::PI_HALF) == 1);
	EXPECT_TRUE(math.Cos(LG_Math::PI * 2) == 1);
	EXPECT_TRUE(math.Tan(LG_Math::PI) <= LG_Math::DELTA && math.Tan(LG_Math::PI) >= -LG_Math::DELTA);

	///max
	EXPECT_TRUE(math.Max(5, 2) == 5);
	///mmin 
	EXPECT_TRUE(math.Min(5, 2) == 2);

	///max3
	EXPECT_TRUE(math.Max3(5, 2, 9) == 9);
	///mmin3 
	EXPECT_TRUE(math.Min3(5, 2, 1) == 1);

	system("pause");
}

TEST(VectorsUnitTest, Vectors)
{
	LG_Vector2D vec2D(0, 1);
	EXPECT_TRUE(LG_Vector2D::Dot(LG_Vector2D(-6, 8), LG_Vector2D(5, 12)) == 66);
	EXPECT_TRUE(vec2D.Equals(LG_Vector2D(0, 1), LG_Math::DELTA));
	EXPECT_TRUE(vec2D.Normalize() <= 1 && vec2D.Normalize() >= 0);
	vec2D = { 0, 5 };
	EXPECT_TRUE(vec2D.Magnitude() == 5);

	LG_Vector2DI vec2DI(0, 1);
	EXPECT_TRUE(LG_Vector2DI::Dot(LG_Vector2DI(-6, 8), LG_Vector2DI(5, 12)) == 66);
	EXPECT_TRUE(vec2DI.Equals(LG_Vector2DI(0, 1), 1));
	EXPECT_TRUE(vec2DI.Normalize() <= 1 && vec2D.Normalize() >= 0);
	vec2DI = { 0, 5 };
	EXPECT_TRUE(vec2DI.Magnitude() == 5);

	LG_Vector3D vec3D(0, 1, 666);
	EXPECT_TRUE(LG_Vector3D::Dot(LG_Vector3D(1, 2, 3), LG_Vector3D(6, 7, 8)) == 44);
	EXPECT_TRUE(vec3D.Equals(LG_Vector3D(0, 1, 666), 1));
	EXPECT_TRUE(vec3D.Normalize() <= 1 && vec3D.Normalize() >= 0);
	vec3D = { 0, 5, 0 };
	EXPECT_TRUE(vec3D.Magnitude() == 5);

	LG_Vector4D vec4D(0, 1, 666, 4);
	EXPECT_TRUE(LG_Vector4D::Dot(LG_Vector4D(1, 2, 3, 4), LG_Vector4D(6, 7, 8, 9)) == 80);
	EXPECT_TRUE(vec4D.Equals(LG_Vector4D(0, 1, 666, 4), 1));
	EXPECT_TRUE(LG_Vector4D::Normalize(vec4D) <= 1 && LG_Vector4D::Normalize(vec4D) >= 0);
	vec4D = { 0, 5, 0, 0 };
	EXPECT_TRUE(vec4D.Magnitude() == 5);

	system("pause");
}