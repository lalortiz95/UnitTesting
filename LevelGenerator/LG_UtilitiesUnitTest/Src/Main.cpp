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