#include "LG_DelaunayTriangulation.h"
#include <LG_Math.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_DelaunayTriangulation::LG_DelaunayTriangulation()
	{
		m_pBigTriangle = nullptr;
		m_pTrianglesVector.clear();
		m_iTrianglesCount = 0;
		m_iEdgesCount = 0;
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

		/// Set the actual triangle to compare with nodes iterating.
		m_pActualTriangle = m_pTrianglesVector.front();
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
		/// 
		Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);
		/// The initial triangulation we base our Delaunay algorithm on.
		IncrementalTriangulation();
		/// Set all triangle's flags as false.
		SetTrianglesAsFalse();

		/// Creates the nodes' pointers to change it's values.
		LG_Node* pFirstNode = nullptr;
		LG_Node* pSecondNode = nullptr;

		/// Creates the triangles' pointers to change it's values.
		LG_Triangle* pFirstTriangle = nullptr;
		LG_Triangle* pSecondTriangle = nullptr;

		/// Create a edge's pointer to legalize before.
		LG_Edge* pActualEdge = nullptr;
		LG_Triangle* pActualTriangle = m_pTrianglesVector.front();
		bool bCanStop = false;

		/// counter to exit the while loop.
		int32 iBreakWhile = 0;

		while (!bCanStop && iBreakWhile < 500)
		{
			bCanStop = true;
			for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
			{
				if (!m_pTrianglesVector[i]->m_bIsChecked)
				{
					pActualTriangle = m_pTrianglesVector[i];
					break;
				}
			}

			for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
			{

				pActualEdge = pActualTriangle->m_pEdges[j];
				if (FindTrianglesToLegalize(pActualEdge, &pFirstTriangle, &pSecondTriangle))
				{
					/// 
					FindNodesToCreatePolygon(pActualEdge, pFirstTriangle, pSecondTriangle, &pFirstNode, &pSecondNode);
					/// If at least one of the nodes was inside the circle we change the arista for a legal one.
					if (pSecondTriangle->m_CircumcircleCircumference.IsDotInside(pFirstNode->m_Position) ||
						pFirstTriangle->m_CircumcircleCircumference.IsDotInside(pSecondNode->m_Position))
					{

						LG_Triangle* pNewFirstTriangle = CreateTriangle(pFirstNode, pSecondNode, pActualEdge->m_pFirstNode);
						LG_Triangle* pNewSecondTriangle = CreateTriangle(pFirstNode, pSecondNode, pActualEdge->m_pSecondNode);
						++iBreakWhile;
						m_pTrianglesVector.push_back(pNewFirstTriangle);
						m_pTrianglesVector.push_back(pNewSecondTriangle);

						/// Erases the triangle that belongs to the legalized edge.
						for (Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin(); itt != m_pTrianglesVector.end(); ++itt)
						{
							if ((*itt) == pFirstTriangle)
							{
								LG_Triangle* pTemp = *itt;
								m_pTrianglesVector.erase(itt);
								delete pTemp;
								pTemp = nullptr;
								break;
							}
						}

						for (Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin(); itt != m_pTrianglesVector.end(); ++itt)
						{
							if ((*itt) == pSecondTriangle)
							{
								LG_Triangle* pTemp = *itt;
								m_pTrianglesVector.erase(itt);
								delete pTemp;
								pTemp = nullptr;
								break;
							}
						}

						//TODO: se borra el edge pero no las conexiones que tienen sus nodos
						pActualEdge->Legalize(pActualEdge->m_pFirstNode, pActualEdge->m_pSecondNode);

						for (Vector<LG_Edge*>::iterator itt = m_pEdgeVector.begin(); itt != m_pEdgeVector.end(); ++itt)
						{
							if ((*itt) == pActualEdge)
							{
								LG_Edge* pTemp = *itt;
								m_pEdgeVector.erase(itt);
								delete pTemp;
								pTemp = nullptr;
								break;
							}
						}
						break;

					}
				}
			}
			pActualTriangle->m_bIsChecked = true;
			bCanStop = CheckIfAllTrianglesAreTrue();
		}

		/// Eliminate the edges of the big triangle from the edges' vector.
		EliminateEdgesBigTriangle();
		/// Eliminate the triangles that shares position with the big triangle.
		while (EliminateTriangles());
		/// Eliminate the edges that shares position with the big triangle.
		while (EliminateEdges());
	}

	//! This function performs an initial triangulation that works as a base for the rest of the algorithm.
	void LG_DelaunayTriangulation::IncrementalTriangulation()
	{
		bool bQuit = false;
		bool bHasNoDotsInside = true;
		int32 iPosTriangle = 0;
		Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin();

		/// A counter for all of the dots inside of a triangle, it's needed because if there is only one, we'll triangulate with that.
		int32 iDotsInside = 0;
		/// Stores the triangle that we want to know whether it contains good angles or not
		LG_Triangle* TempTri;
		/// The best angle in the dots inside a triangle. We start with 80°, or 1.39626 radians.
		float fBestAngle;
		/// A starting default angle to select a good one.
		float fDefaultAngle = 1.74533f;
		/// If the triangle doesn't have triangles with good angles in it, but it's the only one available we triangulate with that.
		bool bHaveGoodAngles = false;

		/// here we store all the nodes that we find inside of the actual triangle. This is needed
		Vector<LG_Node*> pNodesInside;
		/// Here we store the best node inside of the triangle, and we use the variable to change it's properties.
		LG_Node* pBestNode;

		/// we perform incremental triangulation
		while (!bQuit)
		{
			/// Makes sure that the nodes inside list is clear for this iteration
			pNodesInside.clear();
			/// Initialize the best angles array with the default minimum angle needed, this being 100°
			fBestAngle = fDefaultAngle;
			/// Clean the best node for this iteration.
			//BestNode = nullptr;
			/// Reset the value of the flag for this iteration.
			bHaveGoodAngles = false;
			/// 
			bHasNoDotsInside = true;

			/// We are going to find all the nodes inside of the actual triangle, and get the one that makes
			/// the best intrinsic angles.
			for (int32 i = 0; i < m_NodesCloud.size(); ++i)
			{
				if (m_pActualTriangle->IsPointInside(&m_NodesCloud[i]) && !m_NodesCloud[i].m_bIsChecked)
				{
					/// Set this flag to false since the actual triangle did have nodes inside.
					bHasNoDotsInside = false;
					/// We store the node that's inside.
					pNodesInside.push_back(&m_NodesCloud[i]);
				}
			}

			/// Find the best node to triangulate with.
			for (int32 i = 0; i < pNodesInside.size(); ++i)
			{
				/// We check that the node isn't checked already.
				if (pNodesInside[i]->m_bIsChecked)
				{
					continue;
				}
				/// Create 3 triangles between the actual triangle and the iterating node.
				for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
				{
					/// Store the first triangle created between the iterating edge, and the iterating node.
					TempTri = CreateTriangle(m_pActualTriangle->m_pEdges[j]->m_pFirstNode,
						m_pActualTriangle->m_pEdges[j]->m_pSecondNode,
						pNodesInside[i]);

					/// If the biggest angle in the triangle, is smaller than the best angle, that becomes the new best angle.
					if (LG_Math::Max3(TempTri->m_fAngles[0], TempTri->m_fAngles[1], TempTri->m_fAngles[2]) < fBestAngle)
					{
						/// Store the best angle for this triangle.
						fBestAngle = LG_Math::Max3(TempTri->m_fAngles[0], TempTri->m_fAngles[1], TempTri->m_fAngles[2]);
						/// We store the node we the best angles.
						pBestNode = pNodesInside[i];
						/// 
						bHaveGoodAngles = true;
					}
					else
					{
						break;
					}
				}
			}

			/// If the triangles inside of the actual triangle dont make good angles, but it had dots inside
			/// we still need to triangulate, so we set the best node as the first of the list.
			if (!bHaveGoodAngles && !bHasNoDotsInside)
			{
				pBestNode = pNodesInside[0];
			}
			/// See if the node didn't have any nodes inside.
			if (bHasNoDotsInside)
			{
				/// We set that triangle as true.
				m_pActualTriangle->m_bIsChecked = true;
			}
			else
			{
				/// This block of code makes a triangle with every node from all the actual triangle's aristas, and 
				/// the node found as the best one, defined by it's beautiful intrinsic angles.
				for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
				{
					//Creo que esta función está destruyendo todo.
					/// We triangulate with the actual triangle and the best node.
					m_pTrianglesVector.push_back(CreateTriangle(m_pActualTriangle->m_pEdges[i]->m_pFirstNode,
						m_pActualTriangle->m_pEdges[i]->m_pSecondNode,
						pBestNode));
				}

				for (int32 i = 0; i < m_NodesCloud.size(); ++i)
				{
					if (pBestNode->m_iID == m_NodesCloud[i].m_iID)
					{
						/// Mark the best node as checked. 
						m_NodesCloud[i].m_bIsChecked = true;
						break;
					}
				}

				/// We delete the triangle that have the 3 new triangles
				itt = m_pTrianglesVector.begin() + iPosTriangle;
				m_pTrianglesVector.erase(itt);
			}

			///  We find the new actual triangle by iterating through their list, and finding a triangle that
			/// haven't been checked yet.
			for (int32 i = m_pTrianglesVector.size() - 1; i >= 0; --i)
			{
				/// We find the new actual triangle.
				if (!m_pTrianglesVector[i]->m_bIsChecked && m_pActualTriangle != m_pTrianglesVector[i])
				{
					/// set the new triangle.
					m_pActualTriangle = m_pTrianglesVector[i];
					/// Store the place in the array to set the new actual triangle in the next while iteration.
					iPosTriangle = i;
					/// Exits the for.
					break;
				}
			}
			/// Checks if the triangles are already checked.
			for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
			{
				CheckIfTriangleIsChecked(m_pTrianglesVector[i]);
			}
			/// once all the triangles have been checked, we finish the incremental triangulation.
			bQuit = CheckIfAllTrianglesAreTrue();

			// debugging purposes.
			if (bQuit)
			{
				bQuit = bQuit;
			}

			///// We will compare the actual triangle against all of the nodes in the node cloud.
			//for (int32 i = 0; i < m_NodesCloud.size(); ++i)
			//{
			//	/// If there is a dot inside of the triangle
			//	if (m_pActualTriangle->IsPointInside(&m_NodesCloud[i]) && !m_NodesCloud[i].m_bIsChecked)
			//	{
			//		/// set that there were dots inside of the triangle.
			//		bHasNoDotsInside = false;
			//		///Creates 3 new triangles between each edge of the actual triangle, and the iterating node.
			//		for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
			//		{
			//			/// Add one to the dots counter. We want to know if there are more than one inside.
			//			++iDotsInside;
			//			//TODO: Si alguno de los guardados sigue en 80 significa que no cambió, entonces se debe
			//			// buscar un nuevo punto, al final de la iteración con todos los puntos, si no se encontró
			//			// otro nodo adentro entonces se toma el único que estaba y con ese se triangula, ya ni modo.
			//			// esto se hace teniendo una referencia al nodo del último triángulo que no haya sido bueno.
			//			/// Store the first triangle created between the iterating edge, and the iterating node.
			//			TempTri = CreateTriangle(m_pActualTriangle->m_pEdges[j]->m_pFirstNode,
			//				m_pActualTriangle->m_pEdges[j]->m_pSecondNode,
			//				&m_NodesCloud[i]);
			//			/// If the biggest angle in the triangle, is smaller than the best angle, that becomes the new best angle.
			//			if (LG_Math::Max3(TempTri->m_fAngles[0], TempTri->m_fAngles[1], TempTri->m_fAngles[2]) < fBestAngle[j])
			//			{
			//				/// Store the best angle for this triangle.
			//				fBestAngle[j] = LG_Math::Max3(TempTri->m_fAngles[0], TempTri->m_fAngles[1], TempTri->m_fAngles[2]);
			//			}
			//			//m_pTrianglesVector.push_back(
			//			//	CreateTriangle(m_pActualTriangle->m_pEdges[j]->m_pFirstNode,
			//			//		m_pActualTriangle->m_pEdges[j]->m_pSecondNode,
			//			//		&m_NodesCloud[i]));
			//		}
			//		/// Iterate through the calculated best angles.
			//		for (int32 j = 0; j < ANGLES_PER_TRIANGLE; ++j)
			//		{
			//			/// see if there's an angle that didn't change, meaning the triangles it would triangulate are no good for us.
			//			if (fBestAngle[j] < 80)
			//			{
			//				bHaveBadangles = false;
			//			}
			//		}
			//		/// If the angles in one of the triangles is considered a bad triangle.
			//		if (bHaveBadangles)
			//		{
			//			continue;
			//		}
			//		/// Set the node that we just used as checked.
			//		m_NodesCloud[i].m_bIsChecked = true;
			//		///
			//		itt = m_pTrianglesVector.begin() + iPosTriangle;
			//		m_pTrianglesVector.erase(itt);
			//		/// Ends the iteration because now is time to get a new actual triangle.
			//		break;
			//	}
			//}
			///// It didn't have any dots inside.
			//if (bHasNoDotsInside)
			//{
			//	/// We set that triangle as true.
			//	m_pActualTriangle->m_bIsChecked = true;
			//}
			///// Iterates throough the triangles vector.
			//for (int32 i = m_pTrianglesVector.size() - 1; i >= 0; --i)
			//{
			//	/// We find the new actual triangle.
			//	if (!m_pTrianglesVector[i]->m_bIsChecked && m_pActualTriangle != m_pTrianglesVector[i])
			//	{
			//		/// set the new triangle.
			//		m_pActualTriangle = m_pTrianglesVector[i];
			//		iPosTriangle = i;
			//		break;
			//	}
			//}
			///// Checks if the triangles are already checked.
			//for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
			//{
			//	CheckIfTriangleIsChecked(m_pTrianglesVector[i]);
			//}
			///// once all the triangles have been checked, we finish the incremental triangulation.
			//bQuit = CheckIfAllTrianglesAreTrue();
		}
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

	//! This function checks if the triangle is already checked.
	void LG_DelaunayTriangulation::CheckIfTriangleIsChecked(LG_Triangle* pActualTriangle)
	{
		int32 DotsInside, DotsChecked;
		DotsInside = DotsChecked = 0;

		/// Iterates through the nodes cloud.
		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			/// Check if the iterating node is inside of the actual triangle.
			if (pActualTriangle->IsPointInside(&m_NodesCloud[i]))
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
		pActualTriangle->m_bIsChecked = (DotsChecked == DotsInside);
	}

	//! This function create a big triangle.
	void LG_DelaunayTriangulation::CreateBigTriangle(int32 iWidth, int32 iHeight, LG_Vector3D GridCenter)
	{
		/// X * 2 = the lenght of the triangle's arista. This only works when the grid is a square.
		float AristaSize = float(iWidth * 2);
		int32 iCountNode = 0;
		/// The offset is used to make the triangle just a notch larger, this in order to prevent that there are nodes at the arista.
		int iOffset = 50;

		/// We set the center of the grid to start off.
		LG_Node* pNodePosition1 = new LG_Node();
		LG_Node* pNodePosition2 = new LG_Node();
		LG_Node* pNodePosition3 = new LG_Node();

		pNodePosition1->m_Position = GridCenter;

		/// Substract half the height in the Y axis so that it's at the grid's base.
		pNodePosition1->m_Position.Y -= (iHeight / 2) + iOffset;
		/// Substract half of the size of the arista to the left.
		pNodePosition1->m_Position.X -= (AristaSize / 2) + iOffset;
		/// Assign the ID for the node.
		pNodePosition1->m_iID = iCountNode;
		/// Add one to the counter node.
		++iCountNode;

		/// 
		pNodePosition2->m_Position = pNodePosition1->m_Position;
		/// Add the whole size of the arista for the next node.
		///Here we add twice the offset to the arista size, to set it back in the original position it's meant to be, and to add an extra offset.
		pNodePosition2->m_Position.X += AristaSize + (iOffset * 2);
		/// Assign the ID for the node.
		pNodePosition2->m_iID = iCountNode;
		/// Add one to the counter node.
		++iCountNode;

		/// 
		pNodePosition3->m_Position = pNodePosition2->m_Position;
		pNodePosition3->m_Position.X = GridCenter.X;
		/// Get the last top node.
		pNodePosition3->m_Position.Y += AristaSize + iOffset;
		/// Assign the ID for the node.
		pNodePosition3->m_iID = iCountNode;
		/// Add one to the counter node.
		++iCountNode;


		m_pBigTriangle = new LG_Triangle();
		m_pBigTriangle->Init(pNodePosition1, pNodePosition2, pNodePosition3);

		m_pBigTriangle->m_pEdges[FIRST_EDGE]->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

		m_pBigTriangle->m_pEdges[SECOND_EDGE]->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

		m_pBigTriangle->m_pEdges[THIRD_EDGE]->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

		for (int32 i = 0; i < EDGES_PER_TRIANGLE; ++i)
		{
			m_pEdgeVector.push_back(m_pBigTriangle->m_pEdges[i]);
		}

		for (int32 i = 0; i < m_NodesCloud.size(); ++i)
		{
			m_NodesCloud[i].m_iID = iCountNode;
			++iCountNode;
		}

	}

	//! This function sets all the triangles' flags in vector triangles as false.
	void LG_DelaunayTriangulation::SetTrianglesAsFalse()
	{
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			m_pTrianglesVector[i]->m_bIsChecked = false;
		}
	}

	bool LG_DelaunayTriangulation::EliminateTriangles()
	{
		/// Erases the triangle that belongs to the legalized edge.
		for (Vector<LG_Triangle*>::iterator itt = m_pTrianglesVector.begin(); itt != m_pTrianglesVector.end(); ++itt)
		{
			for (int32 i = 0; i < NODES_PER_TRIANGLE; ++i)
			{
				if ((*itt)->CompareOneIndex(m_pBigTriangle->m_pVertices[i]))
				{
					delete *itt;
					m_pTrianglesVector.erase(itt);
					return true;
				}
			}
		}
		return false;
	}

	bool LG_DelaunayTriangulation::EliminateEdges()
	{

		/// Erases the triangle that belongs to the legalized edge.
		for (Vector<LG_Edge*>::iterator itt = m_pEdgeVector.begin(); itt != m_pEdgeVector.end(); ++itt)
		{

			if ((*itt)->CompareOneIndex(m_pBigTriangle->m_pVertices[FIRST_NODE]))
			{
				delete *itt;
				m_pEdgeVector.erase(itt);
				return true;
			}

			else if ((*itt)->CompareOneIndex(m_pBigTriangle->m_pVertices[SECOND_NODE]))
			{
				delete *itt;
				m_pEdgeVector.erase(itt);
				return true;
			}
			else if ((*itt)->CompareOneIndex(m_pBigTriangle->m_pVertices[THIRD_NODE]))
			{
				delete *itt;
				m_pEdgeVector.erase(itt);
				return true;
			}

		}
		return false;
	}

	void LG_DelaunayTriangulation::EliminateEdgesBigTriangle()
	{
		Vector<LG_Edge*>::iterator itt = m_pEdgeVector.begin();
		delete *itt;
		m_pEdgeVector.erase(itt);

		itt = m_pEdgeVector.begin();
		delete *itt;
		m_pEdgeVector.erase(itt);

		itt = m_pEdgeVector.begin();
		delete *itt;
		m_pEdgeVector.erase(itt);
	}

	LG_Triangle* LG_DelaunayTriangulation::CreateTriangle(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode)
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
		pFirstEdge->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

		pSecondEdge->Init(pFirstNode, pThirdNode);
		pSecondEdge->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

		pThirdEdge->Init(pSecondNode, pThirdNode);
		pThirdEdge->m_iID = m_iEdgesCount;
		++m_iEdgesCount;

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


		/// Creates a new triangle, and initializes it.
		pNewTriangle->Init(pFirstEdge, pSecondEdge, pThirdEdge);
		pNewTriangle->m_iID = m_iTrianglesCount;
		++m_iTrianglesCount;

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
		/// Returns the new created triangle.
		return pNewTriangle;
	}

	//! This function search 2 triangles that share the same edge
	bool LG_DelaunayTriangulation::FindTrianglesToLegalize(LG_Edge * pActualEdge, LG_Triangle** ppFirstTriangle, LG_Triangle** ppSecondTriangle)
	{
		int32 iCountTriangle = 0;
		for (int32 i = 0; i < m_pTrianglesVector.size(); ++i)
		{
			for (int32 j = 0; j < EDGES_PER_TRIANGLE; j++)
			{
				if (m_pTrianglesVector[i]->m_pEdges[j]->CompareIndex(*pActualEdge))
				{
					if (0 == iCountTriangle)
					{
						*ppFirstTriangle = m_pTrianglesVector[i];
					}

					else
					{
						*ppSecondTriangle = m_pTrianglesVector[i];
					}
					++iCountTriangle;
					break;
				}
			}
		}
		if (2 == iCountTriangle) return true;
		return false;
	}

	void LG_DelaunayTriangulation::FindNodesToCreatePolygon(LG_Edge* pActualEdge, LG_Triangle * pFirstTriangle, LG_Triangle * pSecondTriangle, LG_Node** ppFirstNode, LG_Node** ppSecondNode)
	{

		for (int32 i = 0; i < NODES_PER_TRIANGLE; ++i)
		{
			if ((pFirstTriangle->m_pVertices[i] != pActualEdge->m_pFirstNode) &&
				(pFirstTriangle->m_pVertices[i] != pActualEdge->m_pSecondNode))
			{
				*ppFirstNode = pFirstTriangle->m_pVertices[i];
			}
			else
			{
				continue;
			}
		}

		for (int32 i = 0; i < NODES_PER_TRIANGLE; ++i)
		{
			if ((pSecondTriangle->m_pVertices[i] != pActualEdge->m_pFirstNode) &&
				(pSecondTriangle->m_pVertices[i] != pActualEdge->m_pSecondNode))
			{
				*ppSecondNode = pSecondTriangle->m_pVertices[i];
			}
			else
			{
				continue;
			}
		}
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