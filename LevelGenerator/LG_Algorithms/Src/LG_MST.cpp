#include "LG_MST.h"

#include <LG_Math.h>
#include <LG_Triangle.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_MST::LG_MST()
	{
		Init();
	}

	//! Default destructor.
	LG_MST::~LG_MST()
	{
		Destroy();
	}

	//! Initializes the member variables of the class.
	void LG_MST::Init()
	{
		Destroy();
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_MST::Destroy()
	{
		m_Triangulation.clear();
		m_FinalTree.clear();
		m_OrderedEdges.clear();
	}

	//! This function is the only one you need to generate Minimum Spanning Tree algorithm.
	void LG_MST::Run(Vector<LG_Edge*> InitialNet, Vector<LG_Triangle*> Triangulation)
	{
		//TODO: verificar que se eliminen las conexiones de los nodos en los edges que no se insertan en la lista final.
		// al tener un nodo que no se va a insertar, si bIsEdgeAdded es falso, eliminar las conexiones entre los 2 nodos de ese edge.
		/// this flag states whether or not we can add an edge to the final list.
		bool bIsEdgeAdded = true;
		/// A copy of the vector to not affect the original one.
		Vector<LG_Edge*> Initial = InitialNet;

		/// We sort the edges from lower to higher value.
		Sort(Initial);

		/// Set all the edges as checked.
		for (int32 i = 0; i < m_OrderedEdges.size(); ++i)
		{
			m_OrderedEdges[i]->m_bIsChecked = false;
		}

		/// See which edges will be added to the final list based on whether or not they make a cycle.
		for (int32 i = 0; i < m_OrderedEdges.size(); ++i)
		{
			for (int32 j = 0; j < Triangulation.size(); ++j)
			{
				/// See if the triangle contains the edge that we want.
				if (Triangulation[j]->HasEdgeInside(m_OrderedEdges[i]))
				{
					/// If we are in the triangle that contains the edge, we see that the triangle doesn't have more
					/// than 2 edges as checked.
					if (Triangulation[j]->m_pEdges[FIRST_EDGE]->m_bIsChecked && Triangulation[j]->m_pEdges[SECOND_EDGE]->m_bIsChecked)
					{
						bIsEdgeAdded = false;
						Triangulation[j]->m_pEdges[THIRD_EDGE]->Legalize();
						break;
					}
					else if (Triangulation[j]->m_pEdges[SECOND_EDGE]->m_bIsChecked && Triangulation[j]->m_pEdges[THIRD_EDGE]->m_bIsChecked)
					{
						bIsEdgeAdded = false;
						Triangulation[j]->m_pEdges[FIRST_EDGE]->Legalize();
						break;
					}
					else if (Triangulation[j]->m_pEdges[FIRST_EDGE]->m_bIsChecked && Triangulation[j]->m_pEdges[THIRD_EDGE]->m_bIsChecked)
					{
						bIsEdgeAdded = false;
						Triangulation[j]->m_pEdges[SECOND_EDGE]->Legalize();
						break;

					}
				}
			}

			/// Makes sure that the edge didn't make a cycle.
			if (bIsEdgeAdded)
			{
				m_FinalTree.push_back(m_OrderedEdges[i]);
			}
			/// Mark the edge as checked.
			m_OrderedEdges[i]->m_bIsChecked = true;
			/// Reeset the flag for the next iteration.
			bIsEdgeAdded = true;
		}
	}

	//! Sorts the initial vector of edges, from lower to higher cost.
	void LG_MST::Sort(Vector<LG_Edge*> InitialNet)
	{
		/// The edge with the smallest magnitude.
		Vector<LG_Edge*>::iterator temp;
		/// Where we store the minimum distance of the edge vectos.
		float fSmallestMag = LG_Math::INFINITE_NUM;
		/// The initial size of the net.
		int32 iInitialSize = (int32)InitialNet.size();
		/// 

		while (m_OrderedEdges.size() != iInitialSize)
		{
			fSmallestMag = LG_Math::INFINITE_NUM;
			/// 
			for (Vector<LG_Edge*>::iterator itt = InitialNet.begin(); itt != InitialNet.end(); ++itt)
			{
				///
				if ((*itt)->m_fDistance < fSmallestMag)
				{
					/// 
					fSmallestMag = (*itt)->m_fDistance;
					///
					temp = itt;
				}
			}
			m_OrderedEdges.push_back((*temp));
			InitialNet.erase(temp);
		}

		m_OrderedEdges = m_OrderedEdges;
	}
}