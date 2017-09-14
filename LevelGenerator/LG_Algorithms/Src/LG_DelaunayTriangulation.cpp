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

		m_iTrianglesAmount = 0;
		m_iEdgeAmount = 0;
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
			CreateBadTriangles(m_NodesCloud[i]);
			/// 
			CreatePolygon();
			/// 
			EliminateBadTrianglesFromTriangulation();
			///
			CreateNewTriangles(&m_NodesCloud[i]);
		}
		EliminateTriangles();

		/*///We now check that none of the triangle's vertices share position with one of the big triangles.
		Vector<LG_Triangle>::iterator itt = m_TrianglesVector.begin();
		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		{
			for (int32 j = 0; j < NUM_EDGES_PER_TRIANGLE; ++j)
			{
				for (int32 k = 0; k < NUM_EDGES_PER_TRIANGLE; ++k)
				{
					/// If any of the nodes in the triangulation shares position with a vertex of the big triangle, we eliminate such triangle.
					if (m_TrianglesVector[i].m_pVertices[j]->m_Position ==
						m_BigTriangle.m_pVertices[k]->m_Position)
					{
						/// Delete the triangle.
						m_TrianglesVector.erase(itt);
					}
				}
			}
			/// change the iterator.
			++itt;
		}*/

		///// Start the while cycle.
		//while (!bQuit)
		//{
		//	/// Reset the flags.
		//	bQuit = true;
		//	bBreakFirstFor = false;
		//	/// Iterate the node's cloud.
		//	for (int32 j = 0; j < m_NodesCloud.size(); ++j)
		//	{
		//		/// Check if the iterating node is inside of the iterating triangle and
		//		/// the iterating triangle is not checked. And we also check that it doesn't compare
		//		/// against itself.
		//		if (m_pActualTriangle->IsPointInside(&m_NodesCloud[j]) &&
		//			!m_pActualTriangle->m_bIsChecked &&
		//			!CheckIfSharesPosition(*m_pActualTriangle, m_NodesCloud[j]) &&
		//			!m_NodesCloud[j].m_bIsInside)
		//		{
		//			/// Create 3 new triangles.
		//			CreateTriangles(*m_pActualTriangle, &m_NodesCloud[j]);
		//			//SetTriangleFlag(*m_pActualTriangle);
		//			/// We set as actaual tile the last inserted node.
		//			m_pActualTriangle = &m_TrianglesVector.front();
		//			/// Set the flag to break the first for.
		//			bBreakFirstFor = true;
		//			/// Break the second for.
		//			break;
		//		}
		//	}
		//	if (!bBreakFirstFor)
		//	{
		//		/// If it didn't have dots inside we set that triangle as checked.
		//		m_pActualTriangle->m_bIsChecked = true;
		//		/// Find a new actual triangle, starting from the last inserted triangle to the first one.
		//		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		//		{
		//			/// If the triangle haven't been checked.
		//			if (!m_TrianglesVector[i].m_bIsChecked)
		//			{
		//				/// Set the new actual tile.
		//				m_pActualTriangle = &m_TrianglesVector[i];
		//				break;
		//			}
		//		}
		//	}
		//	/// Assign the new value to this flag if it's true, finish the cycle.
		//	bQuit = CheckifAllNodesAreTrue();
		//}
	}

	//! This function create a new triangles from the given node.
	void LG_DelaunayTriangulation::CreateNewTriangles(LG_Node* pIteratingNode)
	{
		//TODO: checar que nohayan edges duplicados
		/// Creates a triangle from the polygon's edges and the iterating node.
			LG_Triangle* pTriangle;
		for (int32 i = 0; i < m_Polygon.m_EdgeVector.size(); ++i)
		{
			/// create a new triangle from the iterating edge from the polygon
			/// to the iterating node.
			pTriangle = new LG_Triangle();
			pTriangle->Init(m_Polygon.m_EdgeVector[i].m_pFirstNode,
				m_Polygon.m_EdgeVector[i].m_pSecondNode,
				pIteratingNode, m_iTrianglesAmount, m_iEdgeAmount);

			/// Adds the triangle to the vector.
			m_pTrianglesVector.push_back(pTriangle);
		}
	}

	//! 
	void LG_DelaunayTriangulation::CreateBadTriangles(const LG_Node& IteratingNode)
	{
		///
		for (int32 j = 0; j < m_pTrianglesVector.size(); ++j)
		{
			/// check if the node is inside of the circle.
			if (m_pTrianglesVector[j]->m_CircumcircleCircumference.IsDotInside(
				IteratingNode.m_Position))
			{
				/// Add the triangle to the incorrect triangle's vector.
				m_pBadTriangles.push_back(m_pTrianglesVector[j]);
			}
		}
	}

	//! This function check if one node is inside of one circle.
	bool LG_DelaunayTriangulation::CheckNodeInsideOfCircle(LG_Triangle ActualTriangle)
	{
		uint32 DotsInside = 0;
		/// iterate through the nodde cloud.
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			/// check if the node is inside of the circle.
			if (ActualTriangle.m_CircumcircleCircumference.IsDotInside(
				m_NodesCloud[i].m_Position))
			{
				/// Add one to the counter.
				++DotsInside;
				/// if it have more than 3 nodes inside, it means its an incorrect triangle.
				if (DotsInside > 3)
				{
					return true;
				}
			}
		}

		/// If the code got to this point, the triangle is correct.
		return false;
	}



	//! This function create a big triangle.
	void LG_DelaunayTriangulation::CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter)
	{
		/// X * 2 = the lenght of the triangle's arista. This only works when the grid is a square.
		float AristaSize = float(iWidth * 2);

		/// We set the center of the grid to start off.
		LG_Node* pNodePosition1 = new LG_Node();
		LG_Node* pNodePosition2 = new LG_Node();
		LG_Node* pNodePosition3 = new LG_Node();

		pNodePosition1->m_Position = GridCenter;

		/// Substract half the height in the Y axis so that it's at the base of que grid.
		pNodePosition1->m_Position.Y -= iHeight / 2;
		/// Substract half of the size of the arista to the left.
		pNodePosition1->m_Position.X -= AristaSize / 2;

		/// 
		pNodePosition2->m_Position = pNodePosition1->m_Position;
		/// Add the whole size of the arista for the next node.
		pNodePosition2->m_Position.X += AristaSize;
		pNodePosition2->m_Position.Y -= 1;

		/// 
		pNodePosition3->m_Position = pNodePosition2->m_Position;
		pNodePosition3->m_Position.X = GridCenter.X;
		/// Get the last top node.
		pNodePosition3->m_Position.Y += AristaSize + 1;

		m_pBigTriangle = new LG_Triangle();
		m_pBigTriangle->Init(pNodePosition1, pNodePosition2, pNodePosition3, m_iTrianglesAmount, m_iEdgeAmount);

	}

	//! This function compares the iterating node's position with any of the iterating triangle's node.
	bool LG_DelaunayTriangulation::CheckIfSharesPosition(LG_Triangle IteratingTriangle, LG_Node IteratingNode)
	{
		return ((IteratingTriangle.m_pVertices[FIRST_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[SECOND_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[THIRD_NODE]->m_Position == IteratingNode.m_Position));
	}

	//! This function sees if all the triangles from the vector have their flags set as false.
	bool LG_DelaunayTriangulation::AreTrianglesFalse()
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); i++)
		{
			if (m_pTrianglesVector[i]->m_bIsChecked)
			{
				return false;
			}
		}
		return true;
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
				if (m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[0] ||
					m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[1] ||
					m_pTrianglesVector[i]->m_pVertices[j] == m_pBigTriangle->m_pVertices[2])
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
		//TODO: meter esto al init
		if (m_pBadTriangles.size() == 1)
		{
			for (int32 i = 0; i < NUM_EDGES_PER_TRIANGLE; ++i)
			{
				/// The edge that didn't share position is added to the polygon.
				m_Polygon.InsertEdgeToVector(&m_pBadTriangles[0]->m_Edges[i]);
			}
			return;
		}

		//TODO: crear el poligono, wtf.
		// checar en el poligono los edges que tiene, y le aventamos un edge para comparar
		//
	}

	//! This function create the vector of bad triangles.
	void LG_DelaunayTriangulation::CreateBadTriangles()
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			/// Verify that there are no dots inside of the triangle's circle.
			if (CheckNodeInsideOfCircle(*m_pTrianglesVector[i]))
			{
				/// Set it's flag to false.
				m_pTrianglesVector[i]->m_bIsChecked = false;
				/// add the incorrect triangle to it's corresponding list.
				m_pBadTriangles.push_back(m_pTrianglesVector[i]);
			}
		}
	}

	//! This function eliminate the bad triangles in the vector of triangles.
	void LG_DelaunayTriangulation::EliminateBadTrianglesFromTriangulation()
	{
		/// An iterator to know what triangle to erase.
		Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin();

		/// Iterate through the incorrect triangles.
		for (int32 i = 0; i < m_pBadTriangles.size(); ++i)
		{
			/// Assign an initial value for the iterator.
			itt = m_pTrianglesVector.begin();
			/// Iterate the correct triangles.
			for (int32 j = 0; itt != m_pTrianglesVector.end(); ++itt)
			{
				/// when we find the same triangle we delete from the correct list.
				if (m_pBadTriangles[i] == m_pTrianglesVector[j])
				{
					m_pTrianglesVector.erase(itt);
					break;
				}
				/// Add one to the counter.
				++j;
			}
		}
	}

	//! Check if the triangle already exist in the bad triangle vector.
	bool LG_DelaunayTriangulation::CheckIfBadTriangleExist(int32 TriangleID)
	{
		for (int32 i = 0; i < m_pBadTriangles.size(); ++i)
		{
			if (m_pBadTriangles[i]->m_iID == TriangleID) return true;
		}
		return false;
	}

	//! Check if the triangle already exist in the triangle vector.
	bool LG_DelaunayTriangulation::CheckIfTriangleExist(int32 TriangleID)
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			if (m_pTrianglesVector[i]->m_iID == TriangleID) return true;
		}
		return false;
	}
}