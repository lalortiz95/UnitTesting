#include "LG_Triangle.h"

namespace LevelGenerator
{
	///************************************************************************/
	///*                            Arista class			                  */
	///************************************************************************/

	//! Default constructor.
	LG_Triangle::LG_Arista::LG_Arista()
	{
		m_pFirstNode = nullptr;
		m_pSecondNode = nullptr;
		m_fDistance = 0.0f;
	}

	//! Parameter constructor.
	LG_Triangle::LG_Arista::LG_Arista(LG_Node* pFirstNode, LG_Node* pSecondNode)
	{
		m_pFirstNode = nullptr;
		m_pSecondNode = nullptr;
		m_fDistance = 0.0f;

		/// We assign the nodes.
		m_pFirstNode = pFirstNode;
		m_pSecondNode = pSecondNode;

		/// Assign the pointer of every node of the arista.
		m_pFirstNode->m_PointerNodes.push_back(m_pSecondNode);
		m_pSecondNode->m_PointerNodes.push_back(m_pFirstNode);

		/// Calculate the magnitude of the arista, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! Default destructor.
	LG_Triangle::LG_Arista::~LG_Arista()
	{
		//Destroy();
	}

	//! This function initialize the variables in the arista class.
	void LG_Triangle::LG_Arista::Init(LG_Node* pFirstNode, LG_Node* pSecondNode)
	{
		bool bNodeIsTheSame = false;
		//Destroy();
		/// We assign the nodes.
		m_pFirstNode = pFirstNode;
		m_pSecondNode = pSecondNode;

		/// Assign the pointer of every node of the arista.
		for (int32 i = 0; i < m_pFirstNode->m_PointerNodes.size(); ++i)
		{
			if (m_pSecondNode == m_pFirstNode->m_PointerNodes[i])
			{
				bNodeIsTheSame = true;
			}
		}
		if (!bNodeIsTheSame)
		{
			m_pFirstNode->m_PointerNodes.push_back(m_pSecondNode);
		}
		bNodeIsTheSame = false;
		/// Assign the pointer of every node of the arista.
		for (int32 i = 0; i < m_pSecondNode->m_PointerNodes.size(); ++i)
		{
			if (m_pFirstNode == m_pSecondNode->m_PointerNodes[i])
			{
				bNodeIsTheSame = true;
			}
		}
		if (!bNodeIsTheSame)
		{
			m_pSecondNode->m_PointerNodes.push_back(m_pFirstNode);
		}

		/// Calculate the magnitude of the arista, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! This function realeases memory.
	void LG_Triangle::LG_Arista::Destroy()
	{
		/// If the pointer is not nullptr.
		if (m_pFirstNode != nullptr)
		{
			/// Call it's destroy function to release memory of it's variables.
			m_pFirstNode->Destroy();
			/// Release memory.
			delete m_pFirstNode;
			/// Reset to nullptr.
			m_pFirstNode = nullptr;
		}

		if (m_pSecondNode != nullptr)
		{
			/// Call it's destroy function to release memory of it's variables.
			m_pSecondNode->Destroy();
			/// Release memory.
			delete m_pSecondNode;
			/// Reset to nullptr.
			m_pSecondNode = nullptr;
		}
		/// Reset the distance of the arista.
		m_fDistance = 0.0f;
	}

	///************************************************************************/
	///*                            Triangle class			                  */
	///************************************************************************/

	//! Default constructor.
	LG_Triangle::LG_Triangle()
	{
		m_bIsChecked = false;
	}

	//! Default destructor.
	LG_Triangle::~LG_Triangle()
	{
		//Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Triangle::Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode)
	{
		//Destroy();

		/// We give an inital value to the triangle's vertices.
		m_pVertices.push_back(pFirstNode);
		m_pVertices.push_back(pSecondNode);
		m_pVertices.push_back(pThirdNode);

		m_Aristas[FIRST_ARISTA].Init(pFirstNode, pSecondNode);
		m_Aristas[SECOND_ARISTA].Init(pFirstNode, pThirdNode);
		m_Aristas[THIRD_ARISTA].Init(pSecondNode, pThirdNode);
	}

	//! This function releases memory and clears the variables.
	void LG_Triangle::Destroy()
	{
		m_bIsChecked = false;
	}

	//! This function tells if a given node is inside of the triangle.
	bool LG_Triangle::IsPointInside(LG_Node* pPointToCompare)
	{
		bool b1, b2, b3;

		b1 = Sign(pPointToCompare, m_pVertices[FIRST_NODE], m_pVertices[SECOND_NODE]) < 0.0f;
		b2 = Sign(pPointToCompare, m_pVertices[SECOND_NODE], m_pVertices[THIRD_NODE]) < 0.0f;
		b3 = Sign(pPointToCompare, m_pVertices[THIRD_NODE], m_pVertices[FIRST_NODE]) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}

	//! Calculates the triangle's circumcentre.
	void LG_Triangle::CalculateCircumcenter()
	{
		
		LG_Vector3D	PerpendicularBisectorAB;
		LG_Vector3D	PerpendicularBisectorBC;
		LG_Vector3D	PerpendicularBisectorCA;

		float fPendienteAB, fPendienteBC, fPendienceCA;
		float fPendientePerpendicualarAB, fPendientePerpendicualarBC, fPendientePerpendicualarCA;
		float fX, fY, fXa, fYa, fXb, fYb, fXc, fYc;
		LG_Vector3D PMab, PMbc, PMca;

		fXa = m_pVertices[FIRST_NODE]->m_Position.X;
		fYa = m_pVertices[FIRST_NODE]->m_Position.Y;

		fXb = m_pVertices[SECOND_NODE]->m_Position.X;
		fYb = m_pVertices[SECOND_NODE]->m_Position.Y;

		fXc = m_pVertices[THIRD_NODE]->m_Position.X;
		fYc = m_pVertices[THIRD_NODE]->m_Position.Y;

		PMab.X = ((fXa + fXb) / 2);
		PMab.Y = ((fYa + fYb) / 2);
		fPendienteAB = ((fYb - fYa) / (fXb - fXa));
	}

	//! Perfroms a cross product between the aristas.
	float LG_Triangle::Sign(LG_Node* pNodeToCompare, LG_Node* pNode1, LG_Node* pNode2)
	{
		return ((pNodeToCompare->m_Position.X - pNode2->m_Position.X) *
			(pNode1->m_Position.Y - pNode2->m_Position.Y)) -
			((pNode1->m_Position.X - pNode2->m_Position.X) *
			(pNodeToCompare->m_Position.Y - pNode2->m_Position.Y));
	}
}