#pragma once
#include <LG_MarchingSquare.h>
#include <time.h>
#include <gtest/gtest.h>

using namespace LevelGenerator;
int main()
{
	srand((size_t)time(NULL));
	LG_MarchingSquare MarchingSquare;
	MarchingSquare.Run();

	return 0;
}