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
}