#pragma once
#include "Plane.h"

//! The Main.
int main()
{
	CPlane Plane;
	CVector3D Position = {-15,80,0};

	Plane.Init(Position, 25, 38);

	return 0;
}