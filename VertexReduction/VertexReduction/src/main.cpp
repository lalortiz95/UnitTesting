#pragma once
#include "Grid.h"

#include <time.h>

using namespace LevelGenerator;
//! The Main.
int main()
{
	srand((size_t)time(NULL));
	CGrid Grid2D;

	Grid2D.Init(20, 12);

	Grid2D.MarchingSquare();

	Grid2D.Destroy();
	
	return 0;
}