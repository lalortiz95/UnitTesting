#pragma once
#include <LG_MarchingSquare.h>
#include <time.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;

bool CompareTilesVector(int *CorrectTiles, std::vector<LG_Tile*> CalculatedTiles)
{
	/// We check that we have the same amount of tiles in both vectors.
	if (9 != CalculatedTiles.size())
	{
		/// If not, we return false.
		return false;
	}

	/// We go through the tiles' vector.
	for (int i = 0; i < CalculatedTiles.size(); ++i)
	{
		///If the case is different, we return true.
		if (CorrectTiles[i] != CalculatedTiles[i]->m_iCase)
		{
			return false;
		}
	}

	///After iterating through both lists and veryfing that they had the same cases.
	///we return true. As the 2 vectors are equals.
	return true;
}

TEST(AlgorithmUnitTest, AreTilesInside)
{
	///Initializes the random.
	srand(time(NULL));
	///The variable used to call marching square functions.
	LG_MarchingSquare MarchingSquare;
	///The variable used to call marching square functions with a given circle.
	LG_MarchingSquare SpecificCase;
	///Call the algorithm with a random amount of random circles.
	MarchingSquare.Run();
	/// We test that there are tiles inside of the generated circles.
	EXPECT_TRUE(MarchingSquare.m_pMap->m_pListTilesInside.size() > 0);

	/// The position where the circle will spawn.
	LG_Vector3D posToSpawnCircle = { 275, 275, 0 };
	/// This vector stores the nodes that should be inside, we'll compare this with whatever
	/// Marching squares generate.
	int CorrectCaseValue[9] = { 2,6,4,3,15,12,1,9,8 };

	/// Call the algorithm with one given circle.
	SpecificCase.Run(50, posToSpawnCircle, 10, 10);

	/// We compare that both, the calculated tiles inside, and the ones we know that are inside.
	/// Are the same.
	EXPECT_TRUE(CompareTilesVector(CorrectCaseValue, SpecificCase.m_pMap->m_pListTilesInside));
}