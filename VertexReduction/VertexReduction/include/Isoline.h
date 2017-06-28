#pragma once
#include "PrerequisitesLevelGenerator.h"
#include "Vertex.h"

#include <vector>

namespace LevelGenerator
{
	//!Declaration of CIsoline Class
	class LG_EXPORT CIsoline
	{
	public:
		//!Default constructor and destructor.
		CIsoline();
		~CIsoline();

		void Initialize();
		void Destroy();

		//!Array to store the lines.
		std::vector<CVertex> m_VertexVector;
	};
}

