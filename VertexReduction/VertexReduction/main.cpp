#pragma once
#include "Plane.h"
#include "Isoline.h"

//! The Main.
int main()
{
	CPlane Plane;
	CVector3D Position = {-15,80,0};

	Plane.Init(Position, 25, 38);

	//TODO: reducir lineas del isoline.

	return 0;
}