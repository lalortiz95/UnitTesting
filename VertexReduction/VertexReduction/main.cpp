#pragma once
#include "Grid.h"

using namespace LevelGenerator;
//! The Main.
int main()
{
	CGrid Grid2D;

	Grid2D.Init(20, 12);
	Grid2D.Destroy();
	
	return 0;
}