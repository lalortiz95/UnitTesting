#include "LG_DelaunayTriangulation.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_DelaunayTriangulation::LG_DelaunayTriangulation()
	{
		m_pBigTriangle = nullptr;
		m_pTrianglesVector.clear();
		m_pBadTriangles.clear();
	}

	//! Default destructor.
	LG_DelaunayTriangulation::~LG_DelaunayTriangulation()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_DelaunayTriangulation::Init(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> NodesCloud)
	{
		Destroy();

		/// Store in the nodes cloud all of the nodes in the isoline vector.
		for (int32 i = 0; i < NodesCloud.size(); ++i)
		{
			for (int32 j = 0; j < NodesCloud[i].m_NodeVector.size(); ++j)
			{
				NodesCloud[i].m_NodeVector[j].Init();
				m_NodesCloud.push_back(NodesCloud[i].m_NodeVector[j]);
			}
		}

		/// Create a triangle that is outside of the node's cloud.
		CreateBigTriangle(iGridWidth, iGridHeight, GridCenter);
		m_pTrianglesVector.push_back(m_pBigTriangle);

	}
	//! This function releases memory and clears the variables.
	void LG_DelaunayTriangulation::Destroy()
	{
		if (m_pBigTriangle != nullptr)
		{
			m_pBigTriangle->Destroy();
			delete m_pBigTriangle;
			m_pBigTriangle = nullptr;
		}

		if (m_pTrianglesVector.size() != 0)
		{
		}
	}

	//! This function performs the algorithm.
	void LG_DelaunayTriangulation::Run(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> NodesCloud)
	{
		/// Flag to determinate if we should break the first for.
		bool bBreakFirstFor = false;
		/// Initialize the start parameters.
		Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);

		/// 
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			/// If the node is inside of the circumcircle circumference.
			SetTriangleAsBadTriangle(m_NodesCloud[i]);
			/// 
			CreatePolygon();
			///
			CreateNewTriangles(&m_NodesCloud[i]);
		}
		EliminateTriangles();

		
	}

	void LG_DelaunayTriangulation::CheckIfEdgeIsInside(LG_Triangle& IteratingTriangle)
	{
		bool bCanAddEdge = true;
		for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		{
			for (int32 j = 0; j < m_Polygon.m_pEdgeVector.size(); ++j)
			{
				
				if (IteratingTriangle.m_Edges[i].CompareIndex(*m_Polygon.m_pEdgeVector[j]))
				{
					bCanAddEdge = false;
				}
			}
			if (bCanAddEdge)
			{
				m_Polygon.InsertEdgeToVector(&IteratingTriangle.m_Edges[i]);
			}
			else
			{
				bCanAddEdge = true;
			}
		}
	}

	//! This function create a new triangles from the given node.
	void LG_DelaunayTriangulation::CreateNewTriangles(LG_Node* pIteratingNode)
	{
		/// Creates a triangle from the polygon's edges and the iterating node.
			LG_Triangle* pTriangle;
		for (int32 i = 0; i < m_Polygon.m_pEdgeVector.size(); ++i)
		{
			/// create a new triangle from the iterating edge from the polygon
			/// to the iterating node.
			pTriangle = new LG_Triangle();
			pTriangle->Init(m_Polygon.m_pEdgeVector[i]->m_pFirstNode,
				m_Polygon.m_pEdgeVector[i]->m_pSecondNode,
				pIteratingNode);

			/// Adds the triangle to the vector.
			m_pTrianglesVector.push_back(pTriangle);
		}
	}

	//! 
	void LG_DelaunayTriangulation::SetTriangleAsBadTriangle(const LG_Node& IteratingNode)
	{
		int32 iInitialSize = m_pTrianglesVector.size();
		int32 iCount = 0;

		while (iCount < iInitialSize)
		{
			///
			for (Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin(); itt != m_pTrianglesVector.end(); ++itt)
			{

				if (((*itt)->m_NodeIndex[FIRST_INDEX] != IteratingNode.m_iID) &&
					((*itt)->m_NodeIndex[SECOND_INDEX] != IteratingNode.m_iID) &&
					((*itt)->m_NodeIndex[THIRD_INDEX] != IteratingNode.m_iID))
				{
					/// check if the node is inside of the circle.
					if ((*itt)->m_CircumcircleCircumference.IsDotInside(
						IteratingNode.m_Position))
					{
						LG_Triangle* pTriangle = *itt;
						m_pTrianglesVector.erase(itt);
						m_pBadTriangles.push_back(pTriangle);
						iCount++;
						break;
					}
				}
				iCount++;
			}
		}

	}

	//! This function create a big triangle.
	void LG_DelaunayTriangulation::CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter)
	{
		/// X * 2 = the lenght of the triangle's arista. This only works when the grid is a square.
		float AristaSize = float(iWidth * 2);
		int32 iCountNode = 0;

		/// We set the center of the grid to start off.
		LG_Node* pNodePosition1 = new LG_Node();
		LG_Node* pNodePosition2 = new LG_Node();
		LG_Node* pNodePosition3 = new LG_Node();

		pNodePosition1->m_Position = GridCenter;

		/// Substract half the height in the Y axis so that it's at the base of que grid.
		pNodePosition1->m_Position.Y -= iHeight / 2;
		/// Substract half of the size of the arista to the left.
		pNodePosition1->m_Position.X -= AristaSize / 2;
		/// Assign the ID for the node.
		pNodePosition1->m_iID = iCountNode;
		/// Add one to the counter node.
		iCountNode++;


		/// 
		pNodePosition2->m_Position = pNodePosition1->m_Position;
		/// Add the whole size of the arista for the next node.
		pNodePosition2->m_Position.X += AristaSize;
		pNodePosition2->m_Position.Y -= 1;
		/// Assign the ID for the node.
		pNodePosition2->m_iID = iCountNode;
		/// Add one to the counter node.
		iCountNode++;

		/// 
		pNodePosition3->m_Position = pNodePosition2->m_Position;
		pNodePosition3->m_Position.X = GridCenter.X;
		/// Get the last top node.
		pNodePosition3->m_Position.Y += AristaSize + 1;
		/// Assign the ID for the node.
		pNodePosition3->m_iID = iCountNode;
		/// Add one to the counter node.
		iCountNode++;


		m_pBigTriangle = new LG_Triangle();
		m_pBigTriangle->Init(pNodePosition1, pNodePosition2, pNodePosition3);

		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			m_NodesCloud[i].m_iID = iCountNode;
			iCountNode++;
		}

	}

	//! This function deletes all of the triangles shared with the big triangle.
	void LG_DelaunayTriangulation::EliminateTriangles()
	{
		/// We set all of our triangles' flag to false, in order to see which ones are going to be deleted.
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			m_pTrianglesVector[i]->m_bIsChecked = false;
		}

		/// We iterate and change the flag of the ones being deleted.
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			for (int32 j = 0; j < 3; ++j)
			{
				if (m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[FIRST_NODE] ||
					m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[SECOND_NODE] ||
					m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[THIRD_NODE])
				{
					m_pTrianglesVector[i]->m_bIsChecked = true;
					break;
				}
			}
		}

		Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin();
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			if (m_pTrianglesVector[i]->m_bIsChecked)
			{
				///erases the triangle with it's flag set as true.
				m_pTrianglesVector.erase(itt);
				///Initialize again the iterator.
				i = 0;
				itt = m_pTrianglesVector.begin();
			}
			else
			{
				++itt;
			}
		}
	}

	//! This function creates a polygon.
	void LG_DelaunayTriangulation::CreatePolygon()
	{

		bool bCanAddEdge = false;
		//TODO: meter esto al init
		if (m_pBadTriangles.size() == 1)
		{
			for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
			{
				/// The edge that didn't share position is added to the polygon.
				m_Polygon.InsertEdgeToVector(&m_pBadTriangles[0]->m_Edges[i]);
			}
			return;
		}

		for (int32 i = 0; i < m_pBadTriangles.size(); ++i)
		{
			CheckIfEdgeIsInside(*m_pBadTriangles[i]);
		}
	}
}