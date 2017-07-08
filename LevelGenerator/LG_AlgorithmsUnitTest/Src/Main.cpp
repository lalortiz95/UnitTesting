#pragma once
#include <LG_MarchingSquare.h>
#include <time.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;

TEST(AlgorithmUnitTest, Test1)
{
	srand(time(NULL));
	LG_MarchingSquare MarchingSquare;
	MarchingSquare.Run();
	EXPECT_TRUE(MarchingSquare.m_pMap->m_pListTilesInside.size() > 0);
}