#include "LG_DelaunayTriangulation.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_DelaunayTriangulation::LG_DelaunayTriangulation()
	{
		m_pBigTriangle = nullptr;
		m_pTrianglesVector.clear();
		m_pBadTriangles.clear();
		m_iTrianglesCount = 0;
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
		m_pBigTriangle->m_iID = m_iTrianglesCount;
		m_iTrianglesCount++;
		m_pTrianglesVector.push_back(m_pBigTriangle);
		for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		{
			m_pEdgeVector.push_back(m_pBigTriangle->m_pEdges[i]);
		}

	}

	//! Overload Init
	void LG_DelaunayTriangulation::Init(Vector<LG_Node> PointsCloud, LG_Vector3D GridCenter, int32 iGridWidth, int32 iGridHeight)
	{
		Destroy();

		/// Store in the nodes cloud all of the nodes in the isoline vector.
		for (int32 i = 0; i < PointsCloud.size(); ++i)
		{
			PointsCloud[i].Init();
			m_NodesCloud.push_back(PointsCloud[i]);
		}

		/// Create a triangle that is outside of the node's cloud.
		CreateBigTriangle(iGridWidth, iGridHeight, GridCenter);
		m_pBigTriangle->m_iID = m_iTrianglesCount;
		m_iTrianglesCount++;
		m_pTrianglesVector.push_back(m_pBigTriangle);
		for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		{
			m_pEdgeVector.push_back(m_pBigTriangle->m_pEdges[i]);
		}
	}

	//! This function performs the algorithm.
	void LG_DelaunayTriangulation::Run(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> NodesCloud)
	{

		/// Initialize the start parameters.
		Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);

		/// 
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{

			/// If the node is inside of the circumcircle circumference.
			while (SetTriangleAsBadTriangle(m_NodesCloud[i]));

			/// 
			AddEdgesToPolygon();
			///
			CreateNewTriangles(&m_NodesCloud[i]);
			/*for (int32 i = 0; i < m_Polygon.m_pEdgeVector.size(); ++i)
			{
				m_Polygon.m_pEdgeVector[i]->m_bIsChecked = true;
			}*/
		}
		EliminateTriangles();


	}

	//! This function checks if one edge of the given trinagle is already in the polygon's edge vector.
	void LG_DelaunayTriangulation::CheckIfEdgeIsInside(LG_Triangle* pIteratingTriangle)
	{
		/// Create a flag to determinate when we can add a edge to the polygon.
		bool bCanAddEdge = true;
		/// Iterate for each edge of the triangle.
		for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		{
			/// Iterate for each edge of the polygon.
			for (int32 j = 0; j < m_Polygon.m_pEdgeVector.size(); ++j)
			{
				/// Compare the iterating edge of the given triangle with the iterating polygon's edge.
				if (!pIteratingTriangle->m_pEdges[i]->CompareIndex(*m_Polygon.m_pEdgeVector[j]))
				{
					/// Set the flag to false.
					bCanAddEdge = EdgeIsNotInTriangleVector(pIteratingTriangle->m_pEdges[i]);
					if (!bCanAddEdge)break;
				}
				else
				{
					bCanAddEdge = false;
					break;
				}
			}
			/// If this flag is still true, we add the iterating edge to the polygon.
			if (bCanAddEdge)
			{
				/// The iterating edge is added to the polygon edge vector.
				m_Polygon.InsertEdgeToVector(pIteratingTriangle->m_pEdges[i]);
			}
			/// Set the flag as true.
			bCanAddEdge = true;
		}
	}

	//! This function create a new triangles from the given node.
	void LG_DelaunayTriangulation::CreateNewTriangles(LG_Node* pIteratingNode)
	{
		/// Creates a triangle from the polygon's edges and the iterating node.
		LG_Triangle* pTriangle;
		for (int32 i = 0; i < m_Polygon.m_pEdgeVector.size(); ++i)
		{
			/// create a new triangle from the polygon's iterating edge to the iterating node.
			//TODO: Checar despues esto de la bandera de cada edge del poligono.

			pTriangle = ManageEdges(m_Polygon.m_pEdgeVector[i]->m_pFirstNode,
				m_Polygon.m_pEdgeVector[i]->m_pSecondNode,
				pIteratingNode);

			/// Adds the new triangle to the vector.
			m_pTrianglesVector.push_back(pTriangle);

		}
	}

	//! This function checks if the given edge is the same that anyone edge of the triangle's edges in Triangles Vector.
	bool LG_DelaunayTriangulation::EdgeIsNotInTriangleVector(LG_Edge * IteratingEdge)
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
			{
				if (IteratingEdge->CompareIndex(*m_pTrianglesVector[i]->m_pEdges[j]))
				{
					return false;
				}
			}
		}
		return true;
	}

	//! 
	bool LG_DelaunayTriangulation::SetTriangleAsBadTriangle(const LG_Node& IteratingNode)
	{
		LG_Triangle* pTriangle = nullptr;
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
					pTriangle = *itt;
					m_pTrianglesVector.erase(itt);
					m_pBadTriangles.push_back(pTriangle);
					return true;
				}
			}

		}
		return false;
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
		/// Assign the ID for the node.
		pNodePosition2->m_iID = iCountNode;
		/// Add one to the counter node.
		iCountNode++;

		/// 
		pNodePosition3->m_Position = pNodePosition2->m_Position;
		pNodePosition3->m_Position.X = GridCenter.X;
		/// Get the last top node.
		pNodePosition3->m_Position.Y += AristaSize;
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
			for (int32 j = 0; j < NODES_PER_TRIANGLE; ++j)
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
			if ((*itt)->m_bIsChecked)
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
	void LG_DelaunayTriangulation::AddEdgesToPolygon()
	{

		bool bCanAddEdge = false;
		//TODO: meter esto al init
		if (m_pBadTriangles.size() == 1)
		{
			for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
			{
				/// The edge that didn't share position is added to the polygon.
				m_Polygon.InsertEdgeToVector(m_pBadTriangles[0]->m_pEdges[i]);
			}
			return;
		}

		for (int32 i = 0; i < m_pBadTriangles.size(); ++i)
		{
			CheckIfEdgeIsInside(m_pBadTriangles[i]);
		}
	}

	LG_Triangle* LG_DelaunayTriangulation::ManageEdges(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode)
	{

		///
		LG_Triangle* pNewTriangle = new LG_Triangle();

		///
		LG_Edge* pFirstEdge = new LG_Edge();
		LG_Edge* pSecondEdge = new LG_Edge();
		LG_Edge* pThirdEdge = new LG_Edge();

		/// Initialize the edges.
		pFirstEdge->Init(pFirstNode, pSecondNode);
		pSecondEdge->Init(pFirstNode, pThirdNode);
		pThirdEdge->Init(pSecondNode, pThirdNode);

		for (int32 i = 0; i < m_pEdgeVector.size(); ++i)
		{
			if (pFirstEdge->CompareIndex(*m_pEdgeVector[i]))
			{
				delete pFirstEdge;
				pFirstEdge = m_pEdgeVector[i];
			}

			else if (pSecondEdge->CompareIndex(*m_pEdgeVector[i]))
			{
				delete pSecondEdge;
				pSecondEdge = m_pEdgeVector[i];
			}

			else if (pThirdEdge->CompareIndex(*m_pEdgeVector[i]))
			{
				delete pThirdEdge;
				pThirdEdge = m_pEdgeVector[i];
			}
		}

		pNewTriangle->Init(pFirstEdge, pSecondEdge, pThirdEdge);
		pNewTriangle->m_iID = m_iTrianglesCount;
		m_iTrianglesCount++;
		return pNewTriangle;
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
}