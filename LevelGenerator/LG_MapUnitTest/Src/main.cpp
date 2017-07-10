#pragma once
#include <LG_Grid.h>
#include <time.h>

using namespace LevelGenerator;
//! The Main.
int main()
{
	srand((size_t)time(NULL));
	LG_Grid Grid2D;

	Grid2D.Init(20, 12);
	Grid2D.Destroy();

	return 0;
}