#pragma once
#include <LG_HallwayGeneration.h>
#include <LG_MarchingSquare.h>
#include <LG_Generate.h>
#include <LG_RDP.h>
#include <time.h>

#include <gtest/gtest.h>

using namespace LevelGenerator;

bool CompareTilesVector(int32 *CorrectTiles, Vector<LG_Tile*> CalculatedTiles)
{
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

TEST(HallwayGeneration_Constant, 20_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._20_DEGREES == LG_Math::PI / 9);
}

TEST(HallwayGeneration_Constant, 70_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._70_DEGREES == (LG_Math::PI * 7) / 18);

}

TEST(HallwayGeneration_Constant, 110_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._110_DEGREES == (LG_Math::PI * 11) / 18);

}

TEST(HallwayGeneration_Constant, 160_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._160_DEGREES == (LG_Math::PI * 8) / 9);

}

TEST(HallwayGeneration_Constant, 200_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._200_DEGREES == (LG_Math::PI * 10) / 9);
}

TEST(HallwayGeneration_Constant, 250_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._250_DEGREES == (LG_Math::PI * 25) / 18);

}

TEST(HallwayGeneration_Constant, 290_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._290_DEGREES == (LG_Math::PI * 29) / 18);

}

TEST(HallwayGeneration_Constant, 340_Degrees)
{
	LG_HallwayGeneration TestFunction;
	EXPECT_TRUE(TestFunction._340_DEGREES == (LG_Math::PI * 34) / 18);

}



//TEST(Generate_Algorithm, GenerateCasesFromMS)
//{
//	///Initializes the random.
//	srand((uint32)time(NULL));
//
//	/// The algorithm that unificates the others.
//	LG_Generate GenerateAlgorithm;
//	/// Call its run.
//	GenerateAlgorithm.Run(50, LG_Vector3D(20, 20, 0), LG_Vector3D(70, 70, 0));
//
//	int32 iExpectedCases[47] =
//	{
//		14,4,2,13,8,2,7,11,13,8,2,4,2,7,1,8,2,7,
//		14,4,1,11,2,7,14,4,1,11,3,13,8,1,2,7,13,8,
//		2,7,12,1,11,13,8,1,11,13,8
//	};
//
//	EXPECT_TRUE(CompareTilesVector(iExpectedCases, GenerateAlgorithm.m_TileVector));
//
//	EXPECT_TRUE(GenerateAlgorithm.m_IsolineVector.size() == 3);
//	EXPECT_TRUE(GenerateAlgorithm.m_IsolineVector[0].m_NodeVector.size() == 10);
//	EXPECT_TRUE(GenerateAlgorithm.m_IsolineVector[1].m_NodeVector.size() == 11);
//	EXPECT_TRUE(GenerateAlgorithm.m_IsolineVector[2].m_NodeVector.size() == 29);
//
//	EXPECT_TRUE(GenerateAlgorithm.m_FinalIsolineVector[0].m_NodeVector.size() == 4);
//	EXPECT_TRUE(GenerateAlgorithm.m_FinalIsolineVector[1].m_NodeVector.size() == 4);
//	EXPECT_TRUE(GenerateAlgorithm.m_FinalIsolineVector[2].m_NodeVector.size() == 11);
//
//	EXPECT_TRUE(GenerateAlgorithm.m_DT.m_pTrianglesVector.size() == 58);
//}

//TEST(MarchingSquare_Algorithm, CheckCases)
//{
//	///Initializes the random.
//	srand((uint32)time(NULL));
//
//	///The variable used to call marching square functions.
//	LG_MarchingSquare MarchingSquare;
//	///The variable used to call marching square functions with a given circle.
//	LG_MarchingSquare SpecificCase;
//
//	/// A map to work with for our marching square algorithm.
//	LG_Grid* pMap = new LG_Grid();
//	pMap->Init(20, 12);
//	///Call the algorithm with a random amount of random circles.
//	MarchingSquare.Run(pMap);
//	/// We test that there are tiles inside of the generated circles.
//	EXPECT_TRUE(MarchingSquare.m_pTilesWithCase.size() > 0);
//
//	/// The position where the circle will spawn.
//	LG_Vector3D posToSpawnCircle = { 275, 275, 0 };
//	/// This vector stores the nodes that should be inside, we'll compare this with whatever
//	/// Marching squares generate.
//	int32 CorrectCaseValue[9] = { 2,6,4,3,15,12,1,9,8 };
//
//	/// Call the algorithm with one given circle.
//	SpecificCase.Run(10, 10);
//
//	/// We compare that both, the calculated tiles inside, and the ones we know that are inside.
//	/// Are the same.
//
//	EXPECT_TRUE(CompareTilesVector(CorrectCaseValue, SpecificCase.m_pTilesWithCase));
//}

//TEST(RDP_Algorithm, IsIsolineReduced)
//{
//	///Initializes the random.
//	srand((uint32)time(NULL));
//
//	/// We generate a isoline.
//	LG_Isoline Isoline;
//	Isoline.Init();
//	Isoline.AddNodeBack(LG_Vector3D(1, 1, 0));
//	Isoline.AddNodeBack(LG_Vector3D(2, 2, 0));
//	Isoline.AddNodeBack(LG_Vector3D(2, 4, 0));
//	Isoline.AddNodeBack(LG_Vector3D(3, 6, 0));
//	Isoline.AddNodeBack(LG_Vector3D(4, 5, 0));
//	Isoline.AddNodeBack(LG_Vector3D(5, 5, 0));
//	Isoline.AddNodeBack(LG_Vector3D(6, 5, 0));
//	Isoline.AddNodeBack(LG_Vector3D(7, 5, 0));
//	Isoline.AddNodeBack(LG_Vector3D(8, 5, 0));
//	Isoline.AddNodeBack(LG_Vector3D(9, 7, 0));
//	Isoline.AddNodeBack(LG_Vector3D(9, 9, 0));
//	Isoline.AddNodeBack(LG_Vector3D(9, 10, 0));
//
//	LG_RDP RDP;
//	RDP.Run(0.3f, Isoline);
//	EXPECT_TRUE(RDP.m_FinalIsoline.m_NodeVector.size() == 7);
//}