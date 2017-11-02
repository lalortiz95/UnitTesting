
#include "Wrapp_C++.h"

extern "C"
{
	float TestMultiply(float a, float b)
	{
		return a * b;
	}

	float TestDivide(float a, float b)
	{
		if (b == 0) {
			return 0;
			//throw invalid_argument("b cannot be zero!");
		}

		return a / b;
	}

	LG_Node* TestNode()
	{
		LG_Node* pNewNode = new LG_Node();
		return pNewNode;
	}

	void TestPosition(LG_Node& Node, LG_Vector3D Position)
	{
		Node.m_Position = Position;
	}

	LG_Node** TestVectorNodes(LG_Node* pNode)
	{
		LG_Node* pNewNode = new LG_Node();
		pNewNode->m_iID = 1;
		pNode->m_Pointers.push_back(pNewNode);

		pNewNode = new LG_Node();
		pNewNode->m_iID = 2;
		pNode->m_Pointers.push_back(pNewNode);

		LG_Node**  connections = new LG_Node*[pNewNode->m_Pointers.size()];
		// Stores the node's connections in an array of pointers.
		for (int i = 0; i < pNewNode->m_Pointers.size(); i++)
		{
			connections[i] = pNewNode->m_Pointers[i];
		}
		return connections;
	}
}