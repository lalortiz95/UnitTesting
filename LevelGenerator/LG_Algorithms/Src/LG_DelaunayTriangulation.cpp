#include "LG_DelaunayTriangulation.h"
#include "LG_Triangle.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_DelaunayTriangulation::LG_DelaunayTriangulation()
	{
		m_pActualTriangle = nullptr;
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
		/// Create 3 new triangles.
		if (m_BigTriangle.IsPointInside(&m_NodesCloud[FIRST_NODE]))
		{
			CreateTriangles(m_BigTriangle, &m_NodesCloud[FIRST_NODE]);
		}

		/// Set the actual triangle to compare with nodes iterating.
		m_pActualTriangle = &m_TrianglesVector.front();
	}
	//! This function releases memory and clears the variables.
	void LG_DelaunayTriangulation::Destroy()
	{
		if (m_pActualTriangle != nullptr)
		{
			m_pActualTriangle->Destroy();
		}
	}

	//! This function performs the algorithm.
	void LG_DelaunayTriangulation::Run(int32 iGridWidth, int32 iGridHeight, LG_Vector3D GridCenter, Vector<LG_Isoline> NodesCloud)
	{
		/// Flag to determinate when to end the while cycle.
		bool bQuit = false;
		/// Flag to determinate if we should break the first for.
		bool bBreakFirstFor = false;
		/// Initialize the start parameters.
		Init(iGridWidth, iGridHeight, GridCenter, NodesCloud);

		/// Start the while cycle.
		while (!bQuit)
		{
			/// Reset the flags.
			bQuit = true;
			bBreakFirstFor = false;

			//TODO: esto no es necesariamente correcto, lo apropiado sería tener un
			//triangulo actual, con el que se trabaje, que se cambie cuando tenga
			//mas triangulos dentro, y cuando no tenga más puntos adentro que 
			//lo setee como checado, y busque uno que no esté para que sea el nuevo actual.

			///// Iterating the triangle vector to compare with the node's cloud.
			//for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
			//{
			/// Iterate the node's cloud.
			for (int32 j = 0; j < m_NodesCloud.size(); ++j)
			{
				/// Check if the iterating node is inside of the iterating triangle and
				/// the iterating triangle is not checked. And we also check that it doesn't compare
				/// against itself.
				if (m_pActualTriangle->IsPointInside(&m_NodesCloud[j]) &&
					!m_pActualTriangle->m_bIsChecked &&
					!CheckIfSharesPosition(*m_pActualTriangle, m_NodesCloud[j]) &&
					!m_NodesCloud[j].m_bIsInside)
				{
					/// Create 3 new triangles.
					CreateTriangles(*m_pActualTriangle, &m_NodesCloud[j]);
					//SetTriangleFlag(*m_pActualTriangle);
					/// We set as actaual tile the last inserted node.
					m_pActualTriangle = &m_TrianglesVector.front();
					/// Set the flag to break the first for.
					bBreakFirstFor = true;
					/// Break the second for.
					break;
				}
			}

			if (!bBreakFirstFor)
			{
				/// If it didn't have dots inside we set that triangle as checked.
				m_pActualTriangle->m_bIsChecked = true;
				/// Find a new actual triangle, starting from the last inserted triangle to the first one.
				for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
				{
					/// If the triangle haven't been checked.
					if (!m_TrianglesVector[i].m_bIsChecked)
					{
						/// Set the new actual tile.
						m_pActualTriangle = &m_TrianglesVector[i];
						break;
					}
				}
			}
			/// Assign the new value to this flag if it's true, finish the cycle.
			bQuit = CheckifAllNodesAreTrue();
		}

		EliminateTriangles();
		//debugging purposes
		m_TrianglesVector = m_TrianglesVector;

		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		{
			m_TrianglesVector[i].CalculateCircumcenter();
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
			Triangle.Init(ActualTriangle.m_pVertices[iNode],
				ActualTriangle.m_pVertices[FIRST_NODE],
				pNodeInside);
		}

		else
		{
			/// Initialize a new triangle with the node given.
			Triangle.Init(ActualTriangle.m_pVertices[iNode],
				ActualTriangle.m_pVertices[iNode + 1],
				pNodeInside);
		}

		Triangle.m_iID = m_iTrianglesAmount;
		++m_iTrianglesAmount;
		/// Add the new triangle in the triangles vector.
		m_TrianglesVector.insert(m_TrianglesVector.begin(), Triangle);
	}

	//! This function create a 3 triangles from one triangle and a node.
	void LG_DelaunayTriangulation::CreateTriangles(LG_Triangle ActualTriangle, LG_Node * pNodeInside)
	{
		if (m_TrianglesVector.size() > 0)
		{
			//m_TrianglesVector.erase(m_TrianglesVector.begin());
		}

		for (int32 i = 0; i < VERTEX_PER_TRIANGLE; ++i)
		{
			CreateTriangle(ActualTriangle, pNodeInside, i);
		}
		pNodeInside->m_bIsInside = true;
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

		/// Save that position as the first node of the big triangle.
		m_BigTriangle.m_pVertices.push_back(pNodePosition1);

		m_BigTriangle.m_pVertices[FIRST_NODE]->m_Position = GridCenter;

		/// Substract half the height in the Y axis so that it's at the base of que grid.
		m_BigTriangle.m_pVertices[FIRST_NODE]->m_Position.Y -= iHeight / 2;
		/// Substract half of the size of the arista to the left.
		m_BigTriangle.m_pVertices[FIRST_NODE]->m_Position.X -= AristaSize / 2;

		/// Save that position as the first node of the big triangle.
		m_BigTriangle.m_pVertices.push_back(pNodePosition2);

		m_BigTriangle.m_pVertices[SECOND_NODE]->m_Position = m_BigTriangle.m_pVertices[FIRST_NODE]->m_Position;
		/// Add the whole size of the arista for the next node.
		m_BigTriangle.m_pVertices[SECOND_NODE]->m_Position.X += AristaSize;

		/// store the final node.
		m_BigTriangle.m_pVertices.push_back(pNodePosition3);

		m_BigTriangle.m_pVertices[THIRD_NODE]->m_Position = m_BigTriangle.m_pVertices[SECOND_NODE]->m_Position;
		m_BigTriangle.m_pVertices[THIRD_NODE]->m_Position.X = GridCenter.X;
		/// Get the last top node.
		m_BigTriangle.m_pVertices[THIRD_NODE]->m_Position.Y += AristaSize;

	}

	//! This function determine when we can stop the triangulation.
	bool LG_DelaunayTriangulation::CheckifAllNodesAreTrue()
	{
		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		{
			if (!m_TrianglesVector[i].m_bIsChecked)
			{
				return false;
			}
		}
		return true;
	}

	//! This function compares the iterating node's position with any of the iterating triangle's node.
	bool LG_DelaunayTriangulation::CheckIfSharesPosition(LG_Triangle IteratingTriangle, LG_Node IteratingNode)
	{
		return ((IteratingTriangle.m_pVertices[FIRST_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[SECOND_NODE]->m_Position == IteratingNode.m_Position) ||
			(IteratingTriangle.m_pVertices[THIRD_NODE]->m_Position == IteratingNode.m_Position));
	}

	//! This function set the triangle as check when it doesn't have any node inside.
	void LG_DelaunayTriangulation::SetTriangleFlag(LG_Triangle& IteratingTriangle)
	{
		/// Iterate the node's cloud.
		for (int32 j = 0; j < m_NodesCloud.size(); ++j)
		{	/// If one of the node are inside of the triangle return.
			if (IteratingTriangle.IsPointInside(&m_NodesCloud[j]) &&
				!m_NodesCloud[j].m_bIsInside)
				return;
		}
		/// Set the triangle as checked.
		IteratingTriangle.m_bIsChecked = true;
	}

	//! This function sees if all the triangles from the vector have their flags set as false.
	bool LG_DelaunayTriangulation::AreTrianglesFalse()
	{
		for (int32 i = 0; i < m_TrianglesVector.size(); i++)
		{
			if (m_TrianglesVector[i].m_bIsChecked)
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
		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		{
			m_TrianglesVector[i].m_bIsChecked = false;
		}

		/// We iterate and change the flag of the ones being deleted.
		for (int32 i = 0; i < m_TrianglesVector.size(); ++i)
		{
			for (int32 j = 0; j < 3; ++j)
			{
				if (m_TrianglesVector[i].m_pVertices[j] == m_BigTriangle.m_pVertices[0] ||
					m_TrianglesVector[i].m_pVertices[j] == m_BigTriangle.m_pVertices[1] ||
					m_TrianglesVector[i].m_pVertices[j] == m_BigTriangle.m_pVertices[2])
				{
					m_TrianglesVector[i].m_bIsChecked = true;
					break;
				}
			}
		}

		int32 it = 0;
		while (!AreTrianglesFalse())
		{
			//eliminar el que tenga su bandera en true
			if (m_TrianglesVector[it].m_bIsChecked)
			{
				///erases the triangle with it's flag set as true.
				m_TrianglesVector.erase(m_TrianglesVector.begin() + it);
				///Initialize again the iterator.
				it = 0;
			}
			else
			{
				///Adds one to the counter.
				++it;
			}
		}
	}
}