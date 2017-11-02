#pragma once
#include <vector>

#define TESTFUNCDLL_API __declspec(dllexport) 

struct LG_Vector3D
{

public:
	float X, Y, Z;

};

class LG_Node
{

public:
	LG_Node() {}
	~LG_Node() {}

	LG_Vector3D m_Position;
	float m_fValue;
	int m_iID;
	LG_Node* m_pParent;
	std::vector<LG_Node*> m_Pointers;

};

extern "C"
{
	TESTFUNCDLL_API float TestMultiply(float a, float b);
	TESTFUNCDLL_API float TestDivide(float a, float b);
	TESTFUNCDLL_API LG_Node* TestNode();
	TESTFUNCDLL_API void TestPosition(LG_Node& pNode , LG_Vector3D Position);
	TESTFUNCDLL_API LG_Node** TestVectorNodes(LG_Node* pNode);
}