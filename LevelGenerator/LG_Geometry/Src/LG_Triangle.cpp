#include "LG_Triangle.h"
#include <LG_Matrix4D.h>

namespace LevelGenerator
{
	///************************************************************************/
	///*                            Edge class			                      */
	///************************************************************************/

	//! Default constructor.
	LG_Triangle::LG_Edge::LG_Edge()
	{
		m_pFirstNode = nullptr;
		m_pSecondNode = nullptr;
		m_fDistance = 0.0f;
	}

	//! Parameter constructor.
	LG_Triangle::LG_Edge::LG_Edge(LG_Node* pFirstNode, LG_Node* pSecondNode, int32& EdgeID)
	{
		m_pFirstNode = nullptr;
		m_pSecondNode = nullptr;
		m_fDistance = 0.0f;

		/// We assign the nodes.
		m_pFirstNode = pFirstNode;
		m_pSecondNode = pSecondNode;
		m_iID = EdgeID;

		/// Assign the pointer of every node of the arista.
		m_pFirstNode->m_PointerNodes.push_back(m_pSecondNode);
		m_pSecondNode->m_PointerNodes.push_back(m_pFirstNode);

		/// Calculate the magnitude of the arista, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! Default destructor.
	LG_Triangle::LG_Edge::~LG_Edge()
	{
		//Destroy();
	}

	//! This function initialize the variables in the edge class.
	void LG_Triangle::LG_Edge::Init(LG_Node* pFirstNode, LG_Node* pSecondNode, int32& EdgeID)
	{
		bool bNodeIsTheSame = false;
		//Destroy();

		/// We assign the nodes.
		m_pFirstNode = pFirstNode;
		m_pSecondNode = pSecondNode;
		m_iID = EdgeID;


		/// Assign the pointer of every node of the edge.
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
			bNodeIsTheSame = false;
		}
		 ///Assign the pointer of every node of the edge.
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

		/// Calculate the magnitude of the edge, and store it.
		LG_Vector3D magnitude = pSecondNode->m_Position - pFirstNode->m_Position;
		m_fDistance = magnitude.Magnitude();
	}

	//! This function realeases memory.
	void LG_Triangle::LG_Edge::Destroy()
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
		/// Reset the distance of the edges.
		m_fDistance = 0.0f;
	}

	bool LG_Triangle::LG_Edge::CompareEdges(LG_Edge * EdgeToCompare)
	{
		/// If both nodes of the edge are the same that the node's of the edge to compare.
		return m_iID == EdgeToCompare->m_iID;
	}

	//! This operator assign the values of the given edge in this edge.
	LG_Triangle::LG_Edge& LG_Triangle::LG_Edge::operator=(const LG_Edge& OtherEdge)
	{
		m_fDistance = OtherEdge.m_fDistance;
		m_pFirstNode = OtherEdge.m_pFirstNode;
		m_pSecondNode = OtherEdge.m_pSecondNode;
		return *this;
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
	void LG_Triangle::Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode, int32& TriangleID, int32& EdgeID)
	{
		//Destroy();

		/// We give an initial value to the triangle's vertex.
		m_pVertices.push_back(pFirstNode);
		m_pVertices.push_back(pSecondNode);
		m_pVertices.push_back(pThirdNode);
		m_iID = TriangleID;
		TriangleID++;

		m_Edges[FIRST_ARISTA].Init(pFirstNode, pSecondNode, EdgeID);
		EdgeID++;
		m_Edges[SECOND_ARISTA].Init(pFirstNode, pThirdNode, EdgeID);
		EdgeID++;
		m_Edges[THIRD_ARISTA].Init(pSecondNode, pThirdNode, EdgeID);
		EdgeID++;

		CalculateCircumcenter();
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
		/// Create a vector 3D to store the middle point between 2 vectors.
		LG_Vector3D	MiddlePoint_AB{ 0,0,0 };
		LG_Vector3D	MiddlePoint_BC{ 0,0,0 };
		LG_Vector3D	MiddlePoint_CA{ 0,0,0 };

		/// Create a variables to store the slope.
		float fSlope_AB, fSlope_BC, fSlope_CA;
		/// Create a variables to store the perpendicular slope.
		float fPerpendicualarSlope_AB, fPerpendicualarSlope_BC, fPerpendicualarSlope_CA;
		/// Create a variables to store the position of every node of the triangle.
		float fXa, fYa, fXb, fYb, fXc, fYc;
		/// Create a final value.
		float fCircumCenterX = 1, fCircumCenterY = 1;
		/// 
		float fB1, fB2, fB3;

		/// We store the positions from the first node.
		fXa = m_pVertices[FIRST_NODE]->m_Position.X;
		fYa = m_pVertices[FIRST_NODE]->m_Position.Y;

		/// We store the positions from the second node.
		fXb = m_pVertices[SECOND_NODE]->m_Position.X;
		fYb = m_pVertices[SECOND_NODE]->m_Position.Y;

		/// We store the positions from the third node.
		fXc = m_pVertices[THIRD_NODE]->m_Position.X;
		fYc = m_pVertices[THIRD_NODE]->m_Position.Y;

		/// We obtain the middle point between 2 node's position.
		MiddlePoint_AB = FindMiddlePoint(*m_pVertices[FIRST_NODE], *m_pVertices[SECOND_NODE]);
		MiddlePoint_BC = FindMiddlePoint(*m_pVertices[SECOND_NODE], *m_pVertices[THIRD_NODE]);
		MiddlePoint_CA = FindMiddlePoint(*m_pVertices[THIRD_NODE], *m_pVertices[FIRST_NODE]);

		/// We obtain the slope value between 2 node's position.
		fSlope_AB = FindSlope(*m_pVertices[FIRST_NODE], *m_pVertices[SECOND_NODE]);
		fSlope_BC = FindSlope(*m_pVertices[SECOND_NODE], *m_pVertices[THIRD_NODE]);
		fSlope_CA = FindSlope(*m_pVertices[THIRD_NODE], *m_pVertices[FIRST_NODE]);

		/// We obtain the perpendicular slope value.
		fPerpendicualarSlope_AB = (-1.0f / fSlope_AB);
		fPerpendicualarSlope_BC = (-1.0f / fSlope_BC);
		fPerpendicualarSlope_CA = (-1.0f / fSlope_CA);
		//TODO: resolver para cuando el slope sea 0 ó inifito.
		// en dado caso, rotar el triangulo para que todas sus aristas tengan una pendiente.
		// calcular dichas pendientes, resolver, y volver a rotar todo en conjunto.

		/// calculates b from y = mx + 'b'
		fB1 = -(fPerpendicualarSlope_AB * MiddlePoint_AB.X) + MiddlePoint_AB.Y;
		fB2 = -(fPerpendicualarSlope_BC * MiddlePoint_BC.X) + MiddlePoint_BC.Y;

		/// This variable is used as the denominator to obtain the intersection between two dots.
		float SlopesSubstraction = fPerpendicualarSlope_BC - fPerpendicualarSlope_AB;

		/// The intersection between two 
		m_Circumcenter.X = (fB1 - fB2) / SlopesSubstraction;
		m_Circumcenter.Y = fPerpendicualarSlope_AB * m_Circumcenter.X + fB1;
		m_Circumcenter.Z = 0;

		/// Generates the triangle's circle.
		GenerateCircle();
	}

	//! This operator compares that 2 triangles are the same.
	bool LG_Triangle::operator==(const LG_Triangle & OtherTriangle) const
	{
		if (m_iID == OtherTriangle.m_iID)
		{
			if (((m_pVertices[FIRST_NODE] == OtherTriangle.m_pVertices[FIRST_NODE]) ||
				(m_pVertices[FIRST_NODE] == OtherTriangle.m_pVertices[SECOND_NODE]) ||
				(m_pVertices[FIRST_NODE] == OtherTriangle.m_pVertices[THIRD_NODE])) &&
				((m_pVertices[SECOND_NODE] == OtherTriangle.m_pVertices[FIRST_NODE]) ||
				(m_pVertices[SECOND_NODE] == OtherTriangle.m_pVertices[SECOND_NODE]) ||
					(m_pVertices[SECOND_NODE] == OtherTriangle.m_pVertices[THIRD_NODE])) &&
					((m_pVertices[THIRD_NODE] == OtherTriangle.m_pVertices[FIRST_NODE]) ||
				(m_pVertices[THIRD_NODE] == OtherTriangle.m_pVertices[SECOND_NODE]) ||
						(m_pVertices[THIRD_NODE] == OtherTriangle.m_pVertices[THIRD_NODE])))
			{
				return true;
			}
			else
			{
				return false;
			}

		}
		return false;
	}

	//! Performs a cross product between the aristas.
	float LG_Triangle::Sign(LG_Node* pNodeToCompare, LG_Node* pNode1, LG_Node* pNode2)
	{
		return ((pNodeToCompare->m_Position.X - pNode2->m_Position.X) *
			(pNode1->m_Position.Y - pNode2->m_Position.Y)) -
			((pNode1->m_Position.X - pNode2->m_Position.X) *
			(pNodeToCompare->m_Position.Y - pNode2->m_Position.Y));
	}

	//! This function find the middle point between 2 position.
	LG_Vector3D LG_Triangle::FindMiddlePoint(LG_Node NodeA, LG_Node NodeB)
	{
		LG_Vector3D MiddlePoint{ 0,0,0 };
		/// We obtain the middle point between two positions.
		MiddlePoint.X = ((NodeA.m_Position.X + NodeB.m_Position.X) / 2);
		MiddlePoint.Y = ((NodeA.m_Position.Y + NodeB.m_Position.Y) / 2);
		/// Returns the middle point.
		return MiddlePoint;
	}

	//! This function find the slope between 2 position.
	float LG_Triangle::FindSlope(LG_Node NodeA, LG_Node NodeB)
	{
		return((NodeB.m_Position.Y - (NodeA.m_Position.Y)) /
			(NodeB.m_Position.X - (NodeA.m_Position.X)));
	}

	//! Generates the triangle's circumcircle circumference.
	void LG_Triangle::GenerateCircle()
	{
		LG_Vector3D RadiusDistance;
		float fRadius = 0;

		/// Calculates the circle's radius.
		RadiusDistance = m_pVertices[0]->m_Position - m_Circumcenter;
		fRadius = RadiusDistance.Magnitude();
		/// Creates the circle.
		m_CircumcircleCircumference.Init(m_Circumcenter, fRadius);
	}
}