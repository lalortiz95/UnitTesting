#include "LG_Triangle.h"
#include <LG_Matrix4D.h>

namespace LevelGenerator
{

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

	void LG_Triangle::Init(LG_Edge* pFirstEdge, LG_Edge* pSecondEdge, LG_Edge* pThirdEdge)
	{
		m_pEdges[FIRST_EDGE] = pFirstEdge;
		m_pEdges[SECOND_EDGE] = pSecondEdge;
		m_pEdges[THIRD_EDGE] = pThirdEdge;

		m_pVertices[FIRST_NODE] = pFirstEdge->m_pFirstNode;
		m_pVertices[SECOND_NODE] = pFirstEdge->m_pSecondNode;
		m_pVertices[THIRD_NODE] = pSecondEdge->m_pSecondNode;

		m_NodeIndex[FIRST_INDEX] = m_pVertices[FIRST_NODE]->m_iID;
		m_NodeIndex[SECOND_INDEX] = m_pVertices[SECOND_NODE]->m_iID;
		m_NodeIndex[THIRD_INDEX] = m_pVertices[THIRD_NODE]->m_iID;

		CalculateCircumcenter();
	}

	//! This function initialize all variables of the class.
	void LG_Triangle::Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode)
	{
		//Destroy();

		/// We give an initial value to the triangle's vertex.
		m_pVertices[FIRST_NODE] = pFirstNode;
		m_pVertices[SECOND_NODE] = pSecondNode;
		m_pVertices[THIRD_NODE] = pThirdNode;

		m_NodeIndex[FIRST_INDEX] = pFirstNode->m_iID;
		m_NodeIndex[SECOND_INDEX] = pSecondNode->m_iID;
		m_NodeIndex[THIRD_INDEX] = pThirdNode->m_iID;

		m_pEdges[FIRST_EDGE] = new LG_Edge();
		m_pEdges[SECOND_EDGE] = new LG_Edge();
		m_pEdges[THIRD_EDGE] = new LG_Edge();

		m_pEdges[FIRST_EDGE]->Init(pFirstNode, pSecondNode);
		m_pEdges[SECOND_EDGE]->Init(pFirstNode, pThirdNode);
		m_pEdges[THIRD_EDGE]->Init(pSecondNode, pThirdNode);

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

	//! This function compare if the index of the given triangle are the same.
	bool LG_Triangle::CompareIndex(const LG_Triangle & OtherTriangle)
	{
		return (((m_NodeIndex[FIRST_INDEX] == OtherTriangle.m_NodeIndex[FIRST_INDEX]) ||
			(m_NodeIndex[FIRST_INDEX] == OtherTriangle.m_NodeIndex[SECOND_INDEX]) ||
			(m_NodeIndex[FIRST_INDEX] == OtherTriangle.m_NodeIndex[THIRD_INDEX])) &&
			((m_NodeIndex[SECOND_INDEX] == OtherTriangle.m_NodeIndex[FIRST_INDEX]) ||
			(m_NodeIndex[SECOND_INDEX] == OtherTriangle.m_NodeIndex[SECOND_INDEX]) ||
				(m_NodeIndex[SECOND_INDEX] == OtherTriangle.m_NodeIndex[THIRD_INDEX])) &&
				((m_NodeIndex[THIRD_INDEX] == OtherTriangle.m_NodeIndex[FIRST_INDEX]) ||
			(m_NodeIndex[THIRD_INDEX] == OtherTriangle.m_NodeIndex[SECOND_INDEX]) ||
					(m_NodeIndex[THIRD_INDEX] == OtherTriangle.m_NodeIndex[THIRD_INDEX])));
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

		/*if ((0 == fSlope_AB) || (0 == fSlope_BC) || (0 == fSlope_CA))
		{
			/// Rotate all nodes of the triangle.
			fXa *= fXa * LG_Math::Cos(0.1f) - fYa * LG_Math::Sin(0.1f);
			fYa *= fXa * LG_Math::Sin(0.1f) + fYa * LG_Math::Cos(0.1f);

			fXb *= fXb * LG_Math::Cos(0.1f) - fYb * LG_Math::Sin(0.1f);
			fYb *= fXb * LG_Math::Sin(0.1f) + fYb * LG_Math::Cos(0.1f);

			fXc *= fXc * LG_Math::Cos(0.1f) - fYc * LG_Math::Sin(0.1f);
			fYc *= fXc * LG_Math::Sin(0.1f) + fYc * LG_Math::Cos(0.1f);

			/// Recalculate all variables of the triangle.

			/// We obtain the middle point between 2 node's position.
			MiddlePoint_AB = FindMiddlePoint(LG_Vector2D(fXa, fYa), LG_Vector2D(fXb, fYb));
			MiddlePoint_BC = FindMiddlePoint(LG_Vector2D(fXb, fYb), LG_Vector2D(fXc, fYc));
			MiddlePoint_CA = FindMiddlePoint(LG_Vector2D(fXc, fYc), LG_Vector2D(fXa, fYa));

			fSlope_AB = FindSlope(LG_Vector2D(fXa, fYa), LG_Vector2D(fXb, fYb));
			fSlope_BC = FindSlope(LG_Vector2D(fXb, fYb), LG_Vector2D(fXc, fYc));
			fSlope_CA = FindSlope(LG_Vector2D(fXc, fYc), LG_Vector2D(fXa, fYa));
		}*/

		if (0 == fSlope_AB)
		{
			fPerpendicualarSlope_BC = (-1.0f / fSlope_BC);
			fPerpendicualarSlope_CA = (-1.0f / fSlope_CA);

			/// calculates b from y = mx + 'b'
			fB1 = -(fPerpendicualarSlope_BC * MiddlePoint_BC.X) + MiddlePoint_BC.Y;
			fB2 = -(fPerpendicualarSlope_CA * MiddlePoint_CA.X) + MiddlePoint_CA.Y;

			/// This variable is used as the denominator to obtain the intersection between two dots.
			float SlopesSubstraction = fPerpendicualarSlope_CA - fPerpendicualarSlope_BC;

			LG_Vector3D CirclePosition;

			/// The intersection between two 
			CirclePosition.X = (fB1 - fB2) / SlopesSubstraction;
			CirclePosition.Y = fPerpendicualarSlope_BC * CirclePosition.X + fB1;
			CirclePosition.Z = 0;

			/// Generates the triangle's circle.
			GenerateCircle(CirclePosition);
		}
		else if (0 == fSlope_BC)
		{
			fPerpendicualarSlope_AB = (-1.0f / fSlope_AB);
			fPerpendicualarSlope_CA = (-1.0f / fSlope_CA);

			/// calculates b from y = mx + 'b'
			fB1 = -(fPerpendicualarSlope_AB * MiddlePoint_AB.X) + MiddlePoint_AB.Y;
			fB2 = -(fPerpendicualarSlope_CA * MiddlePoint_CA.X) + MiddlePoint_CA.Y;

			/// This variable is used as the denominator to obtain the intersection between two dots.
			float SlopesSubstraction = fPerpendicualarSlope_CA - fPerpendicualarSlope_AB;

			LG_Vector3D CirclePosition;

			/// The intersection between two 
			CirclePosition.X = (fB1 - fB2) / SlopesSubstraction;
			CirclePosition.Y = fPerpendicualarSlope_AB * CirclePosition.X + fB1;
			CirclePosition.Z = 0;

			/// Generates the triangle's circle.
			GenerateCircle(CirclePosition);
		}
		else if (0 == fSlope_CA)
		{
			fPerpendicualarSlope_AB = (-1.0f / fSlope_AB);
			fPerpendicualarSlope_BC = (-1.0f / fSlope_BC);
			/// calculates b from y = mx + 'b'
			fB1 = -(fPerpendicualarSlope_AB * MiddlePoint_AB.X) + MiddlePoint_AB.Y;
			fB2 = -(fPerpendicualarSlope_BC * MiddlePoint_BC.X) + MiddlePoint_BC.Y;

			/// This variable is used as the denominator to obtain the intersection between two dots.
			float SlopesSubstraction = fPerpendicualarSlope_BC - fPerpendicualarSlope_AB;

			LG_Vector3D CirclePosition;

			/// The intersection between two 
			CirclePosition.X = (fB1 - fB2) / SlopesSubstraction;
			CirclePosition.Y = fPerpendicualarSlope_AB * CirclePosition.X + fB1;
			CirclePosition.Z = 0;

			/// Generates the triangle's circle.
			GenerateCircle(CirclePosition);
		}
		else
		{

			/// We obtain the perpendicular slope value.
			fPerpendicualarSlope_AB = (-1.0f / fSlope_AB);
			fPerpendicualarSlope_BC = (-1.0f / fSlope_BC);
			fPerpendicualarSlope_CA = (-1.0f / fSlope_CA);

			/// calculates b from y = mx + 'b'
			fB1 = -(fPerpendicualarSlope_AB * MiddlePoint_AB.X) + MiddlePoint_AB.Y;
			fB2 = -(fPerpendicualarSlope_BC * MiddlePoint_BC.X) + MiddlePoint_BC.Y;

			/// This variable is used as the denominator to obtain the intersection between two dots.
			float SlopesSubstraction = fPerpendicualarSlope_BC - fPerpendicualarSlope_AB;

			LG_Vector3D CirclePosition;

			/// The intersection between two 
			CirclePosition.X = (fB1 - fB2) / SlopesSubstraction;
			CirclePosition.Y = fPerpendicualarSlope_AB * CirclePosition.X + fB1;
			CirclePosition.Z = 0;

			/// Generates the triangle's circle.
			GenerateCircle(CirclePosition);
		}
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
	LG_Vector3D LG_Triangle::FindMiddlePoint(const LG_Node& NodeA,const LG_Node& NodeB)
	{
		LG_Vector3D MiddlePoint{ 0,0,0 };
		/// We obtain the middle point between two positions.
		MiddlePoint.X = ((NodeA.m_Position.X + NodeB.m_Position.X) / 2);
		MiddlePoint.Y = ((NodeA.m_Position.Y + NodeB.m_Position.Y) / 2);
		/// Returns the middle point.
		return MiddlePoint;
	}

	//! This function find the middle point between 2 position. 
	LG_Vector3D LG_Triangle::FindMiddlePoint(const LG_Vector2D& PositionA, const LG_Vector2D& PositionB)
	{
		LG_Vector3D MiddlePoint{ 0,0,0 };
		/// We obtain the middle point between two positions.
		MiddlePoint.X = ((PositionA.X + PositionB.X) / 2);
		MiddlePoint.Y = ((PositionA.Y + PositionB.Y) / 2);
		/// Returns the middle point.
		return MiddlePoint;
	}

	//! This function find the slope between 2 positions.
	float LG_Triangle::FindSlope(const LG_Node& NodeA,const LG_Node& NodeB)
	{
		return((NodeB.m_Position.Y - (NodeA.m_Position.Y)) /
			(NodeB.m_Position.X - (NodeA.m_Position.X)));
	}

	//! This function find the slope between 2 positions.
	float LG_Triangle::FindSlope(const LG_Vector2D& PositionA, const LG_Vector2D& PositionB)
	{

		return((PositionB.Y - (PositionA.Y)) /
			(PositionB.X - (PositionA.X)));
	}

	//! Generates the triangle's circumcircle circumference.
	void LG_Triangle::GenerateCircle(const LG_Vector3D& Position)
	{
		LG_Vector3D RadiusDistance;
		float fRadius = 0;

		/// Calculates the circle's radius.
		RadiusDistance = m_pVertices[0]->m_Position - Position;
		fRadius = RadiusDistance.Magnitude();
		/// Creates the circle.
		m_CircumcircleCircumference.Init(Position, fRadius);
	}
}