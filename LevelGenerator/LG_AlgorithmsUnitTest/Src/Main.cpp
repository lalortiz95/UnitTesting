#pragma once
#include <LG_MarchingSquare.h>
#include <LG_Generate.h>
#include <LG_RDP.h>
#include <time.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;

bool CompareTilesVector(int32 *CorrectTiles, Vector<LG_Tile*> CalculatedTiles)
{
	/// We check that we have the same amount of tiles in both vectors.
	if (9 != CalculatedTiles.size())
	{
		/// If not, we return false.
		return false;
	}

	/// We go through the tiles' vector.
	for (int32 i = 0; i < CalculatedTiles.size(); ++i)
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
	/// The algorithm that unificates the others.
	LG_Generate GenerateAlgorithm;
	/// Call its run.
	GenerateAlgorithm.Run();

	///Initializes the random.
	srand((uint32)time(NULL));
	///The variable used to call marching square functions.
	LG_MarchingSquare MarchingSquare;
	///The variable used to call marching square functions with a given circle.
	LG_MarchingSquare SpecificCase;

	/// A map to work with for our marching square algorithm.
	LG_Grid* pMap = new LG_Grid();
	pMap->Init(20, 12);
	///Call the algorithm with a random amount of random circles.
	MarchingSquare.Run(pMap);
	/// We test that there are tiles inside of the generated circles.
	EXPECT_TRUE(MarchingSquare.m_pMap->m_pListTilesInside.size() > 0);

	/// The position where the circle will spawn.
	LG_Vector3D posToSpawnCircle = { 275, 275, 0 };
	/// This vector stores the nodes that should be inside, we'll compare this with whatever
	/// Marching squares generate.
	int32 CorrectCaseValue[9] = { 2,6,4,3,15,12,1,9,8 };

	/// Call the algorithm with one given circle.
	SpecificCase.Run(2, 10, 10);

	/// We compare that both, the calculated tiles inside, and the ones we know that are inside.
	/// Are the same.

	EXPECT_TRUE(CompareTilesVector(CorrectCaseValue, SpecificCase.m_pMap->m_pListTilesInside));

	/// We generate a isoline.
	LG_Isoline Isoline;
	Isoline.Init();
	Isoline.AddNode(LG_Vector3D(1, 1, 0));
	Isoline.AddNode(LG_Vector3D(2, 2, 0));
	Isoline.AddNode(LG_Vector3D(2, 4, 0));
	Isoline.AddNode(LG_Vector3D(3, 6, 0));
	Isoline.AddNode(LG_Vector3D(4, 5, 0));
	Isoline.AddNode(LG_Vector3D(5, 5, 0));
	Isoline.AddNode(LG_Vector3D(6, 5, 0));
	Isoline.AddNode(LG_Vector3D(7, 5, 0));
	Isoline.AddNode(LG_Vector3D(8, 5, 0));
	Isoline.AddNode(LG_Vector3D(9, 7, 0));
	Isoline.AddNode(LG_Vector3D(9, 9, 0));
	Isoline.AddNode(LG_Vector3D(9, 10, 0));

	LG_RDP RDP;
	RDP.Run(0.3f, Isoline);
	EXPECT_TRUE(RDP.m_FinalIsoline.m_NodeVector.size() == 7);
}

TEST(RDP_Algorithm, IsIsolineReduced)
{
	
}