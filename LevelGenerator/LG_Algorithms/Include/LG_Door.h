#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Vector3D.h>

namespace LevelGenerator
{

	class LG_ALGORITHMS_EXPORT LG_Door
	{
	public:
		LG_Door();
		~LG_Door();

		LG_Vector3D m_FirstPosition;
		LG_Vector3D m_SecondPosition;
	};
}

