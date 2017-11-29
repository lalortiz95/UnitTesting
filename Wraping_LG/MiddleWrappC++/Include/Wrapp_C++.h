#pragma once
#include <vector>

#define TESTFUNCDLL_API __declspec(dllexport) 

struct LG_Vector3D
{
public:
	float X, Y, Z;

	LG_Vector3D() {}

	LG_Vector3D(float fx, float fy, float fz)
	{
		X = fx;
		Y = fy;
		Z = fz;
	}
};

class LG_Node
{

public:
	LG_Node() {}
	~LG_Node() {}

	int m_iID;
	float m_fValue;
	LG_Vector3D m_Position;
	LG_Node* m_pParent;
	std::vector<LG_Node*> m_Pointers;

	void SetNodeID(int ID);
	void SetNodeValue(float fValue);
	void SetPosition(LG_Vector3D Position);
	void SetNodeParentID(int iParentID);
	void SetNumNodes(int iNumNodes);

	int GetNodeID();
	float GetNodeValue();
	LG_Vector3D GetNodePosition();
	//int GetParentNodeID();

	int GetID(int iNodeConnection);
	int GetNodeConnectionsSize();
};

extern "C"
{
	TESTFUNCDLL_API void Start(int iNodeID, float fNodeValue, float NodePosition, int iParentNodeID, int iSizeNodeConections, float* pos);
	TESTFUNCDLL_API float TestMultiply(float a, float b);
	TESTFUNCDLL_API float TestDivide(float a, float b);
	TESTFUNCDLL_API float TestGlobalVar();
}