
#include "Wrapp_C++.h"

void LG_Node::SetNodeID(int ID)
{
	m_iID = ID;
}
void LG_Node::SetNodeValue(float fValue)
{
	m_fValue = fValue;
}
void LG_Node::SetPosition(LG_Vector3D Position)
{
	m_Position = Position;
}
void LG_Node::SetNodeParentID(int iParentID)
{
	m_pParent->SetNodeID(iParentID);
}
void LG_Node::SetNumNodes(int iNumNodes)
{
	for (int i = 0; i < iNumNodes; ++i)
	{

	}
}

int LG_Node::GetID(int iNodeConnection)
{
	return m_Pointers[iNodeConnection]->m_iID;
}

int LG_Node::GetNodeConnectionsSize()
{
	return m_Pointers.size();
}

int LG_Node::GetNodeID()
{
	return m_iID;
}

float LG_Node::GetNodeValue()
{
	return m_fValue;
}

LG_Vector3D LG_Node::GetNodePosition()
{
	return m_Position;
}

extern "C"
{
	float TestMultiply(float a, float b)
	{
		return a * b;
	}

	float TestGlobalVar()
	{
		//return GetNodeValue();
		return 0.f;
	}

	float TestDivide(float a, float b)
	{
		if (b == 0) {
			return 0;
			//throw invalid_argument("b cannot be zero!");
		}

		return a / b;
	}

	void Start(int iNodeID, float fNodeValue, float NodePosition, int iParentNodeID, int iSizeNodeConections, float* pos)
	{
		LG_Node* gGlobalNode;
		gGlobalNode = new LG_Node();
		gGlobalNode->SetNodeID(iNodeID);
		gGlobalNode->SetNodeValue(fNodeValue);
		//gGlobalNode->SetPosition(NodePosition);
		gGlobalNode->SetNodeParentID(iParentNodeID);
		gGlobalNode->SetNumNodes(iSizeNodeConections);

		pos = &gGlobalNode->m_Position.X;
	}
}


