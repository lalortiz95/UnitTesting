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
		/// Insert the big triangle to the vector.
		m_pTrianglesVector.push_back(m_pBigTriangle);
		// Create 3 new triangles.
		//if (m_pBigTriangle->IsPointInside(&m_NodesCloud[FIRST_NODE]))
		//{
		//	CreateTriangles(*m_pBigTriangle, &m_NodesCloud[FIRST_NODE]);
		//}

		/// Set the actual triangle to compare with nodes iterating.
		m_pActualTriangle = m_pTrianglesVector.front();

		//m_pTrianglesVector.push_back(m_pBigTriangle);
		//for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		//{
		//	m_pEdgeVector.push_back(m_pBigTriangle->m_pEdges[i]);
		//}

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
		//TODO: hcaer triangulación incremental.
		// una vez teniendo una triangulación, empezamos a tomar cada edge de cada triangulo, y tomamos los 2 triangulos unidos por esa arista.
		// con esos triangulos revisamos que sólo tengan 3 nodos dentro, de lo contrario hacemos un cambio de arista, eliminando los 2 triangulos
		// anteriores y creando 2 nuevos con los mismos puntos, pero unidos por el otro edge posible, y verificar que cumpla con la regla de delaunay.
		// al cumplir con dicha regla se marca como revisado, así mismo el triangulo se queda como revisado, para que no se vuelva a tomar.
		// Repetir hasta que todos los edges estén marcados como revisados.

		/// 
		Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);

		IncrementalTriangulation();
		
		//while (!bQuit)
		//{
		//	/// Reset the flag.
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
		//			m_pActualTriangle = m_pTrianglesVector.front();
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
		//		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		//		{
		//			/// If the triangle haven't been checked.
		//			if (!m_pTrianglesVector[i]->m_bIsChecked)
		//			{
		//				/// Set the new actual tile.
		//				m_pActualTriangle = m_pTrianglesVector[i];
		//				break;
		//			}
		//		}
		//	}
		//	/// Assign the new value to this flag if it's true, finish the cycle.
		//	bQuit = CheckifAllNodesAreTrue();
		//}

		///// Initialize the start parameters.
		//Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);
		///// 
		//for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		//{
		//	/// If the node is inside of the circumcircle circumference.
		//	while (SetTriangleAsBadTriangle(m_NodesCloud[i]));
		//	/// 
		//	AddEdgesToPolygon();
		//	///
		//	CreateNewTriangles(&m_NodesCloud[i]);
		//	/*for (int32 i = 0; i < m_Polygon.m_pEdgeVector.size(); ++i)
		//	{
		//		m_Polygon.m_pEdgeVector[i]->m_bIsChecked = true;
		//	}*/
		//}
		//EliminateTriangles();
	}

	//! This function performs an initial triangulation that works as a base for the rest of the algorithm.
	void LG_DelaunayTriangulation::IncrementalTriangulation()
	{
		bool bQuit = false;
		bool bHasNoDotsInside = true;

		/// Variable used to add triangles into the vector.
		LG_Triangle newTriangle;

		/// we perform incremental triangulation
		while (!bQuit)
		{
			/// We will compare the actual triangle against all of the nodes in the node cloud.
			for (int32 i = 0; i < m_NodesCloud.size(); ++i)
			{
				/// If there is a dot inside of the triangle
				if (m_pActualTriangle->IsPointInside(&m_NodesCloud[i]) && !m_NodesCloud[i].m_bIsChecked)
				{
					///Creates 3 new triangles between each edge of the actual triangle, and the iterating node.
					for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
					{
							m_pTrianglesVector.push_back(
								ManageEdges(m_pActualTriangle->m_pEdges[j]->m_pFirstNode,
									m_pActualTriangle->m_pEdges[j]->m_pSecondNode,
									&m_NodesCloud[i]));
						
					}
					/// Set the node that we just used as checked.
					m_NodesCloud[i].m_bIsChecked = true;
					/// set that there were dots inside of the triangle.
					bHasNoDotsInside = false;
					/// 
					m_pEdgeVector = m_pEdgeVector;
					/// Ends the iteration because now is time to get a new actual triangle.
					break;
				}
			}

			/// It didn't have any dots inside.
			if (bHasNoDotsInside)
			{
				/// We set that triangle as true.
				m_pActualTriangle->m_bIsChecked = true;
			}

			// Siempre que itere buscará un nuevo actual, ya sea porque hizo nuevos triangulos, o porque ya no podía hacer triangulos.
			/// Iterates throough the triangles vector.
			for (int32 i = m_pTrianglesVector.size() - 1; i >= 0; --i)
			{
				/// We find the new actual triangle.
				if (!m_pTrianglesVector[i]->m_bIsChecked && m_pActualTriangle != m_pTrianglesVector[i])
				{
					/// set the new triangle.
					m_pActualTriangle = m_pTrianglesVector[i];
					break;
				}
			}

			/// Checks if the triangles are already checked.
			for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
			{
				CheckIfTriangleIsChecked(m_pTrianglesVector[i]);
			}

			/// once all the triangles have been checked, we finish the incremental triangulation.
			if (CheckIfAllTrianglesAreTrue())
			{
				bQuit = true;
			}
		}
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

	//! This function create a 3 triangles from one triangle and a node.
	void LG_DelaunayTriangulation::CreateTriangle(LG_Triangle ActualTriangle, LG_Node* pNodeInside, int32 iNode)
	{
		/// 
		LG_Triangle Triangle;

		if (iNode == 2)
		{
			/// Initialize a new triangle with the node given.
			Triangle.Init(m_pBigTriangle->m_pVertices[iNode],
				m_pBigTriangle->m_pVertices[FIRST_NODE],
				pNodeInside);
		}

		else
		{
			/// Initialize a new triangle with the node given.
			Triangle.Init(m_pBigTriangle->m_pVertices[iNode],
				m_pBigTriangle->m_pVertices[iNode + 1],
				pNodeInside);
		}
		/// Add the new triangle in the triangles vector.
		m_pTrianglesVector.push_back(&Triangle);
	}

	//! This function create a 3 triangles from one triangle and a node.
	void LG_DelaunayTriangulation::CreateTriangles(LG_Triangle ActualTriangle, LG_Node * pNodeInside)
	{
		for (int32 i = 0; i < NODES_PER_TRIANGLE; ++i)
		{
			CreateTriangle(ActualTriangle, pNodeInside, i);
		}
		pNodeInside->m_bIsInside = true;
	}


	//! This function determine when we can stop the triangulation.
	bool LG_DelaunayTriangulation::CheckifAllNodesAreTrue()
	{
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			if (!m_NodesCloud[i].m_bIsChecked)
			{
				return false;
			}
		}
		return true;
	}

	bool LG_DelaunayTriangulation::CheckIfAllTrianglesAreTrue()
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			/// Check if the triangle isn't checked.
			if (!m_pTrianglesVector[i]->m_bIsChecked)
			{
				/// If even one of the triangles is false, we return.
				return false;
			}
		}
		/// All triangles were checked.
		return true;
	}

	//! This function compares the iterating node's position with any of the iterating triangle's node.
	bool LG_DelaunayTriangulation::CheckIfSharesPosition(LG_Triangle IteratingTriangle, LG_Node IteratingNode)
	{
		return ((IteratingTriangle.m_pVertices[FIRST_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[SECOND_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[THIRD_NODE]->m_Position == IteratingNode.m_Position));
	}

	//! This function checks if the triangle is already checked.
	void LG_DelaunayTriangulation::CheckIfTriangleIsChecked(LG_Triangle* tri)
	{
		int32 DotsInside, DotsChecked;
		DotsInside = DotsChecked = 0;

		/// Iterates through the nodes cloud.
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			/// Check if the iterating node is inside of the actual triangle.
			if (tri->IsPointInside(&m_NodesCloud[i]))
			{
				/// add one to the dots inside counter.
				++DotsInside;
				/// Check that the node inside is checked
				if (m_NodesCloud[i].m_bIsChecked)
				{
					/// add one to the nodes checked counter.
					++DotsChecked;
				}
			}
		}

		/// if the nodes inside of the triangle are the same amount of dots checked.
		tri->m_bIsChecked = (DotsChecked == DotsInside);
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
		/// This flags tells us if we are to add a new edge to the edge's vector.
		bool bIsFirstEdgeNew, bIsSecondEdgeNew, bIsThridEdgeNew;
		bIsFirstEdgeNew = bIsSecondEdgeNew = bIsThridEdgeNew = true;
		///
		LG_Triangle* pNewTriangle = new LG_Triangle();

		/// Assigns memory.
		LG_Edge* pFirstEdge = new LG_Edge();
		LG_Edge* pSecondEdge = new LG_Edge();
		LG_Edge* pThirdEdge = new LG_Edge();

		/// Initialize 3 new edges.
		pFirstEdge->Init(pFirstNode, pSecondNode);
		pSecondEdge->Init(pFirstNode, pThirdNode);
		pThirdEdge->Init(pSecondNode, pThirdNode);

		/// Checks if the edge haven't been inserted already. If so it gives a reference of the memory.
		for (int32 i = 0; i < m_pEdgeVector.size(); ++i)
		{
			/// We also check that the boolean is still true, so that it doesn't get inside twice and deletes an object of the vector.
			if (pFirstEdge->CompareIndex(*m_pEdgeVector[i]) && bIsFirstEdgeNew)
			{
				delete pFirstEdge;
				pFirstEdge = m_pEdgeVector[i];
				/// We are not creating a new edge for the vector.
				bIsFirstEdgeNew = false;
			}

			else if (pSecondEdge->CompareIndex(*m_pEdgeVector[i]) && bIsSecondEdgeNew)
			{
				delete pSecondEdge;
				pSecondEdge = m_pEdgeVector[i];
				/// We are not creating a new edge for the vector.
				bIsSecondEdgeNew = false;
			}

			else if (pThirdEdge->CompareIndex(*m_pEdgeVector[i]) && bIsThridEdgeNew)
			{
				delete pThirdEdge;
				pThirdEdge = m_pEdgeVector[i];
				/// We are not creating a new edge for the vector.
				bIsThridEdgeNew = false;
			}
		}

		/// Check if it is needed to add new edges.
		if (bIsFirstEdgeNew)
		{
			m_pEdgeVector.push_back(pFirstEdge);
		}
		if (bIsSecondEdgeNew)
		{
			m_pEdgeVector.push_back(pSecondEdge);
		}
		if (bIsThridEdgeNew)
		{
			m_pEdgeVector.push_back(pThirdEdge);
		}

		/// Creates a new triangle, and initializes it.
		pNewTriangle->Init(pFirstEdge, pSecondEdge, pThirdEdge);
		pNewTriangle->m_iID = m_iTrianglesCount;
		m_iTrianglesCount++;
		/// Returns the new created triangle.
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