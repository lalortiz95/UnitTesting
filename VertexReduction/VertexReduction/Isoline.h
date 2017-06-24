#pragma once
#include "Vertex.h"

#include <vector>

//!Declaration of CIsoline Class
class CIsoline
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

