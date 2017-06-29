#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Node.h"

#include <vector>

namespace LevelGenerator
{
	//!Declaration of LG_Isoline Class
	class LG_MAP_EXPORT LG_Isoline
	{
	public:
		//!Default constructor and destructor.
		LG_Isoline();
		~LG_Isoline();

		void Initialize();
		void Destroy();

		//!Array to store the lines.
		std::vector<LG_Node> m_VertexVector;
	};
}

